#include "main.h"
#include "AutoFunctions.cpp"
#include "../include/display/lv_conf.h"
#include "../include/display/lvgl.h"

int AutoCount;

static lv_res_t btn_click_action(lv_obj_t * btn1)
{
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

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	Gui();
	if(AutoCount == 5){
		Skills();
	}

	if(AutoCount == 1){
		Red_Back();
	}

	if(AutoCount == 2){
		Red_Front();
	}

	if(AutoCount == 3){
		Blue_Back();
	}

	if(AutoCount == 4){
		Blue_Front();
	}

}
