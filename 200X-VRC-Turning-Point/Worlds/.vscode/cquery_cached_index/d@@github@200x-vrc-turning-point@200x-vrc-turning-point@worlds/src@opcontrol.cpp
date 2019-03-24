#include "main.h"
#include "api.h"
#include "pros/rtos.h"
#include "functions.h"


void opcontrol() {
 	pros::Motor Intake(16);
	pros::Motor Lift(5);
  pros::Motor Puncher(6);
  pros::ADIAnalogIn AnglePot (2);
	pros::ADIAnalogIn IntakeLine_Top1 (3);
  pros::ADIGyro gyro (4);

	pros::Controller master(pros::E_CONTROLLER_MASTER);

 	Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);

  pros::Task puncher_task(angle_close_mid,(void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");
  pros::Task drive_task(Drive, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");


  // if(master.get_digital(DIGITAL_DOWN)){
  //   pros::Task puncher_task(&anglerTask_fn);
  // }
  //tasks on buttons



 	AnglePot.calibrate();


 	while (true) {


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

 		int AngleRead = AnglePot.get_value_calibrated();
 		printf("Angle Potentiometer reading: %d\n", AnglePot.get_value_calibrated());
    pros::delay(20);
 		//////////////////////////////////////
 	  }
  }
