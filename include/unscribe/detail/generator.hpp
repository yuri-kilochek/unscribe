#ifndef UNSCRIBE_DETAIL_INCLUDE_DETAIL_GENERATOR_HPP
#define UNSCRIBE_DETAIL_INCLUDE_DETAIL_GENERATOR_HPP

#include <cstddef>
#include <coroutine>
#include <concepts>
#include <iterator>
#include <optional>
#include <utility>

#include <unscribe/detail/version_namespace.hpp>
#include <unscribe/detail/unique_coroutine_handle.hpp>
#include <unscribe/detail/overload.hpp>

namespace unscribe::inline UNSCRIBE_DETAIL_VERSION_NAMESPACE::detail {
///////////////////////////////////////////////////////////////////////////////

template <typename Value>
struct [[nodiscard]] generator
{
    struct promise_type {
        std::optional<Value> value;

        auto get_return_object() {
            return generator(handle_type(*this));
        }

        auto initial_suspend() {
            return std::suspend_always();
        }

        template <typename Arg>
        requires std::constructible_from<Value, Arg>
              && std::assignable_from<Value&, Arg>
        auto yield_value(Arg&& arg) {
            value = std::forward<Arg>(arg);
            return std::suspend_always();
        }

        void return_void() {
            ;
        }

        void unhandled_exception() {
            throw;
        }

        auto final_suspend() {
            return std::suspend_always();
        }
    };

    struct iterator {
        using iterator_caegory = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Value;

        iterator() = default;

        bool operator==(std::default_sentinel_t) const {
            return !handle_ || handle_.done();
        }

        friend
        bool operator==(std::default_sentinel_t, iterator const& it) {
            return it == std::default_sentinel;
        }

        Value& operator*() const {
            auto& promise = handle_.promise();
            return *promise.value;
        }

        Value* operator->() const {
            return std::addressof(**this);
        }

        iterator& operator++() {
            handle_.resume();
            return *this;
        }

        void operator++(int) {
            ++*this;
        }

    private:
        friend generator;

        using handle_type = std::coroutine_handle<promise_type>;

        handle_type handle_;

        explicit
        iterator(handle_type handle)
        : handle_(std::move(handle))
        {}
    };

    generator() = default;

    auto begin() {
        handle_.resume();
        return iterator(handle_.get());
    }

    auto end() {
        return std::default_sentinel;
    }

private:
    using handle_type = unique_coroutine_handle<promise_type>;

    handle_type handle_;

    explicit
    generator(handle_type&& handle)
    : handle_(std::move(handle))
    {}
};

///////////////////////////////////////////////////////////////////////////////
}

#endif
