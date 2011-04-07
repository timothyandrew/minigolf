/*
 * Point.cpp
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "Point.h"

using namespace std;

// default constructor
Point::Point()
{
	coords[0] = coords[1] = coords[2] = 0.0f;
	coords[3] = 1.0f;
}

// copy constructor
Point::Point(float x, float y, float z, float w)
{
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
	coords[3] = w;
}

// Copy another Point & return self
Point& Point::operator= (Point point)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		coords[i] = point.coords[i];
	}
	return (*this);
}

bool Point::operator== (Point point)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		if(coords[i] != point.coords[i])
		{
			return false;
		}
	}
	return true;
}

bool Point::operator!= (Point point)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		if(coords[i] != point.coords[i])
		{
			return true;
		}
	}
	return false;
}

// Scalar right-multiplication
Point Point::operator* (float scaleFactor)
{
	Point result;
	int i;
	for (i = 0; i < 4; i++)
	{
		result.coords[i] = coords[i] * scaleFactor;
	}
	return result;
}


// Scalar right-division
Point Point::operator/ (float scaleFactor)
{
	Point result;
	int i;
	for (i = 0; i < 4; i++)
	{
		result.coords[i] = coords[i] / scaleFactor;
	}
	return result;
}

// Add a Vector3 to a point to get another point
// Does so in Cartesian space, but leaves w-coordinate the same
Point Point::operator+ (Vector3 vector)
{
	Point result;
	int i;
	// add the Vector3, multiplied by w
	for (i = 0; i < 4; i++)
	{
		result.coords[i] = coords[i] + vector.coords[i] * coords[3];
	}
	return result;
}

// Negation (unary minus)
Point Point::operator- ()
{
	Point result;
	int i;
	// note that the w coordinate is unchanged
	// either that, or we could flip w instead
	for (i = 0; i < 3; i++)
	{
		result.coords[i] = -coords[i];
	}
	return result;
}

// Subtract a Vector3 from a point
Point Point::operator- (Vector3 vector)
{
	Point result;
	int i;
	// subtract the Vector3, multiplied by w
	for (i = 0; i < 4; i++)
	{
		result.coords[i] = coords[i] - vector.coords[i] * coords[3];
	}
	return result;
}

// Subtraction (returns a Vector3)
Vector3 Point::operator- (Point point)
{
	Vector3 result;
	int i;
	for (i = 0; i < 3; i++)
	{
		result.coords[i] = coords[i] / coords[3] - point.coords[i] / point.coords[3];
	}
	return result;
}

// Divide through by homogeneous coordinate (if a point)
Point Point::DeHomogenize()
{
	Point result;
	int i;
	for (i = 0; i < 3; i++)
	{
		result.coords[i] = coords[i] / coords[3];
	}
	coords[3] = 0.0;
	return result;
}

// routine to read it in as a Cartesian (3 coords)
// returns 0 on success, non-0 on failure
long Point::ReadCartesian(FILE *inFile)
{
	// try reading in three values
	long nScanned = fscanf(inFile, "%f %f %f ",
		&(coords[0]), &(coords[1]), &(coords[2]));

	// check to make sure we read 3 in
	if (nScanned != 3)
		return -1;

	// set homogeneous coordinate
	coords[3] = 1.0;

	// we succeeded
	return 0;
}

// routine to print it out
void Point::Print(FILE *outFile)
{
	fprintf(outFile, "(%10.6f, %10.6f, %10.6f, %10.6f)",
		coords[0], coords[1], coords[2], coords[3]);
}

// routine to print it out
void Point::PrintCartesian(FILE *outFile)
{
	fprintf(outFile, " %10.6f %10.6f %10.6f",
		coords[0]/coords[3], coords[1]/coords[3], coords[2]/coords[3]);
}

// Scalar left-multiplication
Point operator* (Point point, float scaleFactor)
{ // operator *
	Point result;
	int i;
	for (i = 0; i < 4; i++)
	{
		result.coords[i] = point.coords[i] * scaleFactor;
	}
	return result;
} // operator *

void Point::print()
{
	cout << coords[0] << "," << coords[1] << "," << coords[2] << "," << coords[3] << endl;
}
