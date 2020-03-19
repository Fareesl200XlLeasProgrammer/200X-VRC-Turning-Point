#include "main.h"
#include "Functions.hpp"
#include "Motors.hpp"
#include "Variables.hpp"
#include "Sensors.hpp"
#include "Tasks.hpp"


void calibrateSensors()
{
	trayPot.calibrate();
	ArmEncoder.reset();
	LeftTracker.reset();
	RightTracker.reset();
}

void initialize()
{
	pros::lcd::initialize();
	trayPot.calibrate();
	ArmEncoder.reset();
	LeftTracker.reset();
	RightTracker.reset();
	gyro.reset();
}

void collect(void*)
{
	IntakeL.move(127);
	IntakeR.move(127);
}



void disabled() {}

void competition_initialize() {}

void autonomous()
{

	int current, stage = 0, time, starting_Tray;
	while(true)
	{

		switch(stage)
		{

			case 0:

				deploy();
				stage++;

			break;

			//Move forward
			case 1:
				time = pros::millis() + 2700;
				do
				{

					IntakeL.move(127);
					IntakeR.move(127);

					LF.move_velocity(127 * 0.4);
					RF.move_velocity(127 * 0.4);
					LB.move_velocity(127 * 0.4);
					RB.move_velocity(127 * 0.4);

				} while(pros::millis() < time);

				starting_Tray = trayPot.get_value_calibrated();
				stage++;

			break;

			//Move backwards
			case 2:

				time = pros::millis() + 600;
				do
				{

					IntakeL.move(127);
					IntakeR.move(127);

					LF.move_velocity(-127 * 0.8);
					RF.move_velocity(-127 * 0.8);
					LB.move_velocity(-127 * 0.8);
					RB.move_velocity(-127 * 0.8);

				} while(pros::millis() < time);

				stage++;

			break;

		//Turn right
		case 3:

		time = pros::millis() + 870;
		do
		{

			IntakeL.move(127);
			IntakeR.move(127);

			LF.move_velocity(127 * 0.6);
			RF.move_velocity(-127 * 0.6);
			LB.move_velocity(127 * 0.6);
			RB.move_velocity(-127 * 0.6);

		} while(pros::millis() < time);
 	stage++;
			break;

			//Move forwad
			case 4:
				time = pros::millis() + 850;
				do
				{

					LF.move_velocity(127 * 0.4);
					RF.move_velocity(127 * 0.4);
					LB.move_velocity(127 * 0.4);
					RB.move_velocity(127 * 0.4);

				} while(pros::millis() < time);
				stage++;
			break;


			//Outtake with intakes
			case 5:

			time = pros::millis() + 150;
			do
			{

				IntakeL.move(-127);
				IntakeR.move(-127);

			} while(pros::millis() < time);

			stage++;
			break;

			//Stack with tray
			case 6:

				do
				{
					tilt.move(90);
				} while(trayPot.get_value_calibrated() < 3680);
				stage++;
			break;

			//Move back and pull back tray
			case 7:
			time = pros::millis() + 1000;
			tilt.set_brake_mode(MOTOR_BRAKE_COAST);
			do
			{
				IntakeL.move(-127);
				IntakeR.move(-127);
				LF.move_velocity(-127 * 0.8);
				RF.move_velocity(-127 * 0.8);
				LB.move_velocity(-127 * 0.8);
				RB.move_velocity(-127 * 0.8);

				if(trayPot.get_value_calibrated() > starting_Tray + 20){
					tilt.move(-127);
				}

			} while(pros::millis() < time);
			stage++;
			std::cout << pros::millis() << std::endl;
			break;
		}
	}
}

void opcontrol()
{
	while(true)
	{
		std::cout << "Left: " << LeftTracker.get_value() << std::endl;
		std::cout << "Right: " << RightTracker.get_value()<< std::endl;

		pros::delay(20);
	}
}
