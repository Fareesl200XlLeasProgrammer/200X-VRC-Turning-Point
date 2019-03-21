#include "../include/main.h"
#include "../include/api.h"
#include "../include/pros/rtos.h"

void drive_subsys(void*){
	pros::Motor LeftF(10, true);
 	pros::Motor LeftB(1, true);
 	pros::Motor RightF(20, true);
 	pros::Motor RightB(11, true);
 	pros::Motor Intake(16, true);
 	pros::Motor Puncher(18, true);
 	pros::Motor Angler(15, true);
	pros::Motor Lift(17, true);
 	pros::ADIAnalogIn AnglePot (2);
	pros::ADIAnalogIn IntakeLine_Top1 (3);

 	pros::Controller master(pros::E_CONTROLLER_MASTER);

	RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
	RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
	LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
	LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
	Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
	Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
	Angler.set_brake_mode(MOTOR_BRAKE_COAST);
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);
	Puncher.set_encoder_units(MOTOR_ENCODER_COUNTS);

	while(true){
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

	if(master.get_digital(DIGITAL_UP)){
		Puncher.move_velocity(200);
	}
	else{
		Puncher.move_velocity(0);
	}
pros::delay(20);

}


}


void opcontrol() {
	pros::Motor LeftF(10);
 	pros::Motor LeftB(1);
 	pros::Motor RightF(20, true);
 	pros::Motor RightB(11, true);
 	pros::Motor Intake(16);
 	pros::Motor Puncher(21);
 	pros::Motor Angler(18);
	pros::Motor Lift(17);
 	pros::ADIAnalogIn AnglePot (2);
	pros::ADIAnalogIn IntakeLine_Top1 (3);

	pros::Controller master(pros::E_CONTROLLER_MASTER);

 	RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
 	RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
 	LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
 	LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
 	Angler.set_brake_mode(MOTOR_BRAKE_COAST);
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Puncher.set_encoder_units(MOTOR_ENCODER_COUNTS);

 	Puncher.tare_position();
 	while(Puncher.get_position() < 50){
 		Puncher.move_velocity(200);
 	}

 	AnglePot.calibrate();

	pros::Task Drive(drive_subsys, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");

 	while (true) {
 		int AngleRead = AnglePot.get_value_calibrated();
 		// printf("Angle Potentiometer reading: %d", AngleRead);

 		if(master.get_digital(DIGITAL_B)){
			Puncher.tare_position();
			while(Puncher.get_position() < 2000){
 				Puncher.move_velocity(200);
 			}
 			Puncher.move_velocity(0);

			while(Angler.get_position() < 150){
 				Angler.move_velocity(70);
 			}
 			Angler.move_velocity(0);

 			Puncher.tare_position();
 			while(Puncher.get_position() < 3000){
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
 		if(master.get_digital(DIGITAL_Y)){
			Angler.tare_position();
 			while(Angler.get_position() < 140){
 				Angler.move_velocity(200);
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

 		if(master.get_digital(DIGITAL_X)){
			Puncher.tare_position();
			while(Puncher.get_position() < 2000){
 				Puncher.move_velocity(200);
 			}
 			Puncher.move_velocity(0);
 		}
 		else{
 			Puncher.move_velocity(0);
 		}
 	}


 		pros::delay(20);
}
