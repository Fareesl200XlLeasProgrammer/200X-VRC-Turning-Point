#include "main.h"
#include "tracking.hpp"
#include "vision.hpp"
using namespace pros;

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
	  front_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	  front_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	  back_L.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	  back_R.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
		double power = 0;
		double kP = 1.2;
	  delay(6000);
		green.sig_num = 1;
		purple.sig_num = 2;
	  Task tracking_task(update);
		tracking.setAngleHold(0);
		Task angleTracking(pointToAngle);

	  while (true){
	     tracking.trackingInput();
			
			 // green.update();
			 // printf("center: %d\n",green.obj.x_middle_coord);
			 // printf("global angle: %f\n", tracking.global_angle);
	     // green.lineMiddle(1.2);
			 // printf("L:%d R:%d G:%f\n",leftencoder.get_value(),rightencoder.get_value(),tracking.global_angle);
	   }
	}
