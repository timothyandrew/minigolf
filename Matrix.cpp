/*
 * Matrix.cpp
 *
 *  Created on: Oct 14, 2008
 *      Author: the1schwartz
 */

#include <math.h>
#include "Matrix.h"

// returns an identity matrix

Matrix Matrix::Identity()
{
	Matrix result;
	// quick hack: diagonal elements are zero mod 5
	for (int i = 0; i < 16; i++)
	{
		result.coords[i] = !(i%5);
	}
	return result;
}

// returns a zero matrix
Matrix Matrix::Zero()
{
	Matrix result;
	for (int i = 0; i < 16; i++)
	{
		result.coords[i] = 0;
	}
	return result;
}

void Matrix::SetElement(int row, int col, float value)
{
	coords[row + 4 * col] = value;
}

// returns a specified element in the matrix
float& Matrix::Element(int row, int col)
{
	// column-major, so multiply column by height
	return coords[row + 4 * col];
}

// Copy another Matrix & return self
Matrix& Matrix::operator= (Matrix otherMatrix)
{
	for (int i = 0; i < 16; i++)
	{
		coords[i] = otherMatrix.coords[i];
	}
	return (*this);
}

// Add another Matrix
Matrix Matrix::operator+ (Matrix otherMatrix)
{
	Matrix result;
	for (int i = 0; i < 16; i++)
	{
		result.coords[i] = coords[i] + otherMatrix.coords[i];
	}
	return result;
}

// Subtract another Matrix
Matrix Matrix::operator- (Matrix otherMatrix)
{
	Matrix result;
	for (int i = 0; i < 16; i++)
	{
		result.coords[i] = coords[i] - otherMatrix.coords[i];
	}
	return result;
}

// Scale the matrix by a constant
Matrix Matrix::operator* (float scaleFactor)
{
	Matrix result;
	for (int i = 0; i < 16; i++)
	{
		result.coords[i] = coords[i] * scaleFactor;
	}
	return result;
}

// Left-multiply a Point
Point Matrix::operator* (Point point)
{
	Point result;

	// loop through rows of matrix, multiplying by point
	for (int row = 0; row < 4; row++)
	{
		result.coords[row] = 0.0f;
		// loop along row, multiplying and adding
		for (int col = 0; col < 4; col++)
		{
			result.coords[row] += Element(row,col) * point.coords[col];
		}
	}

	return result;
}

// Left-multiply a Vector
Vector3 Matrix::operator* (Vector3 vector)
{
	Vector3 result;

	// loop through rows of matrix, multiplying by point
	for (int row = 0; row < 3; row++)
	{
		result.coords[row] = 0.0f;
		// loop along row, multiplying and adding
		// note that we ignore the fourth (w) coord
		for (int col = 0; col < 3; col++)
		{
			result.coords[row] += Element(row,col) * vector.coords[col];
		}
	}

	return result;
}

// multiply by another matrix
Matrix Matrix::operator* (Matrix otherMatrix)
{
	// make a temporary copy of the other
	Matrix result;

	// now do the standard loops: it's inefficient, but works
	for (int row = 0; row < 4; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			result.Element(row, col) = 0.0;
			for (int entry = 0; entry < 4; entry++)
			{
				result.Element(row, col) += Element(row, entry) *
					otherMatrix.Element(entry, col);
			}
		}
	}
	return result;
}

// Scales a row by a given factor
void Matrix::ScaleRow(int row, float scaleFactor)
{
	for (int entry = 0; entry < 4; entry++)
	{
		Element(row, entry) *= scaleFactor;
	}
}

// Swaps two rows
void Matrix::SwapRows(int row1, int row2)
{
	float temp;
	for (int entry = 0; entry < 4; entry++)
	{
		temp = Element(row1, entry);
		Element(row1, entry) = Element(row2, entry);
		Element(row2, entry) = temp;
	}
}

// Adds multiple of one row to another row
void Matrix::AddRows(int row1, float multiple, int row2)
{
	// simple loop to add entries
	for (int entry = 0; entry < 4; entry++)
	{
		Element(row1, entry) += multiple * Element(row2, entry);
	}
}

// Reduces all elements in a column except the diagonal element
// Returns 0 on success, 1 if the column cannot be reduced
int Matrix::ReduceColumn(int column, Matrix &inverse)
{
	// loop variable for working down column
	int row, pivot = column;

	// find the first non-zero element in the column
	// that is not above the diagonal
	for (row = pivot; row < 4; row++)
		if (fabs(Element(row, pivot)) > ERROR_TOLERANCE)
			break;

	// if we didn't find one, return an error code
	if (row == 4) return 1;

	// if we did, but it wasn't on the diagonal, swap with the pivot row
	// this makes sure we never get divide by zero errors
	if (row != pivot)
	{
		SwapRows(pivot, row);
		inverse.SwapRows(pivot, row);
	}

	// now scale the pivot row so the pivot element is one
	float scaleFactor = 1.0 / Element(pivot, pivot);
	ScaleRow(pivot, scaleFactor);
	inverse.ScaleRow(pivot, scaleFactor);

	// for each row
	for (row = 0; row < 4; row++)
	{
		// skip the row we're pivoting on
		if (row == column) continue;
		scaleFactor = -Element(row, pivot);
		AddRows(row, scaleFactor, pivot);
		inverse.AddRows(row, scaleFactor, pivot);
	}

	// and we're done
	return 0;
}

// Computes a matrix inverse with brute force Gauss-Jordan method
// returns a zero matrix on failure
Matrix Matrix::Inverse()
{
	// working copy of the matrix
	Matrix workingCopy = (*this);
	Matrix result = Matrix::Identity();

	// now perform Gauss-Jordan reduction on the elements of each column
	if (0 != workingCopy.ReduceColumn(0, result)) return Zero();
	if (0 != workingCopy.ReduceColumn(1, result)) return Zero();
	if (0 != workingCopy.ReduceColumn(2, result)) return Zero();
	if (0 != workingCopy.ReduceColumn(3, result)) return Zero();

	// and we're done!
	return result;
}

// routines to extract the translation part of the matrix
// assumes no entries in perspective section of matrix
Vector3 Matrix::TranslationVector()
{
	Vector3 result;
	// copy last column into result vector
	for (int i = 0; i < 3; i++)
		result.coords[i] = coords[i,3];
	return result;
}

Matrix Matrix::TranslationMatrix()
{
	Matrix result = Identity();

	// copy last column into result
	for (int i = 0; i < 3; i++)
		result.Element(i,3) = Element(i,3);
	return result;
}

// routine to extract the rotation part of the matrix
// assumes no entries in perspective section of matrix
Matrix Matrix::RotationMatrix()
{
	Matrix result = Identity();

	// copy first three elements of first three columns into result
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			result.Element(i,j) = Element(i,j);
	return result;
}
