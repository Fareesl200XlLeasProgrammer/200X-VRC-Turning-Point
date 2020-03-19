#include "main.h"

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

extern void deploy();
extern int sgn(double v);
extern int inchToTick(int inch);
extern void drive(void*);
extern void arm(void*);
extern void intake(void*);
extern void tilter(void*);
extern void liftTo(void*);
extern void tiltTo(void*);
extern void Gui();
extern void intakeControl(int speed);
#endif
