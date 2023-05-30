#include "catch.hpp"
#include "../code/carObj.hpp"

TEST_CASE("Create car") {
    CarObj car;
    REQUIRE(car.getSpeed() == 0);
    REQUIRE(car.getAngle() == 0);
    REQUIRE(car.getPosX() == 0);
    REQUIRE(car.getPosY() == 0);
    REQUIRE(car.getPoints() == 0);
    REQUIRE(car.getLap() == 0);
    REQUIRE(car.getLapTime() == 0);
}