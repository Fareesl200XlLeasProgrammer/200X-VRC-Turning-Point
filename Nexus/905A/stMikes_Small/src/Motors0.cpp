#include "main.h"
#include "Motors.hpp"

pros::Motor LB(14, MOTOR_GEARSET_06,true);
pros::Motor RB(20, MOTOR_GEARSET_06, false);
pros::Motor RF(10, MOTOR_GEARSET_06, false);
pros::Motor LF(15, MOTOR_GEARSET_06,true);

pros::Motor Arm(11,MOTOR_GEARSET_36, true);

pros::Motor IntakeL(16, MOTOR_GEARSET_18, false);
pros::Motor IntakeR(19, MOTOR_GEARSET_18, true);

pros::Motor tilt(12, MOTOR_GEARSET_36, true);
