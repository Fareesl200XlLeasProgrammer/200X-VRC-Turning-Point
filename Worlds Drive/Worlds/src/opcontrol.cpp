#include "main.h"
#include "api.h"
#include "pros/rtos.h"
#include "functions.h"

void PIDTurnDrive(double target){
  pros::Motor Intake(16);
	pros::Motor Lift(5);
  pros::ADIAnalogIn IntakeLine_Top1 (3);
  pros::ADIGyro gyro (4);
  pros::Motor LeftF(10);
  pros::Motor LeftB(1);
  pros::Motor RightF(20, true);
  pros::Motor RightB(11, true);

	pros::Controller master(pros::E_CONTROLLER_MASTER);

  double kP = 0.3;
  double kI = 0.00000003;
  double kD = 20; /*was 1.35 test with current value if improvement is seen keep value*/
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

    if(error<= 1 && error>= -1){
      break;
    }
  } while(!(error<= 1 && error>= -1));

  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
}

void puncherTask(void*){//function to reset puncher
  pros::Motor Angler(15);
  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  pros::ADIPotentiometer AnglePot(2);
  pros::Motor Puncher(6, true);
  pros::Motor Intake(16, true);

  pros::Controller master(pros::E_CONTROLLER_MASTER);

  int button = 0;

  while(true){
    if(master.get_digital(DIGITAL_X)){
      button = 0;
      while(AnglePot.get_value_calibrated() > 0){
        Angler.move_velocity(-200);
      }
      Angler.move_velocity(0);
    }
    if(master.get_digital(DIGITAL_Y) && button == 3){
      button = 2;

      while(AnglePot.get_value_calibrated() > 120){
        Angler.move_velocity(-200);
      }
      Angler.move_velocity(0);
    }
    else if(master.get_digital(DIGITAL_Y) && button < 3){
      button = 2;
      while(AnglePot.get_value_calibrated() < 120){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_A)){

      button = 2;

      Puncher.tare_position();
      while(Puncher.get_position() < 1850){
        pros::delay(1);
      }

      while(AnglePot.get_value_calibrated() < 120){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_UP) && button < 1){
      button = 1;
      while(AnglePot.get_value_calibrated() < 20){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_UP) && button > 1){
      button = 1;
    while(AnglePot.get_value_calibrated() > 20){
      Angler.move_velocity(-200);
  }
  Angler.move_velocity(0);
}


    if(master.get_digital(DIGITAL_DOWN)){
      button = 3;
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
LeftF.move((master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_RIGHT_X) + master.get_analog(ANALOG_LEFT_X))*1.6);
LeftB.move((master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_RIGHT_X) - master.get_analog(ANALOG_LEFT_X))*1.6);
RightF.move((master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_RIGHT_X) - master.get_analog(ANALOG_LEFT_X))*1.6);
RightB.move((master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_RIGHT_X) + master.get_analog(ANALOG_LEFT_X))*1.6);
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

  // if(Puncher.get_position() < 900){
  //   while(Puncher.get_position() < 900){
  //     Puncher.move_velocity(200);
  //   }
  //
  //   Puncher.move_velocity(0);
  // }
  pros::Task Drive_task(Drive, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");
  pros::Task punchTask(puncherTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");

while(true){
    AnglePot.calibrate();

    while (true) {

      Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
        if(master.get_digital(DIGITAL_X)){
          Puncher.tare_position();
          while(Puncher.get_position() < 1850){
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
          while(Puncher.get_position() < 1850){
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
          gyro.reset();
          PIDTurnDrive(250);
        }
        if(master.get_digital(DIGITAL_A)){
          Puncher.tare_position();

          while(Puncher.get_position() < 1850){
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

          while(Puncher.get_position() < 1850){
            Puncher.move_velocity(200);
          }
          Puncher.move_velocity(0);
        }

        if(master.get_digital(DIGITAL_UP)){
          Puncher.tare_position();
          while(Puncher.get_position() < 1850){
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
          while(Puncher.get_position() < 1850){
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
