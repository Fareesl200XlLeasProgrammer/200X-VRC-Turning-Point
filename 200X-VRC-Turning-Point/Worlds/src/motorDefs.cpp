#include "main.h"
#include "motorDefs.h"

pros::Motor LeftF(10);
pros::Motor LeftB(1);
pros::Motor RightF(20, true);
pros::Motor RightB(11, true);
pros::Motor Puncher(6);
pros::Motor Angler(15);
pros::Motor Lift(5);
pros::Motor Intake(16);
pros::ADIAnalogIn IntakeLine_Top1 (3);
pros::ADIGyro gyro (4);
pros::ADIPotentiometer anglePot(2);


pros::Controller master(pros::E_CONTROLLER_MASTER);
