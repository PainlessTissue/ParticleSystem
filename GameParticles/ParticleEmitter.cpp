#include "DO_NOT_MODIFY\Timer.h"
#include "DO_NOT_MODIFY\GlobalTimer.h"
#include "DO_NOT_MODIFY\OpenGLInterface.h"

#include <assert.h>

#define UNUSED_VAR(v) ((void *)v)
#include "ParticleEmitter.h"
#include "Settings.h"

#include "DO_NOT_MODIFY\Trace.h"

static const unsigned char squareColors[] =
{
	255,  255,  000,  255,
	000,  255,  255,  255,
	000,  000,  000,  000,
	255,  000,  255,  255,
};

static const float squareVertices[] =
{
	-0.015f,  -0.015f, 0.0f,
	 0.015f,  -0.015f, 0.0f,
	-0.015f,   0.015f, 0.0f,
	 0.015f,   0.015f, 0.0f,
};


ParticleEmitter::ParticleEmitter()
	: last_active_particle(0),
	spawn_frequency(0.0000001f),
	last_spawn(globalTimer::getTimerInSec()),
	last_loop(globalTimer::getTimerInSec()),
	headParticle(0),
	vel_variance(1.0f, 4.0f, 0.4f),
	pos_variance(1.0f, 1.0f, 1.0f)
{
	//headParticle = new Particle[NUM_PARTICLES];
}

ParticleEmitter::ParticleEmitter(const ParticleEmitter & pe)
	:last_active_particle(pe.last_active_particle),
	spawn_frequency(pe.spawn_frequency),
	last_spawn(pe.last_spawn),
	last_loop(pe.last_loop), 
	headParticle(pe.headParticle),
	vel_variance(pe.vel_variance), 
	pos_variance(pe.pos_variance) 
{}



ParticleEmitter & ParticleEmitter::operator=(const ParticleEmitter & pe)
{
	last_active_particle = pe.last_active_particle;
	spawn_frequency = pe.spawn_frequency;
	last_spawn = pe.last_spawn;
	last_loop = pe.last_loop;
	headParticle = pe.headParticle;
	vel_variance = pe.vel_variance;
	pos_variance = pe.pos_variance;

	return *this;

}

ParticleEmitter::~ParticleEmitter()
{
	// do nothing
}


void ParticleEmitter::SpawnParticle()
{
	// create another particle if there are ones free
	if (last_active_particle < NUM_PARTICLES)
	{
		// create new particle
		Particle *newParticle = new Particle();
		//Particle *newParticle = headParticle + last_active_particle - sizeof(Particle);

		// apply the variance
		this->Execute(newParticle->position, newParticle->velocity, newParticle->scale);

		// increment count
		++last_active_particle;

		// add to list
		this->addParticleToList(newParticle);
	}
}

void ParticleEmitter::update()
{
	// get current time
	float current_time = globalTimer::getTimerInSec();

	// spawn particles
	float time_elapsed = current_time - last_spawn;

	// update
	while (spawn_frequency < time_elapsed)
	{
		// spawn a particle
		this->SpawnParticle();
		// adjust time
		time_elapsed -= spawn_frequency;
		// last time
		last_spawn = current_time;
	}

	// total elapsed
	time_elapsed = current_time - last_loop;

	Particle *p = this->headParticle;
	// walk the particles

	while (p != 0)
	{
		// call every particle and update its position 
		p->Update(time_elapsed);

		// if it's live is greater that the max_life 
		// and there is some on the list
		// remove node
		if ((p->life > MAX_LIFE) && (last_active_particle > 0))
		{
			Particle *past = p;

			// need to squirrel it away.
			p = p->next;

			// remove last node
			this->removeParticleFromList(past);

			// update the number of particles
			--last_active_particle;
		}
		else
		{
			// increment to next point
			p = p->next;
		}
	}

	//move a copy to vector for faster iterations in draw
	p = this->headParticle;

	last_loop = current_time;
}

void ParticleEmitter::addParticleToList(Particle * const p)
{
	assert(p);
	if (this->headParticle == 0)
	{ // first on list
		this->headParticle = p;
		p->next = 0;
		p->prev = 0;
	}
	else
	{ // add to front of list
		headParticle->prev = p;
		p->next = headParticle;
		p->prev = 0;
		headParticle = p;
	}
}

void ParticleEmitter::removeParticleFromList(const Particle * const p)
{
	// make sure we are not screwed with a null pointer
	assert(p);

	if (p->prev == 0 && p->next == 0)
	{ // only one on the list
		this->headParticle = 0;
	}
	else if (p->prev == 0 && p->next != 0)
	{ // first on the list
		p->next->prev = 0;
		this->headParticle = p->next;
	}
	else if (p->prev != 0 && p->next == 0)
	{ // last on the list 
		p->prev->next = 0;
	}
	else//( p->next != 0  && p->prev !=0 )
	{ // middle of the list
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}

	// bye bye
	delete p;
}

void ParticleEmitter::draw() const
{
	// get the camera matrix from OpenGL
	// need to get the position
	Matrix cameraMatrix;

	// get the camera matrix from OpenGL
	glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<float*>(&cameraMatrix));

	// camera position
	Matrix transCamera(cameraMatrix.v3);

	// OpenGL goo... don't worrry about this
	glVertexPointer(3, GL_FLOAT, 0, squareVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
	glEnableClientState(GL_COLOR_ARRAY);

	// iterate throught the list of particles
	for (Particle *it = headParticle; it != 0; it = it->next)
	{
		// total transformation of particle
		Matrix tmp = transCamera * Matrix(it->position) * Matrix(it->rotation);

		// set the transformation matrix
		//glLoadMatrixf(reinterpret_cast<float*>(&(transCamera * transParticle * rotParticle)));
		glLoadMatrixf(reinterpret_cast<float*>(&(tmp)));

		// draw the trangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc)
{
	// Add some randomness...

	// Ses it's ugly - I didn't write this so don't bitch at me
	// Sometimes code like this is inside real commerical code ( so now you know how it feels )

	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.001f;
	float *t_pos = reinterpret_cast<float*>(&pos);
	float *t_var = &pos_variance.x;
	if (static_cast<float>(rand() % 2) == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;

	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	t_pos++;
	t_var++;
	if (static_cast<float>(rand() % 2) == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;

	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	t_pos++;
	t_var++;
	if (static_cast<float>(rand() % 2) == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;

	var = static_cast<float>(rand() % 1000) * 0.001f;

	// x  - add velocity
	t_pos = &vel.x;
	t_var = &vel_variance.x;
	if (static_cast<float>(rand() % 2) == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;

	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	t_pos++;
	t_var++;
	if (static_cast<float>(rand() % 2) == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;

	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	t_pos++;
	t_var++;
	if (static_cast<float>(rand() % 2) == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;

	// correct the sign
	var = 2.0f * static_cast<float>(rand() % 1000) * 0.001f;

	if (static_cast<float>(rand() % 2) == 0)
	{
		var *= -1.0f;
	}
	sc = sc * var;
}

void * ParticleEmitter::operator new(size_t i)
{
	return _aligned_malloc(i, 16);
}

void * ParticleEmitter::operator new[](size_t i)
{
	return _aligned_malloc(i, 16);
}

void ParticleEmitter::operator delete(void * p)
{
	_aligned_free(p);
}

void ParticleEmitter::operator delete[](void * p)
{
	_aligned_free(p);
}


// End of file