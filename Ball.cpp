/*
 * Ball.cpp
 *
 *  Created on: Oct 14, 2008
 *      Author: the1schwartz
 */

#include <iostream>
#include "Ball.h"
#include "gllib.h"
#include "Math.h"

using namespace std;

static GLfloat white_colour[] = {1.0f, 1.0f, 1.0f};

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::create(Point const& p, int tile)
{
	radius = 0.03f;
	pos = p;

	//pos.coords[1] += 1.0f;

	speed = 0.0005f;
	startSpeed = speed;
	velocity = Vector3(0,0,-1);
	moving = false;
	rotation = 0.0f;
	curTile = tile;
	flying = false;
	finished = false;
}

void Ball::draw()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white_colour);
	if(!moving)
	{
		glBegin(GL_LINES);
		Point p1(pos.coords[0],pos.coords[1]+radius,pos.coords[2],1.0f);
		glVertex3fv(p1.coords);
		Point p2 = p1+velocity;
		glVertex4fv(p2.coords);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(pos.coords[0],pos.coords[1]+radius,pos.coords[2]);
	glutSolidSphere (radius, 20, 16);
	glPopMatrix();
}

void Ball::move()
{
	pos = pos+velocity;
	//pos.print();
	//Vector3 v = direction.scale(speed);
	//direction.print();
}

void Ball::changeDir(float angle)
{
	rotation = angle;
	velocity = rotateVector(velocity,Vector3(0,1,0),rotation);
	velocity = velocity.unit();
}
