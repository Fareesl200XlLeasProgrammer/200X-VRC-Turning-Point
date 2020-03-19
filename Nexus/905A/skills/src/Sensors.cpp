#include "main.h"
#include "Sensors.hpp"

pros::ADIPotentiometer trayPot(8);
pros::ADIEncoder tracker(1, 2);
pros::ADIGyro gyro(7, 10);
pros::ADILineSensor leftTray(7);
pros::ADIAccelerometer test(12);
pros::Imu imu(2);
