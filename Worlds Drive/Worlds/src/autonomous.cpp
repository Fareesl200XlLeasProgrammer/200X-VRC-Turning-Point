#include "main.h"
#include "okapi/api.hpp"
#include "functions.h"
//#include "Autos.h"
#include "AutoVars.cpp"

using namespace okapi;
using namespace pros;


void autonomous() {
  //motor definitions
  pros::Motor Puncher(6);
  pros::Motor Angler(15);
  pros::Motor Intake(16);
 pros::Motor Lift(5);
 pros::Motor LeftF(1);
pros::Motor LeftB(10);
pros::Motor RightF(20,true);
pros::Motor RightB(11,true);
 pros::ADIPotentiometer AnglePot(1);
 pros::ADIGyro GyroAuto(4);

 //calibrating the Potentiometer
 AnglePot.calibrate();

 //creating the chassis that are used in the auton
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

   //Creating the paths that the bot has to take in auton
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.66519143_ft, 0_ft, 0_deg}}, "firstCap");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.523598776_ft, 0_ft, 0_deg}}, "firstCapBack");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0_ft, 2_ft, 0_deg}}, "secondCapAlign");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.523598776_ft, 0_ft, 0_deg}}, "secondCap");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 0_deg}}, "shootAdjust");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.523598776_ft, 0_ft, 0_deg}}, "secondCapBack");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.4_ft, 0_ft, 0_deg}}, "flipSecondCap");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0_ft, 5_ft, 0_deg}}, "climb");

   //start of the auton
   profileController.setTarget("firstCap");//get the ball under the first cap
   Lift.move_relative(400, 200);
   Intake.move_velocity(-200);
   Puncher.move_absolute(600, 200);
   profileController.waitUntilSettled();

   profileController.setTarget("firstCapBack",true);//move away from the first cap
   Intake.move_velocity(0);
   profileController.waitUntilSettled();

   while(GyroAuto.get_value() != 288.958596){//turn towards the first flag
     LeftF.move_velocity(-200);
     LeftB.move_velocity(-200);
     RightF.move_velocity(200);
     RightB.move_velocity(200);
   }
   LeftF.move_velocity(0);
   LeftB.move_velocity(0);
   RightF.move_velocity(0);
   RightB.move_velocity(0);
   //myChassis.turnAngle(-71.041404_deg);
   profileController.waitUntilSettled();


   while(AnglePot.get_value_calibrated() < 97){//shoot the middle flag on the middle post
     Angler.move_velocity(100);
   }
   Angler.move_velocity(0);
   Puncher.tare_position();

   while(Puncher.get_position() < 2100){
     Puncher.move_velocity(100);
   }
   Puncher.move_velocity(0);

     while(Angler.get_position() > 0){
       Angler.move_velocity(-100);
       Intake.move_velocity(200);
     }
     Angler.move_velocity(0);

     Puncher.tare_position();

     while(AnglePot.get_value_calibrated() < 10){//shoot the upper flag on the middle post
       Angler.move_velocity(70);
     }
     Angler.move_velocity(0);
     Puncher.tare_position();

     while(Puncher.get_position() < 2100){
       Puncher.move_velocity(200);
     }
     Puncher.move_velocity(0);

       while(Angler.get_position() > 0){
         Angler.move_velocity(-200);
       }
       Angler.move_velocity(0);
       Intake.move_velocity(0);
     profileController.waitUntilSettled();

     while(GyroAuto.get_value() != 0){// turn back towards the caps
       LeftF.move_velocity(200);
       LeftB.move_velocity(200);
       RightF.move_velocity(-200);
       RightB.move_velocity(-200);
     }
     LeftF.move_velocity(0);
     LeftB.move_velocity(0);
     RightF.move_velocity(0);
     RightB.move_velocity(0);
//   myChassis.turnAngle(71.041404_deg);
   profileController.waitUntilSettled();

   profileController.setTarget("secondCapAlign");//move towards the second cap
   profileController.waitUntilSettled();

   profileController.setTarget("secondCap");//move towards the second cap and angle it down to scrape
   Intake.move_velocity(200);
   profileController.waitUntilSettled();

   Lift.move_relative(-400, 200);// move the lift onto the cap to pull balls of
   profileController.waitUntilSettled();

   profileController.setTarget("secondCapBack",true);//pull the balls off the cap
   profileController.waitUntilSettled();

   while(GyroAuto.get_value() != 310){//turn towards the flag (need to test)
     LeftF.move_velocity(-200);
     LeftB.move_velocity(-200);
     RightF.move_velocity(200);
     RightB.move_velocity(200);
   }
   LeftF.move_velocity(0);
   LeftB.move_velocity(0);
   RightF.move_velocity(0);
   RightB.move_velocity(0);
   //myChassis.turnAngle(-51.041404_deg);
   Intake.move_velocity(0);
   profileController.waitUntilSettled();

   while(AnglePot.get_value_calibrated() < 97){//shooting the first flag (need to test)
     Angler.move_velocity(100);
   }
   Angler.move_velocity(0);
   Puncher.tare_position();

   while(Puncher.get_position() < 2100){
     Puncher.move_velocity(100);
   }
   Puncher.move_velocity(0);

     while(Angler.get_position() > 0){
       Angler.move_velocity(-100);
       Intake.move_velocity(200);
     }
     Angler.move_velocity(0);

     Puncher.tare_position();

     while(AnglePot.get_value_calibrated() < 10){//shoot the second flag (need to test)
       Angler.move_velocity(70);
     }
     Angler.move_velocity(0);
     Puncher.tare_position();

     while(Puncher.get_position() < 2100){
       Puncher.move_velocity(200);
     }
     Puncher.move_velocity(0);

       while(Angler.get_position() > 0){
         Angler.move_velocity(-200);
       }
       Angler.move_velocity(0);
       Intake.move_velocity(0);
   profileController.waitUntilSettled();

   Lift.move_relative(1600, 200);//moving the lift over the bot so it can flip the cap
   while(GyroAuto.get_value() != 180){//turn around to flip cap
     LeftF.move_velocity(-200);
     LeftB.move_velocity(-200);
     RightF.move_velocity(200);
     RightB.move_velocity(200);
   }
   LeftF.move_velocity(0);
   LeftB.move_velocity(0);
   RightF.move_velocity(0);
   RightB.move_velocity(0);
   profileController.waitUntilSettled();

   profileController.setTarget("flipSecondCap",true);//move into a postion to flip the second cap
   profileController.waitUntilSettled();

   Lift.move_relative(-400, 200);//flip the cap
   profileController.waitUntilSettled();

   while(GyroAuto.get_value() != 90){//turn around face the platform
     LeftF.move_velocity(-200);
     LeftB.move_velocity(-200);
     RightF.move_velocity(200);
     RightB.move_velocity(200);
   }
   LeftF.move_velocity(0);
   LeftB.move_velocity(0);
   RightF.move_velocity(0);
   RightB.move_velocity(0);
   profileController.waitUntilSettled();

   profileController.setTarget("climb",true);//climb
   profileController.waitUntilSettled();
}
