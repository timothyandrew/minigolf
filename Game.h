/*
 * Game.h
 *
 *  Created on: Oct 21, 2008
 *      Author: the1schwartz
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "Course.h"
#include "Camera.h"
#include "Hole.h"

using namespace std;

class Game
{
public:
	Game();
	virtual ~Game();
	void create(int players, const char* file);
	void initHole(int h);
	void nextHole();
	Hole* getCurHole();
	void nextPlayer();
	Ball* getCurPlayer();

	vector<Ball*>* balls;
	Course* course;
	unsigned int curHole;
	unsigned int curBall;
	unsigned int numPlayers;
};

#endif /* GAME_H_ */
