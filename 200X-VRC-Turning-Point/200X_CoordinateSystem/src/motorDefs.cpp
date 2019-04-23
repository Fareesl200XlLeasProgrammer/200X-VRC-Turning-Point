#include "main.h"
#include "motorDefs.hpp"

pros::Motor LeftF(10);
pros::Motor LeftB(1);
pros::Motor RightF(20, true);
pros::Motor RightB(11, true);
pros::Motor Puncher(6, MOTOR_GEARSET_18, MOTOR_ENCODER_DEGREES);
pros::Motor Angler(15);
pros::Motor Lift(3);
pros::Motor Intake(16, true);
pros::ADIAnalogIn IntakeLine_Top1 (3);
pros::ADIGyro gyro (4);
pros::ADIPotentiometer AnglePot(2);


pros::Controller master(pros::E_CONTROLLER_MASTER);
