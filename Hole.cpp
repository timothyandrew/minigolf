/*
 * Level.cpp
 *
 *  Created on: Oct 14, 2008
 *      Author: the1schwartz
 */

#include <math.h>
#include "Hole.h"

Hole::Hole()
{
}



Hole::~Hole()
{
}

void Hole::create(Cup* c, Tee* t, int p, string n, vector<Tile*>* tss)
{
	cup = c;
	tee = t;
	tiles = tss;
	par = p;
	name = n;
}

void Hole::draw()
{
	for(unsigned i = 0; i < tiles->size(); i++)
	{
		tiles->at(i)->draw();
	}
	tee->draw();
	cup->draw();
}

void Hole::checkCup(Ball* ball)
{
	float d = (ball->pos.coords[0]-cup->cupPos.coords[0])*(ball->pos.coords[0]-cup->cupPos.coords[0])+
		(ball->pos.coords[2]-cup->cupPos.coords[2])*(ball->pos.coords[2]-cup->cupPos.coords[2]);

	if(sqrt(d) <= ball->radius-0.02)
	{
		ball->speed = 0;
		ball->velocity = ball->velocity.scale(0.0f);
		ball->pos.coords[1] -= ball->radius*2.0f;
		ball->finished = true;
	}
}
