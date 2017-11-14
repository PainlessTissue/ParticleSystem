#include <math.h>
#include <assert.h>

#include "Vect4D.h"


Vect4D::Vect4D()
{
}

Vect4D::Vect4D(float const &tx, float const &ty, float const &tz, float const &tw)
{
	this->_m = _mm_set_ps(tw, tz, ty, tx);
}

Vect4D::~Vect4D()
{
	// nothing to delete
}

Vect4D::Vect4D(__m128 const &_m)
{
	this->_m = _m;
}

void Vect4D::norm(Vect4D& out) 
{
	//alternative square root method 
	float mag = altSqrt( this->x * this->x + this->y * this->y + this->z * this->z );

	if( 0.0f < mag )
	{
		out.x = this->x / mag;
		out.y = this->y / mag;
		out.z = this->z / mag;
		out.w = 1.0f;
	}
}

Vect4D Vect4D::operator + (Vect4D const &t) const
{
	return Vect4D(_mm_add_ps(this->_m, t._m));
}

Vect4D Vect4D::operator - (Vect4D const &t) const
{
	return Vect4D(_mm_sub_ps(this->_m, t._m)); //this is working now... but i dont know why
}

Vect4D Vect4D::operator *(float const &scale) const
{
	return Vect4D(_mm_mul_ps(this->_m, _mm_set_ps1(scale)));
}

Vect4D Vect4D::operator*=(float const & scale)
{
	this->_m = (_mm_mul_ps(this->_m, _mm_set_ps1(scale)));

	return *this;
}

float& Vect4D::operator[](const char &e )
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

void Vect4D::Cross(Vect4D const& vin, Vect4D& vout) const
{
	vout.x = (y*vin.z - z*vin.y);
	vout.y = (z*vin.x - x*vin.z);
	vout.z = (x*vin.y - y*vin.x);
	vout.w = 1.0f;
}

void Vect4D::set(float const &tx, float const &ty, float const &tz, float const &tw)
{
	this->_m = _mm_set_ps(tw, tz, ty, tx);
}

float Vect4D::altSqrt(float const &num) const
{
	union
	{
		int i;
		float x;
	} u;

	u.x = num;
	u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

	u.x = u.x + num / u.x;
	u.x = 0.25f*u.x + num / u.x;

	return u.x;
}

void * Vect4D::operator new (size_t i)
{
	return _aligned_malloc(i, 16);
}

void * Vect4D::operator new[](size_t i)
{
	return _aligned_malloc(i, 16);
}

void Vect4D::operator delete(void * const p)
{
	_aligned_free(p);
}

void Vect4D::operator delete[](void * const p)
{	
	_aligned_free(p);
}
