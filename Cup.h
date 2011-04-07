/*
 * Cup.h
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#ifndef CUP_H_
#define CUP_H_

#define PI 3.14159265358979

#include <vector>
#include <string>
#include "Point.h"
#include "gllib.h"

using namespace std;

class Cup
{
public:
	void create(vector<string> *ss);
	void draw();

	Point cupPos;
	float radius;
	int tile;
};

#endif /* CUP_H_ */
