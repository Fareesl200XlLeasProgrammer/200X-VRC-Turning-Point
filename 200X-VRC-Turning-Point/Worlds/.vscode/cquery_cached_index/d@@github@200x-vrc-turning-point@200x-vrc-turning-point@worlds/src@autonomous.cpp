#include "main.h"
#include "okapi/api.hpp"
#include "functions.h"
#include "Autos.h"
#include "AutoVars.cpp"
#include "motorDefs.h"

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

  double kP = 0.2;
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

    if(error<= 1 && error>= -1){
      break;
    }
  } while(!(error<= 1 && error>= -1));

  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
}
void autonomous() {
  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  AnglePot.calibrate();
  Angler.tare_position();

  LeftF.tare_position();

  Lift.move_absolute(-400, 200);

  Intake.move_velocity(-200);

  while(LeftF.get_position() < 1700){
    LeftF.move_velocity(150);
    LeftB.move_velocity(150);
    RightF.move_velocity(150);
    RightB.move_velocity(150);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
  Intake.move_relative(-900, 200);
  pros::delay(1000);

  while(LeftF.get_position() > 900){
    LeftF.move_velocity(-150);
    LeftB.move_velocity(-150);
    RightF.move_velocity(-150);
    RightB.move_velocity(-150);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);

  PIDTurn(-550);//555

  while(Puncher.get_position() < 3000){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  Lift.move_absolute(-200, 200);

  Intake.move_relative(-3000, 200);

  pros::delay(500);

  while(Angler.get_position() < 150){
    Angler.move_velocity(200);
  }
  Angler.move_velocity(0);

  while(Puncher.get_position() < 6000){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);



}
