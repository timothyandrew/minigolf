/*
 * Math.cpp
 *
 *  Created on: Oct 16, 2008
 *      Author: the1schwartz
 */

#include "Math.h"
#include "Matrix.h"

float degToRad(float deg)
{
	return deg*PI/180.0f;
}

float radToDeg(float rad)
{
	return rad*180.0f/PI;
}

float vectorAngle(Vector3 u, Vector3 v)
{
	float a = u.dot(v)/(u.length()*v.length());

	return radToDeg(acos(a));
}

float heightInPlane(float x, float z, Plane p)
{
	return (-p.normal.coords[0]*x - p.normal.coords[2]*z - p.d)/p.normal.coords[1];
}

Vector3 rotateVector(Vector3 v, Vector3 l, float angle)
{
	Matrix L = Matrix::Zero();

	float a = degToRad(angle);

	L.SetElement(0,1,l.coords[2]);
	L.SetElement(0,2,-l.coords[1]);
	L.SetElement(1,0,-l.coords[2]);
	L.SetElement(1,2,l.coords[0]);
	L.SetElement(2,0,l.coords[1]);
	L.SetElement(2,1,-l.coords[0]);
	L.SetElement(3,3,1);

	float d = l.length();

	Matrix m = Matrix::Identity() + L*(sin(a)/d) + (L*L)*((1.0f-cos(a))/(d*d));

	return m*v;
}

Point rotatePoint(Point v, Vector3 w, float angle)
{
	Point temp;

	Vector3 w_x;
	Vector3 w_y;
	Vector3 w_z;

	for(unsigned i = 0; i < 3; i++)
	{
		w_x.coords[i] = v.coords[i]*w.coords[0];
		w_y.coords[i] = v.coords[i]*w.coords[1];
		w_z.coords[i] = v.coords[i]*w.coords[2];
	}


	float sa = sin(degToRad(angle));
	float ca = cos(degToRad(angle));

	float f1 = w_x.coords[0]+w_y.coords[1]+w_z.coords[2];
	float f3[3];
	f3[0] = w_y.coords[1]+w_z.coords[2];
	f3[1] = w_x.coords[0]+w_z.coords[2];
	f3[2] = w_x.coords[0]+w_y.coords[1];
	float f4[3];
	f4[0] = -w_z.coords[1]+w_y.coords[2];
	f4[1] = w_z.coords[0]-w_x.coords[2];
	f4[2] = -w_y.coords[0]+w_x.coords[1];

	for(unsigned i = 0; i < 3; i++)
	{
		int j = (i-1) % 3;
		int k = (i+1) % 3;
		float f2 = w.coords[j]*w.coords[j]+w.coords[k]*w.coords[k];

		temp.coords[i] = w.coords[i]*f1 + (v.coords[i]*f2 - w.coords[i]*f3[i])*ca + f4[i]*sa;
	}

	return temp;
}
