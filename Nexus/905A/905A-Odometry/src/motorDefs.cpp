#include "main.h"
#include "motorDefs.hpp"

pros::Motor LB(14, MOTOR_GEARSET_18,true);
pros::Motor RB(20, MOTOR_GEARSET_18, false);
pros::Motor RF(9, MOTOR_GEARSET_18, false);
pros::Motor LF(15, MOTOR_GEARSET_18,true);

pros::Motor Arm(11,MOTOR_GEARSET_36, true);

pros::Motor IntakeL(13, MOTOR_GEARSET_18, false);
pros::Motor IntakeR(19, MOTOR_GEARSET_18, true);

pros::Motor tilt(12, MOTOR_GEARSET_36, false);

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::ADIPotentiometer trayPot(8);
pros::ADIEncoder ArmEncoder(1, 2, true);
pros::ADIEncoder RightTracker(3, 4, true);
pros::ADIEncoder LeftTracker(5, 6, true);
pros::ADIGyro gyro(7, 10);
