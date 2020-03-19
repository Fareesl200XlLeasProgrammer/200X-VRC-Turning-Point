#include "main.h"

#ifndef MOTORS_HPP
#define MOTORS_HPP

extern pros::Motor RB;
extern pros::Motor LB;
extern pros::Motor RF;
extern pros::Motor LF;

extern pros::Motor IntakeL;
extern pros::Motor IntakeR;

extern pros::Motor Arm;
extern pros::Motor tilt;

extern pros::Controller master;

extern pros::ADIPotentiometer trayPot;
extern pros::ADIEncoder ArmEncoder;
extern pros::ADIEncoder RightTracker;
extern pros::ADIEncoder LeftTracker;
extern pros::ADIGyro gyro;

#endif
