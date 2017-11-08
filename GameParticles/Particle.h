#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

__declspec(align(16)) class Particle
{
public:
	friend class ParticleEmitter;
	
	Particle();	
	~Particle();
	void Update(const float& time_elapsed);
	void CopyDataOnly(const Particle *p );

	//needed for 16 byte alignment and simd
	void* operator new(size_t i);
	void operator delete(void* p);

private: //272
	Particle *next;
	Particle *prev;
	float padding1;
	float padding2;

	Vect4D	prev_Row0;
	Vect4D	prev_Row1;
	Vect4D  prev_Row2;
	Vect4D  prev_Row3;

	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;
	Vect4D  diff_Row0;
	Vect4D  diff_Row1;
	Vect4D  diff_Row2;
	Vect4D  diff_Row3;

	Vect4D	curr_Row0;
	Vect4D	curr_Row1;
	Vect4D  curr_Row2;
	Vect4D  curr_Row3;

	//moving these three down moved the size of particle from 304 to 272
	float	rotation_velocity;
	float	life;
	float	rotation;
	float padding3;

};


#endif //PARTICLE_H
