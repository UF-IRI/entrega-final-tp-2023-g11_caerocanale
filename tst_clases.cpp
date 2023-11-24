#include <catch2/catch.hpp>

TEST_CASE("My first test with Catch2", "[fancy]")
{int a =1;
    REQUIRE(a == 1);
}
