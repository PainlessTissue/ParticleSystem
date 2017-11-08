#include "Particle.h"
#include "Matrix.h"

Particle::Particle()
	:rotation_velocity(0.5f), life(0.0f), rotation(0.0f)
{
	// construtor
	this->position.set( 0.0f, 0.0f,  0.0f );
	this->velocity.set( 0.0f, 0.0f,  0.0f );
	this->scale.set( 1.0f, 1.0f, 1.0f );

}

Particle::~Particle()
{
	// nothing to do
}

void Particle::CopyDataOnly(const Particle *p )
{
	// copy the data only
	// this way of copying data is more efficient that element by element
	this->position = p->position;
	this->velocity = p->velocity;
	this->scale    = p->scale;
	this->rotation = p->rotation;
	this->rotation_velocity = p->rotation_velocity;
	this->life     = p->life;
}

void * Particle::operator new(size_t i)
{
	return _mm_malloc(i, 16);
}

void Particle::operator delete(void * p)
{
	_mm_free(p);
}

void Particle::Update(const float& time_elapsed)
{
	// Rotate the matrices
	Vect4D tmp_Row0;
	tmp_Row0 = curr_Row0;
	prev_Row0 = tmp_Row0;

	Vect4D tmp_Row1;
	tmp_Row1 = curr_Row1;
	prev_Row1 = tmp_Row1;

	Vect4D tmp_Row2;
	tmp_Row2 = curr_Row2;
	prev_Row2 = tmp_Row2;

	Vect4D tmp_Row3;
	tmp_Row3 = curr_Row3;
	prev_Row3 = tmp_Row3;

	Matrix tmp;

	tmp.set(0, &this->diff_Row0);
	tmp.set(1, &this->diff_Row1);
	tmp.set(2, &this->diff_Row2);
	tmp.set(3, &this->diff_Row3);

	float MatrixScale = tmp.Determinant();

	// serious math below - magic secret sauce
	life += time_elapsed;
	position = position + (velocity * time_elapsed);
	Vect4D z_axis(0.0f, -0.25f, 1.0f);
	Vect4D v(3,4,0);
	position.Cross( z_axis, v);
	v.norm(v);
	position = position + v * 0.05f * life;

	if( MatrixScale > 1.0f )
	{
		MatrixScale = 1.0f/MatrixScale;
	};

	rotation = rotation + MatrixScale + rotation_velocity * time_elapsed *2.01f;
}


// End of file


