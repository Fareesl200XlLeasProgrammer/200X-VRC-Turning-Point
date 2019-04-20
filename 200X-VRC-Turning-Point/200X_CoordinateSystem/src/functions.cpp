#include "main.h"
#include "functions.hpp"
#include "motorDefs.hpp"
#include <math.h>
double one_tile = 667;
double deltaT;
char turn;
double t2;
double xDistance, yDistance, distance;
double rAcute;
int quadrant;
bool skipT2;
double xpos, ypos, x2, y2, theta1;


void getQuadrant(){
  if (xDistance>0 && yDistance>0) {
			quadrant=1;
		}
		else if (xDistance<0 && yDistance>0) {
			quadrant=2;
		}
		if (xDistance<0 && yDistance<0) {
			quadrant=3;
		}
		else if (xDistance>0 && yDistance<0) {
			quadrant=4;
		}
		if (xDistance==0||yDistance==0) {
			skipT2=true;
			if (xDistance==0 && yDistance>0) {
				t2=0;
			}
			else if (xDistance==0 & yDistance<0) {
				t2=180;
			}
			else if (yDistance==0 && xDistance>0) {
				t2=90;
			}
			else if (yDistance==0 && xDistance<0) {
				t2=270;
			}
		}
}
void findT2() {
		if (skipT2==false) {
			rAcute=(180/M_PI)*(abs(atan(yDistance/xDistance)));
			if (quadrant==1) {
				t2=90-rAcute;
			}
			else if (quadrant==2) {
				t2=270+rAcute;
			}
			else if (quadrant==3) {
				t2=270-rAcute;
			}
			else if (quadrant==4) {
				t2=90+rAcute;
			}
		}
		else if (skipT2==true) {
			skipT2=false;
		}
	}
void orient(double t1) {
	deltaT=t2-t1;
	if (deltaT<0) {
		deltaT=abs(deltaT);
		if (deltaT>=180) {
			deltaT=360-deltaT;
			turn='r';
		}
		else {
			turn='l';
		}
	}
	else{
	      if (deltaT>=180){
	          deltaT=360-deltaT;
	          turn='l';
	      }
	      else{
	        turn='r';
	      }
	    }
	}


void move(double x1, double y1, double x2, double y2, double t1){
  xDistance=x2-x1;
  yDistance=y2-y1;
  getQuadrant();
  findT2();
  orient(t1);
  //Add Motor turns here
  if (turn=='l'){
  }
  else if (turn=='r'){
  }
  xDistance=abs(xDistance);
  yDistance=abs(yDistance);
  distance=sqrt(pow(xDistance,2)+pow(yDistance,2));
  //Add Motor commands here
  LeftF.move_relative(667*distance,100);
  RightF.move_relative(667*distance,100);
  LeftB.move_relative(667*distance,100);
  RightB.move_relative(667*distance,100);
  xpos=x2;
  ypos=y2;
  theta1=t2;
}
