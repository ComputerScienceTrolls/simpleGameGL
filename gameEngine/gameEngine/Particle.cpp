#include "Particle.h"



Particle::Particle()
{
	this->life = 1;
	this->delta = 0;
}

Particle::Particle(int l)
{
	this->life = l;
	this->delta = 0;
}

void Particle::Update()
{
	this->life -= delta; // reduce life
	if (this->life > 0.0f)
	{	// particle is alive, thus update
		this->Position -= this->Velocity * this->delta;
		this->Color.b -= this->delta * 2.5;
	}

	this->delta += .1;
}

void Particle::Draw(AbstractRenderer *renderer)
{
	ParticleRenderer *pr = static_cast<ParticleRenderer*>(renderer);
}

float Particle::getLife()
{
	return this->life;
}

float Particle::getDelta()
{
	return this->delta;
}

void Particle::setLife(float l)
{
	this->life = l;
}

void Particle::setDelta(float d)
{
	this->delta = d;
}


Particle::~Particle()
{
}
