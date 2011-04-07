/*
 * Plane.cpp
 *
 *  Created on: Oct 16, 2008
 *      Author: the1schwartz
 */

#include "Plane.h"

Plane::Plane()
{
	d = 0.0f;
}

Plane::Plane(Vector3 n, Point p)
{
	normal = n;
	d = 0.0;
	for(unsigned i = 0; i < 3; i++)
	{
		d += n.coords[i]*p.coords[i];
	}
	d = -d;
}

Plane::~Plane()
{
}

Plane& Plane::operator= (Plane plane)
{
	normal = plane.normal;
	d = plane.d;
	return (*this);
}

float Plane::distance(Point p)
{
	float dd = 0.0f;
	for(unsigned i = 0; i < 3; i++)
	{
		dd += normal.coords[i]*p.coords[i];
	}
	return dd + d;
}
