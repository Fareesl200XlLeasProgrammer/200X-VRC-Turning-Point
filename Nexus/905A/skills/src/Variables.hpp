#include "main.h"

#ifndef VARIABLES_HPP
#define VARIABLES_HPP

extern pros::Controller master;

extern int LPower;
extern int RPower;
extern int AutoCount;

enum armPositions {
  stopArm,

  controlArm,//User control for arm

  Intake, //Intake position for arm

  lowTower, //Low tower preset

  midTower, //mid tower preset

  highTower//High tower preset
};

extern armPositions armPos;

extern float wheelSize;

extern int driveInch;

#endif
