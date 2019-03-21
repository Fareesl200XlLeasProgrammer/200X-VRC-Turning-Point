#include "../include/main.h"

void reset()
{
  pros::ADIGyro Gyro(2);
  pros::ADIPotentiometer AngleCheck(1);
  pros::Motor LeftF(1);
  pros::Motor LeftB(2);
  pros::Motor RightF(3, true);
  pros::Motor RightB(4, true);
  pros::Motor Lift(5);
  pros::Motor Intake(6);
  pros::Motor Angle(7);
  pros::Motor Puncher(8);
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
  LeftF.tare_position();
  LeftB.tare_position();
  RightF.tare_position();
  RightB.tare_position();
}
void autonomous() {
  pros::ADIGyro Gyro(1);
  pros::ADIPotentiometer AngleCheck(2);
	pros::Motor LeftF(1);
	pros::Motor LeftB(2);
	pros::Motor RightF(3, true);
	pros::Motor RightB(4, true);
	pros::Motor Lift(5);
	pros::Motor Intake(6);
	pros::Motor Angle(7);
	pros::Motor Puncher(8);

  //setting encoder units and brake types
  Puncher.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
  Lift.set_brake_mode(MOTOR_BRAKE_HOLD);
  Angle.set_brake_mode(MOTOR_BRAKE_HOLD);
  Puncher.set_brake_mode(MOTOR_BRAKE_HOLD);
  Intake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
  LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
  LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);

  if(Puncher.get_position() <= 1){
    Puncher.tare_position();
  }

  while(LeftF.get_position() != 1000){//move forwards to get the ball from the cap
    LeftF.move_velocity(200);
    LeftB.move_velocity(200);
    RightF.move_velocity(200);
    RightB.move_velocity(200);
    Intake.move_velocity(200);
  }
  reset();
  pros::delay(200);
  Intake.move_velocity(0);

  while(LeftF.get_position() != -100){//move Backwards from cap
    LeftF.move_velocity(-200);
    LeftB.move_velocity(-200);
    RightF.move_velocity(-200);
    RightB.move_velocity(-200);
  }
  reset();

  while(Gyro.get_value() != 3450){//turns towards the flags
    LeftF.move_velocity(-200);
    LeftB.move_velocity(-200);
    RightF.move_velocity(200);
    RightB.move_velocity(200);
  }
  reset();

  while(Puncher.get_position() != 1){//shoots the flag
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  while(AngleCheck.get_value() != 45){//re angles
    Angle.move_velocity(-200);
  }
  Angle.move_velocity(0);

  while(Puncher.get_position() != 1){//shoots the flag
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  while(Gyro.get_value() != 1500){//turns towards the cap with balls on top
    LeftF.move_velocity(200);
    LeftB.move_velocity(200);
    RightF.move_velocity(-200);
    RightB.move_velocity(-200);
  }
  reset();

  while(Lift.get_position() != 200){// raises the scraper
    Lift.move_velocity(200);
  }
  Lift.move_velocity(0);

  while(LeftF.get_position() != 200){//move forwards towards the cap
    LeftF.move_velocity(200);
    LeftB.move_velocity(200);
    RightF.move_velocity(200);
    RightB.move_velocity(200);
    Intake.move_velocity(200);
  }
  reset();

  while(Lift.get_position() != -100){//lowers the scraper on the cap
    Lift.move_velocity(-200);
  }
  Lift.move_velocity(0);

  while(LeftF.get_position() != -200){//move away from the cap to pull the balls off
    LeftF.move_velocity(-200);
    LeftB.move_velocity(-200);
    RightF.move_velocity(-200);
    RightB.move_velocity(-200);
  }
  reset();

  pros::delay(300);

  Intake.move_velocity(0);

  while(Gyro.get_value() != 150){//turns towards the flags
    LeftF.move_velocity(-200);
    LeftB.move_velocity(-200);
    RightF.move_velocity(200);
    RightB.move_velocity(200);
  }
  reset();

  while(AngleCheck.get_value() != 60){ //angles to shoot the flags
    Angle.move_velocity(200);
  }
  Angle.move_velocity(0);

  while(Puncher.get_position() != 1){//shoots the flag
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  while(AngleCheck.get_value() != 45){//angles to shoot the flag
    Angle.move_velocity(-200);
  }
  Angle.move_velocity(0);

  while(Puncher.get_position() != 1){//shoots the flag
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  while(Gyro.get_value() != 3350){//turns towards the platform
    LeftF.move_velocity(-200);
    LeftB.move_velocity(-200);
    RightF.move_velocity(200);
    RightB.move_velocity(200);
  }
  reset();

  while(Lift.get_position() != 200){//raises the scraper
    Lift.move_velocity(200);
  }
  Lift.move_velocity(0);

  while(LeftF.get_position() != 800){//move forwards to get the ball from the platform
    LeftF.move_velocity(200);
    LeftB.move_velocity(200);
    RightF.move_velocity(200);
    RightB.move_velocity(200);
    Intake.move_velocity(200);
  }
  reset();

  while(Lift.get_position() != -100){//lowers the lift onto the platform
    Lift.move_velocity(-200);
  }
  Lift.move_velocity(0);

  while(LeftF.get_position() != -200){//move backwards to get the ball off the platform
    LeftF.move_velocity(-200);
    LeftB.move_velocity(-200);
    RightF.move_velocity(-200);
    RightB.move_velocity(-200);
  }
  reset();

  pros::delay(300);

  Intake.move_velocity(0);

  while(Gyro.get_value() != 4500){//turns towards the flags
    LeftF.move_velocity(200);
    LeftB.move_velocity(200);
    RightF.move_velocity(-200);
    RightB.move_velocity(-200);
  }
  reset();

  while(AngleCheck.get_value() != 60){//changes the angle
    Angle.move_velocity(200);
  }
  Angle.move_velocity(0);

  while(Puncher.get_position() != 1){//shoots the flag
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);
}
