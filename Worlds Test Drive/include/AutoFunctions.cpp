#include "main.h"

void Skills(){//Skills Auto
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


  while(Left.get_position() > -610){
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

	pros::delay(1000);

	Index.move_relative(500, 200);

	pros::delay(1000);

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

	while(Left.get_position() > 7300){
    Right.move_velocity(200);
    Right2.move_velocity(200);
    Left2.move_velocity(-200);
    Left.move_velocity(-200);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() > 6700){
    Right.move_velocity(-20);
    Right2.move_velocity(-20);
    Left2.move_velocity(-20);
    Left.move_velocity(-20);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);

	while(Left.get_position() < 7500){
    Right.move_velocity(-100);
    Right2.move_velocity(-100);
    Left2.move_velocity(100);
    Left.move_velocity(100);
  }
  Right.move_velocity(0);
  Right2.move_velocity(0);
  Left2.move_velocity(0);
  Left.move_velocity(0);
}

void Red_Front(){
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor LeftF(1);

	pros::Motor LeftB(2);

	pros::Motor RightF(3, true);

	pros::Motor RightB(4, true);

	LeftF.move_relative(-500, 500);
	LeftB.move_relative(-500, 500);
	RightF.move_relative(-500, 500);
	RightB.move_relative(-500, 500);
}

void Red_Back(){
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor LeftF(1);

	pros::Motor LeftB(2);

	pros::Motor RightF(3, true);

	pros::Motor RightB(4, true);

	LeftF.move_relative(-500, 500);
	LeftB.move_relative(500, 500);
	RightF.move_relative(500, 500);
	RightB.move_relative(-500, 500);

}

void Blue_Front(){
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor LeftF(1);

	pros::Motor LeftB(2);

	pros::Motor RightF(3, true);

	pros::Motor RightB(4, true);

	LeftF.move_relative(500, 500);
	LeftB.move_relative(500, 500);
	RightF.move_relative(500, 500);
	RightB.move_relative(500, 500);

}

void Blue_Back(){

}
