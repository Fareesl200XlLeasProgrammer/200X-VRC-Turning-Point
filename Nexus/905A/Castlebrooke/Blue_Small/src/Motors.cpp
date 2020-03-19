#include "main.h"
#include "Motors.hpp"

pros::Motor LB(1, MOTOR_GEARSET_18,true);
pros::Motor RB(20, MOTOR_GEARSET_18, false);
pros::Motor RF(9, MOTOR_GEARSET_18, false);
pros::Motor LF(2, MOTOR_GEARSET_18,true);

pros::Motor Arm(10,MOTOR_GEARSET_36, true);

pros::Motor IntakeL(4, MOTOR_GEARSET_18, false);
pros::Motor IntakeR(7, MOTOR_GEARSET_18, true);

pros::Motor tilt(11, MOTOR_GEARSET_36, false);
