#include "MovingSceneObject.h"

//pie constant for math
const double PI = 3.141592653589793238463;

MovingSceneObject::MovingSceneObject()
{
}

void MovingSceneObject::setVelocity(glm::vec2 newVelocity)
{
	this->Velocity = newVelocity;
}

void MovingSceneObject::setDX(float newDX)
{
	this->Velocity.x = newDX;
}

void MovingSceneObject::setDY(float newDY)
{
	this->Velocity.y = newDY;
}

void MovingSceneObject::setSpeed(float newSpeed)
{
	this->speed = newSpeed;
}

void MovingSceneObject::setMoveAngle(float newMovleAngle)
{
	this->moveAngle = newMovleAngle;
}

glm::vec2 MovingSceneObject::getVelocity()
{
	return this->Velocity;
}

int MovingSceneObject::getDX()
{
	return this->Velocity.x;
}

int MovingSceneObject::getDY()
{
	return this->Velocity.y;
}

float MovingSceneObject::getSpeed()
{
	return this->speed;
	this->calcVector();
}

float MovingSceneObject::getMoveAngle()
{
	return this->moveAngle;
	this->calcVector();
}

void MovingSceneObject::addForce(float angle, float thrust)
{
	//input angle is in degrees - convert to radians    
	angle = angle * PI / 180;

	//calculate dx and dy
	double newDX = thrust * std::cos(angle);
	double newDY = thrust * std::sin(angle);

	//this->setDX(this->getDX() + newDX);
	//this->setDY(this->getDY() + newDY);
	this->Velocity.x += newDX;
	this->Velocity.y += newDY;


	//ensure speed and angle are updated
	this->calcSpeedAngle();
}

void MovingSceneObject::calcSpeedAngle()
{
	this->speed = std::sqrt((this->Velocity.x * this->Velocity.y) + (this->Velocity.x * this->Velocity.y));
	this->moveAngle = std::atan2(this->Velocity.y, this->Velocity.x);
}

void MovingSceneObject::calcVector()
{
	this->Velocity.x = this->speed * std::cos(this->moveAngle);
	this->Velocity.y = this->speed * std::sin(this->moveAngle);
}

MovingSceneObject::~MovingSceneObject()
{
}
