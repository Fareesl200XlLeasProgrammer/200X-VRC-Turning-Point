#include "main.h"
#include "okapi/api.hpp"
#include "AutoVars.cpp"
#include "Autos.h"

using namespace pros;
using namespace okapi;


void redFront_3flag(){

}

void blueFront_3flag(){
  LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
  LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
  Lift.set_brake_mode(MOTOR_BRAKE_HOLD);

  gyro.reset();

  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  AnglePot.calibrate();
  Angler.tare_position();
  Puncher.tare_position();
  AnglePot.calibrate();

  LeftF.tare_position();

  Lift.tare_position();

  while(Lift.get_position() > -300){
    Lift.move_velocity(-200);
  }
  Lift.move_velocity(0);

  Puncher.move_absolute(900, 200);
  Angler.move_absolute(300, 200);

  // Intake.move_velocity(200);

  while(LeftF.get_position() < 2000){
    LeftF.move_velocity(100);
    LeftB.move_velocity(100);
    RightF.move_velocity(100);
    RightB.move_velocity(100);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);

  Intake.move_relative(1000, 200);
  pros::delay(1000);

  while(LeftF.get_position() > 380){
    LeftF.move_velocity(-100);
    LeftB.move_velocity(-100);
    RightF.move_velocity(-100);
    RightB.move_velocity(-100);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);



  PIDTurn(835);

  LeftF.tare_position();

  while(LeftF.get_position() > -100){
    LeftF.move_velocity(-100);
    LeftB.move_velocity(-100);
    RightF.move_velocity(-100);
    RightB.move_velocity(-100);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);

  while(Puncher.get_position() < 2200){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  Puncher.tare_position();
  Angler.move_absolute(0, 200);

  while(Intake.get_position() < 2000){
    Intake.move_velocity(200);
  }

  while(Puncher.get_position() < 2200){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  PIDTurn(40);

  while(LeftF.get_position() < 2000){
    LeftF.move_velocity(100);
    LeftB.move_velocity(100);
    RightF.move_velocity(100);
    RightB.move_velocity(100);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);

}
