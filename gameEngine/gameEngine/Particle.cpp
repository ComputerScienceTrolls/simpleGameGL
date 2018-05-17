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

void Particle::Draw(SpriteRenderer & renderer)
{
}


Particle::~Particle()
{
}
