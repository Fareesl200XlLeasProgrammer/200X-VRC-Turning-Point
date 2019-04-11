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

    if(error<= 5 && error>= -5){
      break;
    }
  } while(!(error<= 5 && error>= -2));

  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
}
void autonomous() {
  gyro.reset();

  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  AnglePot.calibrate();
  Angler.tare_position();
  Puncher.tare_position();
  AnglePot.calibrate();

  LeftF.tare_position();

  Lift.move_absolute(-300, 200);

  Puncher.move_absolute(900, 200);

  Intake.move_velocity(200);

  while(LeftF.get_position() < 1500){
    LeftF.move_velocity(150);
    LeftB.move_velocity(150);
    RightF.move_velocity(150);
    RightB.move_velocity(150);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
  pros::delay(200);

  while(IntakeLine_Top1.get_value() > 2828){
    Intake.move_velocity(200);
  }
  Intake.move_velocity(0);

  while(LeftF.get_position() > 800){
    LeftF.move_velocity(-150);
    LeftB.move_velocity(-150);
    RightF.move_velocity(-150);
    RightB.move_velocity(-150);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
  pros::delay(20);

  PIDTurn(-480);

  while(Puncher.get_position() < 2200){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  Lift.move_absolute(-200, 200);

  Intake.move_relative(3000, 200);

  Puncher.tare_position();

  while(AnglePot.get_value_calibrated() < 100){
    Angler.move_velocity(200);
  }
  Angler.move_velocity(0);

  while(Puncher.get_position() < 2200){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  PIDTurn(-490);//Useless but this is just to adjust to scrape (Doesnt work)

  Lift.move_relative(-400, 200);

  while(LeftF.get_position() < 800){
    LeftF.move_velocity(50);
    LeftB.move_velocity(50);
    RightF.move_velocity(50);
    RightB.move_velocity(50);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
  pros::delay(200);

  while(LeftF.get_position() < 1000){
    LeftF.move_velocity(20);
    LeftB.move_velocity(20);
    RightF.move_velocity(20);
    RightB.move_velocity(20);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
  Lift.move_relative(600, 95);
  Intake.move_velocity(200);
  pros::delay(300);

  while(LeftF.get_position() > 800){
    LeftF.move_velocity(-120);
    LeftB.move_velocity(-120);
    RightF.move_velocity(-120);
    RightB.move_velocity(-120);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
  Lift.move_absolute(-200, 200);

  while(LeftF.get_position() < 1000){
    LeftF.move_velocity(200);
    LeftB.move_velocity(200);
    RightF.move_velocity(200);
    RightB.move_velocity(200);

  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);

  while(IntakeLine_Top1.get_value() > 2848){
    Intake.move_velocity(200);
  }
  Intake.move_velocity(0);

  while(LeftF.get_position() > 600){
    LeftF.move_velocity(-120);
    LeftB.move_velocity(-120);
    RightF.move_velocity(-120);
    RightB.move_velocity(-120);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);

  PIDTurn(-900);

  while(LeftF.get_position() > 300){
    LeftF.move_velocity(-120);
    LeftB.move_velocity(-120);
    RightF.move_velocity(-120);
    RightB.move_velocity(-120);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);




}
