#include "main.h"
// #include "test/tests/impl/allImplTests.hpp"

using namespace okapi;

std::shared_ptr<OdomChassisController> drive;

void opcontrol() {
  pros::delay(100);

  drive = ChassisControllerBuilder()
            .withMotors(-1, 2)
            .withDimensions(AbstractMotor::gearset::green, {{4_in, 11_in}, imev5GreenTPR})
            .withMaxVelocity(60)
            .withOdometry(StateMode::FRAME_TRANSFORMATION)
            .buildOdometry();

  // drive->driveToPoint({6_in, 2_in});
  // drive->driveToPoint({6_in, 6_in});
  // drive->driveToPoint({0_in, 0_in}, true);
  // drive->turnToPoint({6_in, 2_in});
  // drive->turnToAngle(90_deg);
  // drive->moveDistance(6_in);
  // drive->turnAngle(90_deg);
  // drive->moveDistance(6_in);

  while (true) {
    pros::delay(50);
  }
}

void initialize() {
}

void disabled() {
}

void competition_initialize() {
}

void autonomous() {
}
