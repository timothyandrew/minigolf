/*
 * Cup.cpp
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#include <math.h>
#include "Cup.h"

static GLfloat black_colour[] = {0.0f, 0.0f, 0.0f};

void Cup::create(vector<string> *ss)
{
	float x,y,z;
	tile = atoi(ss->at(1).c_str());
	x = atof(ss->at(2).c_str());
	y = atof(ss->at(3).c_str());
	z = atof(ss->at(4).c_str());

	cupPos.coords[0] = x;
	cupPos.coords[1] = y+0.01f;
	cupPos.coords[2] = z;
	cupPos.coords[3] = 1.0f;
	radius = 0.1f;
}

void Cup::draw()
{
	glBegin(GL_TRIANGLES);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black_colour);
	for(unsigned i = 0; i < 20; i++)
	{
		float theta1 = i * 2 * PI / 20;
		float theta2 = (i + 1) * 2 * PI / 20;

		Point p1(cos(theta1)*radius+cupPos.coords[0], cupPos.coords[1], sin(theta1)*radius+cupPos.coords[2],1.0f);
		Point p2(cos(theta2)*radius+cupPos.coords[0], cupPos.coords[1], sin(theta2)*radius+cupPos.coords[2],1.0f);

		if(i == 0)
		{
			Vector3 u = p1-cupPos;
			Vector3 v = p2-cupPos;
			Vector3 norm = u*v;
			glNormal3fv(norm.coords);
		}

		glVertex4fv(cupPos.coords);
		glVertex4fv(p1.coords);
		glVertex4fv(p2.coords);
	}
	glEnd();
}
