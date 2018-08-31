#pragma once
#include "MovingSceneObject.h"
#include "DrawSceneObject.h"
#include "ParticleRenderer.h"

class Particle : virtual public MovingSceneObject, virtual public DrawSceneObject
{
public:
	Particle();
	Particle(int life);
	virtual void Update();
	virtual void Draw(AbstractRenderer *renderer);
	virtual float getLife();
	virtual float getDelta();
	virtual void setLife(float);
	virtual void setDelta(float);
	~Particle();

private:
	float life;
	float delta;
};

