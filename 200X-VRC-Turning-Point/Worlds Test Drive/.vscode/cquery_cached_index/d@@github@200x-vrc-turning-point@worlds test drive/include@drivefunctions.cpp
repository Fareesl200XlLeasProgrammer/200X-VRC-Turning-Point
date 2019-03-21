#include "main.h"

void drive(){
    pros::Motor LeftF(1);
    pros::Motor LeftB(2);
    pros::Motor RightF(3, true);
    pros::Motor RightB(4, true);
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
    RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
    LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
    LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);

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
  }
