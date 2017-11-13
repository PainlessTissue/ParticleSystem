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


private:
	//128
	Vect4D	start_position;
	Vect4D	start_velocity;

	float	max_life;
	int		max_particles;
	int		last_active_particle;
	float	spawn_frequency;
	float	last_spawn;
	float	last_loop;


	// added for speed efficiency
	int bufferCount;
	Particle *headParticle;
	Vect4D	vel_variance;
	Vect4D	pos_variance;
	float	scale_variance;
};

#endif // PARTICLEEMITTER_H
