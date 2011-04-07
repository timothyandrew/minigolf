/*
 * Math.h
 *
 *  Created on: Oct 16, 2008
 *      Author: the1schwartz
 */

#ifndef MATH_H_
#define MATH_H_

#include <math.h>
#include "Vector3.h"
#include "Plane.h"
#include "Point.h"

#ifndef PI
#define PI 3.14159265358979f
#endif

float degToRad(float deg);
float vectorAngle(Vector3 u, Vector3 v);
float heightInPlane(float x, float z, Plane p);
Point rotatePoint(Point v, Vector3 w, float angle);
Vector3 rotateVector(Vector3 v, Vector3 l, float angle);

#endif /* MATH_H_ */
