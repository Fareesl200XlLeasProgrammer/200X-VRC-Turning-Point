#include "main.h"

void opcontrol() {
	//Motor Definitions
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor RightB(14);

	pros::Motor RightF(12);

	pros::Motor LeftF(13);

	pros::Motor LeftB(11);

	pros::Motor Intake(17);

	pros::Motor Lift(19);

	pros::Motor Flywheel(16);

	pros::Motor Index(18);

	// Gui();//Run the gui

	//Setting Brake Modes
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);

	//Setting Encoder Units for the Flipper
	while (true) {
		Flywheel.move_velocity(135);

    //Drive Code
    RightF.move(master.get_analog(ANALOG_RIGHT_X)*0.8 + master.get_analog(ANALOG_LEFT_Y));
    RightB.move(master.get_analog(ANALOG_RIGHT_X)*0.8 + master.get_analog(ANALOG_LEFT_Y));
    LeftF.move(master.get_analog(ANALOG_RIGHT_X)*0.8 - master.get_analog(ANALOG_LEFT_Y));
    LeftB.move(master.get_analog(ANALOG_RIGHT_X)*0.8 - master.get_analog(ANALOG_LEFT_Y));

		if(master.get_analog(ANALOG_LEFT_Y) < 15 && master.get_analog(ANALOG_LEFT_Y) >-15){
			RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
			RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
			LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
			LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
		}

    //Lift Code
    if(master.get_digital(DIGITAL_R1)){
      Lift.move_velocity(160);
    }

    else if(master.get_digital(DIGITAL_R2)){
      Lift.move_velocity(-160);
    }

    else{
      Lift.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_L1)){
      Intake.move_velocity(-200);
    }
    else if(master.get_digital(DIGITAL_L2)){
      Intake.move_velocity(-200);
      Index.move_velocity(150);
    }

		else if(master.get_digital(DIGITAL_UP)){
			Intake.move_velocity(200);
      Index.move_velocity(-150);
		}

    else{
      Intake.move_velocity(0);
      Index.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_A)){
			Flywheel.move_velocity(127);
			master.rumble("-");
    }

		else if(master.get_digital(DIGITAL_B)){
			Flywheel.move_velocity(115);
			master.rumble("...");
		}


		pros::delay(20);
	}
}
