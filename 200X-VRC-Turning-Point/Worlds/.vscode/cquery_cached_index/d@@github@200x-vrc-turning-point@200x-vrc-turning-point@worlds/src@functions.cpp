#include "main.h"
#include "api.h"
#include "pros/rtos.h"
#include "functions.h"
using namespace pros;
void punchReset(void*){//function to reset puncher
  Motor Puncher(6);
  Controller master(pros::E_CONTROLLER_MASTER);

  Puncher.set_brake_mode(MOTOR_BRAKE_COAST);
  Puncher.set_zero_position(0);//zero encoder value

  while(true){
    Puncher.move_absolute(200, 200);//Draw back puncher

    if(Puncher.is_stopped()){//sets braketype to coast
      Puncher.move_velocity(0);
    }
    delay(20);
  }
}

void angle_close_mid(void*){
  Motor Angler(15);
  Controller master(pros::E_CONTROLLER_MASTER);

  Angler.tare_position();
  while(true){
    if(master.get_digital(DIGITAL_Y)){
      Angler.move_absolute(500, 200);
      pros::Task resetPunch_task(&punchReset);
    }
    delay(20);
  }
}

void Drive(void*){
  Motor LeftF(10);
  Motor LeftB(1);
  Motor RightF(20, true);
  Motor RightB(11, true);
  Motor Puncher(6);

  Controller master(pros::E_CONTROLLER_MASTER);

  RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
  LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
  LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
  while(true){
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

    if(master.get_digital(DIGITAL_X)){
      Puncher.move_relative(500, 200);
    }
    delay(20);
  }

}
