#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

/*__declspec(align(16))*/ class Particle
{
public:
	friend class ParticleEmitter;
	
	Particle();	
	~Particle();
	void Update(float const & time_elapsed);
	void CopyDataOnly(const Particle * const p );

	//needed for 16 byte alignment and simd
	void* operator new(size_t i);
	void* operator new[](size_t i);
	void operator delete(void* const p);
	void operator delete[](void * const p);

private: //size of: 80
	Particle *next;
	Particle *prev;
	float padding1;
	float padding2;

	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;

	//REMOVING THESE MAY HAVE MESSED WITH THE SPIN. CHECK
	//Vect4D  diff_Row0;
	//Vect4D  diff_Row1;
	//Vect4D  diff_Row2;
	//Vect4D  diff_Row3;

	//moving these three down moved the size of particle from 304 to 272
	float	rotation_velocity;
	float	life;
	float	rotation;
	float	padding3;

};


#endif //PARTICLE_H
