#include "main.h"
#include "okapi/api.hpp"
#include "functions.h"
//#include "Autos.h"
#include "AutoVars.cpp"

using namespace okapi;
using namespace pros;

void PIDTurn(double target){
  pros::Motor Intake(16);
	pros::Motor Lift(5);
	 pros::ADIAnalogIn IntakeLine_Top1 (3);
  pros::ADIGyro gyro (4);
  pros::Motor LeftF(10);
  pros::Motor LeftB(1);
  pros::Motor RightF(20, true);
  pros::Motor RightB(11, true);

	pros::Controller master(pros::E_CONTROLLER_MASTER);
  gyro.reset();

  double kP = 0.3;
  double kI = 0.00000003;
  double kD = 1.35; /*was 1.35 test with current value if improvement is seen keep value*/
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

    if(error<= 5 && error>= -5){
      break;
    }
  } while(!(error<= 5 && error>= -5));

  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
}

void PIDDrive(double target){
   pros::Motor Intake(16);
	 pros::Motor Lift(5);
	 pros::ADIAnalogIn IntakeLine_Top1 (3);
   pros::ADIGyro gyro (4);

   pros::Motor LeftF(10);
   pros::Motor LeftB(1);
   pros::Motor RightF(20, true);
   pros::Motor RightB(11, true);

  double kP = 0.0009;
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

  if(errorL<= 5 && errorL>= -5 || errorR<= 5 && errorR>= -5){
    break;
  }

  }while(!(errorL<= 5 && errorL>= -5 && errorR<= 5 && errorR>= -5));
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);

  RightF.move_velocity(0);
  RightB.move_velocity(0);

}

void PIDAngle(double target){
  pros::Motor Angler(15);
  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  pros::ADIPotentiometer anglePot(2);

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

void Intake(int target){
  pros::Motor Intake(16, true);

  Intake.set_brake_mode(MOTOR_BRAKE_HOLD);

  int intakeSpeed = 200;

  Intake.tare_position();
  while (Intake.get_position() < target){
    Intake.move_velocity(intakeSpeed);
  }
  Intake.move_velocity(0);

}

void Puncher(int target){
  pros::Motor Puncher(6);

  Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
  Puncher.set_encoder_units(MOTOR_ENCODER_COUNTS);

  int puncherSpeed = 200;

  Puncher.tare_position();
  while (Puncher.get_position() < target){
    Puncher.move_velocity(puncherSpeed);
  }
  Puncher.move_velocity(0);
}

void Lift(int target){
  pros::Motor Lift(5, true);

  Lift.set_brake_mode(MOTOR_BRAKE_HOLD);

  int liftSpeed = 200;

  Lift.tare_position();
  while (Lift.get_position() < target){//get ball from cap
    Lift.move_velocity(liftSpeed);
  }
  Lift.move_velocity(0);
}

void Shoot(){
  pros::Motor Puncher(6, true);
  pros::Motor Angler(15);
  pros::Motor Lift(5);
  pros::Motor Intake(16, true);
  pros::ADIAnalogIn AnglePot (2);

  Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
  Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  Lift.set_brake_mode(MOTOR_BRAKE_HOLD);
  Puncher.set_encoder_units(MOTOR_ENCODER_COUNTS);

  double aAngleSpeed = 10;
  double yAngleSpeed = 30;
  double puncherSpeed = 200;
  double intakeSpeed = 200;
  double presetIntake = 1000;

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
  }

  void Scrape(){
    pros::Motor IntakeMotor(16);

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    IntakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);

    int angleSpeed = 40;
    int puncherSpeed = 200;
    int intakeSpeed = 200;
    int liftSpeed = 200;

    double DTF = 343.774678;//degrees to feet

    IntakeMotor.move_velocity(intakeSpeed);

    Lift(400);

    PIDDrive(1*DTF);

    Lift(-400);

    PIDDrive(-1*DTF);

    IntakeMotor.move_velocity(0);

    Intake(800);
  }



void autonomous() {

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

   //creating the chassis that are used in the auton
   auto myChassis = ChassisControllerFactory::create(
     {1, 10}, // Left motors
     {-20, -11},   // Right motorszz
     AbstractMotor::gearset::red, // Torque gearset
     {12_in, 18.5_in} // 4 inch wheels, 12.5 inch wheelbase width
   );

   auto profileController = AsyncControllerFactory::motionProfile(

     1.05,  // Maximum linear velocity of the Chassis in m/s
     2.0,  // Maximum linear acceleration of the Chassis in m/s/s
     10.0, // Maximum linear jerk of the Chassis in m/s/s/s
     myChassis // Chassis Controller
   );


  LeftF.tare_position();
  RightF.tare_position();
  RightB.tare_position();
  LeftB.tare_position();

  Intake.move_velocity(-200);
  Lift.move_absolute(-500, 200);
  while(LeftF.get_position() < 400){
    LeftF.move_velocity(50);
    LeftB.move_velocity(50);
    RightF.move_velocity(50);
    RightB.move_velocity(50);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);

    pros::delay(1000);
  Intake.move_velocity(0);
  while(LeftF.get_position() > 310){
    LeftF.move_velocity(-50);
    LeftB.move_velocity(-50);
    RightF.move_velocity(-50);
    RightB.move_velocity(-50);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
  PIDTurn(-400);
  Shoot();
}
