#include "main.h"

void opcontrol() {
	int FlywheelVel = 135;
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

	//Setting Brake Modes
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);

	//Setting Encoder Units for the Flipper
	Flipper.set_encoder_units(MOTOR_ENCODER_ROTATIONS);

	while (true) {
		Flywheel.move_velocity(FlywheelVel);

    //Drive Code
    Right.move(master.get_analog(ANALOG_RIGHT_X)*0.8 - master.get_analog(ANALOG_LEFT_Y));
    Right2.move(master.get_analog(ANALOG_RIGHT_X)*0.8 - master.get_analog(ANALOG_LEFT_Y));
    Left.move(master.get_analog(ANALOG_RIGHT_X)*0.8 + master.get_analog(ANALOG_LEFT_Y));
    Left2.move(master.get_analog(ANALOG_RIGHT_X)*0.8 + master.get_analog(ANALOG_LEFT_Y));

		if(master.get_analog(ANALOG_LEFT_Y) < 15 && master.get_analog(ANALOG_LEFT_Y) >-15){
			Right.set_brake_mode(MOTOR_BRAKE_HOLD);
			Right2.set_brake_mode(MOTOR_BRAKE_HOLD);
			Left.set_brake_mode(MOTOR_BRAKE_HOLD);
			Left2.set_brake_mode(MOTOR_BRAKE_HOLD);
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
			Index.move_relative(500, 200);
			Flywheel.move_velocity(120);
			pros::delay(3000);
			Intake.move_relative(-2000, 200);
			Index.move_relative(2000, 200);
    }

		else if(master.get_digital(DIGITAL_B)){
			Flywheel.move_velocity(115);
			master.rumble("...");
		}


		pros::delay(20);
	}
}
