#include <math.h>
#include <assert.h>

#include "Vect4D.h"


Vect4D::Vect4D()
	:x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

Vect4D::Vect4D(const float &tx, const float &ty, const float &tz, const float &tw)
	: x(tx), y(ty), z(tz), w(tw) {}

Vect4D::~Vect4D()
{
	// nothing to delete
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
	return Vect4D(this->x + t.x, this->y + t.y, this->z + t.z);
}

Vect4D Vect4D::operator - (const Vect4D &t) const
{
	return Vect4D(this->x - t.x, this->y - t.y, this->z - t.z);
}

Vect4D Vect4D::operator *(const float &scale) const
{
	return Vect4D(this->x * scale, this->y * scale, this->z * scale);
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
	this->x = tx;
	this->y = ty;
	this->z = tz;
	this->w = tw;
}

// End of file