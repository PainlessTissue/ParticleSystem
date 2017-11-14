// Vect4D.h
//
// This is a 4 dimensional Vect4D class
#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"

#include <xmmintrin.h>
#include <smmintrin.h>  

// Foward Declarations
class Matrix;

// class
__declspec(align(16)) class Vect4D
{
public:
	friend class Matrix;

	Vect4D();
	Vect4D(float const &tx, float const &ty, float const &tz, float const &tw = 1.0f);
	~Vect4D();

	//specialized for intrinsics
	Vect4D(__m128 const &_m);

	void norm(Vect4D &out);
	void set(float const &tx, float const &ty, float const &tz, float const &tw = 1.0f);

	Vect4D operator + (Vect4D const &t) const;
	Vect4D operator - (Vect4D const &t) const;
	Vect4D operator * (float const &scale) const;

	Vect4D operator *= (float const &f);

	void Cross(Vect4D const &vin, Vect4D &vout) const;

	float &operator[](char const &e);

	//faster square root because math.sqrt is slow
	float altSqrt(float const &number) const;

	void* operator new(size_t i);
	void* operator new[](size_t i);
	void operator delete(void* const p);
	void operator delete[](void * const p);

//private:
	//16
	union
	{
		__m128 _m;

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#endif  //Vect4D.h
