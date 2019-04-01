#include "main.h"
#include "api.h"
#include "pros/rtos.h"
#include "functions.h"
#include "motorDefs.h"
void PIDTurn(double target){
  // pros::Motor Intake(16);
	// pros::Motor Lift(5);
	// pros::ADIAnalogIn IntakeLine_Top1 (3);
  // pros::ADIGyro gyro (4);
  //
  // pros::Motor LeftF(10);
  // pros::Motor LeftB(1);
  // pros::Motor RightF(20, true);
  // pros::Motor RightB(11, true);
  //
	// pros::Controller master(pros::E_CONTROLLER_MASTER);
  gyro.reset();

  double kP = 0.3;
  double kI = 0.00000003;
  double kD = 4; /*was 1.35 test with current value if improvement is seen keep value*/
  double error;
  double totalError;
  double lastError;
  double pwr;
  do{
    double current = gyro.get_value();
    error = target - current;
    double P = error * kP;
    totalError += error;
    lastError = error;
    double I = kI * totalError;
    double D = kD * (error - lastError);
    pwr = P+I+D;
    LeftF.move_velocity(pwr);
    LeftB.move_velocity(pwr);
    RightF.move_velocity(-pwr);
    RightB.move_velocity(-pwr);
    if(error ==0){
      I = 0;
    }
  } while(!(error<= 5 && error>= -5));
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
}

void PIDDrive(double target){
  // pros::Motor Intake(16);
	// pros::Motor Lift(5);
	// pros::ADIAnalogIn IntakeLine_Top1 (3);
  // pros::ADIGyro gyro (4);
  //
  // pros::Motor LeftF(10);
  // pros::Motor LeftB(1);
  // pros::Motor RightF(20, true);
  // pros::Motor RightB(11, true);

  double kP = 0.3;
  double kI = 0.000003;
  double kD = 1.35;
  double errorL, totalErrorL, lastErrorL, errorR, totalErrorR, lastErrorR,pwrL,pwrR,CurrentL, CurrentR;

  do{
    CurrentL = LeftF.get_position();
    CurrentR = RightF.get_position();
    // target = 800; /*Test this function without this line*/
    errorL = target - CurrentL;
    errorR = target - CurrentR;
    totalErrorL += errorL;
    totalErrorR += errorR;
    lastErrorL = errorL;
    lastErrorR = errorR;

    double Pl, Il, Dl, Pr, Ir, Dr;
    Pl = errorL*kP;

    Il = kI * totalErrorL;

    Dl = kD * (errorL - lastErrorL);

    Pr = errorR*kP;

    Ir = kI * totalErrorR;

    Dr = kD * (errorR - lastErrorR);

    pwrL = Pl + Il + Dl;
    pwrR = Pr + Ir + Dr;

    LeftF.move_velocity(pwrL);
    LeftB.move_velocity(pwrL);

    RightF.move_velocity(pwrR);
    RightB.move_velocity(pwrR);
  }while(!(errorL<= 5 && errorL>= -5 && errorR<= 5 && errorR>= -5));
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);

  RightF.move_velocity(0);
  RightB.move_velocity(0);

}

void anglePID(double target){
  // pros::Motor Angler(15);
  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  // pros::ADIPotentiometer anglePot(2);

  double current;
  double kP = 0.25;
  double kI = 0.000000;
  double kD = 0.75;
  double error;
  double totalError;
  double lastError;
  double pwr;

  do{
    current = anglePot.get_value();
    error = target - current;

    totalError += error;
    lastError = error;

    double P = kP * error;
    double I = kI * totalError;
    double D = kD * (error - lastError);

    pwr = P+I+D;
    Angler.move_velocity(pwr);

  }while(!(error<= 5 && error>= -5));

  Angler.move_velocity(0);

}

void opcontrol() {

 	Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);
  // PIDTurn(900);
  // pros::delay(1000);
  // PIDDrive(800);
  pros::Task puncher_task(puncherTask,(void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");
  pros::Task drive_task(Drive, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");

  while(true){

    if(master.get_digital(DIGITAL_X)){
      Puncher.move_relative(1200, 200);
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

    if(master.get_digital(DIGITAL_Y)){
      Puncher.tare_position();
      Intake.tare_position();
      anglePID(2150);
      while(Puncher.get_position() < 1200){
        Puncher.move_velocity(200);
      }
      Puncher.move_velocity(0);
      while(Intake.get_position() < 800){
        Intake.move_velocity(200);
      }
      Intake.move_velocity(0);

    }

    pros::delay(20);
  }
}
