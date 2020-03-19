#include "main.h"
#include "Motors.hpp"
#include "Sensors.hpp"
#include "Variables.hpp"
#include "Functions.hpp"
#include "../include/display/lv_conf.h"
#include "../include/display/lvgl.h"
//#include "Tasks.hpp"
// extern const lv_img_t six_logo;
// extern const lv_img_t lance;

void intakeControl(int speed){
  IntakeL.move_velocity(speed);
  IntakeR.move_velocity(speed);
}

static lv_res_t btn_click_action(lv_obj_t * btn1){
  uint8_t id = lv_obj_get_free_num(btn1);

  if(id == 1){
    AutoCount = 1;
    printf("Mode %d: Red Back\n", AutoCount);
  }

  if(id == 2){
    AutoCount = 2;
    printf("Mode %d: Red Front\n", AutoCount);
  }

  if(id == 3){

    AutoCount = 3;
    printf("Mode %d: Blue Back\n", AutoCount);
  }

  if(id == 4){
    AutoCount = 4;
    printf("Mode %d: Blue Front\n", AutoCount);
  }

  if(id == 5){
    AutoCount = 5;
    printf("Mode %d: Skills\n", AutoCount);
  }

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}
void Gui(){
  lv_theme_t * th = lv_theme_alien_init(100, NULL);

  lv_obj_t *tabview;
  tabview = lv_tabview_create(lv_scr_act(), NULL);

  lv_obj_t *RedAutoSelect = lv_tabview_add_tab(tabview, "Red");//RedAutoSelect
  lv_obj_t *BlueAutoSelect = lv_tabview_add_tab(tabview, "Blue");//BlueAutoSelect

  lv_obj_t * label = lv_label_create(RedAutoSelect, NULL);
  lv_label_set_text(label, "Red Auto Selector\nClick the Button to switch Auto");

  lv_obj_t * label2 = lv_label_create(BlueAutoSelect, NULL);
  lv_label_set_text(label2, "Blue Auto Selector\nClick the button to switch Auto");

  lv_obj_t * btn1 = lv_btn_create(RedAutoSelect, NULL);
  lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
  lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 35);
  lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

  /*Add a label to the button*/
  label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "Back");

  /*Button two*/

  lv_obj_t * btn2 = lv_btn_create(RedAutoSelect, NULL);
  lv_cont_set_fit(btn2, true, true); /*Enable resizing horizontally and vertically*/
  lv_obj_align(btn2, label, LV_ALIGN_OUT_BOTTOM_RIGHT, 390, -48);
  lv_obj_set_free_num(btn2, 2);/*Set a unique number for the button*/
  lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);

  /*Add a label to the button*/
  label = lv_label_create(btn2, NULL);
  lv_label_set_text(label, "Front");

  /*Button Three*/

  lv_obj_t * btn3 = lv_btn_create(BlueAutoSelect, NULL);
  lv_cont_set_fit(btn3, true, true); /*Enable resizing horizontally and vertically*/
  lv_obj_align(btn3, label, LV_ALIGN_OUT_BOTTOM_LEFT, 80, -40);
  lv_obj_set_free_num(btn3, 3);   /*Set a unique number for the button*/
  lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);

  /*Add a label to the button*/
  label = lv_label_create(btn3, NULL);
  lv_label_set_text(label, "Back");

  /*Button four*/
  lv_obj_t * btn4 = lv_btn_create(BlueAutoSelect, NULL);
  lv_cont_set_fit(btn4, true, true); /*Enable resizing horizontally and vertically*/
  lv_obj_align(btn4, label, LV_ALIGN_OUT_BOTTOM_RIGHT, 400, -50);
  lv_obj_set_free_num(btn4, 4);/*Set a unique number for the button*/
  lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_click_action);

  /*Add a label to the button*/
  label = lv_label_create(btn4, NULL);
  lv_label_set_text(label, "Front");

  // lv_obj_t * sixLogo = lv_img_create(lv_scr_act(), NULL);
  // lv_img_set_src(sixLogo, &six_logo);
  // lv_obj_align(sixLogo, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);
  //
  // lv_obj_t * LanceLogo = lv_img_create(lv_scr_act(), NULL);
  // lv_img_set_src(LanceLogo, &lance);
  // lv_obj_align(LanceLogo, NULL, LV_ALIGN_IN_TOP_RIGHT, -120, 190);

}


int sgn(double v) {
  return (v < 0) ? -1 : ((v > 0) ? 1 : 0);
}

int inchToTick(int inch)
{
    return (((inch + 3) / (2.7765 * M_PI)) * 360) - 500;
}

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
    if(master.get_digital(DIGITAL_R1)){IntakeL.move(127);
      IntakeR.move(127);
    }

    else if(master.get_digital(DIGITAL_R2)){
      IntakeL.move(-127);
      IntakeR.move(-127);
    }

    else {
      IntakeL.move_velocity(0);
      IntakeR.move_velocity(0);
      IntakeL.set_brake_mode(MOTOR_BRAKE_HOLD);
      IntakeR.set_brake_mode(MOTOR_BRAKE_HOLD);
    }
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
