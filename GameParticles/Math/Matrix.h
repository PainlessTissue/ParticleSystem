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
__declspec(align(16)) class Matrix
{
public:

	//these are a bunch of overloaded operators that allow for 
	//less temporary variables to be created
	Matrix(); //default
	Matrix(const Matrix& t); //copy
	Matrix(float const &ROTZ);
	Matrix(const Vect4D * const SCALE);
	Matrix(Vect4D const & TRANS);

	Matrix(Vect4D const &v0, const Vect4D &v1, const Vect4D &v2, const Vect4D &v3);

	Matrix &operator=(const Matrix &m); //assignment
	~Matrix(); //destructor

	void setIdentMatrix();

	Matrix GetAdjugate();

	void Matrix::Inverse(Matrix &out);

	void* operator new(const size_t i);
	void* operator new[](const size_t i);
	void operator delete(void* p);
	void operator delete[](void *p);

	//made public for proxy creation. Wouldve taken far longer to make proxy if was private
	//private:
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


//proxy shit

struct mMul2
{
	const Matrix &m0, &m1;

	mMul2(const Matrix &mm0, const Matrix &mm1)
		:m0(mm0), m1(mm1) {};

	mMul2() = delete;
	mMul2(const mMul2 &m) = default;
	mMul2 operator = (const mMul2 &m) = delete;
	~mMul2() = default;

	operator Matrix()
	{
		return Matrix(
			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v0.x), m1.v0._m),
						_mm_mul_ps(_mm_set_ps1(m0.v0.y), m1.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v0.z), m1.v2._m),
						_mm_mul_ps(_mm_set_ps1(m0.v0.w), m1.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v1.x), m1.v0._m),
						_mm_mul_ps(_mm_set_ps1(m0.v1.y), m1.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v1.z), m1.v2._m),
						_mm_mul_ps(_mm_set_ps1(m0.v1.w), m1.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v2.x), m1.v0._m),
						_mm_mul_ps(_mm_set_ps1(m0.v2.y), m1.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v2.z), m1.v2._m),
						_mm_mul_ps(_mm_set_ps1(m0.v2.w), m1.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v3.x), m1.v0._m),
						_mm_mul_ps(_mm_set_ps1(m0.v3.y), m1.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v3.z), m1.v2._m),
						_mm_mul_ps(_mm_set_ps1(m0.v3.w), m1.v3._m)))));
	}

};

struct mMul3
{
	const Matrix &m0, &m1, &m2;

	mMul3(const mMul2 &mm0, const Matrix &mm1)
		:m0(mm0.m0), m1(mm0.m1), m2(mm1) {};

	mMul3() = delete;
	mMul3(const mMul3 &m) = default;
	mMul3 operator = (const mMul3 &m) = delete;
	~mMul3() = default;

	operator Matrix()
	{
		Matrix a(
			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v0.x), m1.v0._m),
						_mm_mul_ps(_mm_set_ps1(m0.v0.y), m1.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v0.z), m1.v2._m),
						_mm_mul_ps(_mm_set_ps1(m0.v0.w), m1.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v1.x), m1.v0._m),
						_mm_mul_ps(_mm_set_ps1(m0.v1.y), m1.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v1.z), m1.v2._m),
						_mm_mul_ps(_mm_set_ps1(m0.v1.w), m1.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v2.x), m1.v0._m),
						_mm_mul_ps(_mm_set_ps1(m0.v2.y), m1.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v2.z), m1.v2._m),
						_mm_mul_ps(_mm_set_ps1(m0.v2.w), m1.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v3.x), m1.v0._m),
						_mm_mul_ps(_mm_set_ps1(m0.v3.y), m1.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(m0.v3.z), m1.v2._m),
						_mm_mul_ps(_mm_set_ps1(m0.v3.w), m1.v3._m)))));

		//second matrix
		return Matrix(
			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(a.v0.x), m2.v0._m),
						_mm_mul_ps(_mm_set_ps1(a.v0.y), m2.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(a.v0.z), m2.v2._m),
						_mm_mul_ps(_mm_set_ps1(a.v0.w), m2.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(a.v1.x), m2.v0._m),
						_mm_mul_ps(_mm_set_ps1(a.v1.y), m2.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(a.v1.z), m2.v2._m),
						_mm_mul_ps(_mm_set_ps1(a.v1.w), m2.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(a.v2.x), m2.v0._m),
						_mm_mul_ps(_mm_set_ps1(a.v2.y), m2.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(a.v2.z), m2.v2._m),
						_mm_mul_ps(_mm_set_ps1(a.v2.w), m2.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(a.v3.x), m2.v0._m),
						_mm_mul_ps(_mm_set_ps1(a.v3.y), m2.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(a.v3.z), m2.v2._m),
						_mm_mul_ps(_mm_set_ps1(a.v3.w), m2.v3._m)))));
	}

};

inline mMul2 operator *(const Matrix &m0, const Matrix &m1)
{
	return mMul2(m0, m1);
}

inline mMul3 operator*(const mMul2 &m0, const Matrix &m1)
{
	return mMul3(m0, m1);
}

#endif  // Matrix.h
