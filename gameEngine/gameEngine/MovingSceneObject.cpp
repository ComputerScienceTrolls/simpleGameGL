#include "MovingSceneObject.h"



MovingSceneObject::MovingSceneObject()
{
}

void MovingSceneObject::setPosition(glm::vec2 newPos)
{
	this->Position = newPos;
}

void MovingSceneObject::setRenderPosition(glm::vec2 newRenderPos)
{
	this->RenderPosiiton = newRenderPos;
}


void MovingSceneObject::setVelocity(glm::vec2 newVelocity)
{
	this->Velocity = newVelocity;
}

MovingSceneObject::~MovingSceneObject()
{
}
