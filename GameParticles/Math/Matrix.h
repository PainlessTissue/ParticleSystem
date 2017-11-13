#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include "Vect4D.h"

#include <xmmintrin.h>
#include <smmintrin.h>  

#define PROXY 0

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

	//my reasoning for changing this to shoort is because it is the lowest byte size
	void set(const char &row, const Vect4D *t);
	void get(const char &row, Vect4D *vOut);

	void setIdentMatrix();
	void setTransMatrix(const Vect4D *t);
	void setScaleMatrix(const Vect4D *s);
	void setRotZMatrix(const float &Z_Radians);

	float &operator[](const short &e);

#if !PROXY
	Matrix operator*(const Matrix &t);
#endif
	//Matrix operator*( float s );

	float Determinant();

	Matrix GetAdjugate();
	Matrix& Matrix::operator/=(float t);

	void Matrix::Inverse(Matrix &out);

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

#if PROXY
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
		return Matrix();
	}

};

struct mMul4
{
	const Matrix &m0, &m1, &m2, &m3;

	mMul4(const mMul3 &mm0, const Matrix &mm1)
		:m0(mm0.m0), m1(mm0.m1), m2(mm0.m2), m3(mm1) {};

	mMul4() = delete;
	mMul4(const mMul4 &m) = default;
	mMul4 operator = (const mMul4 &m) = delete;
	~mMul4() = default;

	operator Matrix()
	{
		return Matrix();
	}

};


struct mMul5
{
	const Matrix &m0, &m1, &m2, &m3, &m4;

	mMul5(const mMul4 &mm0, const Matrix &mm1)
		:m0(mm0.m0), m1(mm0.m1), m2(mm0.m2), m3(mm0.m3), m4(mm1) {};

	mMul5() = delete;
	mMul5(const mMul5 &m) = default;
	mMul5 operator = (const mMul5 &m) = delete;
	~mMul5() = default;

	operator Matrix()
	{
		//first matrix
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
		Matrix b(
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

		//third matrix
		Matrix c(
			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(b.v0.x), m3.v0._m),
						_mm_mul_ps(_mm_set_ps1(b.v0.y), m3.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(b.v0.z), m3.v2._m),
						_mm_mul_ps(_mm_set_ps1(b.v0.w), m3.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(b.v1.x), m3.v0._m),
						_mm_mul_ps(_mm_set_ps1(b.v1.y), m3.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(b.v1.z), m3.v2._m),
						_mm_mul_ps(_mm_set_ps1(b.v1.w), m3.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(b.v2.x), m3.v0._m),
						_mm_mul_ps(_mm_set_ps1(b.v2.y), m3.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(b.v2.z), m3.v2._m),
						_mm_mul_ps(_mm_set_ps1(b.v2.w), m3.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(b.v3.x), m3.v0._m),
						_mm_mul_ps(_mm_set_ps1(b.v3.y), m3.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(b.v3.z), m3.v2._m),
						_mm_mul_ps(_mm_set_ps1(b.v3.w), m3.v3._m)))));
		/*
		//third matrix
		Matrix d(
			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v0.x), m3.v0._m),
						_mm_mul_ps(_mm_set_ps1(c.v0.y), m3.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v0.z), m3.v2._m),
						_mm_mul_ps(_mm_set_ps1(c.v0.w), m3.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v1.x), m3.v0._m),
						_mm_mul_ps(_mm_set_ps1(c.v1.y), m3.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v1.z), m3.v2._m),
						_mm_mul_ps(_mm_set_ps1(c.v1.w), m3.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v2.x), m3.v0._m),
						_mm_mul_ps(_mm_set_ps1(c.v2.y), m3.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v2.z), m3.v2._m),
						_mm_mul_ps(_mm_set_ps1(c.v2.w), m3.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v3.x), m3.v0._m),
						_mm_mul_ps(_mm_set_ps1(c.v3.y), m3.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v3.z), m3.v2._m),
						_mm_mul_ps(_mm_set_ps1(c.v3.w), m3.v3._m)))));
						*/
		return Matrix(
			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v0.x), m4.v0._m),
						_mm_mul_ps(_mm_set_ps1(c.v0.y), m4.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v0.z), m4.v2._m),
						_mm_mul_ps(_mm_set_ps1(c.v0.w), m4.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v1.x), m4.v0._m),
						_mm_mul_ps(_mm_set_ps1(c.v1.y), m4.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v1.z), m4.v2._m),
						_mm_mul_ps(_mm_set_ps1(c.v1.w), m4.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v2.x), m4.v0._m),
						_mm_mul_ps(_mm_set_ps1(c.v2.y), m4.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v2.z), m4.v2._m),
						_mm_mul_ps(_mm_set_ps1(c.v2.w), m4.v3._m)))),

			Vect4D(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v3.x), m4.v0._m),
						_mm_mul_ps(_mm_set_ps1(c.v3.y), m4.v1._m)),
					_mm_add_ps(
						_mm_mul_ps(_mm_set_ps1(c.v3.z), m4.v2._m),
						_mm_mul_ps(_mm_set_ps1(c.v3.w), m4.v3._m)))));
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

inline mMul4 operator*(const mMul3 &m0, const Matrix &m1)
{
	return mMul4(m0, m1);
}

inline mMul5 operator*(const mMul4 &m0, const Matrix &m1)
{
	return mMul5(m0, m1);
}

#endif //proxy
#endif  // Matrix.h
