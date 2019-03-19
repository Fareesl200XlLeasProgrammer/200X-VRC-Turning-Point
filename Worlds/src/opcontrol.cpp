#include "main.h"
#include "api.h"
#include "pros/rtos.h"

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


void doubleShot(void*){
 	pros::Motor Puncher(18);
 	pros::Motor Angler(17);
	pros::ADIAnalogIn AnglePot (2);


 	pros::Controller master(pros::E_CONTROLLER_MASTER);

	Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
	Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
	Puncher.set_encoder_units(MOTOR_ENCODER_COUNTS);

	AnglePot.calibrate();

	while(true){
		if(master.get_digital(DIGITAL_B)){
			Puncher.tare_position();
			while(Puncher.get_position() < 2100){
 				Puncher.move_velocity(200);
 			}
 			Puncher.move_velocity(0);

			while(Angler.get_position() < 150){
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
 		}

		//Puncher Preset Top Full Court
 		if(master.get_digital(DIGITAL_Y)){
			Angler.tare_position();
 			while(AnglePot.get_value_calibrated() < 100){
 				Angler.move_velocity(200);
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

 		}

 		if(master.get_digital(DIGITAL_X)){
			Puncher.tare_position();
			while(Puncher.get_position() < 2100){
 				Puncher.move_velocity(200);
 			}
 			Puncher.move_velocity(0);
 		}
 		else{
 			Puncher.move_velocity(0);
 		}

		if(master.get_digital(DIGITAL_A)){
			Angler.tare_position();
 			while(Angler.get_position() < 200){
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
		}

	}


}


void opcontrol() {
	pros::Motor LeftF(10);
 	pros::Motor LeftB(1);
 	pros::Motor RightF(20, true);
 	pros::Motor RightB(11, true);
 	pros::Motor Intake(16);
 	pros::Motor Puncher(18);
 	pros::Motor Angler(17);
	pros::Motor Lift(21);
	pros::ADIAnalogIn AnglePot (2);
	pros::ADIAnalogIn IntakeLine_Top1 (3);

	pros::Controller master(pros::E_CONTROLLER_MASTER);

 	RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
 	RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
 	LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
 	LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
 	Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Puncher.set_encoder_units(MOTOR_ENCODER_COUNTS);

	Puncher.tare_position();
	while(Puncher.get_position() < 50){
		Puncher.move_velocity(200);
	}

	while(true){

 	AnglePot.calibrate();

	pros::Task Drive(doubleShot, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");

 	while (true) {
		if(master.get_analog(ANALOG_LEFT_Y) == 0 && master.get_analog(ANALOG_LEFT_X) == 0 && master.get_analog(ANALOG_RIGHT_X) == 0){
			LeftF.move_velocity(0);
			LeftB.move_velocity(0);
			RightB.move_velocity(0);
			RightF.move_velocity(0);
		}
		else {//drive code
			LeftF.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_RIGHT_X) + master.get_analog(ANALOG_LEFT_X));
			LeftB.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_RIGHT_X) - master.get_analog(ANALOG_LEFT_X));
			RightF.move(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_RIGHT_X) - master.get_analog(ANALOG_LEFT_X));
			RightB.move(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_RIGHT_X) + master.get_analog(ANALOG_LEFT_X));
		}

		if(master.get_digital(DIGITAL_R1)){
			Lift.move_velocity(200);
		}

		else if(master.get_digital(DIGITAL_R2)){
			Lift.move_velocity(-200);
		}

		else{
			Lift.move_velocity(0);
		}

	 if(master.get_digital(DIGITAL_L1)){
		 Intake.move_velocity(200);
	 }

	 else if(master.get_digital(DIGITAL_L2)){
		 Intake.move_velocity(-200);
	 }

	 else{
		 Intake.move_velocity(0);
		}

	 pros::delay(20);
 		int AngleRead = AnglePot.get_value_calibrated();
 		// printf("Angle Potentiometer reading: %d", AngleRead);

 		//////////////////////////////////////
 	}
}


 		pros::delay(20);
}
