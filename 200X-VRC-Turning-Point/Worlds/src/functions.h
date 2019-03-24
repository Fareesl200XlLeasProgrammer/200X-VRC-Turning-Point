#include "main.h"
#include "AutoVars.cpp"
#include "../include/display/lv_conf.h"
#include "../include/display/lvgl.h"
extern bool check;
void Drive(void*);//definition of drive task
void anglerTask_fn(void*param);
void Gui();//definition of gui function

void angle_close_mid(void*);
void punchReset(void*);
