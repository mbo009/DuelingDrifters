#include "catch2.hpp"
#include "../code/carObj.hpp"

TEST_CASE("CarObj tests")
{
    // Test case for getX() and getY()
    SECTION("Getters")
    {
        CarObj car(0.0f, 0.0f);
        REQUIRE(car.getX() == 0.0f);
        REQUIRE(car.getY() == 0.0f);
    }

    // Test case for setX() and setY()
    SECTION("Setters")
    {
        CarObj car(0.0f, 0.0f);
        car.setX(5.0f);
        car.setY(-2.0f);
        REQUIRE(car.getX() == 5.0f);
        REQUIRE(car.getY() == -2.0f);
    }

    // Test case for getPoint() and setPoint()
    SECTION("Points")
    {
        CarObj car(0.0f, 0.0f);
        REQUIRE(car.getPoint() == 0);

        car.setPoint(10);
        REQUIRE(car.getPoint() == 10);

        car.setPoint(-5);
        REQUIRE(car.getPoint() == 5);
    }

    // Test case for resetVelocity()
    SECTION("Reset Velocity")
    {
        CarObj car(0.0f, 0.0f);
        car.setX(5.0f);
        car.setY(-2.0f);
        car.resetVelocity();
        REQUIRE(car.getXVelocity() == 0.0f);
        REQUIRE(car.getYVelocity() == 0.0f);
    }

    // Test case for resetPosition()
    SECTION("Reset Position")
    {
        CarObj car(0.0f, 0.0f);
        car.setX(5.0f);
        car.setY(-2.0f);
        car.resetPosition();
        REQUIRE(car.getX() == 0.0f);
        REQUIRE(car.getY() == 0.0f);
    }

    // Test case for reset()
    SECTION("Reset")
    {
        CarObj car(0.0f, 0.0f);
        car.setX(5.0f);
        car.setY(-2.0f);
        car.setPoint(10);
        car.reset();
        REQUIRE(car.getX() == 0.0f);
        REQUIRE(car.getY() == 0.0f);
        REQUIRE(car.getXVelocity() == 0.0f);
        REQUIRE(car.getYVelocity() == 0.0f);
        REQUIRE(car.getPoint() == 10);
    }
}

TEST_CASE("Car movement") {
    SECTION("Move car") {
        CarObj car(0.0f, 0.0f);
        car.setAcceleration(1.0f);

        car.reset();
        car.move(0);
        REQUIRE(car.getX() == 0.0f);
        REQUIRE(car.getY() == -1.0f);

        car.reset();
        car.move(1);
        REQUIRE(car.getX() == 1.0f);
        REQUIRE(car.getY() == -1.0f);

        car.reset();
        car.move(2);
        REQUIRE(car.getX() == 1.0f);
        REQUIRE(car.getY() == 0.0f);

        car.reset();
        car.move(3);
        REQUIRE(car.getX() == 1.0f);
        REQUIRE(car.getY() == 1.0f);

        car.reset();
        car.move(4);
        REQUIRE(car.getX() == 0.0f);
        REQUIRE(car.getY() == 1.0f);

        car.reset();
        car.move(5);
        REQUIRE(car.getX() == -1.0f);
        REQUIRE(car.getY() == 1.0f);
    
        car.reset();
        car.move(6);
        REQUIRE(car.getX() == -1.0f);
        REQUIRE(car.getY() == 0.0f);

        car.reset();
        car.move(7);
        REQUIRE(car.getX() == -1.0f);
        REQUIRE(car.getY() == -1.0f);

        car.reset();
        car.move(8);
        REQUIRE(car.getX() == 0.0f);
        REQUIRE(car.getY() == 0.0f);
    }
    SECTION("Car push") {
        CarObj car(0.0f, 0.0f);
        car.push(1.0f, 1.0f);
        REQUIRE(car.getXVelocity() == -0.5f);
        REQUIRE(car.getYVelocity() == -0.5f);

    }
    SECTION("Car get pushed") {
        CarObj car(0.0f, 0.0f);
        car.getPushed(1.0f, 1.0f);
        REQUIRE(car.getXVelocity() == 2.0f);
        REQUIRE(car.getYVelocity() == 2.0f);
    }
    
}
