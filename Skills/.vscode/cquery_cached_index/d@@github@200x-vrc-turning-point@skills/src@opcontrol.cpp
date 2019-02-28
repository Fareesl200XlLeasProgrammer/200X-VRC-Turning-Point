#include "main.h"
#include "D:/GitHub/200X-VRC-Turning-Point/Skills/include/display/lv_conf.h"
#include "D:/GitHub/200X-VRC-Turning-Point/Skills/include/display/lvgl.h"

static lv_res_t btn_click_action(lv_obj_t * btn1)
{
    uint8_t id = lv_obj_get_free_num(btn1);

    printf("Button %d is released\n", id);

    /* The button is released.
     * Make something here */

    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void Gui(){
	lv_theme_t *th = lv_theme_alien_init(100, NULL);

	/*Create a Tab view object*/
	lv_obj_t *tabview;
	tabview = lv_tabview_create(lv_scr_act(), NULL);

	lv_obj_t *RedAutoSelect = lv_tabview_add_tab(tabview, "Red");//RedAutoSelect
	lv_obj_t *BlueAutoSelect = lv_tabview_add_tab(tabview, "Blue");//BlueAutoSelect
	lv_obj_t *Skillz = lv_tabview_add_tab(tabview, "Skillz");//Skills run
	lv_obj_t *RPMSelect = lv_tabview_add_tab(tabview, "RPMSelect");//RPM selector

	lv_obj_t * label = lv_label_create(RedAutoSelect, NULL);
	lv_label_set_text(label, "Red Auto Selector\nClick the Button to switch Auto");

	lv_obj_t * label2 = lv_label_create(BlueAutoSelect, NULL);
	lv_label_set_text(label2, "Blue Auto Selector\nClick the button to switch Auto");

	lv_obj_t * btn1 = lv_btn_create(RedAutoSelect, NULL);
	lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
	lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
	lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
	lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

	/*Add a label to the button*/
	label = lv_label_create(btn1, NULL);
	lv_label_set_text(label, "Back");

	/*Button two*/

	lv_obj_t * btn2 = lv_btn_create(RedAutoSelect, NULL);
	lv_cont_set_fit(btn2, true, true); /*Enable resizing horizontally and vertically*/
	lv_obj_align(btn2, label, LV_ALIGN_OUT_BOTTOM_RIGHT, 390, -50);
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
	lv_obj_align(btn4, label, LV_ALIGN_OUT_BOTTOM_RIGHT, 390, -50);
	lv_obj_set_free_num(btn4, 4);/*Set a unique number for the button*/
	lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_click_action);

	/*Add a label to the button*/
	label = lv_label_create(btn4, NULL);
	lv_label_set_text(label, "Front");

	/*Button five*/
	lv_obj_t * btn5 = lv_btn_create(Skillz, NULL);
	lv_cont_set_fit(btn5, true, true); /*Enable resizing horizontally and vertically*/
	lv_obj_align(btn5, label, LV_ALIGN_OUT_BOTTOM_RIGHT, 390, -50);
	lv_obj_set_free_num(btn5, 5);/*Set a unique number for the button*/
	lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn_click_action);

	/*Add a label to the button*/
	label = lv_label_create(btn5, NULL);
	lv_label_set_text(label, "SKILLZ");
}

void opcontrol() {
	Gui();
	//Motor Definitions
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor Right(1, false);

	pros::Motor Right2(2, false);

	pros::Motor Left(3);

	pros::Motor Left2(4);

	pros::Motor Flipper(20);

	pros::Motor Intake(7, false);

	pros::Motor Lift(8);

	pros::Motor Flywheel(10);

	pros::Motor Index(17);

	//Setting Brake Modes
	Lift.set_brake_mode(MOTOR_BRAKE_HOLD);

	//Setting Encoder Units for the Flipper
	Flipper.set_encoder_units(MOTOR_ENCODER_ROTATIONS);

	while (true) {
		Flywheel.move_velocity(135);

    //Drive Code
    Right.move(master.get_analog(ANALOG_RIGHT_X)*0.8 - master.get_analog(ANALOG_LEFT_Y));
    Right2.move(master.get_analog(ANALOG_RIGHT_X)*0.8 - master.get_analog(ANALOG_LEFT_Y));
    Left.move(master.get_analog(ANALOG_RIGHT_X)*0.8 + master.get_analog(ANALOG_LEFT_Y));
    Left2.move(master.get_analog(ANALOG_RIGHT_X)*0.8 + master.get_analog(ANALOG_LEFT_Y));

		if(master.get_analog(ANALOG_LEFT_Y) < 15 && master.get_analog(ANALOG_LEFT_Y) >-15){
			Right.set_brake_mode(MOTOR_BRAKE_HOLD);
			Right2.set_brake_mode(MOTOR_BRAKE_HOLD);
			Left.set_brake_mode(MOTOR_BRAKE_HOLD);
			Left2.set_brake_mode(MOTOR_BRAKE_HOLD);
		}

    //Lift Code
    if(master.get_digital(DIGITAL_R1)){
      Lift.move_velocity(160);
    }

    else if(master.get_digital(DIGITAL_R2)){
      Lift.move_velocity(-160);
    }

    else{
      Lift.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_L1)){
      Intake.move_velocity(-200);
    }
    else if(master.get_digital(DIGITAL_L2)){
      Intake.move_velocity(-200);
      Index.move_velocity(150);
    }

		else if(master.get_digital(DIGITAL_UP)){
			Intake.move_velocity(200);
      Index.move_velocity(-150);
		}

    else{
      Intake.move_velocity(0);
      Index.move_velocity(0);
    }

    if(master.get_digital(DIGITAL_A)){
			Flywheel.move_velocity(127);
			master.rumble("-");
    }

		else if(master.get_digital(DIGITAL_B)){
			Flywheel.move_velocity(115);
			master.rumble("...");
		}


		pros::delay(20);
	}
}
