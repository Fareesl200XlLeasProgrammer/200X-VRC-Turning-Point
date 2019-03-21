#include "main.h"
#include "AutoFunctions.cpp"
#include "initialize.cpp"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  if(AutoCount == 5){
		Skills();
	}

	if(AutoCount == 1){
		Red_Back();
	}

	if(AutoCount == 2){
		Red_Front();
	}

	if(AutoCount == 3){
		Blue_Back();
	}

	if(AutoCount == 4){
		Blue_Front();
	}
}
