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
class Vect4D
{
public:
	friend class Matrix;

	Vect4D();
	Vect4D(const float &tx, const float &ty, const float &tz, const float &tw = 1.0f);
	~Vect4D();

	void norm(Vect4D &out) const;
	void set(const float &tx, const float &ty, const float &tz, const float &tw = 1.0f);

	Vect4D operator + (const Vect4D &t) const;
	Vect4D operator - (const Vect4D &t) const;
	Vect4D operator * (const float &scale) const;

	void Cross(const Vect4D &vin, Vect4D &vout) const;

	float &operator[](const VECT_ENUM &e);

#if 1
private:
	float x;
	float y;
	float z;
	float w;
};
#else

public:
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

#endif //if
#endif  //Vect4D.h
