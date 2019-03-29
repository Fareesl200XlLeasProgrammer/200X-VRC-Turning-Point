#include "main.h"
#include "okapi/api.hpp"
#include "AutoVars.cpp"
#include "Autos.h"

using namespace pros;
using namespace okapi;

void redBack_4Flag(){
  auto myChassis = ChassisControllerFactory::create(
    {1, 10}, // Left motors
    {-20, -11},   // Right motors
    AbstractMotor::gearset::red, // Torque gearset
    {12_in, 18.5_in} // 4 inch wheels, 12.5 inch wheelbase width
  );

  auto profileController = AsyncControllerFactory::motionProfile(
    1.0,  // Maximum linear velocity of the Chassis in m/s
    2.0,  // Maximum linear acceleration of the Chassis in m/s/s
    10.0, // Maximum linear jerk of the Chassis in m/s/s/s
    myChassis // Chassis Controller
  );
}

void redFront_6flag(){
  auto myChassis = ChassisControllerFactory::create(
    {1, 10}, // Left motors
    {-20, -11},   // Right motors
    AbstractMotor::gearset::red, // Torque gearset
    {12_in, 18.5_in} // 4 inch wheels, 12.5 inch wheelbase width
  );

  auto profileController = AsyncControllerFactory::motionProfile(
    1.0,  // Maximum linear velocity of the Chassis in m/s
    2.0,  // Maximum linear acceleration of the Chassis in m/s/s
    10.0, // Maximum linear jerk of the Chassis in m/s/s/s
    myChassis // Chassis Controller
  );

}

void redFront_full(){
  auto myChassis = ChassisControllerFactory::create(
    {1, 10}, // Left motors
    {-20, -11},   // Right motors
    AbstractMotor::gearset::red, // Torque gearset
    {12_in, 18.5_in} // 4 inch wheels, 12.5 inch wheelbase width
  );

  auto profileController = AsyncControllerFactory::motionProfile(
    1.0,  // Maximum linear velocity of the Chassis in m/s
    2.0,  // Maximum linear acceleration of the Chassis in m/s/s
    10.0, // Maximum linear jerk of the Chassis in m/s/s/s
    myChassis // Chassis Controller
  );

}

void redFront_descore(){
  auto myChassis = ChassisControllerFactory::create(
    {1, 10}, // Left motors
    {-20, -11},   // Right motors
    AbstractMotor::gearset::red, // Torque gearset
    {12_in, 18.5_in} // 4 inch wheels, 12.5 inch wheelbase width
  );

  auto profileController = AsyncControllerFactory::motionProfile(
    1.0,  // Maximum linear velocity of the Chassis in m/s
    2.0,  // Maximum linear acceleration of the Chassis in m/s/s
    10.0, // Maximum linear jerk of the Chassis in m/s/s/s
    myChassis // Chassis Controller
  );
  
}
