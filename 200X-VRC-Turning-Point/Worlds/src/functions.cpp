#include "main.h"
#include "api.h"
#include "pros/rtos.h"
#include "functions.h"
#include "motorDefs.h"

using namespace pros;//just so i dont have to do pros:: before everything
using namespace okapi;

void puncherTask(void*){//function to reset puncher
  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);
  AnglePot.calibrate();

  while(true){
    printf("Angler: %f\n",AnglePot.get_value_calibrated());
    if(Puncher.get_position() == 1800){
      Puncher.tare_position();
    }
		if(master.get_digital(DIGITAL_B)){

 		}

		//Puncher Preset Top Full Court
 		else if(master.get_digital(DIGITAL_Y)){//middle   IF BROKEN CHANGE TO 105
      Puncher.tare_position();
      while(AnglePot.get_value_calibrated() < 50){
        Angler.move_velocity(70);
      }
      Angler.move_velocity(0);
      while(Puncher.get_position() < 1800){
        Puncher.move_velocity(200);
      }
      Puncher.move_velocity(0);

      while(AnglePot.get_value_calibrated() > 0){
        Angler.move_velocity(-200);
      }
      Angler.move_velocity(0);

 		}

		else if(master.get_digital(DIGITAL_A)){//top

		}


    else if(master.get_digital(DIGITAL_UP)){//top platform

		}

    else if(master.get_digital(DIGITAL_DOWN)){// middle platform

    }

    else if(master.get_digital(DIGITAL_LEFT)){// Back Double Shot

    }

    else if(master.get_digital(DIGITAL_X)){//default
			Puncher.tare_position();
			while(Puncher.get_position() < 2100){
 				Puncher.move_velocity(200);
 			}
 			Puncher.move_velocity(0);
 		}
 		else{
        Puncher.move_velocity(0);
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

    delay(20);
  }

}
