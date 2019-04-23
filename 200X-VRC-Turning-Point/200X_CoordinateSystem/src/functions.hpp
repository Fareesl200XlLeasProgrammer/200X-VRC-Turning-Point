#include "main.h"
void move(double x1, double y1, double x2, double y2, double t1);
void getQuadrant();
void findT2();
void orient(double t1);
void getDistance();
void getDeltaT();
void getTurn();
void getT2();

extern double one_tile;
extern double deltaT;
extern char turn;
extern double t2;
extern double xDistance, yDistance, distance;
extern double rAcute;
extern int quadrant;
extern bool skipT2;
extern double xpos, ypos, x2, y2, theta1;
