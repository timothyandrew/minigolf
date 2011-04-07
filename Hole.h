/*
 * Level.h
 *
 *  Created on: Oct 14, 2008
 *      Author: the1schwartz
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <string>
#include "Cup.h"
#include "Tee.h"
#include "Point.h"
#include "Tile.h"
#include "Ball.h"

using namespace std;

class Hole
{
public:
	Hole();
	virtual ~Hole();
	void create(Cup* c, Tee* t, int p, string n, vector<Tile*>* tss);
	void draw();
	void checkCup(Ball* ball);

	Cup* cup;
	Tee* tee;
	vector<Tile*>* tiles;
	int par;
	string name;
};

#endif /* LEVEL_H_ */
