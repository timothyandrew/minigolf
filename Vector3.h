#ifndef VECTOR3_H_
#define VECTOR3_H_

// forward declaration for mutually recursive inclusion
class Vector3;

#include <stdio.h>
#include "Point.h"

class Vector3
{
public:
	Vector3();
	Vector3(float,float,float);
	virtual ~Vector3();
	Vector3 scale (float const& param);
	float dot (Vector3 const& param);
	Vector3 operator* (Vector3 const& param);

	// Scalar right-division
	Vector3 operator/ (float scaleFactor);

	// Add a point to a vector to get another point
	// Does so in Cartesian space, but leaves w-coordinate the same
	Point operator+ (Point point);

	// Add a vector to a vector to get another vector
	// Does so in Cartesian space, but leaves w-coordinate the same
	Vector3 operator+ (Vector3 vector);

	// Negation (unary minus)
	Vector3 operator- ();

	// Subtraction (returns a vector)
	Vector3 operator- (Vector3 vector);

	// Copy another Vector & return self
	Vector3& operator= (Vector3 vector);

	float length();
	Vector3 unit();

	float coords[3];

	// routine to read it in
	// returns 0 on success, non-0 on failure
	long ReadCartesian(FILE *inFile);

	// routine to print it out
	void Print(FILE *outFile);

	void print();
};

#endif /*VECTOR3_H_*/
