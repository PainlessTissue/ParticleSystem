#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include "Vect4D.h"

#include <xmmintrin.h>
#include <smmintrin.h>  

// forward declare
class Vect4D;

// class
class Matrix
{
public:

	Matrix();	
	Matrix(const Matrix& t);	

	//specialized for rvo and only floats
	Matrix(
		const float &m0, const float &m1, const float &m2, const float &m3,
		const float &m4, const float &m5, const float &m6, const float &m7,
		const float &m8, const float &m9, const float &m10, const float &m11,
		const float &m12, const float &m13, const float &m14, const float &m15);

	Matrix(const Vect4D &v0, const Vect4D &v1, const Vect4D &v2, const Vect4D &v3);

	~Matrix();

	//my reasoning for changing this to short is because it is the lowest byte size
	//possible for storing integer values, and are we only going to 3
	void set(const short &row, const Vect4D *t );
	void get(const short &row, Vect4D *vOut );

	void setIdentMatrix();
	void setTransMatrix(const Vect4D *t );
	void setScaleMatrix(const Vect4D *s );
	void setRotZMatrix(const float &Z_Radians );

	float &operator[](const INDEX_ENUM &e);
	
	Matrix operator*(const Matrix &t );
	//Matrix operator*( float s );

	float Determinant();
	
	Matrix GetAdjugate();
	Matrix& Matrix::operator/=(float t);
	
	void Matrix::Inverse(Matrix &out );
	
private:
	//64
	union
	{
		struct
		{
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
		};

		struct
		{
			// ROW 0
			float m0;
			float m1;
			float m2;
			float m3;

			// ROW 1
			float m4;
			float m5;
			float m6;
			float m7;

			// ROW 2
			float m8;
			float m9;
			float m10;
			float m11;

			// ROW 3
			float m12;
			float m13;
			float m14;
			float m15;

		};
	};
};

#endif  // Matrix.h
