#include "main.h"
#include "../include/display/lv_conf.h"
#include "../include/display/lvgl.h"

extern lv_img_t six_logo;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img1, &six_logo);
	lv_obj_align(img1, NULL, LV_ALIGN_IN_TOP_MID, 20, 40);
}
