/*
 * Plane.h
 *
 *  Created on: Oct 16, 2008
 *      Author: the1schwartz
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "Vector3.h"
#include "Point.h"

class Plane
{
public:
	Plane();
	Plane(Vector3 n, Point p);
	virtual ~Plane();
	Plane& operator= (Plane vector);
	float distance(Point p);

	Vector3 normal;
	float d;
};

#endif /* PLANE_H_ */
