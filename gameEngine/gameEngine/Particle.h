#pragma once
#include "MovingSceneObject.h"
#include "DrawSceneObject.h"

class Particle : virtual public MovingSceneObject, virtual public DrawSceneObject
{
public:
	Particle();
	Particle(int life);
	virtual void Update();
	virtual void Draw(SpriteRenderer &renderer);
	~Particle();

private:
	float life;
	float delta;
};

