#include "main.h"
#include "okapi/api.hpp"
#include "functions.h"
#include "Autos.h"
#include "AutoVars.cpp"
#include "motorDefs.h"

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
 // void gyroTurn(double target){
 //   pros::Motor Intake(16);
 // 	pros::Motor Lift(5);
 // 	pros::ADIAnalogIn IntakeLine_Top1 (3);
 //   pros::ADIGyro gyro (4);
 //
 //   pros::Motor LeftF(10);
 //   pros::Motor LeftB(1);
 //   pros::Motor RightF(20, true);
 //   pros::Motor RightB(11, true);
 //
 //   // double target = 900;
 //   double kP = 0.3;
 //   double kI = 0.0000003;
 //   double kD = 1.3;
 //   double error;
 //   double totalError;
 //   double lastError;
 //   double pwr;
 //   gyro.reset();
 //
 //     double current = gyro.get_value();
 //     error = target - current;
 //     double P = error * kP;
 //     totalError += error;
 //     lastError = error;
 //
 //     double I = kI * totalError;
 //     double D = kD * (error - lastError);
 //     pwr = P+I+D;
 //
 //     if(error == 0){
 //       I = 0;
 //     }
 //
 //       LeftF.move_velocity(pwr);
 //       LeftB.move_velocity(pwr);
 //       RightF.move_velocity(-pwr);
 //       RightB.move_velocity(-pwr);
 // }


void autonomous() {


  auto myChassis = ChassisControllerFactory::create(
    {1, 10}, // Left motors
    {-20, -11},   // Right motorszz
    AbstractMotor::gearset::red, // Torque gearset
    {12_in, 18.5_in} // 4 inch wheels, 12.5 inch wheelbase width
  );

  auto profileController = AsyncControllerFactory::motionProfile(

    1.0,  // Maximum linear velocity of the Chassis in m/s
    2.0,  // Maximum linear acceleration of the Chassis in m/s/s
    10.0, // Maximum linear jerk of the Chassis in m/s/s/s
    myChassis // Chassis Controller
  );
  if(AutoCount == 1){
    /** Call Auto Function*/
  }

  if(AutoCount == 2){
    /** Call Auto Function*/
  }

  if(AutoCount == 3){
    /** Call Auto Function*/
  }

  if(AutoCount == 3){
    /** Call Auto Function*/
  }

  if(AutoCount == 5){
    /** Call Auto Function*/
  }

  // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "firstCap");
  // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "firstCap2");
  //
  // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{5_ft, 0_ft, 0_deg}}, "firstCapBack");
  // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 0_deg}}, "firstCapadjust");
  // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1.4_ft, 0_ft, 0_deg}}, "shootAdjust");
  //
  // profileController.setTarget("firstCap");
  // Lift.move_absolute(-400, 200);
  // Intake.move_velocity(-200);
  // Puncher.move_absolute(600, 200);
  //
  // profileController.waitUntilSettled();
  // profileController.setTarget("firstCapBack",true);
  // Intake.move_velocity(0);
  // profileController.waitUntilSettled();
  // profileController.setTarget("firstCapadjust");
  // profileController.waitUntilSettled();
  // while(GyroAuto.get_value() < 700){
  //   LeftF.move_velocity(200);
  //   LeftB.move_velocity(200);
  //   RightF.move_velocity(-200);
  //   RightB.move_velocity(-200);
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);  profileController.setTarget("shootAdjust",true);
  // profileController.waitUntilSettled();
  //
  // Angler.move_absolute(100, 200);
  // while(Puncher.get_position() < 2000){
  //   Puncher.move_velocity(200);
  // }
  // Puncher.move_velocity(0);
  // Puncher.move_velocity(0);
  // Intake.move_velocity(-200);
  // Angler.move_absolute(160, 200);
  // // pros::delay(500);
  // Puncher.tare_position();
  // while(Puncher.get_position() < 2000){
  //   Puncher.move_velocity(200);
  // }
  // Puncher.move_velocity(0);


  // gyroTurn(-450);







}
