#include "main.h"
#include "api.h"
#include "pros/rtos.h"
#include "functions.h"

void puncherTask(void*){//function to reset puncher
  pros::Motor Angler(15);
  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  pros::ADIPotentiometer AnglePot(2);
  pros::Motor Puncher(6, true);
  pros::Motor Intake(16, true);

  pros::Controller master(pros::E_CONTROLLER_MASTER);

  while(true){
    if(master.get_digital(DIGITAL_X)){
      while(AnglePot.get_value_calibrated() > 0){
        Angler.move_velocity(-200);
      }
      Angler.move_velocity(0);
    }
    if(master.get_digital(DIGITAL_Y)){
      while(AnglePot.get_value_calibrated() < 130){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);

      while(AnglePot.get_value_calibrated() > 130){
        Angler.move_velocity(-200);
      }
      Angler.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_B)){

      while(Puncher.get_position() < 1800){
        pros::delay(1);
      }

      while(AnglePot.get_value_calibrated() < 120){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_UP)){
      while(AnglePot.get_value_calibrated() > 5){
        Angler.move_velocity(-200);
      }
      Angler.move_velocity(0);

        while(AnglePot.get_value_calibrated() < 5){
          Angler.move_velocity(200);
        }
        Angler.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_DOWN)){
      while(AnglePot.get_value_calibrated() < 160){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);
    }

  }

    pros::delay(20);
}

void Drive(void*){
  pros::Motor LeftF(10);
  pros::Motor LeftB(1);
  pros::Motor RightF(20, true);
  pros::Motor RightB(11, true);
  pros::Motor Puncher(6, true);


  pros::Controller master(pros::E_CONTROLLER_MASTER);

  RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
  LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
  LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
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

    pros::delay(20);
  }

}


void opcontrol() {

  pros::Motor LeftF(10);
pros::Motor LeftB(1);
pros::Motor RightF(20, true);
pros::Motor RightB(11, true);
pros::Motor Puncher(6, true);
pros::Motor Angler(15);
pros::Motor Lift(5);
pros::Motor Intake(16, true);
pros::ADIAnalogIn IntakeLine_Top1 (3);
pros::ADIGyro gyro (4);
pros::ADIPotentiometer AnglePot(2);
pros::Controller master(pros::E_CONTROLLER_MASTER);

 	RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
 	RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
 	LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
 	LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
 	Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
 	Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);

	Puncher.tare_position();
	Puncher.move_absolute(800, 200);

  if(Puncher.get_position() < 900){
    while(Puncher.get_position() < 900){
      Puncher.move_velocity(200);
    }

    Puncher.move_velocity(0);
  }
  pros::Task Drive_task(Drive, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");
  pros::Task punchTask(puncherTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");

	while(true){
    AnglePot.calibrate();

   	while (true) {

      Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
        if(master.get_digital(DIGITAL_X)){
          Puncher.tare_position();
          while(Puncher.get_position() < 1800){
            Puncher.move_velocity(200);
          }
          Puncher.move_velocity(0);

          Intake.tare_position();
          while(Intake.get_position() < 1000){
            Intake.move_velocity(200);
          }
          Intake.move_velocity(0);
        }

        if(master.get_digital(DIGITAL_Y)){
          Puncher.tare_position();
          while(Puncher.get_position() < 1800){
            Puncher.move_velocity(200);
          }
          Puncher.move_velocity(0);

          Intake.tare_position();
          while(Intake.get_position() < 1000){
            Intake.move_velocity(200);
          }
          Intake.move_velocity(0);
        }

        if(master.get_digital(DIGITAL_A)){
          Puncher.tare_position();
          while(Puncher.get_position() < 1800){
            Puncher.move_velocity(200);
          }
          Puncher.move_velocity(0);

          Intake.tare_position();
          while(Intake.get_position() < 1000){
            Intake.move_velocity(200);
          }
          Intake.move_velocity(0);
        }
        if(master.get_digital(DIGITAL_B)){
          Puncher.tare_position();

          while(Puncher.get_position() < 1800){
            Puncher.move_velocity(200);
          }
          Puncher.move_velocity(0);

          Puncher.tare_position();

          while(AnglePot.get_value_calibrated() < 70){
            pros::delay(1);
          }

          Intake.tare_position();
          while(Intake.get_position() < 1000){
            Intake.move_velocity(200);
          }
          Intake.move_velocity(0);

          while(Puncher.get_position() < 1800){
            Puncher.move_velocity(200);
          }
          Puncher.move_velocity(0);
        }

        if(master.get_digital(DIGITAL_UP)){
          Puncher.tare_position();
          while(Puncher.get_position() < 1800){
            Puncher.move_velocity(200);
          }
          Puncher.move_velocity(0);

          Intake.tare_position();
          while(Intake.get_position() < 1000){
            Intake.move_velocity(200);
          }
          Intake.move_velocity(0);
        }

        if(master.get_digital(DIGITAL_DOWN)){
          Puncher.tare_position();
          while(Puncher.get_position() < 1800){
            Puncher.move_velocity(200);
          }
          Puncher.move_velocity(0);

          Intake.tare_position();
          while(Intake.get_position() < 1000){
            Intake.move_velocity(200);
          }
          Intake.move_velocity(0);
        }

        else{
          Puncher.move_velocity(0);
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
  		 Intake.move_velocity(-200);
  	 }

  	 else if(master.get_digital(DIGITAL_L2)){
  		 Intake.move_velocity(200);
  	 }
  	 else{
  		 Intake.move_velocity(0);
  		}

  	 pros::delay(20);
   	}
  }
}
