/*
 * Tee.cpp
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#include "Tee.h"
#include "Vector3.h"
#include "Point.h"

static GLfloat blue_colour[] = {0.0f, 0.0f, 1.0f};

void Tee::create(vector<string> *ss)
{
	float x,y,z;
	tile = atoi(ss->at(1).c_str());
	x = atof(ss->at(2).c_str());
	y = atof(ss->at(3).c_str());
	z = atof(ss->at(4).c_str());

	halfWidth = 0.05;
	teePos.coords[0] = x;
	teePos.coords[1] = y+0.01;
	teePos.coords[2] = z;
	teePos.coords[3] = 1.0f;
}

void Tee::draw()
{
	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue_colour);

	Point a(teePos.coords[0]-halfWidth,teePos.coords[1],teePos.coords[2]-halfWidth,1.0f);
	Point b(teePos.coords[0]+halfWidth,teePos.coords[1],teePos.coords[2]-halfWidth,1.0f);
	Point c(teePos.coords[0]+halfWidth,teePos.coords[1],teePos.coords[2]+halfWidth,1.0f);

	Vector3 u = a-b;
	Vector3 v = c-b;
	Vector3 norm = u*v;
	glNormal3fv(norm.coords);
	glVertex4fv(a.coords);
	glVertex4fv(b.coords);
	glVertex4fv(c.coords);
	glVertex3f(teePos.coords[0]-halfWidth,teePos.coords[1],teePos.coords[2]+halfWidth);

	glEnd();
}
