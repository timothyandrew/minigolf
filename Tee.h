/*
 * Tee.h
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#ifndef TEE_H_
#define TEE_H_

#include <vector>
#include <string>
#include "Point.h"
#include "gllib.h"

using namespace std;

class Tee
{
public:
	void create(vector<string> *ss);
	void draw();

	Point teePos;
	float halfWidth;
	int tile;
};

#endif /* TEE_H_ */
