#include <iostream>
#include <math.h>
#include "Vector3.h"

using namespace std;

// default constructor
Vector3::Vector3()
{
	coords[0] = coords[1] = coords[2] = 0.0f;
}

// copy constructor
Vector3::Vector3(float x, float y, float z)
{
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
}

Vector3::~Vector3()
{
}

// Add a vector to a vector to get another vector
// Does so in Cartesian space, but leaves w-coordinate the same
Vector3 Vector3::operator+ (Vector3 vector)
{
	Vector3 result;
	for (int i = 0; i < 3; i++)
	{
		result.coords[i] = coords[i] + vector.coords[i];
	}
	return result;
}

// Add a point to a vector to get another point
// Does so in Cartesian space, but leaves w-coordinate the same
Point Vector3::operator+ (Point point)
{
	Point result;
	for (int i = 0; i < 3; i++)
	{
		result.coords[i] = this->coords[i]*point.coords[3] + point.coords[i];
	}
	result.coords[3] = point.coords[3];
	return result;
}

// Negation (unary minus)
Vector3 Vector3::operator- ()
{
	Vector3 result;
	for (int i = 0; i < 3; i++)
	{
		result.coords[i] = coords[i] * -1.0f;
	}
	return result;
}

// Subtraction (returns a vector)
Vector3 Vector3::operator- (Vector3 vector)
{
	Vector3 result;
	for (int i = 0; i < 3; i++)
	{
		result.coords[i] = this->coords[i] - vector.coords[i];
	}
	return result;
}

Vector3 Vector3::scale (float const& param)
{
	Vector3 temp;
	for(unsigned int i = 0; i < 3; i++)
	{
		temp.coords[i] = coords[i] * param;
	}
	return temp;
}

float Vector3::dot (Vector3 const& param)
{
	float d = 0.0f;
	for(unsigned i = 0; i < 3; i++)
	{
		d += coords[i]*param.coords[i];
	}
	return d;
}

Vector3 Vector3::operator* (Vector3 const& param)
{
	Vector3 result;
	result.coords[0] = coords[1] * param.coords[2] - coords[2] * param.coords[1];
	result.coords[1] = coords[2] * param.coords[0] - coords[0] * param.coords[2];
	result.coords[2] = coords[0] * param.coords[1] - coords[1] * param.coords[0];

	return result;
}

// Copy another Vector & return self
Vector3& Vector3::operator= (Vector3 vector)
{
	for (int i = 0; i < 3; i++)
	{
		coords[i] = vector.coords[i];
	}
	return (*this);
}

// Scalar right-division
Vector3 Vector3::operator/ (float scaleFactor)
{
	Vector3 result;
	for (int i = 0; i < 3; i++)
	{
		result.coords[i] = coords[i] / scaleFactor;
	}
	return result;
}

// scalar left-multiplication
Vector3 operator *(float scaleFactor, Vector3 vector)
{
	Vector3 result;
	for (int i = 0; i < 3; i++)
	{
		result.coords[i] = scaleFactor * vector.coords[i];
	}
	return result;
} // scalar left-multiplication

float Vector3::length()
{
	return sqrt(dot(*this));
}

Vector3 Vector3::unit()
{
	float l = length();
	if(l == 0)
	{
		return Vector3(0,0,0);
	}
	Vector3 result = (*this) / l;
	return result;
}

void Vector3::print()
{
	cout << coords[0] << "," << coords[1] << "," << coords[2] << endl;
}
