#include "main.h"
#include "okapiChassis.hpp"
#include "okapi/api.hpp"

okapi::ChassisControllerIntegrated myChassis = okapi::ChassisControllerFactory::create(
  {-14, -15}, // Left motors
  {20, 9},   // Right motors
  AbstractMotor::gearset::blue, // Torque gearset
  {3.25_in, 14.5_in} // 3.25 inch wheels, 12.5 inch wheelbase width
);
