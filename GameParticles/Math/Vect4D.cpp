#include <math.h>
#include <assert.h>

#include "Vect4D.h"


Vect4D::Vect4D()
{
	this->_m = _mm_setzero_ps();
}

Vect4D::Vect4D(const float &tx, const float &ty, const float &tz, const float &tw)
{
	this->_m = _mm_set_ps(tw, tz, ty, tx);
}

Vect4D::~Vect4D()
{
	// nothing to delete
}

Vect4D::Vect4D(const __m128 &_m)
{
	this->_m = _m;
}

void Vect4D::norm(Vect4D& out) const
{
	//THIS WILL NEED TO BE CHANGED TO AVOID SQUARE ROOT
	float mag = sqrtf( this->x * this->x + this->y * this->y + this->z * this->z );

	if( 0.0f < mag )
	{
		out.x = this->x / mag;
		out.y = this->y / mag;
		out.z = this->z / mag;
		out.w = 1.0;
	}
}

Vect4D Vect4D::operator + (const Vect4D &t) const
{
	return Vect4D(_mm_add_ps(this->_m, t._m));
}

Vect4D Vect4D::operator - (const Vect4D &t) const
{
	return Vect4D(this->x - t.x, this->y - t.y, this->z - t.z, this->w - t.w);
	//__m128 d = _mm_sub_ps(this->_m, t._m);
	//return Vect4D(d);
	//return Vect4D(_mm_sub_ps(this->_m, t._m));
}

Vect4D Vect4D::operator *(const float &scale) const
{
	//return Vect4D(this->x * scale, this->y * scale, this->z * scale);
	return Vect4D(_mm_mul_ps(this->_m, _mm_set_ps1(scale)));
}

float& Vect4D::operator[](const VECT_ENUM &e )
{
	switch(e)
	{
	case 0:
			return x;
			break;
	case 1:
			return y;
			break;
	case 2: 
			return z;
			break;
	case 3:
			return w;
			break;
	default:
			assert(0);
			return x;
	}
}

void Vect4D::Cross(const Vect4D& vin, Vect4D& vout) const
{
	vout.x = (y*vin.z - z*vin.y);
	vout.y = (z*vin.x - x*vin.z);
	vout.z = (x*vin.y - y*vin.x);
	vout.w = 1.0f;
}

void Vect4D::set(const float &tx, const float &ty, const float &tz, const float &tw)
{
	this->_m = _mm_set_ps(tw, tz, ty, tx);
}

// End of file