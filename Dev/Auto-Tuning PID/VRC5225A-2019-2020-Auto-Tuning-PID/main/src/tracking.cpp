#include "tracking.hpp"


Tracking tracking;
double test_angle = 90;
double kP_a = 132;
//test without extra angle thing
//test which way negative mode turns
//print values every hundred millis after exit
//decrease angle threshold
//tune PID after adding intake stuff
//classes and cleaning code

double deg_to_rad(double degrees){
  return degrees/180 *M_PI;
}

double rad_to_deg(double radians){
  return radians/M_PI *180;
}

int sgn(double num){
  if (num < 0){
    return -1;
  }
  else if (num > 0){
    return 1;
  }
  else{
    return 0;
  }
}

void clear_line(int line) {
  master.print(0, line, "                                                                                       ");

}

void update (void* param){
 double distance_LR = 14.5; double distance_B = 7.25;
 double radiusR = 0;
 double radiusB = 0;
 double h = 0;
 double h2 = 0;
 double theta = 0; double beta = 0; double alpha = 0;
 double Xx = 0; double Xy = 0; double Yx = 0; double Yy = 0;

 leftencoder.reset(); rightencoder.reset(); backencoder.reset();
 double newleft = 0; double newright = 0; double newback = 0;
 double Right = 0; double Left = 0; double Back = 0;
 double lastleft = 0, lastright = 0, lastback = 0;
 double last_time = 0;

 // printf("%d | rightE: %d\n", millis(), rightencoder.get_value());
 // printf("%d | leftE: %d\n", millis(), leftencoder.get_value());
 // printf("%d | backE: %d\n", millis(), backencoder.get_value());

 while (true) {
//amount encoders moved (radians)
	 newleft = leftencoder.get_value() / 360.0* (2.75*M_PI);
	 newright = rightencoder.get_value() / 360.0* (2.75*M_PI);
	 newback = backencoder.get_value() / 360.0* (2.77*M_PI);
	 Right = newright - lastright;
	 Left = newleft - lastleft;
	 Back = newback - lastback;

//update last
	 lastright = newright;
	 lastleft = newleft;
	 lastback = newback;
	 theta = (Left - Right) / distance_LR;
//if robot turned in any direction
	 if (theta != 0){
		 radiusR = Right / theta;
		 beta = theta / 2.0;
		 h = (radiusR + distance_LR/2) * 2 *sin(beta);
		 radiusB = Back / theta;
		 h2 = (radiusB + distance_B) * 2 *sin(beta);
	 }
//if robot moved straight or didn't move
	 else {
		 h = Right;
		 h2 = Back;
		 beta = 0;
	 }
		 alpha = tracking.global_angle + beta;
//update global x, y and angle
		 Xx = h2 * cos(alpha);
		 Xy = h2 * -sin(alpha);
		 Yx = h * sin(alpha);
		 Yy = h * cos(alpha);
		 tracking.xcoord += Yx + Xx;
		 tracking.ycoord += Yy + Xy;

     tracking.global_angle += theta;


	// 	 if ((millis() - last_time) > 100){
	// 		 printf("%d | X: %f, Y: %f, A: %f\n", millis(), tracking.xcoord, tracking.ycoord, rad_to_deg(tracking.global_angle));
	// 		 // printf("%d | Y: %f\n", millis(), ycoord);
	// 		 // printf("%d | A: %f\n", millis(), rad_to_deg(global_angle));
 //       // printf("%d | A2: %f\n", millis(), rad_to_deg((newleft - newright)/distance_LR));
 //       // printf("%d | rightE: %d\n", millis(), rightencoder.get_value());
 //       // printf("%d | leftE: %d\n", millis(), leftencoder.get_value());
 //       // printf("%d | backE: %d\n", millis(), backencoder.get_value());
	// 	 last_time = millis();
	// 	 }
	// 	 delay(10);
 // }
}
}

void move_drive(int x, int y, int a){

  front_L.move(x + y + a);
  front_R.move(-x + y - a);
  back_L.move(-x + y + a);
  back_R.move(x + y - a);

}

void brake(){
  front_L.move_velocity(0);
  front_R.move_velocity(0);
  back_L.move_velocity(0);
  back_R.move_velocity(0);
  delay(300);
}

void Tracking::move_to_target(double target_x, double target_y, double target_a, bool cubeLineUp,  bool debug){
  printf("%d | Started move to target: (%f, %f, %f)", pros::millis(), target_x, target_y, rad_to_deg(target_a));
  printf("kp : %f \n", kP_a );
  double max_power_a = 55.0, max_power_xy = 90.0;
  double min_power_a = 12, min_power_xy = 10;
  double scale;

  double last_power_a = max_power_a, last_power_x = max_power_xy, last_power_y = max_power_xy;
  double integral_a = 0.0, integral_d = 0.0;

  double error_a, error_x, error_y, error_d;
  double difference_a;
  double  kP_d = 11.4;
  double kI_a = 0.0, kI_d = 0.0;   // kI_a = 0.01, kI_d = 0.0022;
  unsigned long last_time = millis();
  while (true){

    error_a = target_a - global_angle;
    error_x = target_x - xcoord;
    error_y = target_y - ycoord;
    error_d = sqrtf(powf(error_x, 2) + powf(error_y, 2));

    difference_a = global_angle + atan(error_y/error_x);

    if(debug) {
    printf("%d | X: %f, Y: %f, A: %f\n", millis(), xcoord, ycoord, rad_to_deg(global_angle));
    printf("%d | err_x: %f, err_y: %f, err_a: %f, err_d: %f\n", millis(), error_x, error_y, rad_to_deg(error_a), error_d);
    printf("%d| difference_a: %f\n", millis(), rad_to_deg(difference_a));
    }

    if (fabs(last_power_a) < max_power_a){
      integral_a += error_a * (millis() - last_time);
    }

    if (fabs(error_a) < deg_to_rad(0.5)){
      integral_a = 0;
      power_a  = 0;
    }

    if (fabs(last_power_x) < max_power_xy && fabs(last_power_y) < max_power_xy){ // what triggers integral to start adding?
      integral_d += error_d * (millis() - last_time);
    }

    // if (fabs(error_d) < 0.5){
    //   integral_d = 0;
    //   power_x = 0;
    //   power_y = 0;
    // }

//DOES MOD OF A NEGATIVE# RETURN POSTITIVE OR NEGATIVE VALUE? -- Negative!
    power_a = error_a*kP_a + integral_a*kI_a;
    if (error_x >= 0){
      power_x = error_d*cos(difference_a)*kP_d; // + integral_d*kI_d;
      power_y = error_d*sin(difference_a)*kP_d; // + integral_d*kI_d;
    }
    else{
      power_x = -error_d*cos(difference_a)*kP_d; // + integral_d*kI_d;
      power_y = -error_d*sin(difference_a)*kP_d; // + integral_d*kI_d;
    }

//controlling max power for a, x, and y
    if (fabs(power_a) > max_power_a){
      power_a = sgn(power_a)*max_power_a;
    }
    //need to scale x and y powers
    if (fabs(power_x) > max_power_xy || fabs(power_y) > max_power_xy){
      if (fabs(power_x) > fabs(power_y)){
        scale = max_power_xy/fabs(power_x);
        power_x = max_power_xy *sgn(power_x);
        power_y = power_y *scale;
      }
      else {
        scale = max_power_xy/fabs(power_y);
        power_y = max_power_xy *sgn(power_y);
        power_x = power_x *scale;
      }
    }

//setting min power if a, x, and y are not within target
    if(fabs(power_a) < min_power_a){
      if (fabs(error_a) > deg_to_rad(0.5)){
        power_a = sgn(power_a)*min_power_a;
      }
      else{
        power_a = 0;
      }
    }

    if (fabs(error_x) > 0.5){
        if (fabs(power_x) < min_power_xy){
        power_x = sgn(power_x)*min_power_xy;
      }
    }
    else{
      power_x = 0;
    }

    if (fabs(error_y) > 0.5){
      if(fabs(power_y) < min_power_xy){
      power_y = sgn(power_y)*min_power_xy;
      }
    }
    else{
      power_y = 0;
    }

    if(debug) printf("%d| pow_x: %f, pow_y: %f, pow: %f\n", millis(), power_x, power_y, power_a);
    move_drive(power_x, power_y, power_a);

    last_power_x = power_x;
    last_power_y = power_y;
    last_power_a = power_a;
    last_time = millis();
    if (fabs(error_a) <= deg_to_rad(0.5) && fabs(error_d) < 2){
      printf("Here 1\n");
      if(cubeLineUp){
      green.linedUp = false;
      while(!green.linedUp || (fabs(error_a) >= deg_to_rad(0.5)) || (fabs(target_a)==deg_to_rad(90) ? (fabs(error_x) >= 0.5 ) : (fabs(error_y) >= 0.5 ))) {
        error_y = target_y - ycoord;
        error_x = target_x - xcoord;
        error_a = target_a - global_angle;
        green.update();
        green.lineMiddle(0.8, target_y, target_x,target_a);
        move_drive(power_x, power_y, power_a);
      }
      fabs(target_a)==90 ? tracking.ycoord = target_y : tracking.xcoord = target_x;
      move_drive(0, 0, 0);
      difference_a = 0;
      printf("Movement to (%f, %f, %f) ended\n", target_x, target_y, rad_to_deg(target_a));
      printf("X : %f, Y : %f, A : %f, kp : %f", xcoord, ycoord, rad_to_deg(global_angle), kP_a);
      master.print(0, 3, "X : %f, Y : %f, A : %f", xcoord, ycoord, rad_to_deg(global_angle));
      master.print(0, 5,"Movement to (%f, %f, %f) ended\n", target_x, target_y, rad_to_deg(target_a));
      break;
    }
    printf("Error A: %f \n", error_a);
    kP_a += error_a * 100;
      difference_a = 0;
      brake();
      delay(300);
      printf("Movement to (%f, %f, %f) ended\n", target_x, target_y, rad_to_deg(target_a));
      printf("X : %f, Y : %f, A : %f", xcoord, ycoord, rad_to_deg(global_angle));
      master.print(0, 3, "X : %f, Y : %f, A : %f", xcoord, ycoord, rad_to_deg(global_angle));
      master.print(0, 5,"Movement to (%f, %f, %f) ended\n", target_x, target_y, rad_to_deg(target_a));
      break;
    }
    else if (master.get_digital(E_CONTROLLER_DIGITAL_X)){
      printf("Error A: %f \n", error_a);
      kP_a += error_a * 100;
      difference_a = 0;
      brake();
      delay(300);
      printf("Movement to (%f, %f, %f) ended\n", target_x, target_y, rad_to_deg(target_a));
      printf("X : %f, Y : %f, A : %f\n", xcoord, ycoord, rad_to_deg(global_angle));
      master.print(0, 3, "X : %f, Y : %f, A : %f", xcoord, ycoord, rad_to_deg(global_angle));
      master.print(0, 5, "Movement to (%f, %f, %f) ended", target_x, target_y, rad_to_deg(target_a));
      break;
    }
    delay(3);
  }
}
void Tracking::trackingInput() {
  tracking.power_a = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
  tracking.power_x = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
  tracking.power_y = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);

  if (fabs(tracking.power_a) < 5){
    tracking.power_a = 0;
  }
  if (fabs(tracking.power_x) < 5){
    tracking.power_x = 0;
  }
  if (fabs(tracking.power_y) < 5){
    tracking.power_y = 0;
  }

  move_drive(tracking.power_x, tracking.power_y, tracking.power_a);

  if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
    tracking.x2 = tracking.xcoord;
    tracking.y2 = tracking.ycoord;
    tracking.a2 = tracking.global_angle;
  }
  if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
    tracking.xcoord = 0;
    tracking.ycoord = 0;
    tracking.global_angle = 0;
  }

  if (master.get_digital(E_CONTROLLER_DIGITAL_Y)){
    tracking.move_to_target(tracking.x2, tracking.y2, tracking.a2);
  }

  if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
    // tracking.move_to_target(-25, 0.0, deg_to_rad(-90), true);
    // delay(500);
    // tracking.move_to_target(-25, 16, 0, true);
    // delay(500);
    // tracking.move_to_target(0.0, 16, deg_to_rad(90), true);
    // delay(500);
    // tracking.move_to_target(0.0, 0.0, deg_to_rad(180), true);
    while(true){
    tracking.move_to_target(0, 0, deg_to_rad(test_angle), false);
    test_angle +=90;
    delay(500);
  }

  }
}
void Tracking::setAngleHold(double angle) {
  holdAngle = angle;
}
void pointToAngle(void *param) {
    double angle_hold = deg_to_rad(tracking.holdAngle);
    while(true){
      double angle_error = tracking.global_angle-angle_hold;
      if(fabs(angle_error)>(deg_to_rad(0.5)))
      {
        tracking.power_a = -30*sgn(angle_error);
      }
      else tracking.power_a = 0;
    }
}
