#include "main.h"

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

extern void deploy();
extern void rotate(bool left, int target);
//This is called a signum function, it returns the sign (positive or negative) of a number
extern int sgn(double v);
extern int inchToTick(int inch);
extern void drive(void*);
extern void arm(void*);
extern void intake(void*);
extern void tilter(void*);
extern void liftTo(void*);
extern void tiltTo(void*);

#endif
