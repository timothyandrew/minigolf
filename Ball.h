/*
 * Ball.h
 *
 *  Created on: Oct 14, 2008
 *      Author: the1schwartz
 */

#ifndef BALL_H_
#define BALL_H_

class Ball;

#include "Point.h"
#include "Vector3.h"

class Ball
{
public:
	Ball();
	virtual ~Ball();
	void create(Point const& p, int tile);
	void draw();
	void move();
	void changeDir(float angle);

	Point pos;
	float radius;
	Vector3 velocity;
	float speed;
	float startSpeed;
	bool moving;
	float rotation;
	int curTile;
	bool flying;
	bool finished;
};

#endif /* BALL_H_ */
