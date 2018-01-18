#include "MovingSceneObject.h"
#include <iostream>

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

glm::vec2 MovingSceneObject::getLastPosition()
{
	return	this->lastPosition;
}

glm::vec2 MovingSceneObject::getLastVelocity()
{
	return this->lastVelocity;
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

std::string MovingSceneObject::getBoundAction()
{
	return this->boundAction;
}

void MovingSceneObject::Update()
{
	this->Position.x += this->Velocity.x;
	this->Position.y -= this->Velocity.y;

	//update Center
	this->Center.x += this->Velocity.x;
	this->Center.y -= this->Velocity.y;

	glm::vec2 diffPos = glm::vec2(0);
	glm::vec2 diffSize = glm::vec2(0);
	bool change = false;

	if (Position != lastPosition)
	{
		diffPos = Position - lastPosition;
		change = true;
	}

	if (Size != lastSize)
	{
		diffSize = Size - lastSize;
		//we need to recalc center
		this->Position.x = this->Center.x - this->Size.x / 2;
		this->Position.y = this->Center.y - this->Size.y / 2;
		change = true;
	}

	if (change)
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->changePositionBy(diffPos);
			children[i]->setSize(children.at(i)->getSize() + diffSize);
		}
	}

	lastPosition = Position;
	lastSize = Size;
}

void MovingSceneObject::setBoundAction(std::string newAction)
{
	this->boundAction = newAction;
}

bool MovingSceneObject::checkBounds(double screenWidth, double screenHeight)
{
	double rightBorder = screenWidth;
	double leftBorder = 0;
	double topBorder = 0;
	double bottomBorder = screenHeight;

	bool offRight = false;
	bool offLeft = false;
	bool offTop = false;
	bool offBottom = false;

	//since the Position.x starts on the left most of the sprite, we need to calculate and account for it's size
	double offsetX = 0;
	double offsetY = 0;
	if (this->Size.x > 0)
	{
		offsetX = this->Size.x;
	}
	if (this->Size.y > 0)
	{
		offsetY = this->Size.y;
	}

	if (this->Position.x > rightBorder - offsetX) {
		offRight = true;
	}

	if (this->Position.x < leftBorder) {
		offLeft = true;
	}

	if (this->Position.y > bottomBorder - offsetY) {
		offBottom = true;
	}

	if (this->Position.y < 0) {
		offTop = true;
	}
	//if all are false, return false
	if (!offTop && !offBottom && !offLeft && !offRight)
	{
		return false;
	}

	if (this->boundAction == "WRAP") {
		if (offRight) {
			this->Position.x = leftBorder;
		} // end if

		if (offBottom) {
			this->Position.y = topBorder;
		} // end if

		if (offLeft) {
			this->Position.x = rightBorder;
		} // end if

		if (offTop) {
			this->Position.y = bottomBorder;
		}
	}
	else if (this->boundAction == "BOUNCE") {
		if (offTop || offBottom) {
			this->Velocity.y *= -1;
			this->calcSpeedAngle();
			setImageAngle(this->moveAngle);
		}

		if (offLeft || offRight) {
			this->Velocity.x *= -1;
			this->calcSpeedAngle();
			setImageAngle(this->moveAngle);
		}
		//check if it reaches a bound with no dt, if so prevent it from leaving the screen
		//bascially treat it as STOP
		if (this->Velocity.x == 0 && this->Velocity.y == 0)
		{
			if (offLeft || offRight || offTop || offBottom) {
				this->setSpeed(0);

				//if user is moving object by positon.x or position.y +=
				if (offLeft)
				{
					this->Position.x = leftBorder;

					//check for corners
					if (offBottom)
					{
						this->Position.y = bottomBorder - offsetY;
					}
					else if (offTop)
					{
						this->Position.y = topBorder;
					}
				}
				else if (offRight)
				{
					this->Position.x = rightBorder - offsetX;

					//check for corners
					if (offBottom)
					{
						this->Position.y = bottomBorder - offsetY;
					}
					else if (offTop)
					{
						this->Position.y = topBorder;
					}
				}
				else if (offBottom)
				{
					this->Position.y = bottomBorder - offsetY;

					//check for corners
					if (offRight)
					{
						this->Position.x = rightBorder - offsetX;
					}
				}
				else if (offTop)
				{
					this->Position.y = topBorder;
				}
				//check for corners
				else if (offTop && offRight)
				{
					this->Position.y = topBorder;
					this->Position.x = rightBorder - offsetX;
				}
			}
		}

	}
	else if (this->boundAction == "STOP") {
		if (offLeft || offRight || offTop || offBottom) {
			this->setSpeed(0);
			this->Velocity.x = 0;
			this->Velocity.y = 0;

			//if user is moving object by positon.x or position.y +=
			if (offLeft)
			{
				this->Position.x = offLeft + .1;
				//check for corners
				if (offBottom)
				{
					this->Position.y = bottomBorder - offsetY - .1;
				}
				else if (offTop)
				{
					this->Position.y = topBorder + .1;
				}
			}
			else if (offRight)
			{
				this->Position.x = rightBorder - offsetX - .1;

				//check for corners
				if (offBottom)
				{
					this->Position.y = bottomBorder - offsetY -.1;
				}
				else if (offTop)
				{
					this->Position.y = topBorder + .1;
				}
			}
			else if (offBottom)
			{
				this->Position.y = bottomBorder - offsetY - .1;

				//check for corners
				if (offRight)
				{
					this->Position.x = rightBorder - offsetX - .1;
				}
			}
			else if (offTop)
			{
				this->Position.y = topBorder + .1;
			}
			//check for corners
			else if (offTop && offRight)
			{
				this->Position.y = topBorder;
				this->Position.x = rightBorder - offsetX;
			}
		}
	}
	else if (this->boundAction == "DIE") {
		if (offLeft || offRight || offTop || offBottom) {
			this->setSpeed(0);
			this->active = false;
			this->setVisible(false);
		}

	}
	else {
		//keep on going forever
	}
	return true;
}

void MovingSceneObject::addForce(float angle, float thrust)
{
	//input angle is in degrees - convert to radians    
	angle = angle * PI / 180;

	//calculate dx and dy
	double newDX = thrust * std::cos(angle);
	double newDY = thrust * std::sin(angle);

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

//pushes object to another specify object if not within the specified distance
void MovingSceneObject::followObject(SceneObject * o, float distance, float speed)
{
	glm::vec2 dir = this->Position - o->getPosition();
	float angle = atan2(-dir.y, -dir.x) - PI / 2;
	//this->setImageAngle(angle);
	angle = angle * 180 / PI;
	speed = speed * 10;
	this->Velocity = normalize(dir) * speed;
}

void MovingSceneObject::setImageAngle(float angle)
{
	this->setRotation(angle);
}

//return the normalaized vertex of the given vertex
glm::vec2 MovingSceneObject::normalize(glm::vec2 v)
{
	double mag = std::sqrt(v.x*v.x + v.y*v.y);
	glm::vec2 temp = { v.x / mag, v.y / mag };
	return temp;
}

MovingSceneObject::~MovingSceneObject()
{
}
