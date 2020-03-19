#include "main.h"

typedef struct _pos
{
  double lastL;
  double lastR;
  double theta;
  double x;
  double y;
}sPos;

typedef struct _vector
{
	float y;
	float x;
}sVector; // 2D cartesian vector

typedef struct _polar
{
	float magnitude;
	float angle;
}sPolar; // 2D polar vector

typedef struct _line
{
	sVector p1;
	sVector p2;
}sLine;


/*FUNCTION DEFINITIOS*/
void trackPosition(sPos& position, double width); // Update the position of the robot
void resetPosition(sPos& position); // Reset the position
void vectorToPolar(sVector& vector, sPolar& polar); // Convert a cartesian vector to a polar vector
void polarToVector(sPolar& polar, sVector& vector); // Convert a polar vector to a cartesian vector
float getAngleOfLine(sLine line);
float getLengthOfLine(sLine line);

/*Variables*/
sPos gPosition;
