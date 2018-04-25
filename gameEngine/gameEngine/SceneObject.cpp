#include "SceneObject.h"
#include <iostream>

SceneObject::SceneObject()
{
}

SceneObject::SceneObject(SceneObject * copy)
{
	this->name = copy->name;
	this->active = copy->active;
	this->Center = copy->Center;

	for (unsigned int i = 0; i < copy->children.size(); i++)
	{
		this->children.push_back(new SceneObject(copy->children[i]));
	}

	this->Position = copy->Position;
	this->Rotation = copy->Rotation;
	this->Size = copy->Size;
}

void SceneObject::setPosition(glm::vec2 newPosition)
{
	this->Position = newPosition;

	//set Center accordingly
	this->Center.x = this->Position.x + this->Size.x / 2;
	this->Center.y = this->Position.y + this->Size.y / 2;
}

void SceneObject::setPosition(double degrees, glm::vec2 start, int amount)
{
		//input angle is in degrees - convert to radians    
		degrees = degrees * float((PI) / 180);

		//calc x and y based on the degree and amount given
		double newDX = amount * std::cos(degrees);
		double newDY = amount * std::sin(degrees);

		this->Position.x = float(start.x + newDX);
		this->Position.y = float(start.y + newDY);
}

void SceneObject::setPosX(float newX)
{
	this->Position.x = newX;

	//set Center accordingly
	this->Center.x = this->Position.x + this->Size.x / 2;
}

void SceneObject::setPosY(float newY)
{
	this->Position.y = newY;

	//set Center accordingly
	this->Center.y = this->Position.y + this->Size.y / 2;
}

void SceneObject::setCenter(glm::vec2 newCenter)
{
	this->Center = newCenter;

	//we need to change pos accordingly
	this->Position.x = this->Center.x - this->Size.x / 2;
	this->Position.y = this->Center.y - this->Size.y / 2;
}

void SceneObject::setSize(glm::vec2 newSize)
{
	this->Size = newSize;
}

void SceneObject::setWidth(float newWidth)
{
	this->Size.x = newWidth;
}

void SceneObject::setHeight(float newHeight)
{
	this->Size.y = newHeight;
}

void SceneObject::changeWidthBy(float newWidth)
{
	this->Size.x += newWidth;
}

void SceneObject::changeHeightBy(float newHeight)
{
	this->Size.y += newHeight;
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

float SceneObject::getPosX()
{
	return this->Position.x;
}

float SceneObject::getPosY()
{
	return this->Position.y;
}

glm::vec2 SceneObject::getCenter()
{
	return this->Center;
}

glm::vec2 SceneObject::getSize()
{
	return this->Size;
}

float SceneObject::getWidth()
{
	return this->Size.x;
}

float SceneObject::getHeight()
{
	return this->Size.y;
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

void SceneObject::changePositionBy(glm::vec2 dt)
{
	this->Position += dt;
}

void SceneObject::changeXBy(float dx)
{
	this->Position.x += dx;
}

void SceneObject::changeYBy(float dy)
{
	this->Position.y += dy;
}

void SceneObject::setParent(SceneObject *newParent)
{
	this->parent = newParent;

	this->parent->addChildObject(this);
}

void SceneObject::removeChild(SceneObject *child)
{
	for (int i = 0; i < this->children.size(); i++)
	{
		if (children[i] == child)
		{
			this->children.erase(children.begin() + i);
		}
	}
}

SceneObject * SceneObject::getParent()
{
	//if no parent exists return nullptr
	if (!parent)
		return nullptr;
	else
		return parent;
}

void SceneObject::addChildObject(SceneObject *child)
{
	this->children.push_back(child);
}

SceneObject::~SceneObject()
{
}
