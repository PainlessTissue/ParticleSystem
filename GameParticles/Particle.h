#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

__declspec(align(16)) class Particle
{
public:
	friend class ParticleEmitter;
	
	Particle();	//default
	Particle(const Particle &p); //copy
	Particle &operator=(const Particle &p); // assignment
	~Particle(); //destructor

	void Update(float const & time_elapsed);

	//needed for 16 byte alignment and simd
	void* operator new(size_t i);
	void* operator new[](size_t i);
	void operator delete(void* const p);
	void operator delete[](void * const p);

private: //size of: 80
	Particle *next;
	Particle *prev;
	float	 padding1;
	float	 padding2;

	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;

	float	rotation_velocity;
	float	life;
	float	rotation;
	float	padding3;

};


#endif //PARTICLE_H
