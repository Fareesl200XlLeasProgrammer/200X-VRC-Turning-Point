#include "main.h"
#include "AutoVars.cpp"
#include "okapi/api.hpp"
#include "../include/display/lv_conf.h"
#include "../include/display/lvgl.h"
using namespace okapi;
extern int AutoCount;
void Drive(void*);//definition of drive task
void anglerTask_fn(void*param);
void PIDTurn();
void Gui();
static lv_res_t btn_click_action(lv_obj_t * btn1);
void puncherTask(void*);
void angle_close_mid(void*);
void punchReset();
void anglePID(double target);
void IntakeRoll(void*);
void Shoot(void*);
