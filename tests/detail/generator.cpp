#include <doctest/doctest.h>

#include <unscribe/detail/generator.hpp>

#include <concepts>
#include <ranges>

namespace {
///////////////////////////////////////////////////////////////////////////////

using namespace unscribe::detail;

static_assert(std::ranges::input_range<generator<int>>);

TEST_CASE("detail::generator") {
    SUBCASE("iota") {
        auto iota = [](int count) -> generator<int> {
            for (int i = 0; i < count; ++i) {
                co_yield i;
            }
        };

        int j = 0;
        for (auto i : iota(10)) {
            CHECK(i == j);
            ++j;
        }
    }

    SUBCASE("throw") {
        auto f = []() -> generator<int> {
            co_yield 0;
            co_yield 1;
            co_yield 2;
            throw std::runtime_error("oops");
            co_yield 3;
            co_yield 4;
            co_yield 5;
        };

        int j = 0;
        auto g = [&]{
            for (auto i : f()) {
                CHECK(i == j);
                ++j;
            }
        };
        CHECK_THROWS_WITH_AS(g(), "oops", std::runtime_error);
        CHECK(j == 3);
    }
}

///////////////////////////////////////////////////////////////////////////////
}
