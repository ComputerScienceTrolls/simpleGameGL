#include "Particle.h"

Particle::Particle(MovingSceneObject *object, glm::vec2 os, glm::vec2 size, GLchar* t, glm::vec2 velocity, glm::vec3 color, float l) :
	life(l), offset(os)
{
	this->delta = 1;

	this->Position = object->getPosition();
	this->Size = size;
	this->Velocity = velocity;
	this->Color = color;

	//see if texture is already loaded
	if (ResourceManager::Textures[t].Image_Format != 6407)
	{
		//std::cout << "using already loaded Texture";
		this->texture = ResourceManager::GetTexture(t);
	}
	else
	{
		//load texture
		ResourceManager::LoadTexture(t, true, t);
		this->texture = ResourceManager::GetTexture(t);
	}

	this->setActive(true);
	this->setVisible(true);
};

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

void Particle::Draw(Renderer &renderer)
{
	renderer.DrawParticle(this->texture, this->Position, this->Size, 1, this->Color, 1, this->life);
}

float Particle::getLife()
{
	return this->life;
}

float Particle::getDelta()
{
	return this->delta;
}

void Particle::setLife(float newLife)
{
	this->life = newLife;
}

void Particle::setDelta(float newDelta)
{
	this->delta = newDelta;
}


Particle::~Particle()
{
}
