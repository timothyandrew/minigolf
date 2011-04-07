/*
 * Physics.h
 *
 *  Created on: Oct 16, 2008
 *      Author: the1schwartz
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Ball.h"
#include "Hole.h"

void gravity(Ball* ball, Hole* level);
void checkGradient(Ball* ball, Hole* level);
void checkBall(Ball* ball, Hole* level);
void hitWall(Ball* ball, Hole* level);

#endif /* PHYSICS_H_ */
