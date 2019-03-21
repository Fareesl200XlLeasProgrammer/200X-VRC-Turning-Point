#include "main.h"

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
	while (true) {
		double L = Left.get_position();
		double R = Right.get_position();
		//Drive Code
    Right.move(master.get_analog(ANALOG_RIGHT_X)*0.5 - master.get_analog(ANALOG_LEFT_Y));
    Right2.move(master.get_analog(ANALOG_RIGHT_X)*0.5 - master.get_analog(ANALOG_LEFT_Y));
    Left.move(master.get_analog(ANALOG_RIGHT_X)*0.5 + master.get_analog(ANALOG_LEFT_Y));
    Left2.move(master.get_analog(ANALOG_RIGHT_X)*0.5 + master.get_analog(ANALOG_LEFT_Y));
	}
}
