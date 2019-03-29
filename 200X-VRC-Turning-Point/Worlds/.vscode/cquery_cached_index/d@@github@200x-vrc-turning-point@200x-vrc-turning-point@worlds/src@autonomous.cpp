#include "main.h"
#include "okapi/api.hpp"
#include "functions.h"
#include "Autos.h"
#include "AutoVars.cpp"

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


void autonomous() {
  pros::Motor Puncher(6);
  pros::Motor Angler(15);
  pros::Motor Intake(16);
	pros::Motor Lift(5);

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

  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "firstCap");
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{5_ft, 0_ft, 0_deg}}, "firstCapBack");
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 0_deg}}, "firstCapadjust");
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 0_deg}}, "shootAdjust");

  profileController.setTarget("firstCap");
  Lift.move_absolute(-400, 200);
  Intake.move_velocity(-200);
  Puncher.move_absolute(600, 200);

  profileController.waitUntilSettled();
  profileController.setTarget("firstCapBack",true);
  Intake.move_velocity(0);
  profileController.waitUntilSettled();
  profileController.setTarget("firstCapadjust");
  profileController.waitUntilSettled();
  myChassis.turnAngle(105.87346536453_deg);
  profileController.setTarget("shootAdjust",true);
  profileController.waitUntilSettled();
  while(Puncher.get_position() < 2000){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);
  Puncher.move_velocity(0);
  Intake.move_velocity(-200);
  Angler.move_absolute(160, 200);
  pros::delay(500);
  Puncher.tare_position();
  while(Puncher.get_position() < 2000){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);


  // Puncher.move_absolute(1200, 200);



}
