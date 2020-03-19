#include "main.h"
#include "Variables.hpp"

pros::Controller master(CONTROLLER_MASTER);

int LPower = 0;
int RPower = 0;

int LIPower = 0;
int RIPower = 0;

//trayPositions trayPos = stopTray;

armPositions armPos = stopArm;

float wheelSize = 2.8;
int driveInch = 0;
