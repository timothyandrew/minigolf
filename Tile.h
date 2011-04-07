/*
 * Tile.h
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#ifndef TILE_H_
#define TILE_H_

#include <vector>
#include <string>
#include "Point.h"
#include "Vector3.h"
#include "gllib.h"
#include "Plane.h"

using namespace std;

class Tile
{
public:
	void create(vector<string> *ss);
	void draw();

	unsigned int id;
	vector<int>* neighbours;
	vector<Plane>* planes;
	Plane tilePlane;
	vector<Point>* points;
	float angle;
	Vector3 slope;
};

#endif /* TILE_H_ */
