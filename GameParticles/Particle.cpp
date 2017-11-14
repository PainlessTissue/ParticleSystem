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

void Particle::CopyDataOnly(const Particle * const p )
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

void Particle::Update(float const & time_elapsed)
{
	// Rotate the matrices
	
	//Matrix tmp(
	//	this->diff_Row0,
	//	this->diff_Row1,
	//	this->diff_Row2,
	//	this->diff_Row3);

	//float MatrixScale = tmp.Determinant();

	// serious math below - magic secret sauce
	life += time_elapsed;
	position = position + (velocity * time_elapsed);
	
	Vect4D v(3.0f, 4.0f, 0.0f);
	position.Cross(Vect4D(0.0f, -0.25f, 1.0f), v);
	v.norm(v);
	position = position + v * 0.05f * life;

	//if( MatrixScale > 1.0f )
	//{
	//	MatrixScale = 1.0f/MatrixScale;
	//};

	rotation = rotation /*+ MatrixScale */+ rotation_velocity * time_elapsed *2.01f;
}

void * Particle::operator new(size_t i)
{
	return _aligned_malloc(i, 16);
}

void* Particle::operator new[](size_t i)
{
	return _aligned_malloc(i, 16);
}

void Particle::operator delete(void * const p)
{
	_aligned_free(p);
}

void Particle::operator delete[](void * const p)
{
	_aligned_free(p);
}



// End of file


