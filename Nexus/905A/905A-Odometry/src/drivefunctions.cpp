#include "main.h"
#include "motorDefs.hpp"
#include "drivefunctions.hpp"
#include "utilities.hpp"

void drive(void*)
{
    int tempL;
    int tempR;
  while(true)
  {
    tempL = master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X);
    tempR = master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X);

    LPower = int(abs(pow(tempL, 2) / 127)) * sgn(tempL);
    RPower = int(abs(pow(tempL, 2) / 127)) * sgn(tempR);

    LF.move(tempL);
    RF.move(tempR);
    LB.move(tempL);
    RB.move(tempR);
    pros::delay(20);
  }
}

void arm(void*)
{
  while(true)
  {
    if(master.get_digital(DIGITAL_L1)) {
      armPos = controlArm;
    }
    else if(master.get_digital(DIGITAL_L2)) {
      armPos = controlArm;
    }
    else if(master.get_digital(DIGITAL_B)) {
      armPos = Intake;
    }
    else if(master.get_digital(DIGITAL_Y)) {
      armPos = lowTower;
    }
    else if(master.get_digital(DIGITAL_X)) {
      armPos = midTower;
    }
    else if(master.get_digital(DIGITAL_A)) {
      armPos = stopArm;
    }
    else {
      armPos = stopArm;
    }
    pros::delay(20);
  }
}

void intake(void*)
{
  while(true)
  {
    if(master.get_digital(DIGITAL_R1)) {IntakeL.move(127); IntakeR.move(127);}
    else if(master.get_digital(DIGITAL_R2)) {IntakeL.move(-127); IntakeR.move(-127);}
    else {IntakeL.move_velocity(0); IntakeR.move_velocity(0); IntakeL.set_brake_mode(MOTOR_BRAKE_HOLD); IntakeR.set_brake_mode(MOTOR_BRAKE_HOLD); }
    pros::delay(20);
  }
}

void tilter(void*)
{
    int Pow, temp;
  while(true)
  {
    temp = master.get_analog(ANALOG_RIGHT_Y);
    Pow = int((pow(temp, 2)) / 127) * sgn(temp);
    tilt.move(Pow);
    tilt.set_brake_mode(MOTOR_BRAKE_HOLD);

    pros::delay(20);
  }
}

void liftTo(void*)
{
  double  pwr, error, totalError, lastError, P, D;
  int target, time = 0;

  while(true)
  {
    switch(armPos)
    {
      case stopArm:
        Arm.move_velocity(0);
        Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
      break;

      case controlArm:
        if(master.get_digital(DIGITAL_L1))
        {
            Arm.move(127);
        }
        else if(master.get_digital(DIGITAL_L2))
        {
            Arm.move(-127);
        }

        else if(master.get_digital(DIGITAL_B))
        {
            Arm.move(-127);
        }
        break;

      case Intake:
        time = pros::millis()+500;
         target = 0;
         do{
             error = target - ArmEncoder.get_value();
             Arm.move(-100);

             pros::delay(20);

         }while(pros::millis() < time);
         Arm.move(0);

      break;

      case lowTower:
        target = 340;
        do{
		totalError += error;
		lastError = error;
		error = target - ArmEncoder.get_value();

		P = error;
		D = error-lastError;

		pwr = P+D;
        if(trayPot.get_value_calibrated() < 2050)
        {
            tilt.move(80);
	        Arm.move_velocity(pwr);
        }
        else
        {
            tilt.move_velocity(0);
            tilt.set_brake_mode(MOTOR_BRAKE_HOLD);

	        Arm.move_velocity(pwr);
        }

        if(master.get_digital(DIGITAL_A)){
          armPos = stopArm;
        }

		pros::delay(20);

	}while(!(error <= 10 && error >= -10));
      break;

      case midTower:
        target = 450;
        Arm.set_brake_mode(MOTOR_BRAKE_COAST);
        do{
		totalError += error;
		lastError = error;
		error = target - ArmEncoder.get_value();

		P = error;
		D = error-lastError;

		pwr = P+D;
        if(trayPot.get_value_calibrated() < 2050)
        {
            tilt.move(80);
	        Arm.move_velocity(pwr);
        }
        else
        {
            tilt.move_velocity(0);
            tilt.set_brake_mode(MOTOR_BRAKE_HOLD);
	        Arm.move_velocity(pwr);
        }
		pros::delay(20);

	}while(!(error <= 10 && error >= -10));
      break;

      case highTower:
        target = 620;
        Arm.set_brake_mode(MOTOR_BRAKE_COAST);
        do{
		totalError += error;
		lastError = error;
		error = target - ArmEncoder.get_value();

		P = error;
		D = error-lastError;

		pwr = P+D;
        if(trayPot.get_value_calibrated() < 2050)
        {
            tilt.move(80);
	        Arm.move_velocity(pwr);
        }
        else
        {
            tilt.move_velocity(0);
            tilt.set_brake_mode(MOTOR_BRAKE_HOLD);
	        Arm.move_velocity(pwr);
        }
        if(master.get_digital(DIGITAL_A)){
          armPos = stopArm;
        }
		pros::delay(20);

	}while(!(error <= 10 && error >= -10));
      break;
    }
  }
}
