#include "main.h"
#include "api.h"
#include "pros/rtos.h"


void doubleShot(void*){
 	pros::Motor Puncher(6, true);
 	pros::Motor Angler(15);
	pros::Motor Lift(5);
  pros::Motor Intake(16, true);
	pros::ADIAnalogIn AnglePot (2);
 	pros::Controller master(pros::E_CONTROLLER_MASTER);

  int angleSpeed = 30;//remove this variable later
  int aAngleSpeed = 10;
  int yAngleSpeed = 30;
  int puncherSpeed = 200;
  int intakeSpeed = 200;
  int presetIntake = 1000;

  int AngleRead = AnglePot.get_value_calibrated();
  printf("Angle Potentiometer reading: %d", AngleRead);

	Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
	Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
	Puncher.set_encoder_units(MOTOR_ENCODER_COUNTS);

	AnglePot.calibrate();

	while(true){
    //REGULAR PRESETS
 		if(master.get_digital(DIGITAL_Y)){//middle        IF BROKEN CHANGE TO 105
 			while(AnglePot.get_value_calibrated() < 200){
 				Angler.move_velocity(yAngleSpeed);
 			}
 			Angler.move_velocity(0);
 			Puncher.tare_position();

      pros::delay(50);

 			while(Puncher.get_position() < 2100){
 				Puncher.move_velocity(puncherSpeed);
 			}
 			Puncher.move_velocity(0);

 				while(Angler.get_position() > 0){
 					Angler.move_velocity(-yAngleSpeed);
 				}
 				Angler.move_velocity(0);

        Intake.tare_position();
        while(Intake.get_position() < presetIntake){
          Intake.move_velocity(intakeSpeed);
        }
        Intake.move_velocity(0);

 		}


		if(master.get_digital(DIGITAL_A)){//top
 			while(AnglePot.get_value_calibrated() < 100){//53
 				Angler.move_velocity(aAngleSpeed);
 			}
 			Angler.move_velocity(0);
 			Puncher.tare_position();

      pros::delay(50);

 			while(Puncher.get_position() < 2100){
 				Puncher.move_velocity(puncherSpeed);
 			}
 			Puncher.move_velocity(0);

 				while(Angler.get_position() > 0){
 					Angler.move_velocity(-aAngleSpeed);
 				}
 				Angler.move_velocity(0);

        Intake.tare_position();
        while(Intake.get_position() < presetIntake){
          Intake.move_velocity(intakeSpeed);
        }
        Intake.move_velocity(0);
		}

    if(master.get_digital(DIGITAL_X)){//default
			Puncher.tare_position();
			while(Puncher.get_position() < 2100){
 				Puncher.move_velocity(puncherSpeed);
 			}
 			Puncher.move_velocity(0);

      Intake.tare_position();
      while(Intake.get_position() < presetIntake){
        Intake.move_velocity(intakeSpeed);
      }
      Intake.move_velocity(0);
 		}

    //TOP PLATFORM PRESETS
    if(master.get_digital(DIGITAL_UP)){//top yellow platform
 			while(AnglePot.get_value_calibrated() < 110){
 				Angler.move_velocity(aAngleSpeed);
 			}
 			Angler.move_velocity(0);
 			Puncher.tare_position();

 			while(Puncher.get_position() < 2100){
 				Puncher.move_velocity(puncherSpeed);
 			}
 			Puncher.move_velocity(0);

 				while(Angler.get_position() > 0){
 					Angler.move_velocity(-aAngleSpeed);
 				}
 				Angler.move_velocity(0);

        Intake.tare_position();
        while(Intake.get_position() < presetIntake){
          Intake.move_velocity(intakeSpeed);
        }
        Intake.move_velocity(0);
		}

    if(master.get_digital(DIGITAL_DOWN)){// middle yellow platform
      while(AnglePot.get_value_calibrated() < 210){//105
        Angler.move_velocity(yAngleSpeed);
      }
      Angler.move_velocity(0);
      Puncher.tare_position();

      while(Puncher.get_position() < 2100){
        Puncher.move_velocity(puncherSpeed);
      }
      Puncher.move_velocity(0);

        while(Angler.get_position() > 0){
          Angler.move_velocity(-yAngleSpeed);
        }
        Angler.move_velocity(0);

        Intake.tare_position();
        while(Intake.get_position() < presetIntake){
          Intake.move_velocity(intakeSpeed);
        }
        Intake.move_velocity(0);
    }

    //ALLIANCE PLATFORM PRESETS
    //INSERT ALLIANCE PRESETS HERE





























    //DOUBLE SHOTS
    else if(master.get_digital(DIGITAL_LEFT)){// Back Double Shot
      while(AnglePot.get_value_calibrated() < 97){//
        Angler.move_velocity(angleSpeed);
      }
      Angler.move_velocity(0);
      Puncher.tare_position();

      while(Puncher.get_position() < 2100){
        Puncher.move_velocity(puncherSpeed);
        Intake.move_velocity(-intakeSpeed);
      }
      Puncher.move_velocity(0);

        while(Angler.get_position() > 0){
          Angler.move_velocity(-angleSpeed);
        }
        Angler.move_velocity(0);

        Puncher.tare_position();

        while(AnglePot.get_value_calibrated() < 10){//53
   				Angler.move_velocity(angleSpeed);
   			}
   			Angler.move_velocity(0);
   			Puncher.tare_position();

   			while(Puncher.get_position() < 2100){
   				Puncher.move_velocity(puncherSpeed);
   			}
   			Puncher.move_velocity(0);

   				while(Angler.get_position() > 0){
   					Angler.move_velocity(-angleSpeed);
   				}
   				Angler.move_velocity(0);
          Intake.move_velocity(0);
    }

    else if(master.get_digital(DIGITAL_B)){
        while(AnglePot.get_value_calibrated() < 97){// double shot from front
          Angler.move_velocity(40);
        }
        Angler.move_velocity(0);
        Puncher.tare_position();

        while(Puncher.get_position() < 2100){
          Puncher.move_velocity(puncherSpeed);
          Intake.move_velocity(intakeSpeed);
        }
        Puncher.move_velocity(0);

          while(Angler.get_position() > 0){
            Angler.move_velocity(-angleSpeed);
          }
          Angler.move_velocity(0);

          Puncher.tare_position();

          while(Puncher.get_position() < 2100){
            Puncher.move_velocity(puncherSpeed);
          }
          Puncher.move_velocity(0);
          Intake.move_velocity(0);
 		}

    if(master.get_digital(DIGITAL_RIGHT)){// TEST
      while(AnglePot.get_value_calibrated() < 1000){//105
        Angler.move_velocity(angleSpeed);
      }
      Angler.move_velocity(0);
      Puncher.tare_position();

      while(Puncher.get_position() < 2100){
        Puncher.move_velocity(puncherSpeed);
      }
      Puncher.move_velocity(0);

        while(Angler.get_position() > 0){
          Angler.move_velocity(-angleSpeed);
        }
        Angler.move_velocity(0);
    }

 		else{
        Puncher.move_velocity(0);
 		}
	}
}


void opcontrol() {
	pros::Motor LeftF(10);
 	pros::Motor LeftB(1);
 	pros::Motor RightF(20, true);
 	pros::Motor RightB(11, true);
  pros::Motor Intake(16);
 	pros::Motor Puncher(6, true);
 	pros::Motor Angler(15);
	pros::Motor Lift(5);
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

  int angleSpeed = 40;
  int puncherSpeed = 200;
  int intakeSpeed = 200;
  int liftSpeed = 200;

	Puncher.tare_position();
	Puncher.move_absolute(800, 200);

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
			Lift.move_velocity(liftSpeed);
		}

		else if(master.get_digital(DIGITAL_R2)){
			Lift.move_velocity(-liftSpeed);
		}

		else{
			Lift.move_velocity(0);
		}

	 if(master.get_digital(DIGITAL_L1)){
		 Intake.move_velocity(-intakeSpeed);
	 }

	 else if(master.get_digital(DIGITAL_L2)){
		 Intake.move_velocity(intakeSpeed);
	 }

	 else{
		 Intake.move_velocity(0);
		}

	 pros::delay(20);
 	}
}


 		pros::delay(20);
}
