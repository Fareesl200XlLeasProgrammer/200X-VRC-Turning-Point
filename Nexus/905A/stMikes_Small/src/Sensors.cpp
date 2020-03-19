#include "main.h"
#include "Sensors.hpp"

pros::ADIPotentiometer trayPot(8);
pros::ADIEncoder ArmEncoder(1, 2, true);
pros::ADIEncoder RightTracker(3, 4, true);
pros::ADIEncoder LeftTracker(5, 6, true);
pros::ADIGyro gyro(7, 10);
pros::ADILineSensor leftTray(7);
pros::ADIAccelerometer test(12);
