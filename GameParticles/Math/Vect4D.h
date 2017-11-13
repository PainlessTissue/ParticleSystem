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
	Vect4D(const float &tx, const float &ty, const float &tz, const float &tw = 1.0f);
	~Vect4D();

	//specialized for intrinsics
	Vect4D(const __m128 &_m);

	void norm(Vect4D &out);
	void set(const float &tx, const float &ty, const float &tz, const float &tw = 1.0f);

	Vect4D operator + (const Vect4D &t) const;
	Vect4D operator - (const Vect4D &t) const;
	Vect4D operator * (const float &scale) const;

	Vect4D operator *= (const float &f);

	void Cross(const Vect4D &vin, Vect4D &vout) const;

	float &operator[](const char &e);

	//faster square root because math.sqrt is slow
	float altSqrt(const float &number) const;

	void* operator new(const size_t i);
	void* operator new[](const size_t i);
	void operator delete(void* p);
	void operator delete[](void *p);

private:
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
