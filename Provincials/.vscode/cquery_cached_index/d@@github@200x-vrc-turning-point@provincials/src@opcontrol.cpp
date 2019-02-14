#include "main.h"


void opcontrol() {
	#include "motordef.hpp"

	//Setting Brake Modes
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);

	//Setting Encoder Units for the Flipper
	Flipper.set_encoder_units(MOTOR_ENCODER_ROTATIONS);

	while (true) {
		Flywheel.move_velocity(135);//test 120

    //Drive Code
    Right.move(master.get_analog(ANALOG_RIGHT_X)*0.5 - master.get_analog(ANALOG_LEFT_Y));
    Right2.move(master.get_analog(ANALOG_RIGHT_X)*0.5 - master.get_analog(ANALOG_LEFT_Y));
    Left.move(master.get_analog(ANALOG_RIGHT_X)*0.5 + master.get_analog(ANALOG_LEFT_Y));
    Left2.move(master.get_analog(ANALOG_RIGHT_X)*0.5 + master.get_analog(ANALOG_LEFT_Y));

		if(master.get_analog(ANALOG_RIGHT_X) ==0){
			Right.set_brake_mode(MOTOR_BRAKE_HOLD);
			Right2.set_brake_mode(MOTOR_BRAKE_HOLD);
			Left.set_brake_mode(MOTOR_BRAKE_HOLD);
			Left2.set_brake_mode(MOTOR_BRAKE_HOLD);
		}


    //Lift Code
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
      Intake.move_velocity(-200);
    }
    else if(master.get_digital(DIGITAL_L2)){
      Intake.move_velocity(-200);
      Index.move_velocity(200);
    }
		else if(master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_L2)){
			Intake.move_velocity(200);
      Index.move_velocity(200);
		}

    else if(master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_L2)){
      Intake.move_velocity(200);
      Index.move_velocity(200);
    }
    else{
      Intake.move_velocity(0);
      Index.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_A)){
			Flywheel.move_velocity(140);
    }

		if(master.get_digital(DIGITAL_B)){
			Flywheel.move_velocity(120);
		}



		pros::delay(20);
	}
}
