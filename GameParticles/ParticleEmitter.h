#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Particle.h"

#include <list>

__declspec(align(16)) class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	
	void SpawnParticle();
	void update();
	void draw() const;

	void addParticleToList(Particle * const p );
	void removeParticleFromList(const Particle * const p);

	void Execute(Vect4D &pos, Vect4D &vel, Vect4D &sc);

	void* operator new(size_t i);
	void* operator new[](size_t i);
	void operator delete(void* p);
	void operator delete[](void *p);


private: //size of :64

	int		last_active_particle;
	float	spawn_frequency;
	float	last_spawn;
	float	last_loop;
	Particle *headParticle;

	Vect4D	vel_variance;
	Vect4D	pos_variance;
};

#endif // PARTICLEEMITTER_H
