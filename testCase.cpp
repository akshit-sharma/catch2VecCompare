#include <catch2/catch.hpp>

#include <string>
#include <vector>

TEST_CASE("Some Scenario") {
  std::vector<float> tActual = {-0.15586f, -0.00923f, 0.2877f, -0.10718f};
  std::vector<float> tExpected = {-0.155f, -0.009f, 0.288f, -0.107f};
  SECTION("Approx") {
    REQUIRE_THAT(tActual, Catch::Matchers::Approx(tExpected));
  }
  SECTION("Epsilon") {
    REQUIRE_THAT(tActual, Catch::Matchers::Approx(tExpected).epsilon(0.01));
  }
  SECTION("Reverse Approx") {
    REQUIRE_THAT(tExpected, Catch::Matchers::Approx(tActual));
  }
  SECTION("Reverse Epsilon") {
    REQUIRE_THAT(tExpected, Catch::Matchers::Approx(tActual).epsilon(0.01));
  }
}
