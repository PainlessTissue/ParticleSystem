#include "Particle.h"
#include "Matrix.h"

Particle::Particle()
	:rotation_velocity(0.5f),
	life(0.0f),
	rotation(0.0f),
	position(Vect4D(0.0f, 0.0f, 0.0f)),
	velocity(Vect4D(0.0f, 0.0f, 0.0f)),
	scale(Vect4D(1.0f, 1.0f, 1.0f))
{}

Particle::Particle(const Particle & p)
	:next(p.next), 
	prev(p.prev), 
	position(p.position), 
	velocity(p.velocity),
	scale(p.scale), rotation_velocity(p.rotation_velocity), 
	life(p.life), 
	rotation(p.rotation) 
{}

Particle & Particle::operator=(const Particle & p)
{
	this->next = p.next;
	this->prev = p.prev;
	this->position = p.position;
	this->velocity = p.velocity;
	this->scale = p.scale;
	this->rotation_velocity = p.rotation_velocity;
	this->life = p.life;
	this->rotation = p.rotation;

	return *this;
}

Particle::~Particle()
{
	// nothing to do
}

void Particle::Update(float const & time_elapsed)
{
	// serious math below - magic secret sauce
	life += time_elapsed;
	position = position + (velocity * time_elapsed);

	Vect4D v(3.0f, 4.0f, 0.0f);
	position.Cross(Vect4D(0.0f, -0.25f, 1.0f), v);
	v.norm(v);
	position += v * 0.05f * life;

	rotation += rotation_velocity * time_elapsed *2.01f;
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


