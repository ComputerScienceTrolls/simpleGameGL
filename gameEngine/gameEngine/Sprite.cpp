#include "Sprite.h"
//#include "Scene.h"
//pie constant for math
const double PI = 3.141592653589793238463;

//Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

Sprite::Sprite()
	: Position(0, 0), Size(1, 1), Velocity(10.0f), Color(1.0f), Rotation(0.0f), Texture(), IsSolid(false), Destroyed(false), dx(0), dy(0), speed(10), moveAngle(0), imgAngle(0), collideDebug(false)
{
	//give default box collider
	boxCollider *temp = new boxCollider("default",*this, 1, 1);
	colliders_.push_back(temp);
	//texture for collider debug
	ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
}


Sprite::Sprite(std::string name,Scene &scene, glm::vec2 pos, glm::vec2 size, GLchar* texture, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), IsSolid(false), Destroyed(false), collideDebug(false)
{
	boxCollider *temp = new boxCollider("default",*this, size.x, size.y);
	colliders_.push_back(temp);
	this->setBoundAction("DIE");

	this->name = name;
	//load texture
	ResourceManager::LoadTexture(texture,true,texture);
	this->Texture = ResourceManager::GetTexture(texture);
	
	//texture for collider debug
	ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");

	//parentScene = &scene;


	int lastSprite = 0;
	lastSprite = scene.Sprites.size();

	//add Sprite to Scene
	scene.Sprites.push_back(this);

	scene.Sprites.at(lastSprite)->setPosition(Position);
	scene.Sprites.at(lastSprite)->setPosition(this->Size);
	scene.Sprites.at(lastSprite)->setVelocity(this->Velocity);
	scene.Sprites.at(lastSprite)->setColor(this->Color);
	scene.Sprites.at(lastSprite)->setRotation(this->Rotation);
	scene.Sprites.at(lastSprite)->setTexture(this->Texture);
	scene.Sprites.at(lastSprite)->IsSolid = this->IsSolid;
	scene.Sprites.at(lastSprite)->Destroyed = this->Destroyed;
	scene.Sprites.at(lastSprite)->collideDebug = this->collideDebug;
	
	this->setState("active", true);
	
}

void Sprite::Draw(SpriteRenderer &renderer)
{
	GLfloat t = 1;
	renderer.DrawSprite(this->getTexture(), this->getPosition(), this->getSize(), this->getRotation(), this->getColor(),t);
	//check if collideDebug is true, if so draw all colliders

	if (collideDebug)
	{
		for (int i = 0; i < getColliders().size(); i++)
		{
			if (this->getName() == "Ball")
			{
				t = .15;
			}
			else
			{
				t = 1;
			}
			renderer.DrawSprite(ResourceManager::GetTexture("debugGreen"), glm::vec2(getColliders().at(i)->getPosX() + this->getPosition().x, getColliders().at(i)->getPosY() + this->getPosition().y),glm::vec2(getColliders().at(i)->getWidth(), getColliders().at(i)->getHeight()),0,glm::vec3(0,255,0), t);
		}
	}
	//renderer.DrawSprite(this->Texture, this->Position, this->Size, this->Rotation, this->Color);
}

//iterate through all this sprite's colliders, and have it check if it's colliding with another specified sprite's colliders
bool Sprite::collide(AbstractSprite* otherSprite)
{
	for (int i = 0; i < this->colliders_.size(); i++)
	{
		if (this->colliders_.at(i)->collide(otherSprite->getColliders()))
		{
			return true;
		}
	}
	//if we get here, no collision detected, return false
	return false;
}

void Sprite::setVelocity(GLfloat dt)
{
	this->Position += this->Velocity * dt;
	// Check if outside window bounds; if so, reverse velocity and restore at correct position
	if (this->Position.x <= 0.0f)
	{
		this->Velocity.x = -this->Velocity.x;
		this->Position.x = 0.0f;
	}
}

void Sprite::setDX(float newDx)
{
	this->dx = newDx;
}

void Sprite::setDY(float newDy)
{
	this->dy = newDy;
}

void Sprite::addForce(float angle, float thrust)
{
	//input angle is in degrees - convert to radians    
	angle = angle * PI / 180;

	//calculate dx and dy
	double newDX = thrust * std::cos(angle);
	double newDY = thrust * std::sin(angle);
	this->dx += newDX;
	this->dy += newDY;

	//ensure speed and angle are updated
	this->calcSpeedAngle();
}

void Sprite::calcSpeedAngle()
{
	//opposite of calcVector:
	//sets speed and moveAngle based on dx, dy
	this->speed = std::sqrt((this->dx * this->dx) + (this->dy * this->dy));
	this->moveAngle = std::atan2(this->dy, this->dx);
}

void Sprite::calcVector()
{
	//used throughout speed angle calculations to 
	//recalculate dx and dy based on speed and angle
	this->dx = this->speed * std::cos(this->moveAngle);
	this->dy = this->speed * std::sin(this->moveAngle);
}

void Sprite::setSpeed(float newSpeed)
{
	this->speed = newSpeed;
	this->calcVector();
}

void Sprite::setImgAngle(float newAngle)
{
	this->Rotation = newAngle;
	//this->calcVector();
}

void Sprite::setMoveAngle(float newAngle)
{
	this->moveAngle = newAngle;
	this->calcVector();
}

glm::vec2 Sprite::getPosition()
{
	return this->Position;
}

glm::vec2 Sprite::getSize()
{
	return this->Size;
}

Texture2D Sprite::getTexture()
{
	return this->Texture;
}

glm::vec2 Sprite::getVelocity()
{
	return this->Velocity;
}

glm::vec3 Sprite::getColor()
{
	return this->Color;
}

GLfloat Sprite::getRotation()
{
	return this->Rotation;
}

std::vector<collider*> Sprite::getColliders()
{
	return this->colliders_;
}

std::string Sprite::getName()
{
	return this->name;
}

GLfloat Sprite::getDX()
{
	return this->dx;
}

GLfloat Sprite::getDY()
{
	return this->dy;
}

void Sprite::setPosition(glm::vec2 newPosition)
{
	this->Position = newPosition;
}

void Sprite::setSize(glm::vec2 newSize)
{
	this->Size = newSize;
}

void Sprite::setTexture(Texture2D newTexture)
{
	this->Texture = newTexture;
}

void Sprite::setVelocity(glm::vec2 newVelocity)
{
	this->Velocity = newVelocity;
}

void Sprite::setColor(glm::vec3 newColor)
{
	this->Color = newColor;
}

void Sprite::setRotation(GLfloat newRotation)
{
	this->Rotation = newRotation;
}

void Sprite::setColliders(std::vector<collider*> newColliders)
{
	this->colliders_ = newColliders;
}

void Sprite::setName(std::string newName)
{
	this->name = newName;
}

void Sprite::addBoxCollider(std::string name, int w, int h, int posX, int posY)
{
	boxCollider *temp = new boxCollider(name, *this, w, h, posX, posY);
	this->colliders_.push_back(temp);
}

void Sprite::setColliderPredictive(std::string name, bool predictive)
{

}

void Sprite::addBoxCollider(std::string name, int w, int h)
{
	boxCollider *temp = new boxCollider(name, *this, w, h);
	this->colliders_.push_back(temp);
}

void Sprite::removeCollider(std::string name)
{
	//get index of collider
	int index = -1;
	for (int i = 0; i < this->colliders_.size(); i++)
	{
		if (this->colliders_[i]->getName() == name)
		{
			index = i;
		}
	}

	//if found remove it from the vector
	if (index != -1)
	{
		std::cout << "deleting " << colliders_.at(index)->getName();
		this->colliders_.erase(colliders_.begin() + index);
	}
	else
	{
		std::cout << "collider with the name of " << name << " not found";
	}
}

void Sprite::addCircleCollider(std::string name)
{
}

void Sprite::update()
{
	this->Position.x += this->dx;
	this->Position.y -= this->dy;
}

void Sprite::setState(std::string key, bool state)
{
	states.insert_or_assign(key, state);
}

bool Sprite::getState(std::string key)
{
	return states[key];
}

void Sprite::setBoundAction(std::string newAction)
{
	this->boundAction = newAction;
}

void Sprite::checkBounds(double screenWidth, double screenHeight)
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
	if (this->Size.x > 1)
	{
		offsetX = this->Size.x;
	}
	if (this->Size.y > 1)
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
			this->dy *= -1;
			this->calcSpeedAngle();
			this->imgAngle = this->moveAngle;
		}

		if (offLeft || offRight) {
			this->dx *= -1;
			this->calcSpeedAngle();
			this->imgAngle = this->moveAngle;
		}
		//check if it reaches a bound with no dt, if so prevent it from leaving the screen
		//bascially treat it as STOP
		if (this->dx == 0 && this->dy == 0)
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
	else if (this->boundAction == "DIE") {
		if (offLeft || offRight || offTop || offBottom) {
			this->hide();
			this->setSpeed(0);
		}

	}
	else {
		//keep on going forever
	}
}

void Sprite::hide()
{
	this->Position.x = 10000;
	this->Position.y = 10000;
}

void Sprite::setCollideDebug(bool state)
{
	this->collideDebug = state;
}

Sprite::~Sprite()
{
}
