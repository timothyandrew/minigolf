/*
 * Physics.cpp
 *
 *  Created on: Oct 16, 2008
 *      Author: the1schwartz
 */

#include <iostream>
#include "Physics.h"
#include "Vector3.h"
#include "Math.h"
#include "Game.h"

using namespace std;

static Vector3 g(0,-0.001f,0);
static float friction = 0.9995f;
static float gg = 0.001f;
static float elastic = 0.5f;

void gravity(Ball* ball, Hole* level)
{
	if(level->tiles->at(ball->curTile-1)->tilePlane.distance(ball->pos) > 0)
	{
		ball->velocity = ball->velocity + g.scale(0.0005f);
		ball->flying = true;
	}
	else
	{
		//ball->speed = ball->speed * friction;
		ball->velocity = ball->velocity.scale(friction);
		if(ball->flying)
		{
			ball->velocity.coords[1] *= -elastic;
			ball->flying = false;
		}
		if(ball->velocity.length() < 0.00005f && level->tiles->at(ball->curTile-1)->angle == 0)
		{
			ball->moving = false;
			ball->velocity.coords[1] = 0.0f;
			ball->speed = ball->startSpeed;
			//ball->velocity = ball->velocity.scale(0.0f);
		}
	}
}

void checkGradient(Ball* ball, Hole* level)
{
	if(level->tiles->at(ball->curTile-1)->tilePlane.distance(ball->pos) <= 0)
	{
		float a = degToRad(level->tiles->at(ball->curTile-1)->angle);
		Vector3 s = level->tiles->at(ball->curTile-1)->slope;
		s = s.scale(gg*sin(a)*0.0005f);
		ball->velocity = ball->velocity + s;
		Point newPos = ball->pos + ball->velocity;
		newPos.coords[1] = heightInPlane(newPos.coords[0], newPos.coords[2], level->tiles->at(ball->curTile-1)->tilePlane);
		//ball->velocity.coords[1] = newPos.coords[1] - ball->pos.coords[1];
		//ball->velocity.print();
	}
}

void checkBall(Ball* ball, Hole* level)
{
	if(level->tiles->at(ball->curTile-1)->tilePlane.distance(ball->pos) <= 0)
	{
		ball->pos.coords[1] = heightInPlane(ball->pos.coords[0], ball->pos.coords[2], level->tiles->at(ball->curTile-1)->tilePlane);
	}
}

void hitWall(Ball* ball, Hole* level)
{
	int curIndex = ball->curTile-1;
	for(unsigned i = 0; i < level->tiles->at(curIndex)->planes->size(); i++)
	{
		if(level->tiles->at(curIndex)->planes->at(i).distance(ball->pos) - ball->radius <= 0)
		{
			if(level->tiles->at(curIndex)->neighbours->at(i) == 0)
			{
				float d = ball->velocity.dot(level->tiles->at(curIndex)->planes->at(i).normal);

				d *= 2.0f;

				ball->velocity = ball->velocity - level->tiles->at(curIndex)->planes->at(i).normal.scale(d);
				//ball->velocity = ball->velocity.scale(0.95f);

				if(level->tiles->at(curIndex)->planes->at(i).distance(ball->pos) < 0)
				{
					ball->pos = ball->pos + level->tiles->at(curIndex)->planes->at(i).normal.scale(0.1f);
					cout << "hit" << endl;
				}
			}
			else
			{
				ball->curTile = level->tiles->at(curIndex)->neighbours->at(i);
			}
		}
	}
}
