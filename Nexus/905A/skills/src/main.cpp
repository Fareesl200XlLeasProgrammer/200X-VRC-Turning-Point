#include "main.h"
#include "Motors.hpp"
#include "Sensors.hpp"
#include "Variables.hpp"
#include "okapi/api.hpp"

using namespace okapi;

void intakec(int speed){
	IntakeL.move_velocity(speed);
	IntakeR.move_velocity(speed);
}

auto chassis = ChassisControllerBuilder()
		.withMotors({14,16}, {10,20}) // left motor is 1, right motor is 2 (reversed)
		// green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
		.withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 12.5_in}, imev5BlueTPR})
		// .withGains(
		//     {0.0027, 0.0026, 0.0001}, // Distance controller gains
		//     {0.002, 0.00, 0.0001}, // Turn controller gains
		//     {0.00, 0.000, 0.000}  // Angle controller gains (helps drive straight)
		// )

		.build(); // build an odometry chassis


std::shared_ptr<AsyncMotionProfileController> profileController =
  AsyncMotionProfileControllerBuilder()
    .withLimits({1.0, 2.0, 10.0})
    .withOutput(chassis)
    .buildMotionProfileController();

 int sgn(double v) {
   return (v < 0) ? -1 : ((v > 0) ? 1 : 0);
 }


 void initialize() {

 }

 void drive(void*)
 {
     int tempL;
     int tempR;
   while(true)
   {
     tempL = master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X);
     tempR = master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X);

     LPower = int(abs(pow(tempL, 2) / 127)) * sgn(tempL);
     RPower = int(abs(pow(tempL, 2) / 127)) * sgn(tempR);

     LF.move(tempL);
     RF.move(tempR);
     LB.move(tempL);
     RB.move(tempR);
     pros::delay(20);
   }
 }

 void arm(void*)
 {
   while(true)
   {
     if(master.get_digital(DIGITAL_L1)) {
       armPos = controlArm;
     }
     else if(master.get_digital(DIGITAL_L2)) {
       armPos = controlArm;
     }
     else if(master.get_digital(DIGITAL_B)) {
       armPos = Intake;
     }
     else if(master.get_digital(DIGITAL_A)) {
       armPos = lowTower;
     }
     else if(master.get_digital(DIGITAL_X)) {
       armPos = midTower;
     }
     else if(master.get_digital(DIGITAL_UP)) {
       armPos = stopArm;
     }
     else {
       armPos = stopArm;
     }
     pros::delay(20);
   }
 }

 void intake(void*)
 {
   while(true)
   {
     if(master.get_digital(DIGITAL_R1)){
       IntakeL.move(127);
       IntakeR.move(127);
     }

     else if(master.get_digital(DIGITAL_R2)){
       IntakeL.move(-127);
       IntakeR.move(-127);
     }

     else {
       IntakeL.move_velocity(0);
       IntakeR.move_velocity(0);
       IntakeL.set_brake_mode(MOTOR_BRAKE_HOLD);
       IntakeR.set_brake_mode(MOTOR_BRAKE_HOLD);
     }
     pros::delay(20);
   }
 }

 void scoreStack()
 {
    while (!(1800 < leftTray.get_value() && leftTray.get_value() < 2800)){
       IntakeL.move(-80);
       IntakeR.move(-80);
       if(master.get_digital(DIGITAL_DOWN)){
          break;
       }
    }
   while(trayPot.get_value() > 3100){

       tilt.move_velocity(70);

       if(trayPot.get_value() < 3300){


          //WAS: -80
          //IS: -60
          IntakeL.move(-60);
          IntakeR.move(-60);
       }
       else{
          IntakeL.move(0);
          IntakeR.move(0);
       }

       if(master.get_digital(DIGITAL_DOWN)){
          break;
       }
    }
    IntakeL.move(0);
    IntakeR.move(0);
    while(trayPot.get_value() > 2000){

       tilt.move_velocity(45);

       if(master.get_digital(DIGITAL_DOWN)){
          break;
       }

    }

    tilt.move(0);
    master.rumble("-.-");
 }


 void tilter(void*)
 {
     int Pow, temp;
   while(true)
   {
     temp = master.get_analog(ANALOG_RIGHT_Y);
     Pow = int((pow(temp, 2)) / 127) * sgn(temp);
     tilt.move(Pow);
     tilt.set_brake_mode(MOTOR_BRAKE_HOLD);
     if(master.get_digital(DIGITAL_Y)){
       scoreStack();
    }

     pros::delay(20);
   }
 }

 void liftTo(void*)
 {
   double  pwr, error, totalError, lastError, P, D;
   int target, time = 0;

   while(true)
   {
     switch(armPos)
     {
       case stopArm:
         Arm.move_velocity(0);
         Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
       break;

       case controlArm:
         if(master.get_digital(DIGITAL_L1))
         {
             Arm.move(127);
         }
         else if(master.get_digital(DIGITAL_L2))
         {
             Arm.move(-127);
         }

         else if(master.get_digital(DIGITAL_B))
         {
             Arm.move(-127);
         }
         break;

       case Intake:
         Arm.move_absolute(50, 200);
				 while(Arm.get_position() != 50){
					 pros::delay(1);
				 }
       break;

       case lowTower:
         Arm.move_absolute(2300, 200);
				 while(Arm.get_position() != 2000){
					 pros::delay(1);
				 }
       break;

       case midTower:
         Arm.move_absolute(2700, 200);
				 while(Arm.get_position() != 2700){
					 pros::delay(1);
				 }
       break;

       case highTower:

       break;
     }
   }
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

 void scoreStackAuto()
{
   while (!(1800 < leftTray.get_value() && leftTray.get_value() < 2900)){
      IntakeL.move(-50);
      IntakeR.move(-50);

   }



  while(trayPot.get_value() > 3100){

      tilt.move_velocity(70);

      if(trayPot.get_value() < 3300){



         IntakeL.move(-20);
         IntakeR.move(-20);
      }
      else{
         IntakeL.move(0);
         IntakeR.move(0);
      }


   }
   IntakeL.move(0);
   IntakeR.move(0);
   while(trayPot.get_value() > 2000){

      tilt.move_velocity(45);


   }

   tilt.move(0);
}

void outtake(){
	IntakeL.move_relative(-300, 100);
	IntakeR.move_relative(-300, 100);
}

void shootTower(){
	IntakeL.move_relative(-1500, 200);
	IntakeR.move_relative(-1500, 200);
	pros::delay(500);
}
//
// void blueBack6(){
//   deploy();
// 	Arm.move_absolute(0, 200);
// 	intakec(200);
// 	chassis->setMaxVelocity(150);
// 	chassis->moveDistance(6.5_ft);
//
// 	chassis->turnAngle(40_deg);
// 	chassis->moveDistance(1.5_ft);
// 	chassis->waitUntilSettled();
// 	chassis->moveDistance(-1.5_ft);
// 	chassis->turnAngle(250_deg);
// 	chassis->setMaxVelocity(300);
// 	chassis->moveDistance(5_ft);
// 	intakec(0);
//
// 	outtake();
// 	tilt.move_absolute(3000, 50);
//   pros::delay(1000);
//
// 	intakec(-60);
//
// 	pros::delay(250);
// 	LB.move_velocity(200);
// 	RB.move_velocity(200);
// 	RF.move_velocity(200);
// 	LF.move_velocity(200);
// 	pros::delay(300);
// 	LB.move_velocity(0);
// 	RB.move_velocity(0);
// 	RF.move_velocity(0);
// 	LF.move_velocity(0);
// 	pros::delay(250);
// 	chassis->moveDistance(-2_ft);
// 	tilt.move_absolute(0,200);
//
//
// }
//
// void redBack6(){
//   deploy();
// 	Arm.move_absolute(0, 200);
// 	intakec(200);
// 	chassis->setMaxVelocity(190);
// 	chassis->moveDistance(6_ft);
//
//
// 	chassis->turnAngle(-50_deg);
// 	chassis->moveDistance(1.5_ft);
// 	chassis->waitUntilSettled();
// 	chassis->moveDistance(-1.5_ft);
// 	chassis->turnAngle(-240_deg);
// 	chassis->setMaxVelocity(300);
// 	chassis->moveDistance(5_ft);
// 	intakec(0);
//
// 	outtake();
// 	tilt.move_absolute(3000, 50);
//   pros::delay(1000);
//
// 	intakec(-60);
//
// 	pros::delay(250);
// 	LB.move_velocity(200);
// 	RB.move_velocity(200);
// 	RF.move_velocity(200);
// 	LF.move_velocity(200);
// 	pros::delay(300);
// 	LB.move_velocity(0);
// 	RB.move_velocity(0);
// 	RF.move_velocity(0);
// 	LF.move_velocity(0);
// 	pros::delay(250);
// 	chassis->moveDistance(-2_ft);
// 	tilt.move_absolute(0,200);
//
//
// }
//
//
//
// void red9(){
// 	deploy();
// 	Arm.move_absolute(10, 200);
// 	intakec(200);
// 	chassis->setMaxVelocity(250);
// 	chassis->moveDistance(4.25_ft);
// 	Arm.move_absolute(1000, 200);
// 	chassis->setMaxVelocity(250);
// 	chassis->moveDistance(1_ft);
// 	Arm.move_absolute(10, 100);
// 	chassis->moveDistance(-1_ft);
// 	chassis->setMaxVelocity(300);
// 	chassis->turnAngle(-0_deg);
// 	chassis->moveDistance(-4_ft);
// 	chassis->turnAngle(60_deg);
// 	pros::delay(1);
// 	LB.move_velocity(-600);
// 	RB.move_velocity(-600);
// 	RF.move_velocity(-600);
// 	LF.move_velocity(-600);
// 	pros::delay(300);
// 	LB.move_velocity(0);
// 	RB.move_velocity(0);
// 	RF.move_velocity(0);
// 	LF.move_velocity(0);
//
// 	chassis->setMaxVelocity(220);
// 	intakec(200);
// 	chassis->moveDistance(3.25_ft);
// 	chassis->moveDistance(3.25_ft);
// 	chassis->turnAngle(220_deg);
// 	chassis->setMaxVelocity(160);
// 	chassis->moveDistance(5_ft);
// 	pros::delay(100);
// 	// scoreStackAuto();
// 	outtake();
// 	tilt.move_absolute(3000, 50);
// 	pros::delay(1000);
//
// 	intakec(-60);
//
// 	pros::delay(250);
// 	LB.move_velocity(100);
// 	RB.move_velocity(100);
// 	RF.move_velocity(100);
// 	LF.move_velocity(100);
// 	pros::delay(700);
// 	LB.move_velocity(0);
// 	RB.move_velocity(0);
// 	RF.move_velocity(0);
// 	LF.move_velocity(0);
// 	pros::delay(250);
// 	chassis->moveDistance(-2_ft);
//
// }
//
void Redskills(){
	deploy();
	Arm.move_absolute(0, 200);
	intakec(200);
	chassis->setMaxVelocity(180);
	chassis->moveDistance(4.25_ft);
	Arm.move_absolute(1000, 200);
	pros::delay(200);
	chassis->setMaxVelocity(180);
	chassis->moveDistance(2_ft);
	Arm.move_absolute(0, 100);
	pros::delay(50);
	chassis->setMaxVelocity(180);
	chassis->turnAngle(-37_deg);
	chassis->moveDistance(-6.6_ft);
	chassis->turnAngle(37_deg);

	pros::delay(250);
	LB.move_velocity(-150);
	RB.move_velocity(-150);
	RF.move_velocity(-150);
	LF.move_velocity(-150);
	pros::delay(700);
	LB.move_velocity(0);
	RB.move_velocity(0);
	RF.move_velocity(0);
	LF.move_velocity(0);
	pros::delay(250);

	chassis->setMaxVelocity(120);
	intakec(200);
	chassis->moveDistance(3.25_ft);
	chassis->moveDistance(3.25_ft);
	chassis->turnAngle(220_deg);
	chassis->setMaxVelocity(160);
	chassis->moveDistance(5_ft);
	chassis->waitUntilSettled();
	pros::delay(1000);
	// scoreStackAuto();
	outtake();
	tilt.move_absolute(3000, 50);
  pros::delay(1000);

	intakec(-60);

	pros::delay(250);
	LB.move_velocity(100);
	RB.move_velocity(100);
	RF.move_velocity(100);
	LF.move_velocity(100);
	pros::delay(700);
	LB.move_velocity(0);
	RB.move_velocity(0);
	RF.move_velocity(0);
	LF.move_velocity(0);
	pros::delay(250);
	chassis->moveDistance(-2_ft);

	chassis->turnAngle(180_deg);
	intakec(200);
	pros::delay(50);
	LB.move_velocity(-100);
	RB.move_velocity(-100);
	RF.move_velocity(-100);
	LF.move_velocity(-100);
	pros::delay(1700);
	LB.move_velocity(0);
	RB.move_velocity(0);
	RF.move_velocity(0);
	LF.move_velocity(0);
	pros::delay(250);
	tilt.move_absolute(0,200);

	chassis->moveDistance(7_ft);
	pros::delay(50);
	chassis->moveDistance(-1_ft);
	Arm.move_absolute(3500, 200);
	pros::delay(1000);
	chassis->moveDistance(1_ft);
	intakec(-200);
	pros::delay(1000);
	chassis->setMaxVelocity(200);
	intakec(200);
	Arm.move_absolute(0, 200);
	chassis->moveDistance(-7_ft);
	chassis->waitUntilSettled();
	chassis->moveDistance(4.5_ft);
	chassis->turnAngle(110_deg);
	pros::delay(50);
	LB.move_velocity(-200);
	RB.move_velocity(-200);
	RF.move_velocity(-200);
	LF.move_velocity(-200);
	pros::delay(1700);
	LB.move_velocity(0);
	RB.move_velocity(0);
	RF.move_velocity(0);
	LF.move_velocity(0);
	pros::delay(250);
	chassis->setMaxVelocity(300);
	chassis->moveDistance(7_ft);
	chassis->waitUntilSettled();
	chassis->moveDistance(-1_ft);
	Arm.move_absolute(3500, 200);
	pros::delay(1000);
	chassis->moveDistance(1_ft);
	intakec(-200);



}

void hitWall(int speed, int time){
	LB.move_velocity(speed);
	RB.move_velocity(speed);
	RF.move_velocity(speed);
	LF.move_velocity(speed);
	pros::delay(time);
	LB.move_velocity(0);
	RB.move_velocity(0);
	RF.move_velocity(0);
	LF.move_velocity(0);
}

void autoScore(){
	outtake();
	tilt.move_absolute(3000, 30);
  pros::delay(1000);

	intakec(-60);

	pros::delay(700);
	intakec(-200);
	chassis->moveDistance(-1_ft);
}
//
// void red7(){
// 	deploy();
// 	intakec(200);
// 	Arm.move_absolute(0,200);
// 	chassis->setMaxVelocity(170);
// 	chassis->moveDistance(4_ft);
// 	chassis->setMaxVelocity(300);
// 	chassis->turnAngle(-60_deg);
// 	chassis->moveDistance(-4.5_ft);
// 	chassis->turnAngle(60_deg);
// 	hitWall(-400, 400);
// 	pros::delay(100);
// 	chassis->setMaxVelocity(200);
// 	chassis->moveDistance(3.25_ft);
// 	chassis->moveDistance(3_ft);
// 	chassis->setMaxVelocity(300);
// 	chassis->moveDistance(-2_ft);
// 	chassis->turnAngle(400_deg);
// 	chassis->moveDistance(3.5_ft);
// 	autoScore();
// }
//
// void Skills60(){
// 	deploy();
// 	intakec(200);
// 	Arm.move_absolute(2700, 200);
// 	pros::delay(200);
// 	chassis->setMaxVelocity(200);//velocity
// 	chassis->moveDistance(2.7_ft);
// 	shootTower();
// 	chassis->setMaxVelocity(200);
// 	chassis->moveDistance(-1.5_ft);
// 	chassis->turnAngle(-60_deg);
// 	Arm.move_absolute(0,200);
// 	chassis->setMaxVelocity(170);
// 	intakec(200);
// 	hitWall(-300, 1000);
// 	chassis->moveDistance(3.25_ft);
// 	chassis->moveDistance(3_ft);
// 	chassis->moveDistance(-2_ft);
// 	chassis->setMaxVelocity(200);
// 	chassis->turnAngle(220_deg);
// 	chassis->moveDistance(3_ft);
// 	hitWall(600, 600);
// 	autoScore();
// 	chassis->turnAngle(-60_deg);
// 	tilt.move_absolute(0,200);
// 	hitWall(200, 900);
// 	chassis->setMaxVelocity(300);
// 	chassis->moveDistance(-2_ft);
// 	chassis->turnAngle(-110_deg);
// 	hitWall(-600, 600);
// 	chassis->moveDistance(-0.2_ft);
// 	chassis->moveDistance(7_ft);
// 	Arm.move_absolute(2500, 200);
//
//
// }


void on_center_button() {

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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


// void red9new(){
// profileController->generatePath(
//   {{0_ft, 0_ft, 0_deg}, {3_ft, 0_ft, 0_deg}}, "forward");
//
//
// profileController->generatePath(
// 	{{0_ft, 0_ft, 0_deg}, {2.75_ft, 0_ft, 0_deg}}, "forward2");
//
// profileController->generatePath(
// 	{{5_ft, 0_ft, 0_deg}, {0_ft, 5_ft, 0_deg}}, "s");
//// turnPID(90);
//
//
//
// profileController->generatePath(
// 	{{0_ft, 0_ft, 0_deg}, {1_ft, 0_ft, 0_deg}}, "forward3");
//
//
//
// 	deploy();
// 	Arm.move_absolute(20,200);
// 	intakec(200);
//
//
// 	profileController->setTarget("forward");
// 	profileController->waitUntilSettled();
//
// 	Arm.move_absolute(1000, 200);
//
// 	profileController->setTarget("forward3");
// 	profileController->waitUntilSettled();
//
// 	Arm.move_absolute(0,200);
//
// 	profileController->setTarget("s", true);
// 	profileController->waitUntilSettled();
//
// 	profileController->setTarget("forward2");
// 	profileController->waitUntilSettled();
//
// 	profileController->setTarget("forward2");
// 	profileController->waitUntilSettled();
//
// 	chassis->turnAngle(230_deg);
// 	chassis->moveDistance(5_ft);
//
// 	outtake();
// 	tilt.move_absolute(3000, 50);
//   pros::delay(1000);
//
// 	intakec(-60);
//
// 	LB.move_velocity(100);
// 	RB.move_velocity(100);
// 	RF.move_velocity(100);
// 	LF.move_velocity(100);
// 	pros::delay(700);
// 	LB.move_velocity(0);
// 	RB.move_velocity(0);
// 	RF.move_velocity(0);
// 	LF.move_velocity(0);
// 	pros::delay(250);
// 	chassis->moveDistance(-2_ft);
//
// }

void drivePID(double target, bool intake) {
	double current, lastError, error, P, D, kP = 0.95, kD = 2, pwr;
  do {
		current = tracker.get_value();
		lastError = error;
		error = target - current;
		P = error*kP;
		D = (error - lastError)*kD;

		pwr = P + D;

		if(intake){
			intakec(200);
		}
		else{
			intakec(0);
		}


    LF.move(pwr);
    LB.move(pwr);
    RF.move(pwr);
    RB.move(pwr);

  } while(abs(error) > 25);
  LF.move_velocity(0);
  LB.move_velocity(0);
  RF.move_velocity(0);
  RB.move_velocity(0);
}

void turnPID(double target){
	double current, error, P, D, kP = 7.75, kD = 15, pwr, lastError;
	int time = pros::millis();
	int itr = 0;
	do{

		current = imu.get_heading();
		lastError = error;
		error = target-current;

		P = error*kP;
		D = (error-lastError)*kD;

		pwr =  P + D;


		LF.move(pwr);
		LB.move(pwr);
		RB.move(-pwr);
		RF.move(-pwr);

	}while(abs(error)>0.001);
	LB.move_velocity(0);
	RB.move_velocity(0);
	RF.move_velocity(0);
	LF.move_velocity(0);

}


void skillsNew(){
	deploy();
	intakec(200);
	drivePID(100, true);
	turnPID(45);
	Arm.move_absolute(2700,200);
	drivePID(300, false);


}

void autonomous() {
	Redskills();
}





/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Task driveTask(drive, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");
	pros::Task armTask(arm, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");
	pros::Task intakeTask(intake, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");
	pros::Task tilterTask(tilter, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");
	pros::Task liftTask(liftTo, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");


	// int time = pros::millis();
  // int iter = 0;
	//
	// while (imu.is_calibrating()) {
	// 	printf("IMU calibrating... %d\n", iter);
	// 	iter += 10;
	// 	pros::delay(10);
	// }
	//
	// printf("IMU is done calibrating (took %d ms)\n", iter - time);


	while (true) {

		pros::delay(20);
	}
}
