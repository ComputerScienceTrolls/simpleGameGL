#include "MovingSceneObject.h"
#include <iostream>

MovingSceneObject::MovingSceneObject() :
	lastDir(0), debug(false)
{
	this->Velocity = glm::vec2(0);
	this->Position = glm::vec2(0);
	this->boundAction = "BOUNCE";
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

float MovingSceneObject::getDX()
{
	return this->Velocity.x;
}

float MovingSceneObject::getDY()
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

bool MovingSceneObject::getDebug()
{
	return debug;
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
		//if center is 0,0 probably means center was never calculated, ignore first run but calculate center
		if (this->Center.x != 0 && this->Center.y != 0)
		{
			this->Position.x = this->Center.x - this->Size.x / 2;
			this->Position.y = this->Center.y - this->Size.y / 2;
		}
		else
		{
			this->Center.x = this->Position.x + this->Size.x / 2;
			this->Center.y = this->Position.y + this->Size.x / 2;
		}
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

bool MovingSceneObject::checkBounds(int screenWidth, int screenHeight)
{
	int rightBorder = screenWidth;
	int leftBorder = 0;
	int topBorder = 0;
	int bottomBorder = screenHeight;

	bool offRight = false;
	bool offLeft = false;
	bool offTop = false;
	bool offBottom = false;

	//since the Position.x starts on the left most of the sprite, we need to calculate and account for it's size
	float offsetX = 0;
	float offsetY = 0;
	if (this->Size.x > 0)
	{
		offsetX = this->Size.x;
	}
	if (this->Size.y > 0)
	{
		offsetY = this->Size.y;
	}

	if (this->Position.x > float(rightBorder) - offsetX)
	{
		offRight = true;
	}

	if (this->Position.x < float(leftBorder))
	{
		offLeft = true;
	}

	if (this->Position.y > float(bottomBorder) - offsetY)
	{
		offBottom = true;
	}

	if (this->Position.y < 0)
	{
		offTop = true;
	}
	//if all are false, return false
	if (!offTop && !offBottom && !offLeft && !offRight)
	{
		return false;
	}

	if (this->boundAction == "WRAP") {
		if (offRight) {
			this->Position.x = float(leftBorder);
		} // end if

		if (offBottom) {
			this->Position.y = float(topBorder);
		} // end if

		if (offLeft) {
			this->Position.x = float(rightBorder);
		} // end if

		if (offTop) {
			this->Position.y = float(bottomBorder);
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
					this->Position.x = float(leftBorder);

					//check for corners
					if (offBottom)
					{
						this->Position.y = float(bottomBorder) - offsetY;
					}
					else if (offTop)
					{
						this->Position.y = float(topBorder);
					}
				}
				else if (offRight)
				{
					this->Position.x = float(rightBorder) - offsetX;

					//check for corners
					if (offBottom)
					{
						this->Position.y = float(bottomBorder) - offsetY;
					}
					else if (offTop)
					{
						this->Position.y = float(topBorder);
					}
				}
				else if (offBottom)
				{
					this->Position.y = float(bottomBorder) - offsetY;

					//check for corners
					if (offRight)
					{
						this->Position.x = float(rightBorder) - offsetX;
					}
				}
				else if (offTop)
				{
					this->Position.y = float(topBorder);
				}
				//check for corners
				else if (offTop && offRight)
				{
					this->Position.y = float(topBorder);
					this->Position.x = float(rightBorder) - offsetX;
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
				this->Position.x = offLeft + float(.1);
				//check for corners
				if (offBottom)
				{
					this->Position.y = bottomBorder - offsetY - float(.1);
				}
				else if (offTop)
				{
					this->Position.y = topBorder + float(.1);
				}
			}
			else if (offRight)
			{
				this->Position.x = rightBorder - offsetX - float(.1);

				//check for corners
				if (offBottom)
				{
					this->Position.y = bottomBorder - offsetY - float(.1);
				}
				else if (offTop)
				{
					this->Position.y = topBorder + float(.1);
				}
			}
			else if (offBottom)
			{
				this->Position.y = bottomBorder - offsetY - float(.1);

				//check for corners
				if (offRight)
				{
					this->Position.x = rightBorder - offsetX - float(.1);
				}
			}
			else if (offTop)
			{
				this->Position.y = topBorder + float(.1);
			}
			//check for corners
			else if (offTop && offRight)
			{
				this->Position.y = float(topBorder);
				this->Position.x = float(rightBorder) - offsetX;
			}
		}
	}
	else if (this->boundAction == "DIE") {
		if (offLeft || offRight || offTop || offBottom) {
			this->setSpeed(0);
			this->active = false;
			this->Position = glm::vec2(9999, 9999);
			//this->setVisible(false);
		}

	}
	else {
		//keep on going forever
	}
	return true;
}

void MovingSceneObject::addForce(float angle, float thrust, bool radians)
{
	//doesn't seem to work... recommand just using degrees then convert
	if (radians)
	{
		angle = radians;
	}
	else 
	{
		//input angle is in degrees - convert to radians    
		angle = angle * float((PI) / 180);
	}

	//calculate dx and dy

	float newDX = thrust * std::cos(angle);
	float newDY = thrust * std::sin(angle);

	this->Velocity.x += newDX;
	this->Velocity.y -= newDY;

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

float MovingSceneObject::angleTo(SceneObject *otherObject)
{
	//get centers of sprites
	float myX = this->getPosX() + (this->getWidth() / 2);
	float myY = this->getPosY() + (this->getHeight() / 2);
	float otherX = otherObject->getPosX() + (otherObject->getWidth() / 2);
	float otherY = otherObject->getPosY() + (otherObject->getHeight() / 2);

	//calculate difference
	float diffX = myX - otherX;
	float diffY = myY - otherY;
	float radians = std::atan2(diffY, diffX);
	radians += float(PI) / 2;
	//float degrees = radians * 180 / PI;
	//degrees are offset
	//degrees += 90;

	return radians;

}

//pushes object to another specify object if not within the specified distance
void MovingSceneObject::followObject(SceneObject * o, float distance, float speed)
{
	this->setImageAngle(angleTo(o));
	//this->Velocity -= lastDir;
	//this->Velocity += normalize(dir) * speed;

	//lastDir = normalize(dir) * speed;
	//addForce(angleTo(o), -speed/10);
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

void MovingSceneObject::setDebugMode(bool newState)
{
	debug = newState;
}

MovingSceneObject::~MovingSceneObject()
{
}
