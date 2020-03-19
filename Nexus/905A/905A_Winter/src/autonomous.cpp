#include "main.h"
#include "Motors.hpp"
#include "Sensors.hpp"
#include "Variables.hpp"
#include "Functions.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void redBack8Cube(){
  auto chassis = ChassisControllerBuilder()
    .withMotors(-15,-14, 20,9) // left motor is 1, right motor is 2 (reversed)
    .withGains(
        {0.35, 0, 0}, // Forward Backwards PID
        {0, 0, 0}, // Turn PID
        {0, 0, 0}  // Heading Corrections PID
    )
    // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
    .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 12.5_in}, imev5BlueTPR})
    .withSensors(
        ADIEncoder{'A', 'B'}, // left encoder in ADI ports A & B
        ADIEncoder{'C', 'D', true}  // right encoder in ADI ports C & D (reversed)
    )
    // specify the tracking wheels diameter (2.75 in), Distance between trackers(7 in), and TPR (360)
    .withOdometry({{2.75_in, 7_in}, quadEncoderTPR})
    .buildOdometry(); // build an odometry chassis
    
    auto armController = AsyncPosControllerBuilder()
      .withMotor(-11)
      .withGains({1.0, 0.001, 0.1})
      .build();

    auto tiltController = AsyncPosControllerBuilder()
      .withMotor(-12)
      .withGains({1.0, 0.001, 0.1})
      .build();

    intakeControl(200);

    chassis->setState({0_in, 0_in, 0_deg});

    chassis->driveToPoint({3_ft, 0_ft});

    chassis->waitUntilSettled();

    armController->setTarget(400);

    armController->waitUntilSettled();

    chassis->driveToPoint({4_ft, 0_ft});

    armController->setTarget(-400);

    armController->waitUntilSettled();

    chassis->driveToPoint({1_ft, 2_ft});

    chassis->driveToPoint({6_ft, 0_ft});

    chassis->driveToPoint({0_ft, 6_ft});
    tiltController->setTarget(900);
    chassis->waitUntilSettled();

    intakeControl(-200);
    chassis->moveDistance(-2_ft);

    tiltController->setTarget(-900);

}

void autonomous() {
  redBack8Cube();

}
