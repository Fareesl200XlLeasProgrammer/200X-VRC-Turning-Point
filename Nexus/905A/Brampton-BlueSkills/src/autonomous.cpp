#include "main.h"
#include "Motors.hpp"
#include "Sensors.hpp"
#include "Variables.hpp"
#include "Functions.hpp"
#include "okapi/api.hpp"

using namespace okapi;



auto chassis = ChassisControllerBuilder()
    .withMotors({14,15}, {10,20}) // left motor is 1, right motor is 2 (reversed)
    // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
    .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 12.5_in}, imev5BlueTPR})
    .withSensors(
        ADIEncoder{'A', 'B'}, // left encoder in ADI ports A & B
        ADIEncoder{'C', 'D', true}  // right encoder in ADI ports C & D (reversed)
    )
    .build(); // build an odometry chassis

//
// void skills(){
//   chassis->setMaxVelocity(200);
//   IntakeL.move_velocity(200);
//   IntakeR.move_velocity(200);
//   chassis->moveDistance(3_ft);
// }

float wheelSize = 3.25;
float wheelDist = 9.875;

void resetPos(){

   LF.tare_position();
   LB.tare_position();
   RF.tare_position();
   RB.tare_position();


}

//distance in inches
//300TPR blue cartridges
void pidDrive(float distance, int maxVelocity)
{
  float current, error, lastError, totalError, derivative, kP = 1.05, kI = 0.01, kD = 2.1, P, I, D;
  int target, pwr;
  LF.tare_position();   RF.tare_position();   LB.tare_position();   RB.tare_position();
  target = ((distance / (wheelSize * M_PI)) * 477);
  do
  {
    current = (LF.get_position() + LB.get_position() + RF.get_position() + RB.get_position()) / 4;
    error = target -  current;
    totalError += error;
    derivative = error - lastError;
    lastError = error;
    P = error * kP;


    if(totalError > 3000){
      totalError = 0;
    }
    I = totalError * kI;

    D = derivative * kD;
    pwr = P+I+D;

    if(pwr > maxVelocity){
      pwr = maxVelocity;
   }
    LF.move_velocity(pwr);
    LB.move_velocity(pwr);
    RF.move_velocity(pwr);
    RB.move_velocity(pwr);

    pros::delay(5);
}while(abs(error) > 1);
  LF.move_velocity(0);
  LB.move_velocity(0);
  RF.move_velocity(0);
  RB.move_velocity(0);
  LF.set_brake_mode(MOTOR_BRAKE_HOLD);
  LB.set_brake_mode(MOTOR_BRAKE_HOLD);
  RF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RB.set_brake_mode(MOTOR_BRAKE_HOLD);

}

void pidTurn(int degree)
{
  float error, lastError = 0, totalError, derivative, kP = 1.05, kI = 0, kD = 0, P, I, D, rads;
  int target, pwr;
  target = (wheelDist / 2) * (degree * (M_PI/180));

  do
  {
    rads = (((LF.get_position() + LB.get_position()) / 2) - (RF.get_position() + RB.get_position()) / 2) / 2;
    error = target - rads;
    totalError += error;
    derivative = error - lastError;
    lastError = error;
    P = error * kP;

    if(totalError > 3000){
      totalError = 0;
    }
    I = totalError * kI;

    D = derivative * kD;
    pwr = P+I+D;

    LF.move(pwr);
    LB.move(pwr);
    RF.move(-pwr);
    RB.move(-pwr);

    pros::delay(5);
}while(!(abs(error) > 1));
  LF.move_velocity(500);
  LB.move_velocity(0);
  RF.move_velocity(0);
  RB.move_velocity(0);
}


 //
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
//   IterativePosPIDController::Gains{0.001, 0, 0.0001},
//   IterativePosPIDController::Gains{0.001, 0, 0.0001},
//   IterativePosPIDController::Gains{0.001, 0, 0.0001},
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
void blue8Cube(){

  // intakeControl(127);
  // chassis->waitUntilSettled();
  // chassis->turnAngle(90_deg);

  // chassis->turnAngle(-30_deg);
  //
  // chassis->moveDistance(-5_ft);
  //
  // chassis->turnAngle(30_deg);
  // chassis->moveDistance(5_ft);
  // chassis->waitUntilSettled();
  //
  // chassis->turnAngle(-145_deg);
  // chassis->moveDistance(7_ft);
}

void intakec(int pwr){
   IntakeL.move(pwr);
   IntakeR.move(pwr);

}
void deploy(){

   Arm.move(127);
   pros::delay(300);
   IntakeL.move(-127);
   IntakeR.move(-127);
   pros::delay(100);
   IntakeL.move(0);
   IntakeR.move(0);
   Arm.move(-127);
   pros::delay(500);
   Arm.move_velocity(0);
   Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
}

double error;
double kP = 0.7;
void movef(int target, int max, bool reversed){
   int pwr;

   do{

      error = target -  (LF.get_position() + LB.get_position() + RF.get_position() + RB.get_position()) / 4;
      pwr = kP*error;

      reversed ? pwr < max ? pwr = max : pwr = pwr : pwr > max ? pwr = max : pwr = pwr;

      LF.move(pwr);
      LB.move(pwr);
      RF.move(pwr);
      RB.move(pwr);
      std::cout << "Error: " << error << std::endl;
      std::cout << "Power: " << pwr << std::endl;

      pros::delay(2);
   }while(error >= 5 || error <= -5);


   LF.move(0);
   LB.move(0);
   RF.move(0);
   RB.move(0);


}




void movet(float pwr, double time){

   LF.move_velocity(pwr);
   LB.move_velocity(pwr);
   RF.move_velocity(pwr);
   RB.move_velocity(pwr);

   pros::delay(time);

   LF.move_velocity(0);
   LB.move_velocity(0);
   RF.move_velocity(0);
   RB.move_velocity(0);

}




void scoreStackAuto()
{
   while (!(1800 < leftTray.get_value() && leftTray.get_value() < 2800)){
      IntakeL.move(-60);
      IntakeR.move(-60);
   }
  while(trayPot.get_value() > 3300){
     IntakeL.move(0);
     IntakeR.move(0);
     tilt.move(90);
   }
   IntakeL.move(0);
   IntakeR.move(0);
   while(trayPot.get_value() > 2000){

      tilt.move((127 / 2) + 10);

      if(trayPot.get_value() < 3100 && trayPot.get_value() > 3000){
         IntakeL.move(-80);
         IntakeR.move(-80);
      }
      else{
         IntakeL.move(0);
         IntakeR.move(0);
      }
   }

   tilt.move(0);
}





double errora;
double kPa = 0.7;
void ArmPID(int target, int max, bool reversed){
   int pwr;
   do{

      error = target - Arm.get_position();
      pwr = kP*error;

      reversed ? pwr < max ? pwr = max : pwr = pwr : pwr > max ? pwr = max : pwr = pwr;

      Arm.move(pwr);

      pros::delay(2);
   }while(error >= 5 || error <= -5);
}




// void RedLarge(){
//
//
//       deploy();
//       movet(-30, 100);
//       intakec(127);
//       Arm.move(-50);
//       pros::delay(130);
//       Arm.move(0);
//       chassis->setMaxVelocity(175);
//       chassis->moveDistance(20_in);
//       chassis->setMaxVelocity(125);
//       Arm.move(105);
//       tilt.move_velocity(30);
//       chassis->moveDistance(27.5_in);
//       Arm.move(0);
//       tilt.move_velocity(0);
//       pros::delay(100);
//       Arm.move(-127);
//       tilt.move_velocity(1);
//       LF.move(0);
//       RF.move(0);
//       LB.move(0);
//       RB.move(0);
//       pros::delay(400);
//       LF.move(-20);
//       RF.move(-20);
//       LB.move(-20);
//       RB.move(-20);
//       pros::delay(100);
//       Arm.move(-127);
//       tilt.move_velocity(-100);
//       pros::delay(500);
//       tilt.move(0);
//          Arm.move(-100);
//       chassis->moveDistance(20_in);
//       chassis->setMaxVelocity(400);
//       chassis->turnAngle(-182.5_deg);
//       chassis->moveDistance(70_in);
//       LF.move(40);
//       RF.move(40);
//       RB.move(40);
//       LB.move(40);
//       Arm.move(0);
//       pros::delay(300);
//       scoreStackAuto();
//       tilt.move_velocity(-100);
//       LF.move(-40);
//       RF.move(-40);
//       RB.move(-40);
//       LB.move(-40);
//       IntakeR.move(-90);
//       IntakeL.move(-90);
//
//       // chassis->moveDistance(-18_in);
//       // chassis->turnAngle(45_deg);
//       // chassis->moveDistance(18_in);
//       // chassis->moveDistance(-18_in);
//       // chassis->turnAngle(-37_deg);
//       // chassis->moveDistance(28_in);
//       // chassis->setMaxVelocity(150);
//       // chassis->moveDistance(-45_in);
//       // chassis->setMaxVelocity(100);
//       // chassis->turnAngle(-240_deg);
//       // chassis->setMaxVelocity(150);
//       // chassis->moveDistance(35_in);
//       // scoreStackAuto();
//       // intakec(-127);
//       // chassis->setMaxVelocity(100);
//       // chassis->moveDistance(-24_in);
//
//
// }


















double adj_fact = 1 + (1/23);
//The amount off from the PID
double to_pid_d = 0.575;
//The ratio from chassis drive to PID


/*

   TO DO:
   - Try to turn the pid movement into move_velocity instead of move
   So that we can use the numbers from okapi
   - All speeds are currently guesses that need to be tuned or changed
   to move_velocit in the PID code

*/

void BlueLarge7(){


   deploy();
   movet(-30, 100);
   intakec(80);
   Arm.move(-50);
   pros::delay(130);
   Arm.move(0);
   chassis->setMaxVelocity(175);
   chassis->moveDistance(21_in);
   chassis->setMaxVelocity(125);

   intakec(127);
   Arm.move(127);
   tilt.move_velocity(25);
   movet(125, 1000);

   Arm.move_velocity(0);
   Arm.set_brake_mode(MOTOR_BRAKE_HOLD);

   chassis->moveDistance(7.5_in);

   Arm.move(0);
   tilt.move_velocity(0);
   pros::delay(100);

   Arm.move(-127);
   tilt.move_velocity(1);
   LF.move(0);
   RF.move(0);
   LB.move(0);
   RB.move(0);
   pros::delay(250);

   //Remove this and move 400 ms to the top timer to revert back
   tilt.move_velocity(-50);
   pros::delay(400);

   Arm.move_velocity(0);
   LF.move(40);
   RF.move(40);
   LB.move(40);
   RB.move(40);
   pros::delay(350);


   Arm.move_velocity(-60);
   LF.move(-20);
   RF.move(-20);
   LB.move(-20);
   RB.move(-20);
   tilt.move_velocity(-30);
   pros::delay(300);



   Arm.move(-127);
   tilt.move_velocity(-100);
   pros::delay(500);
   tilt.move(0);
   Arm.move(0);
   chassis->moveDistance(22_in);
   Arm.move(-127);

   chassis->setMaxVelocity(200);
   chassis->turnAngle(188_deg);

   chassis->setMaxVelocity(310);
   chassis->moveDistance(67_in);
   LF.move(127);
   RF.move(100);
   RB.move(100);
   LB.move(127);
   Arm.move(0);
   pros::delay(800);
   LF.move(0);
   RF.move(0);
   RB.move(70);
   LB.move(70);
   scoreStackAuto();
   tilt.move_velocity(-100);
   LF.move(-120);
   RF.move(-80);
   RB.move(-80);
   LB.move(-120);
   IntakeR.move(-90);
   IntakeL.move(-90);

      pros::delay(1000);
      LF.move(0);
      RF.move(0);
      RB.move(0);
      LB.move(0);










}



void RedLarge7(){

   deploy();
   movet(-30, 100);
   intakec(80);
   Arm.move(-50);
   pros::delay(130);
   Arm.move(0);
   chassis->setMaxVelocity(175);
   chassis->moveDistance(20_in);
   chassis->setMaxVelocity(125);
   intakec(127);
   Arm.move(105);
   tilt.move_velocity(30);
   chassis->moveDistance(27.5_in);
   Arm.move(0);
   tilt.move_velocity(0);
   pros::delay(100);
   Arm.move(-127);
   tilt.move_velocity(1);
   LF.move(0);
   RF.move(0);
   LB.move(0);
   RB.move(0);
   pros::delay(250);
   LF.move(50);
   RF.move(50);
   LB.move(50);
   RB.move(50);
   pros::delay(150);
   LF.move(-20);
   RF.move(-20);
   LB.move(-20);
   RB.move(-20);
   pros::delay(250);
   Arm.move(-127);
   tilt.move_velocity(-100);
   pros::delay(500);
   tilt.move(0);
   Arm.move(-100);
   chassis->moveDistance(22_in);
   chassis->setMaxVelocity(200);
   chassis->turnAngle(-177.5_deg);
   chassis->setMaxVelocity(350);
   chassis->moveDistance(62_in);
   LF.move(40);
   RF.move(40);
   RB.move(40);
   LB.move(40);
   Arm.move(0);
   pros::delay(300);
   scoreStackAuto();
   tilt.move_velocity(-100);
   LF.move(-40);
   RF.move(-40);
   RB.move(-40);
   LB.move(-40);
   IntakeR.move(-90);
   IntakeL.move(-90);

      pros::delay(1000);
      LF.move(0);
      RF.move(0);
      RB.move(0);
      LB.move(0);






      // chassis->moveDistance(-18_in);
      // chassis->turnAngle(45_deg);
      // chassis->moveDistance(18_in);
      // chassis->moveDistance(-18_in);
      // chassis->turnAngle(-37_deg);
      // chassis->moveDistance(28_in);
      // chassis->setMaxVelocity(150);
      // chassis->moveDistance(-45_in);
      // chassis->setMaxVelocity(100);
      // chassis->turnAngle(-240_deg);
      // chassis->setMaxVelocity(150);
      // chassis->moveDistance(35_in);
      // scoreStackAuto();
      // intakec(-127);
      // chassis->setMaxVelocity(100);
      // chassis->moveDistance(-24_in);



}




void RedProgramming(){

   deploy();
   movet(-30, 100);
   intakec(80);
   Arm.move(-50);
   pros::delay(130);
   Arm.move(0);
   chassis->setMaxVelocity(175);
   chassis->moveDistance(20_in);
   chassis->setMaxVelocity(125);
   intakec(127);
   Arm.move(105);
   tilt.move_velocity(30);
   chassis->moveDistance(27.5_in);
   Arm.move(0);
   tilt.move_velocity(0);
   pros::delay(100);
   Arm.move(-127);
   tilt.move_velocity(1);
   LF.move(0);
   RF.move(0);
   LB.move(0);
   RB.move(0);
   pros::delay(250);
   LF.move(50);
   RF.move(50);
   LB.move(50);
   RB.move(50);
   pros::delay(150);
   LF.move(-20);
   RF.move(-20);
   LB.move(-20);
   RB.move(-20);
   pros::delay(250);
   Arm.move(-127);
   tilt.move_velocity(-100);
   pros::delay(500);
   tilt.move(0);
   Arm.move(-100);
   chassis->moveDistance(22_in);
   chassis->setMaxVelocity(200);
   chassis->turnAngle(-177.5_deg);
   chassis->setMaxVelocity(350);
   chassis->moveDistance(62_in);
   LF.move(40);
   RF.move(40);
   RB.move(40);
   LB.move(40);
   Arm.move(0);
   pros::delay(300);
   scoreStackAuto();
   tilt.move_velocity(-100);
   LF.move(-40);
   RF.move(-40);
   RB.move(-40);
   LB.move(-40);
   IntakeR.move(-90);
   IntakeL.move(-90);
      pros::delay(1000);
      LF.move(0);
      RF.move(0);
      RB.move(0);
      LB.move(0);
      chassis->setMaxVelocity(140);
      chassis->turnAngle(-198.5_deg);
      intakec(127);
      chassis->setMaxVelocity(170);
      movet(-90, 2000);
      movet(90, 1500);
      chassis->turnAngle(-85.5_deg);
      movet(90,1700);
      movet(-90, 800);
      Arm.move(127);
      pros::delay(1800);
      Arm.move(0);
      movet(90, 800);
      intakec(-127);
      pros::delay(300);
      movet(-90, 1700);
      Arm.move(-127);
      chassis->turnAngle(85.5_deg);
      movet(90,1700);
      movet(-90, 800);
      Arm.move(127);
      pros::delay(1800);
      Arm.move(0);
      movet(90, 800);
      intakec(-127);
      pros::delay(300);
      movet(-90, 1700);
      Arm.move(-127);





      // chassis->moveDistance(-18_in);
      // chassis->turnAngle(45_deg);
      // chassis->moveDistance(18_in);
      // chassis->moveDistance(-18_in);
      // chassis->turnAngle(-37_deg);
      // chassis->moveDistance(28_in);
      // chassis->setMaxVelocity(150);
      // chassis->moveDistance(-45_in);
      // chassis->setMaxVelocity(100);
      // chassis->turnAngle(-240_deg);
      // chassis->setMaxVelocity(150);
      // chassis->moveDistance(35_in);
      // scoreStackAuto();
      // intakec(-127);
      // chassis->setMaxVelocity(100);
      // chassis->moveDistance(-24_in);



}

void tunePID(){

   resetPos();

   pidTurn(90);

}


void autonomous() {

   // skills();

}
