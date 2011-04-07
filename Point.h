/*
 * Point.h
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#ifndef POINT_H_
#define POINT_H_

// forward declaration for mutually recursive inclusion
class Point;

#include <stdio.h>
#include "Vector3.h"

// Assume that we carry EVERYTHING in explicit homogeneous coordinates
class Point
{
	public:
	float coords[4];

	// default constructor
	Point();

	// copy constructor
	Point(float x, float y, float z, float w);

	// Copy another Point & return self
	Point &operator= (Point point);

	bool operator== (Point point);

	bool operator!= (Point point);

	// Scalar right-multiplication
	Point operator* (float scaleFactor);

	// Scalar right-division
	Point operator/ (float scaleFactor);

	// Add a vector to a point to get another point
	// Does so in Cartesian space, but leaves w-coordinate the same
	Point operator+ (Vector3 vector);

	// Negation (unary minus)
	Point operator- ();

	// Subtract a vector from a point
	Point operator- (Vector3 vector);

	// Subtraction (returns a vector)
	Vector3 operator- (Point point);

	// Divide through by homogeneous coordinate (if a point)
	Point DeHomogenize();

	// routine to read it in as a Cartesian (3 coords)
	// returns 0 on success, non-0 on failure
	long ReadCartesian(FILE *inFile);

	// routines to print it out
	void Print(FILE *outFile);
	void PrintCartesian(FILE *outFile);

	void print();
};

// Scalar left-multiplication
Point operator * (Point point, float scaleFactor);

#endif /* POINT_H_ */
