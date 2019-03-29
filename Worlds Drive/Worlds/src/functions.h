#include "main.h"
#include "AutoVars.cpp"
#include "../include/display/lv_conf.h"
#include "../include/display/lvgl.h"
extern bool check;
void puncher(void*);//defintion of puncher preset task
void Drive(void*);//definition of drive task
void anglerTask_fn(void*param);
void Gui();//definition of gui function

void angle_close_mid();
void punchReset();
void punch_shoot_reset();//function to shoot once and reset
static lv_res_t btn_click_action(lv_obj_t * btn1);
