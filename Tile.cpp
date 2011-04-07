/*
 * Tile.cpp
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#include <math.h>
#include <iostream>
#include <limits>
#include "Tile.h"
#include "Math.h"

using namespace std;

static GLfloat red_colour[] = {1.0f, 0.0f, 0.0f};
static GLfloat green_colour[] = {0.0f, 1.0f, 0.0f};

void Tile::create(vector<string> *ss)
{
	unsigned i = 1;
	id = atoi(ss->at(i).c_str());
	i++;
	unsigned int n = atoi(ss->at(i).c_str());
	i++;
	vector<Point> *ps = new vector<Point>;
	float min_y = 1000;
	float max_y = -1000;

	while(i < n*3+3)
	{
		float x,y,z;
		x = atof(ss->at(i).c_str());
		y = atof(ss->at(i+1).c_str());
		z = atof(ss->at(i+2).c_str());

		if(y < min_y)
		{
			min_y = y;
		}
		if(y > max_y)
		{
			max_y = y;
		}

		Point p(x,y,z,1.0f);

		ps->push_back(p);

		i += 3;
	}
	points = ps;

	//cout << min_y << "," << max_y << endl;

	planes = new vector<Plane>;
	for(unsigned j = 0; j < points->size(); j++)
	{
		int k = (j+1) % ps->size();
		Point a(points->at(j).coords[0],points->at(j).coords[1]+0.1,points->at(j).coords[2],1.0f);
		Point b(points->at(j).coords[0],points->at(j).coords[1],points->at(j).coords[2],1.0f);
		Point c(points->at(k).coords[0],points->at(k).coords[1],points->at(k).coords[2],1.0f);

		Vector3 u = a-b;
		Vector3 v = c-b;
		Vector3 norm = u*v;
		Plane pl(norm.unit(),b);
		planes->push_back(pl);
	}

	Point a(points->at(0).coords[0],points->at(0).coords[1],points->at(0).coords[2],1.0f);
	Point b(points->at(1).coords[0],points->at(1).coords[1],points->at(1).coords[2],1.0f);
	Point c(points->at(2).coords[0],points->at(2).coords[1],points->at(2).coords[2],1.0f);

	Vector3 u = a-b;
	Vector3 v = c-b;
	Vector3 norm = v*u;
	Plane pl(norm.unit(),b);
	tilePlane = pl;
	angle = vectorAngle(tilePlane.normal.scale(-1),Vector3(0,-1,0));

	if(min_y != max_y)
	{
		Vector3 aa = rotateVector(u,tilePlane.normal,0);

		for(unsigned j = 1; j < 360; j++)
		{
			//cout << j << endl;
			Vector3 temp = rotateVector(u,tilePlane.normal,(float)j);

			if(temp.coords[1] < aa.coords[1])
			{
				aa = temp;
				//aa.print();
				slope = aa;
			}
		}
		slope = slope.unit();
	}

	//slope.print();

	vector<int> *ns = new vector<int>;
	for(unsigned j = 0; j < n; j++)
	{
		int nb = atoi(ss->at(i).c_str());
		ns->push_back(nb);
		i++;
	}
	neighbours = ns;
}

void Tile::draw()
{
	/*glBegin(GL_LINES);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white_colour);

	for(int i = points->size()-1; i >= 0; i--)
	{
		Point p = points->at(i) + planes->at(i).normal;
		glVertex4fv(points->at(i).coords);
		glVertex4fv(p.coords);
	}

	glEnd();*/

	//the board
	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green_colour);

	for(int i = points->size()-1; i >= 0; i--)
	{
		glNormal3fv(tilePlane.normal.coords);
		glVertex4fv(points->at(i).coords);
	}

	glEnd();

	//the sides
	for(unsigned int i = 0; i < points->size(); i++)
	{
		if(neighbours->at(i) == 0)
		{
			glBegin(GL_QUADS);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red_colour);
			int k = (i+1) % points->size();
			glNormal3fv(planes->at(i).normal.coords);
			glVertex4fv(points->at(i).coords);
			glVertex3f(points->at(i).coords[0],points->at(i).coords[1]+0.1,points->at(i).coords[2]);
			glVertex3f(points->at(k).coords[0],points->at(k).coords[1]+0.1,points->at(k).coords[2]);
			glVertex4fv(points->at(k).coords);
			glEnd();
		}
	}
}
