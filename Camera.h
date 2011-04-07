/*
 * main.h
 *
 *  Created on: Oct 22, 2008
 *      Author: the1schwartz
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector3.h"
#include "Point.h"

class Camera
{
public:
	static Point camPos;
	static Vector3 camLook;
	static float xRot,yRot,zRot;
};

#endif /* MAIN_H_ */
