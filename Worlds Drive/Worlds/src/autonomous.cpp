#include "main.h"
#include "okapi/api.hpp"
//#include "functions.h"
//#include "Autos.h"
//#include "AutoVars.cpp"

using namespace okapi;
using namespace pros;
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

 void RedBack(){
   pros::Motor Puncher(6);
   pros::Motor Angler(15);
   pros::Motor Intake(16);
 	pros::Motor Lift(5);
  pros::ADIPotentiometer AnglePot(1);

  double CTR = 16.38; //(convert to raw) multiply the degrees by this number to get the raw Potentiometer units
  AnglePot.calibrate();

   auto myChassis = ChassisControllerFactory::create(
     {1, 10}, // Left motors
     {-20, -11},   // Right motors
     AbstractMotor::gearset::red, // Torque gearset
     {12_in, 18.5_in} // 4 inch wheels, 12.5 inch wheelbase width
   );

   auto profileController = AsyncControllerFactory::motionProfile(

     1.0,  // Maximum linear velocity of the Chassis in m/s
     2.0,  // Maximum linear acceleration of the Chassis in m/s/s
     10.0, // Maximum linear jerk of the Chassis in m/s/s/s
     myChassis // Chassis Controller
   );

  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.66519143_ft, 0_ft, 0_deg}}, "firstCap");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.523598776_ft, 0_ft, 0_deg}}, "firstCapBack");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0_ft, 2_ft, 0_deg}}, "secondCapAlign");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.523598776_ft, 0_ft, 0_deg}}, "secondCap");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 0_deg}}, "shootAdjust");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.523598776_ft, 0_ft, 0_deg}}, "secondCapBack");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0_ft, 5_ft, 0_deg}}, "climb");

    profileController.setTarget("firstCap");
    Lift.move_absolute(-400, 200);
    Intake.move_velocity(-200);
    Puncher.move_absolute(600, 200);
    profileController.waitUntilSettled();

    profileController.setTarget("firstCapBack",true);
    Intake.move_velocity(0);
    profileController.waitUntilSettled();

    myChassis.turnAngle(-71.041404_deg);
    profileController.waitUntilSettled();

    //Angler.move_absolute(130, 200);  //59.394201992646
    // while (AnglePot.get_value_calibrated() < 59.394201992646*CTR){
    //   Angler.move_velocity(50);
    // }
    // Angler.move_velocity(0);
    Angler.move_absolute(20, 200);
    Puncher.move_relative(2000, 200);
    profileController.waitUntilSettled();

    // while (AnglePot.get_value_calibrated() < 79.394201992646*CTR){
    //   Angler.move_velocity(50);
    // }
    // Angler.move_velocity(0);
    Angler.move_absolute(-10, 200);
    Puncher.move_relative(2000, 200);
    profileController.waitUntilSettled();

    myChassis.turnAngle(71.041404_deg);
    profileController.waitUntilSettled();

    profileController.setTarget("secondCapAlign");
    profileController.waitUntilSettled();

    profileController.setTarget("secondCap");
    profileController.waitUntilSettled();

    Lift.move_absolute(-400, 200);
    Intake.move_velocity(-200);
    profileController.waitUntilSettled();

    profileController.setTarget("secondCapBack",true);
    profileController.waitUntilSettled();

    myChassis.turnAngle(-51.041404_deg);
    Intake.move_velocity(0);
    profileController.waitUntilSettled();

    Puncher.move_relative(2000, 200);
    profileController.waitUntilSettled();

    Angler.move_absolute(-5, 200);
    Puncher.move_relative(2000, 200);
    profileController.waitUntilSettled();

    myChassis.turnAngle(51.041404_deg);
    profileController.waitUntilSettled();

    myChassis.turnAngle(90_deg);
    profileController.waitUntilSettled();

    profileController.setTarget("secondCapBack",true);
    profileController.waitUntilSettled();
 }


void autonomous() {
  RedBack();
  // if(AutoCount == 1){
  //   /** Call Auto Function*/
  // }
  //
  // if(AutoCount == 2){
  //   /** Call Auto Function*/
  // }
  //
  // if(AutoCount == 3){
  //   /** Call Auto Function*/
  // }
  //
  // if(AutoCount == 3){
  //   /** Call Auto Function*/
  // }
  //
  // if(AutoCount == 5){
  //   /** Call Auto Function*/
  // }
}


















/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */




 //  pros::Motor LeftF(10);
 //  pros::Motor LeftB(1);
 //  pros::Motor RightF(20, true);
 //  pros::Motor RightB(11, true);
 //  pros::Motor Intake(16);
 //  pros::Motor Puncher(18);
 //  pros::Motor Angler(17);
 // 	pros::Motor Lift(21);
 // 	pros::ADIAnalogIn AnglePot (2);
 // 	pros::ADIAnalogIn IntakeLine_Top1 (3);
 //  pros::ADIGyro Gyro(1);
 //
 //  RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
 //  RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
 //  LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
 //  LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
 //  Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
 //  Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
 //  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
 // 	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);
 //  Puncher.set_encoder_units(MOTOR_ENCODER_COUNTS);
 //  LeftF.set_encoder_units(MOTOR_ENCODER_ROTATIONS);

  //auto Gyro = okapi::AsyncControllerFactory::posPID({-1, 2}, ADIGyro('A'), 0.001, 0.0, 0.0001);

  // AnglePot.calibrate();
  //
  // while(LeftF.get_position() < 3.5){// move towards cap
  //   LeftF.move_velocity(200);
  //   LeftB.move_velocity(200);
  //   RightF.move_velocity(200);
  //   RightB.move_velocity(200);
  //   Intake.move_velocity(200);
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);
  //
  // pros::delay(300);
  //
  // Intake.move_velocity(0);
  //
  // while(LeftF.get_position() > 0.5){// move towards cap
  //   LeftF.move_velocity(-200);
  //   LeftB.move_velocity(-200);
  //   RightF.move_velocity(-200);
  //   RightB.move_velocity(-200);
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);
  //
  // while(Gyro.get_value() < 288.958596){
  //   LeftF.move_velocity(-200);
  //   LeftB.move_velocity(-200);
  //   RightF.move_velocity(200);
  //   RightB.move_velocity(200);
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);
