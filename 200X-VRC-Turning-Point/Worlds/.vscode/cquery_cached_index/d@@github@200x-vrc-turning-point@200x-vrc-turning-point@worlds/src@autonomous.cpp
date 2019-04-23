#include "main.h"
#include "okapi/api.hpp"
#include "functions.h"
#include "Autos.h"
#include "AutoVars.cpp"
// #include "motorDefs.h"

using namespace okapi;
using namespace pros;

void PIDDrive(double target){
  pros::Motor Intake(16);
  pros::Motor Lift(5);
  pros::ADIAnalogIn IntakeLine_Top1 (3);
  pros::ADIGyro gyro (4);
  pros::Motor LeftF(10);
  pros::Motor LeftB(1);
  pros::Motor RightF(20, true);
  pros::Motor RightB(11, true);

  pros::Controller master(pros::E_CONTROLLER_MASTER);
  double kP = 0.3;
  double kI = 0.000003;
  double kD = 1.35;
  double errorL, totalErrorL, lastErrorL, errorR, totalErrorR, lastErrorR,pwrL,pwrR,CurrentL, CurrentR;

  do{
    CurrentL = LeftF.get_position();
    CurrentR = RightF.get_position();
    errorL = target - CurrentL;
    errorR = target - CurrentR;
    totalErrorL += errorL;
    totalErrorR += errorR;
    lastErrorL = errorL;
    lastErrorR = errorR;

    double Pl, Il, Dl, Pr, Ir, Dr;
    Pl = errorL*kP;

    Il = kI * totalErrorL;

    Dl = kD * (errorL - lastErrorL);

    Pr = errorR*kP;

    Ir = kI * totalErrorR;

    Dr = kD * (errorR - lastErrorR);

    pwrL = Pl + Il + Dl;
    pwrR = Pr + Ir + Dr;

    LeftF.move_velocity(pwrL);
    LeftB.move_velocity(pwrL);

    RightF.move_velocity(pwrR);
    RightB.move_velocity(pwrR);
  }while(!(errorL<= 5 && errorL>= -5 && errorR<= 5 && errorR>= -5));
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);

  RightF.move_velocity(0);
  RightB.move_velocity(0);
}


void PIDTurn(double target){
  pros::Motor Intake(16);
  pros::Motor Lift(5);
  pros::ADIAnalogIn IntakeLine_Top1 (3);
  pros::ADIGyro gyro (4);
  pros::Motor LeftF(10);
  pros::Motor LeftB(1);
  pros::Motor RightF(20, true);
  pros::Motor RightB(11, true);

  pros::Controller master(pros::E_CONTROLLER_MASTER);

  double kP = 0.35;
  double kI = 0.00000003;
  double kD = 1.35; /*was 1.35 test with current value if improvement is seen keep value*/
  double error;
  double totalError;
  double lastError;
  double pwr;
  gyro.reset();
  do{

    double current = gyro.get_value();
    error = target - current;
    double P = error * kP;
    totalError += error;
    lastError = error;
    double I = kI * totalError;
    double D = kD * (error - lastError);
    pwr = P+I+D;
    LeftF.move_velocity(pwr);
    LeftB.move_velocity(pwr);
    RightF.move_velocity(-pwr);
    RightB.move_velocity(-pwr);
    if(error ==0){
      I = 0;
    }

    if(error<= 5 && error>= -5){
      break;
    }
  } while(!(error<= 5 && error>= -2));

  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
}
void autonomous() {
  pros::Motor Intake(16);
  pros::Motor Lift(3);
  pros::ADIAnalogIn IntakeLine_Top1 (3);
  pros::ADIGyro gyro (4);
  pros::Motor LeftF(10);
  pros::Motor LeftB(1);
  pros::Motor RightF(20, true);
  pros::Motor RightB(11, true);
  pros::Motor Puncher(6);
  pros::ADIPotentiometer AnglePot(2);
  pros::Motor Angler(15);

  LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
  LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
  Lift.set_brake_mode(MOTOR_BRAKE_HOLD);
  Angler.set_brake_mode(MOTOR_BRAKE_HOLD);

  Angler.tare_position();
  Puncher.tare_position();

  LeftF.tare_position();

  Lift.tare_position();

  //Bring lift up to intake
  while(Lift.get_position() > -300){
    Lift.move_velocity(-200);
  }
  Lift.move_velocity(0);

  //wind back puncher
  Puncher.move_absolute(900, 200);
  //Angle Puncher to hit mid flag
  Angler.move_absolute(300, 200);
  ////////////////////////////////////////////////////

  //Move to first cap to intake ball
  LeftF.move_absolute(2000, 200);
  RightF.move_absolute(2000, 200);
  RightB.move_absolute(2000, 200);
  LeftB.move_absolute(2000, 200);

  while (!((LeftF.get_position() < 2005) && (LeftF.get_position() > 1995))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }

  //Intake Ball
  while(Intake.get_position() < 900){
    Intake.move_velocity(200);
  }
  Intake.move_velocity(0);

  //Move back to shoot
  LeftF.move_absolute(200, 200);
  RightF.move_absolute(200, 200);
  RightB.move_absolute(200, 200);
  LeftB.move_absolute(200, 200);
  while (!((LeftF.get_position() < 205) && (LeftF.get_position() > 195))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }

  LeftF.move_absolute(0, 200);
  RightF.move_absolute(0, 200);
  RightB.move_absolute(-200, 200);
  LeftB.move_absolute(-200, 200);

  while (!((LeftF.get_position() < -5) && (LeftF.get_position() > 5))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(1);
  }

  while(Puncher.get_position() < 2200){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);
  Angler.move_absolute(0, 200);
  //Move Back to shoot high flag and to park
  LeftF.move_absolute(-200, 200);
  RightF.move_absolute(-200, 200);
  RightB.move_absolute(-400, 200);
  LeftB.move_absolute(-400, 200);

  while (!((LeftF.get_position() < -205) && (LeftF.get_position() > -195))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  Puncher.tare_position();
  while(Puncher.get_position() < 2200){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  PIDTurn(900);

  LeftF.move_absolute(2000, 200);
  RightF.move_absolute(2000, 200);
  RightB.move_absolute(2000, 200);
  LeftB.move_absolute(2000, 200);


  // Intake.move_velocity(200);
  // Test code in /*this type of comment*/
  /*
  while(LeftF.get_position() < 2000){//667ticks/tile
    LeftF.move_velocity(100);
    LeftB.move_velocity(100);
    RightF.move_velocity(100);
    RightB.move_velocity(100);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);

  Intake.move_relative(1000, 200);
  pros::delay(1000);

  while(LeftF.get_position() > 380){
    LeftF.move_velocity(-100);
    LeftB.move_velocity(-100);
    RightF.move_velocity(-100);
    RightB.move_velocity(-100);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);



  PIDTurn(-900);//Useless but this is just to adjust to scrape (Doesnt work)

  LeftF.tare_position();

  while(LeftF.get_position() > -100){
    LeftF.move_velocity(-100);
    LeftB.move_velocity(-100);
    RightF.move_velocity(-100);
    RightB.move_velocity(-100);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);

  while(Puncher.get_position() < 2200){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  Puncher.tare_position();
  Angler.move_absolute(0, 200);

  while(Intake.get_position() < 2000){
    Intake.move_velocity(200);
  }

  while(Puncher.get_position() < 2200){
    Puncher.move_velocity(200);
  }
  Puncher.move_velocity(0);

  PIDTurn(900);

  while(LeftF.get_position() < 2000){
    LeftF.move_velocity(100);
    LeftB.move_velocity(100);
    RightF.move_velocity(100);
    RightB.move_velocity(100);
  }
  LeftF.move_velocity(0);
  LeftB.move_velocity(0);
  RightF.move_velocity(0);
  RightB.move_velocity(0);
  */


  //
  // Lift.move_relative(-100, 200);
  //
  // while(LeftF.get_position() < 1200){
  //   LeftF.move_velocity(50);
  //   LeftB.move_velocity(50);
  //   RightF.move_velocity(50);
  //   RightB.move_velocity(50);
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);
  // pros::delay(200);
  //
  // while(LeftF.get_position() < 1000){
  //   LeftF.move_velocity(20);
  //   LeftB.move_velocity(20);
  //   RightF.move_velocity(20);
  //   RightB.move_velocity(20);
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);
  // Lift.move_relative(600, 95);
  // Intake.move_velocity(200);
  // pros::delay(300);
  //
  // while(LeftF.get_position() > 800){
  //   LeftF.move_velocity(-120);
  //   LeftB.move_velocity(-120);
  //   RightF.move_velocity(-120);
  //   RightB.move_velocity(-120);
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);
  // Lift.move_absolute(-400, 200);
  //
  // while(LeftF.get_position() < 1400){
  //   LeftF.move_velocity(200);
  //   LeftB.move_velocity(200);
  //   RightF.move_velocity(200);
  //   RightB.move_velocity(200);
  //
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);
  // Intake.move_velocity(0);
  //
  // Intake.move_relative(2200, 200);
  //
  // pros::delay(100);
  //
  //
  // while(LeftF.get_position() > 1330){
  //   LeftF.move_velocity(-50);
  //   LeftB.move_velocity(-50);
  //   RightF.move_velocity(-50);
  //   RightB.move_velocity(-50);
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);
  // Intake.move_velocity(0);
  //
  // PIDTurn(-950);
  // pros::delay(300);
  //
  // LeftF.set_brake_mode(MOTOR_BRAKE_HOLD);
  // RightF.set_brake_mode(MOTOR_BRAKE_HOLD);
  // RightB.set_brake_mode(MOTOR_BRAKE_HOLD);
  // LeftB.set_brake_mode(MOTOR_BRAKE_HOLD);
  //
  // while(LeftF.get_position() > -800){
  //   LeftF.move_velocity(-120);
  //   LeftB.move_velocity(-120);
  //   RightF.move_velocity(-120);
  //   RightB.move_velocity(-120);
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);
  //
  // Puncher.tare_position();
  //
  // while(Puncher.get_position() < 1800){
  //   Puncher.move_velocity(200);
  // }
  // Puncher.move_velocity(0);
  // Intake.move_velocity(200);
  //
  // Angler.move_absolute(0, 200);
  //
  // Puncher.tare_position();
  //
  // while(Puncher.get_position() < 1800){
  //   Puncher.move_velocity(200);
  // }
  // Puncher.move_velocity(0);
  //
  // Intake.move_velocity(0);
  // //
  // // PIDTurn(50);
  //
  // // while(LeftF.get_position() > -850){
  // //   LeftF.move_velocity(-120);
  // //   LeftB.move_velocity(-120);
  // //   RightF.move_velocity(-120);
  // //   RightB.move_velocity(-120);
  // // }
  // // LeftF.move_velocity(0);
  // // LeftB.move_velocity(0);
  // // RightF.move_velocity(0);
  // // RightB.move_velocity(0);
  //
  // while(LeftF.get_position() < 2000){
  //   LeftF.move_velocity(200);
  //   LeftB.move_velocity(200);
  //   RightF.move_velocity(200);
  //   RightB.move_velocity(200);
  //
  // }
  // LeftF.move_velocity(0);
  // LeftB.move_velocity(0);
  // RightF.move_velocity(0);
  // RightB.move_velocity(0);






}
