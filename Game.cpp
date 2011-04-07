/*
 * Game.cpp
 *
 *  Created on: Oct 21, 2008
 *      Author: the1schwartz
 */

#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::create(int players, const char* file)
{
	course = new Course();
	course->create(file);
	curHole = 0;
	curBall = 0;
	numPlayers = players;
	balls = new vector<Ball*>;

	for(unsigned int i = 0; i < numPlayers; i++)
	{
		balls->push_back(new Ball);
	}
}

void Game::initHole(int h)
{
	for(unsigned int i = 0; i < numPlayers; i++)
	{
		balls->at(i)->create(course->holes->at(h)->tee->teePos,course->holes->at(h)->tee->tile);
	}

	Camera::camPos = course->holes->at(h)->tee->teePos;
	Camera::camPos = Camera::camPos + Camera::camLook;
	Camera::xRot = 0.0f;
	Camera::yRot = 0.0f;
	Camera::zRot = 0.0f;
}

void Game::nextHole()
{
	if(curHole+1 < course->holes->size())
	{
		curHole++;
		initHole(curHole);
	}
}

void Game::nextPlayer()
{
	if(getCurHole()->tiles->at(getCurPlayer()->curTile-1)->tilePlane.distance(getCurPlayer()->pos) <= 0)
	{
		if(getCurPlayer()->velocity.length() < 0.00005f && getCurHole()->tiles->at(getCurPlayer()->curTile-1)->angle == 0)
		{
			getCurPlayer()->moving = false;
			getCurPlayer()->velocity.coords[1] = 0.0f;
			getCurPlayer()->speed = getCurPlayer()->startSpeed;
			curBall = (curBall+1) % numPlayers;
		}
	}
}

Ball* Game::getCurPlayer()
{
	return balls->at(curBall);
}

Hole* Game::getCurHole()
{
	return course->holes->at(curHole);
}
