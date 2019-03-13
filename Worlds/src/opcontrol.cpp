#include "main.h"
#include "AutoVars.cpp"

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
	pros::Motor LeftF(1);
 	pros::Motor LeftB(2);
 	pros::Motor RightF(3, true);
 	pros::Motor RightB(4, true);
 	pros::Motor Intake(5);
 	pros::Motor Puncher(19);
 	pros::Motor Angler(18);
 	pros::ADIAnalogIn AnglePot (1);

 	pros::Controller master(pros::E_CONTROLLER_MASTER);

 	RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
 	RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
 	LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
 	LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Puncher.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Puncher.set_encoder_units(MOTOR_ENCODER_COUNTS);

 	// Puncher.tare_position();
 	// while(Puncher.get_position() < 5){
 	// 	Puncher.move_velocity(200);
 	// }

 	AnglePot.calibrate();

 	while (true) {
 		int AngleRead = AnglePot.get_value_calibrated();
 		// printf("Angle Potentiometer reading: %d", AngleRead);

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

 		if(master.get_digital(DIGITAL_L1)){
 			Intake.move_velocity(200);
 		}

 		else if(master.get_digital(DIGITAL_L2)){
 			Intake.move_velocity(-200);
 		}

 		else{
 			Intake.move_velocity(0);
 		}

 		if(master.get_digital(DIGITAL_B)){
 			while(Angler.get_position() < 110){
 				Angler.move_velocity(70);
 			}
 			Angler.move_velocity(0);
 			Puncher.tare_position();

 			while(Puncher.get_position() < 2000){
 				Puncher.move_velocity(200);
 			}
 			Puncher.move_velocity(0);

 				while(Angler.get_position() > 0){
 					Angler.move_velocity(-200);
 				}
 				Angler.move_velocity(0);

 				Intake.move_relative(-1200, 200);

 				while(Angler.get_position() < 190){
 					Angler.move_velocity(70);
 				}
 				Angler.move_velocity(0);
 				Puncher.tare_position();

 				while(Puncher.get_position() < 2000){
 					Puncher.move_velocity(200);
 				}
 				Puncher.move_velocity(0);

 				while(Angler.get_position() > 0){
 					Angler.move_velocity(-200);
 				}
 				Angler.move_velocity(0);
 		}

 		//Puncher Preset Mid Full Court
 		if(master.get_digital(DIGITAL_Y)){
 			while(Angler.get_position() < 180){
 				Angler.move_velocity(70);
 			}
 			Angler.move_velocity(0);
 			Puncher.tare_position();

 			while(Puncher.get_position() < 2000){
 				Puncher.move_velocity(200);
 			}
 			Puncher.move_velocity(0);

 			while(Angler.get_position() > 0){
 				Angler.move_velocity(-200);
 			}
 			Angler.move_velocity(0);
 		}
 		//////////////////////////////////////

 		//Puncher Preset Top Full Court
 		if(master.get_digital(DIGITAL_X)){
 			while(Angler.get_position() < 110){
 				Angler.move_velocity(70);
 			}
 			Angler.move_velocity(0);
 			Puncher.tare_position();

 			while(Puncher.get_position() < 2000){
 				Puncher.move_velocity(200);
 			}
 			Puncher.move_velocity(0);

 				while(Angler.get_position() > 0){
 					Angler.move_velocity(-200);
 				}
 				Angler.move_velocity(0);

 		}

 		if(master.get_digital(DIGITAL_R1)){
 			Angler.move_velocity(30);
 		}

 		else if(master.get_digital(DIGITAL_R2)){
 			Angler.move_velocity(-30);
 		}

 		else{
 			Angler.move_velocity(0);
 		}

 		if(master.get_digital(DIGITAL_UP)){
 			Puncher.move_velocity(200);
 		}
 		else{
 			Puncher.move_velocity(0);
 		}
 	}


 		pros::delay(20);
}
