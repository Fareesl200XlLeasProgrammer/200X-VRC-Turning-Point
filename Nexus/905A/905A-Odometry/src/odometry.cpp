#include "main.h"
#include "motorDefs.hpp"
#include "odometry.hpp"


void trackPosition(sPos& position, double width){
  int left = LeftTracker.get_value();
  int right = RightTracker.get_value();

  float L = (left - position.lastL);
  float R = (right - position.lastR);

  //Update Lst values

  position.lastL = left;
  position.lastR = right;

  float h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
  float i; // Half on the angle that I've traveled
	float a = (L - R) / (width); // The angle that I've traveled

  if (a)
	{
		float r = R / a; // The radius of the circle the robot travel's around with the right side of the robot
		i = a / 2.0;
		float sinI = sin(i);
		h = ((r + 9) * sinI) * 2.0;//r + R_DISTANCE_IN
	}
	else
	{
		h = R;
		i = 0;
	}
  float p = i + position.theta; // The global ending angle of the robot
	float cosP = cos(p);
	float sinP = sin(p);

	// Update the global position
	position.y += h * cosP;
	position.x += h * sinP;

	position.theta += a;


}

// void resetPosition(sPos& position)
// {
// 	position.leftLst = position.rightLst = position.backLst = 0;
// 	position.y = position.x = position.a = 0;
// }
//
//
// void vectorToPolar(sVector& vector, sPolar& polar)
// {
// 	if (vector.x || vector.y)
// 	{
// 		polar.magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
// 		polar.angle = atan2(vector.y, vector.x);
// 	}
// 	else
// 		polar.magnitude = polar.angle = 0;
// }
//
// void polarToVector(sPolar& polar, sVector& vector)
// {
// 	if (polar.magnitude)
// 	{
// 		vector.x = polar.magnitude * cos(polar.angle);
// 		vector.y = polar.magnitude * sin(polar.angle);
// 	}
// 	else
// 		vector.x = vector.y = 0;
// }
//
// float getAngleOfLine(sLine line)
// {
// 	return atan2(line.p2.x - line.p1.x, line.p2.y - line.p1.y);
// }
//
// float getLengthOfLine(sLine line)
// {
// 	float x = line.p2.x - line.p1.x;
// 	float y = line.p2.y - line.p1.y;
// 	return sqrt(x * x + y * y);
// }
