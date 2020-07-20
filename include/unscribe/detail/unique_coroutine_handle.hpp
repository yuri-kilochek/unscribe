#ifndef UNSCRIBE_DETAIL_INCLUDE_DETAIL_UNIQUE_COROUTINE_HANDLE_HPP
#define UNSCRIBE_DETAIL_INCLUDE_DETAIL_UNIQUE_COROUTINE_HANDLE_HPP

#include <coroutine>
#include <utility>
#include <compare>

#include <unscribe/detail/version_namespace.hpp>

namespace unscribe::inline UNSCRIBE_DETAIL_VERSION_NAMESPACE::detail {
///////////////////////////////////////////////////////////////////////////////

template <typename Promise>
struct unique_coroutine_handle {
    using raw_type = std::coroutine_handle<Promise>;

    explicit
    unique_coroutine_handle(std::coroutine_handle<Promise> raw)
    noexcept
    : raw_(std::move(raw))
    {}

    explicit
    unique_coroutine_handle(Promise& promise)
    : unique_coroutine_handle(raw_type::from_promise(promise))
    {}

    unique_coroutine_handle(decltype(nullptr) = nullptr)
    noexcept
    : raw_(nullptr)
    {}

    unique_coroutine_handle(unique_coroutine_handle&& other)
    noexcept
    : unique_coroutine_handle(other.release())
    {}

    friend
    void swap(unique_coroutine_handle& a, unique_coroutine_handle& b)
    noexcept
    {
        using std::swap;
        swap(a.raw_, b.raw_);
    }

    unique_coroutine_handle& operator=(unique_coroutine_handle other)
    noexcept
    {
        swap(*this, other);
        return *this;
    }

    ~unique_coroutine_handle() {
        if (raw_) {
            raw_.destroy();
        }
    }

    void reset(std::coroutine_handle<Promise> raw)
    noexcept
    { *this = unique_coroutine_handle(std::move(raw)); }

    void reset(Promise& promise)
    noexcept
    { *this = unique_coroutine_handle(promise); }

    void reset(decltype(nullptr) = nullptr)
    noexcept
    { *this = nullptr; }

    raw_type release()
    noexcept
    { return std::exchange(raw_, nullptr); }

    raw_type get() const
    noexcept
    { return raw_; }

    void resume() {
        raw_.resume();
    }

    explicit
    operator bool() const
    noexcept
    { return !!raw_; }

    bool done() const {
        return raw_.done();
    }

private:
    raw_type raw_;
};

template <typename Promise>
std::strong_ordering operator<=>(unique_coroutine_handle<Promise> const& a,
                                 unique_coroutine_handle<Promise> const& b)
{ return a.get() <=> b.get(); }

///////////////////////////////////////////////////////////////////////////////
}

#endif
