#include "main.h"

#ifndef VARIABLES_HPP
#define VARIABLES_HPP

extern pros::Controller master;

extern int LPower;
extern int RPower;

//enum trayPositions {stopTray, controlTray, low, mid, score};
//extern trayPositions trayPos;

enum armPositions {stopArm, controlArm, Intake, lowTower, midTower, highTower};
extern armPositions armPos;

extern float wheelSize;
extern int driveInch;

#endif
