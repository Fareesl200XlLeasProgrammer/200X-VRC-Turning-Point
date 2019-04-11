#include "main.h"
#include "api.h"
#include "pros/rtos.h"
#include "functions.h"
#include "motorDefs.h"

using namespace pros;//just so i dont have to do pros:: before everything
using namespace okapi;
void anglePID(double target){
  // pros::Motor Angler(15);
  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  // pros::ADIPotentiometer anglePot(2);

  double current;
  double kP = 3;
  double kI = 0.0000003;
  double kD = 1.35;
  double error;
  double totalError;
  double lastError;
  double pwr;

  do{
    current = AnglePot.get_value();
    error = target - current;

    totalError += error;
    lastError = error;

    double P = kP * error;
    double I = kI * totalError;
    double D = kD * (error - lastError);

    pwr = P+I+D;
    Angler.move_velocity(pwr);

  }while(!(error<= 2 && error>= -2));

  Angler.move_velocity(0);

}

void Shoot(void*){
  while(true){
    while(Puncher.get_position() < 1800){
      Puncher.move_velocity(200);
    }
    Puncher.move_velocity(0);
    pros::delay(20);
  }
}

void puncherTask(void*){//function to reset puncher
  pros::Task shootTask(Shoot, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "");
  while(true){

    if(master.get_digital(DIGITAL_X)){
      Angler.move_absolute(0, 200);
      Puncher.tare_position();
    }

    if(master.get_digital(DIGITAL_A)){
      Angler.move_absolute(0, 200);
      Puncher.tare_position();
      while(Puncher.get_position() < 1800){
        pros::delay(1);
      }
      Puncher.tare_position();
      while(AnglePot.get_value_calibrated() < 120){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);
      while(Puncher.get_position() < 1800){
        pros::delay(1);
      }
      Angler.move_absolute(0, 200);
    }

    if(master.get_digital(DIGITAL_Y)){
      Puncher.tare_position();
      while(AnglePot.get_value_calibrated() < 120){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);
      while(Puncher.get_position() < 1800){pros::delay(1);}
      Angler.move_absolute(0, 200);
    }

    if(master.get_digital(DIGITAL_A)){


  }

    if(master.get_digital(DIGITAL_UP) ){
      while(AnglePot.get_value_calibrated() < 20){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_UP)){
    while(AnglePot.get_value_calibrated() > 20){
      Angler.move_velocity(-200);
  }
  Angler.move_velocity(0);
}


    if(master.get_digital(DIGITAL_DOWN)){
      while(AnglePot.get_value_calibrated() < 160){
        Angler.move_velocity(200);
      }
      Angler.move_velocity(0);
    }
    pros::delay(20);
  }
}


extern const lv_img_t six_logo;
extern const lv_img_t lance;

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
	lv_obj_t *ShotTuner= lv_tabview_add_tab(tabview, "ShotTuner");//RPM selector

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

	lv_obj_t * sixLogo = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(sixLogo, &six_logo);
	lv_obj_align(sixLogo, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

	lv_obj_t * LanceLogo = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(LanceLogo, &lance);
	lv_obj_align(LanceLogo, NULL, LV_ALIGN_IN_TOP_RIGHT, -120, 190);

}

void Drive(void*){
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
			LeftF.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_RIGHT_X) + master.get_analog(ANALOG_LEFT_X));
			LeftB.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_RIGHT_X) - master.get_analog(ANALOG_LEFT_X));
			RightF.move(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_RIGHT_X) - master.get_analog(ANALOG_LEFT_X));
			RightB.move(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_RIGHT_X) + master.get_analog(ANALOG_LEFT_X));
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

    delay(20);
  }

}
