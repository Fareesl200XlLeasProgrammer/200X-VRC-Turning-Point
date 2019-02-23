#include "main.h"

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
  //Motor Definitions
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor Right(1, false);

	pros::Motor Right2(2, false);

	pros::Motor Left(3);

	pros::Motor Left2(4);

	pros::Motor Flipper(20);

	pros::Motor Intake(7, false);

	pros::Motor Lift(8);

	pros::Motor Flywheel(10);

	pros::Motor Index(17);

  Right.tare_position();
  Right2.tare_position();
  Left.tare_position();
  Left2.tare_position();

  Right.set_brake_mode(MOTOR_BRAKE_HOLD);
  Right2.set_brake_mode(MOTOR_BRAKE_HOLD);
  Left.set_brake_mode(MOTOR_BRAKE_HOLD);
  Left2.set_brake_mode(MOTOR_BRAKE_HOLD);

	Flywheel.move_velocity(135);
	Intake.move_velocity(-200);

  while(Left.get_position() < 3300){
    Right.move_velocity(-150);
    Right2.move_velocity(-150);
    Left2.move_velocity(150);
    Left.move_velocity(150);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

  pros::delay(1000);

  while(Left.get_position() > 70){
    Right.move_velocity(100);
    Right2.move_velocity(100);
    Left2.move_velocity(-100);
    Left.move_velocity(-100);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

  pros::delay(500);


  while(Left.get_position() > -605){
    Right.move_velocity(-20);
    Right2.move_velocity(-20);
    Left2.move_velocity(-20);
    Left.move_velocity(-20);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() < 3300){
    Right.move_velocity(-100);
    Right2.move_velocity(-100);
    Left2.move_velocity(100);
    Left.move_velocity(100);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	pros::delay(500);

	Index.move_relative(3000, 200);

	pros::delay(200);

	while(Left.get_position() < 4750){
    Right.move_velocity(-100);
    Right2.move_velocity(-100);
    Left2.move_velocity(100);
    Left.move_velocity(100);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	pros::delay(200);

	Index.move_relative(7000, 200);
	Flywheel.move_velocity(125);

	pros::delay(500);

	while(Left.get_position() > 2700){
    Right.move_velocity(150);
    Right2.move_velocity(150);
    Left2.move_velocity(-150);
    Left.move_velocity(-150);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() < 3150){
    Right.move_velocity(30);
    Right2.move_velocity(30);
    Left2.move_velocity(30);
    Left.move_velocity(30);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() < 6500){
    Right.move_velocity(-150);
    Right2.move_velocity(-150);
    Left2.move_velocity(150);
    Left.move_velocity(150);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	pros::delay(300);

	while(Left.get_position() > 6000){
    Right.move_velocity(100);
    Right2.move_velocity(100);
    Left2.move_velocity(-100);
    Left.move_velocity(-100);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	pros::delay(300);

	while(Left.get_position() > 5400){
    Right.move_velocity(-20);
    Right2.move_velocity(-20);
    Left2.move_velocity(-20);
    Left.move_velocity(-20);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	pros::delay(300);

	Index.move_relative(4500, 200);

	pros::delay(1000);

	//////////////////////////////PARK///////////////////////////
	while(Left.get_position() > 4750){
    Right.move_velocity(-20);
    Right2.move_velocity(-20);
    Left2.move_velocity(-20);
    Left.move_velocity(-20);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() < 8000){
    Right.move_velocity(-200);
    Right2.move_velocity(-200);
    Left2.move_velocity(200);
    Left.move_velocity(200);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() > 4450){
    Right.move_velocity(-200);
    Right2.move_velocity(-200);
    Left2.move_velocity(200);
    Left.move_velocity(200);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() > 3450){
    Right.move_velocity(-20);
    Right2.move_velocity(-20);
    Left2.move_velocity(20);
    Left.move_velocity(20);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() > 6450){
    Right.move_velocity(-100);
    Right2.move_velocity(-100);
    Left2.move_velocity(100);
    Left.move_velocity(100);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() > 4450){
    Right.move_velocity(-20);
    Right2.move_velocity(-20);
    Left2.move_velocity(-20);
    Left.move_velocity(-20);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() < 5450){
    Right.move_velocity(-200);
    Right2.move_velocity(-200);
    Left2.move_velocity(200);
    Left.move_velocity(200);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() > 3450){
    Right.move_velocity(200);
    Right2.move_velocity(200);
    Left2.move_velocity(-200);
    Left.move_velocity(-200);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position()  < 5000){
    Right.move_velocity(-200);
    Right2.move_velocity(-200);
    Left2.move_velocity(200);
    Left.move_velocity(200);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() > 4400){
		Right.move_velocity(-20);
		Right2.move_velocity(-20);
		Left2.move_velocity(-20);
		Left.move_velocity(-20);
	}
	Right.move_velocity(0);
	Right2.move_velocity(0);
	Left2.move_velocity(0);
	Left.move_velocity(0);

	while(Left.get_position() < 5500){
		Right.move_velocity(-200);
		Right2.move_velocity(-200);
		Left2.move_velocity(200);
		Left.move_velocity(200);
	}
	Right.move_velocity(0);
	Right2.move_velocity(0);
	Left2.move_velocity(0);
	Left.move_velocity(0);

	while(Left.get_position() > 4500){
		Right.move_velocity(-20);
		Right2.move_velocity(-20);
		Left2.move_velocity(-20);
		Left.move_velocity(-20);
	}
	Right.move_velocity(0);
	Right2.move_velocity(0);
	Left2.move_velocity(0);
	Left.move_velocity(0);


	///////////////////////RED FRONT/////////////////////////////////////////////
/*
	Flywheel.move_velocity(135);

  while(Left.get_position() < 2800){
    Right.move_velocity(-50);
    Right2.move_velocity(-50);
    Left2.move_velocity(50);
    Left.move_velocity(50);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);
	Intake.move_relative(-2000, 200);

  pros::delay(1000);

  while(Left.get_position() > 120){
    Right.move_velocity(100);
    Right2.move_velocity(100);
    Left2.move_velocity(-100);
    Left.move_velocity(-100);
  }

	Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() > -650){
    Right.move_velocity(-20);
    Right2.move_velocity(-20);
    Left2.move_velocity(-20);
    Left.move_velocity(-20);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	pros::delay(300);

	while(Left.get_position() < -200){
    Right.move_velocity(-100);
    Right2.move_velocity(-100);
    Left2.move_velocity(100);
    Left.move_velocity(100);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	pros::delay(500);

	Index.move_relative(2000, 200);

	pros::delay(1000);

	while(Left.get_position() < 400){
    Right.move_velocity(-100);
    Right2.move_velocity(-100);
    Left2.move_velocity(100);
    Left.move_velocity(100);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);
	pros::delay(300);

	Index.move_relative(3000, 200);
	Intake.move_relative(-3000,200);

	pros::delay(500);

	while(Left.get_position() < 3000){
    Right.move_velocity(-110);
    Right2.move_velocity(-110);
    Left2.move_velocity(100);
    Left.move_velocity(100);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);
*/









}
