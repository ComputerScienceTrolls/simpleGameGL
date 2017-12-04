#include "SceneObject.h"

SceneObject::SceneObject()
{
}

void SceneObject::setPosition(glm::vec2 newPosition)
{
	this->Position = newPosition;
}

void SceneObject::setCenter(glm::vec2 newCenter)
{
	this->Center = newCenter;
}

void SceneObject::setSize(glm::vec2 newSize)
{
	this->Size = newSize;
}

void SceneObject::setName(std::string newName)
{
	this->name = newName;
}

void SceneObject::setRotation(GLfloat newRotation)
{
	this->Rotation = newRotation;
}

void SceneObject::setActive(bool newState)
{
	this->active = newState;
}

glm::vec2 SceneObject::getPosition()
{
	return this->Position;
}

glm::vec2 SceneObject::getCenter()
{
	return this->Center;
}

glm::vec2 SceneObject::getSize()
{
	return this->Size;
}

std::string SceneObject::getName()
{
	return this->name;
}

GLfloat SceneObject::getRotation()
{
	return this->Rotation;
}

bool SceneObject::getActive()
{
	return this->active;
}

SceneObject::~SceneObject()
{
}
