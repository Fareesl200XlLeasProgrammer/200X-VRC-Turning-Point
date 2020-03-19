#include "main.h"
#include "Motors.hpp"
#include "Sensors.hpp"
#include "Variables.hpp"
#include "Functions.hpp"
#include "okapi/api.hpp"

using namespace okapi;
//
// auto myChassis = ChassisControllerFactory::create(
//   {-14, -15}, // Left motors
//   {20, 9},   // Right motors
//   AbstractMotor::gearset::blue, // Torque gearset
//   {3.25_in, 14.5_in} // 3.25 inch wheels, 12.5 inch wheelbase width
// );
//
// auto armController = AsyncControllerFactory::posPID(-11, 0.001, 0.0, 0.0001);
// auto tiltController = AsyncControllerFactory::posPID(-12, 0.001, 0.0, 0.0001);



// auto myChassis = ChassisControllerFactory::create(
//   {-14, -15}, {20, 9},
//   ADIEncoder('A', 'B', true), ADIEncoder('C', 'D'),
//
  // IterativePosPIDController::Gains{0.001, 0, 0.0001},
  // IterativePosPIDController::Gains{0.001, 0, 0.0001},
  // IterativePosPIDController::Gains{0.001, 0, 0.0001},
//
//   AbstractMotor::gearset::blue,
//   {3.25_in, 14.5_in}
// );

void red7cube(){
  // myChassis.setMaxVelocity(160);
  // intakeControl(200);
  //
  // myChassis.moveDistance(6_ft);//Intake two cubes
  //
  // myChassis.turnAngle(37_deg);
  // myChassis.setMaxVelocity(300);
  // myChassis.moveDistance(-6_ft);
  // myChassis.setMaxVelocity(160);
  // myChassis.turnAngle(-36_deg);
  // myChassis.moveDistance(3.3_ft);
  // myChassis.turnAngle(135_deg);
  // myChassis.waitUntilSettled();
  // myChassis.moveDistanceAsync(6_ft);
  // tiltController.setTarget(2000);
  // myChassis.waitUntilSettled();
  // intakeControl(-150);
  // pros::delay(200);
  // intakeControl(0);
  // myChassis.moveDistanceAsync(-4_ft);
  // intakeControl(-200);
  // tiltController.setTarget(-2000);
  //
  //
}
//
// void red8CubePilons(){
//   tilt.set_brake_mode(MOTOR_BRAKE_HOLD);
//   myChassis.setMaxVelocity(160); //maxVelocity of the chassis
//   intakeControl(200);
//
//   myChassis.moveDistanceAsync(3.2_ft);//Intake two cubes
//   myChassis.waitUntilSettled();
//   myChassis.stop();
//
//   armController.setTarget(700);
//   tiltController.setTarget(500);
//   myChassis.setMaxVelocity(60); //maxVelocity of the chassis
//   myChassis.waitUntilSettled();
//   myChassis.moveDistance(14_in);
//   armController.setTarget(-700);
//   tiltController.setTarget(-500);
//   pros::delay(500);
//   myChassis.setMaxVelocity(300); //maxVelocity of the chassis
//   myChassis.turnAngle(-40_deg);
//   myChassis.moveDistance(-5.5_ft);
//   myChassis.turnAngle(40_deg);
//   myChassis.setMaxVelocity(160); //maxVelocity of the chassis
//
//   myChassis.moveDistance(7_ft);
//   myChassis.turnAngle(175_deg);
//   myChassis.setMaxVelocity(300);
//   myChassis.moveDistanceAsync(7_ft);
//   intakeControl(-30);
//   tiltController.setTarget(3000);
//   myChassis.waitUntilSettled();
//   intakeControl(-200);
//   myChassis.moveDistance(-2_ft);
//
// }
//
//
//
// void red8Cube(){
//   myChassis.setMaxVelocity(350);
//
//   myChassis.moveDistance(5_ft);
//
//   myChassis.turnAngle(40_deg);
//
//   myChassis.moveDistance(-5_ft);
//
//
//   myChassis.turnAngle(-40_deg);
//   myChassis.moveDistance(5_ft);
//   myChassis.waitUntilSettled();
//
//   myChassis.setMaxVelocity(200);
//   myChassis.turnAngle(152_deg);
//   myChassis.setMaxVelocity(300);
//
//   myChassis.moveDistanceAsync(6.5_ft);
//   tilt.move_absolute(3500, 120);
//   myChassis.waitUntilSettled();
//   myChassis.moveDistanceAsync(-2_ft);
//   tilt.move_absolute(0,200);
// }
//
// void blue8Cube(){
//   myChassis.setMaxVelocity(350);
//
//   myChassis.moveDistance(5_ft);
//
//   myChassis.turnAngle(-30_deg);
//
//   myChassis.moveDistance(-5_ft);
//
//   myChassis.turnAngle(30_deg);
//   myChassis.moveDistance(5_ft);
//   myChassis.waitUntilSettled();
//
//   myChassis.turnAngle(-145_deg);
//   myChassis.moveDistance(7_ft);
// }

void autonomous() {
    // red7cube();

}
