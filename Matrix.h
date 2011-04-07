/*
 * Matrix.h
 *
 *  Created on: Oct 14, 2008
 *      Author: the1schwartz
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "Point.h"
#include "Vector3.h"

#define ERROR_TOLERANCE 1E-7

class Matrix
{
public:

	// returns an identity matrix
	static Matrix Identity();

	// returns a zero matrix
	static Matrix Zero();

	// sets a specified element in the matrix
	void SetElement(int row, int col, float value);

	// returns a specified element in the matrix
	float& Element(int row, int col);

	// Copy another Matrix & return self
	Matrix& operator= (Matrix otherMatrix);

	// Add another Matrix
	Matrix operator+ (Matrix otherMatrix);

	// Subtract another Matrix
	Matrix operator- (Matrix otherMatrix);

	// Scale the matrix by a constant
	Matrix operator* (float scaleFactor);

	// Left-multiply a Point
	Point operator* (Point point);

	// Left-multiply a Vector
	Vector3 operator* (Vector3 vector);

	// Right-multiply by another matrix
	Matrix operator* (Matrix otherMatrix);

	// Scales a row by a given factor
	void ScaleRow(int row, float scaleFactor);

	// Swaps two rows
	void SwapRows(int row1, int row2);

	// Adds multiple of one row to another row
	void AddRows(int row1, float multiple, int row2);

	// Reduces all elements in a column except the diagonal element
	// Returns 0 on success, 1 if the column cannot be reduced
	int ReduceColumn(int column, Matrix &inverse);

	// Computes a matrix inverse with brute force Gauss-Jordan method
	// returns a zero matrix on failure
	Matrix Inverse();

	// routines to extract the translation part of the matrix
	// assumes no entries in perspective section of matrix
	Vector3 TranslationVector();
	Matrix TranslationMatrix();

	// routine to extract the rotation part of the matrix
	// assumes no entries in perspective section of matrix
	Matrix RotationMatrix();


	// remember: this is in column-major form
	float coords[16];
};

#endif /* MATRIX_H_ */
