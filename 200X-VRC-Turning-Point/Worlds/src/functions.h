#include "main.h"
#include "AutoVars.cpp"
#include "/display/lv_conf.h"
#include "/display/lvgl.h"

void puncher(void*);//defintion of puncher preset task
void Drive(void*);//definition of drive task
void Gui();//definition of gui function
static lv_res_t btn_click_action(lv_obj_t * btn1);
