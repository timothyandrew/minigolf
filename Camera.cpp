/*
 * Camera.cpp
 *
 *  Created on: Oct 22, 2008
 *      Author: the1schwartz
 */

#include "Camera.h"

float Camera::xRot = 0.0f;
float Camera::yRot = 0.0f;
float Camera::zRot = 0.0f;
Point Camera::camPos;
Vector3 Camera::camLook(0.0f,3.0f,2.5f);
