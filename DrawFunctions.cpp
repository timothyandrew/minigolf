/*
 * DrawFunctions.cpp
 *
 *  Created on: Oct 14, 2008
 *      Author: the1schwartz
 */

#include "DrawFunctions.h"
#include "Point.h"
#include "gllib.h"

static GLfloat green_colour[] = {0.0f, 1.0f, 0.0f};
static GLfloat red_colour[] = {1.0f, 0.0f, 0.0f};

void drawTiles(vector<Point> *ps)
{
	//the board
	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green_colour);

	for(int i = ps->size()-1; i >= 0; i--)
	{
		int j, k;
		j = (i-1) % ps->size();
		k = (i+1) % ps->size();
		Point a(ps->at(j).coords[0],ps->at(j).coords[1],ps->at(j).coords[2],1.0f);
		Point b(ps->at(i).coords[0],ps->at(i).coords[1],ps->at(i).coords[2],1.0f);
		Point c(ps->at(k).coords[0],ps->at(k).coords[1],ps->at(k).coords[2],1.0f);

		Vector3 u = a-b;
		Vector3 v = c-b;
		Vector3 norm = u*v;
		norm = norm.unit();
		glNormal3fv(norm.coords);

		glVertex4fv(ps->at(i).coords);
	}

	glEnd();

	//the sides
	glBegin(GL_QUAD_STRIP);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red_colour);

	for(unsigned int i = 0; i < ps->size(); i++)
	{
		int k = (i+1) % ps->size();
		Point a(ps->at(i).coords[0],ps->at(i).coords[1]+0.1,ps->at(i).coords[2],1.0f);
		Point b(ps->at(i).coords[0],ps->at(i).coords[1],ps->at(i).coords[2],1.0f);
		Point c(ps->at(k).coords[0],ps->at(k).coords[1],ps->at(k).coords[2],1.0f);

		Vector3 u = a-b;
		Vector3 v = c-b;
		Vector3 norm = v*u;
		norm = norm.unit();
		glNormal3fv(norm.coords);
		glVertex4fv(ps->at(i).coords);
		glVertex3f(ps->at(i).coords[0],ps->at(i).coords[1]+0.1,ps->at(i).coords[2]);
	}

	glVertex4fv(ps->at(0).coords);
	glVertex3f(ps->at(0).coords[0],ps->at(0).coords[1]+0.1,ps->at(0).coords[2]);

	glEnd();
}
