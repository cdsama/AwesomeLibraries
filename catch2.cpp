#define CATCH_CONFIG_MAIN
#include <catch.hpp>
using namespace Catch::literals;
using Catch::Matchers::Contains;
using Catch::Matchers::EndsWith;
using Catch::Matchers::Equals;
using Catch::Matchers::Matches;
using Catch::Matchers::Predicate;
using Catch::Matchers::StartsWith;
using Catch::Matchers::VectorContains;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinULP;

TEST_CASE("Assertion Macros Natural Expressions")
{
    CHECK(true);
    REQUIRE(true);
    CHECK_FALSE(false);
    REQUIRE_FALSE(false);
}

TEST_CASE("Floating point comparisons")
{
    auto a = 1.2 + 2.1;
    REQUIRE(a == Approx(3.3));
    REQUIRE(a == 3.3_a);
    SECTION("epsilon")
    {
        Approx target = Approx(100).epsilon(0.01);
        REQUIRE(100.0 == target);
        REQUIRE(200.0 != target);
        REQUIRE(100.5 == target);
    }
    SECTION("margin")
    {
        Approx target = Approx(100).margin(5);
        REQUIRE(100.0 == target);
        REQUIRE(200.0 != target);
        REQUIRE(104.0 == target);
    }
}

TEST_CASE("Matcher expressions")
{
    SECTION("string")
    {
        std::string str = "http://localhost:8080/index.html";
        REQUIRE_THAT(str, Equals("http://localhost:8080/index.html"));
        REQUIRE_THAT(str, Contains("localhost"));
        REQUIRE_THAT(str, StartsWith("http"));
        REQUIRE_THAT(str, EndsWith("html"));
        REQUIRE_THAT(str, StartsWith("http") && (EndsWith("htm") || EndsWith("html")));
        REQUIRE_THAT(str, Matches("http.*\\.html"));
    }
    SECTION("vector")
    {
        std::vector<int> vec = {1, 2, 3, 4};
        REQUIRE_THAT(vec, Contains(std::vector<int>{2, 3}));
        REQUIRE_THAT(vec, VectorContains(2));
        REQUIRE_THAT(vec, Equals(std::vector<int>{1, 2, 3, 4}));
    }
    SECTION("Floating point")
    {
        REQUIRE_THAT(3.14159265358979323846, WithinULP(3.1415926535897936, 1));
        REQUIRE_THAT(100.5, WithinAbs(100, 1));
    }
    SECTION("Generic matchers")
    {
        REQUIRE_THAT("Hello olleH", Predicate<std::string>([](std::string const &str) -> bool { return str.front() == str.back(); },
                                                           "First and last character should be equal"));
        REQUIRE_THAT(123, Predicate<int>([](int i) { return i - 100 == 23; }));
    }
}

TEST_CASE("Exceptions")
{
    REQUIRE_NOTHROW([]() { return 1 + 1; }());
    REQUIRE_THROWS([]() { throw std::string("str"); }());
    REQUIRE_THROWS_AS([]() { throw 1; }(), int);
    REQUIRE_THROWS_AS([]() { throw std::string("str"); }(), std::string);
    REQUIRE_THROWS_WITH([]() { throw std::string("str"); }(), "str");
    REQUIRE_THROWS_WITH([]() { throw std::string("str"); }(), Contains("t"));
    REQUIRE_THROWS_WITH([]() { throw std::string("str"); }(), Contains("t") && StartsWith("s") && EndsWith("r"));
    REQUIRE_THROWS_WITH([]() { throw std::string("str"); }(), Equals("string") || Equals("str"));
    REQUIRE_THROWS_MATCHES([]() { throw 1; }(), int, Predicate<int>([](int i) { return i == 1; }));
}

TEST_CASE("Logging macros")
{
    INFO("Test case start");
    for (int i = 0; i < 2; ++i)
    {
        INFO("The number is " << i);
        CHECK(i == i);
    }
}

TEST_CASE("Quickly capture a variable value")
{
    int THE_ANSWER_TO_EVERYTHING = 42;
    CAPTURE(THE_ANSWER_TO_EVERYTHING);
    SUCCEED();
}

TEST_CASE("Streaming macros")
{
    WARN("WARN expression");
    FAIL_CHECK("FAIL_CHECK expression");
    FAIL("FAIL expression");
    INFO("Will not show because last line aborted the check.");
}
