#include "Sprite.h"
//#include "Scene.h"
//pie constant for math
const double PI = 3.141592653589793238463;

//Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

Sprite::Sprite()
	: Position(0, 0), Size(1, 1), Velocity(10.0f), Color(1.0f), Rotation(0.0f), Texture(), IsSolid(false), Destroyed(false), dx(0), dy(0), speed(10), moveAngle(0), imgAngle(0), collideDebug(false)
{
	//give default box collider
	boxCollider *temp = new boxCollider(1, 1);
	colliders_.push_back(temp);
	//texture for collider debug
	ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
}


Sprite::Sprite(Scene &scene, glm::vec2 pos, glm::vec2 size, GLchar* texture, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), IsSolid(false), Destroyed(false), collideDebug(false)
{
	boxCollider *temp = new boxCollider(size.x, size.y);
	colliders_.push_back(temp);
	this->setBoundAction("DIE");
	
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
	//check if collideDebug is true, if so draw all colliders
	if (collideDebug)
	{
		for (int i = 0; i < colliders_.size(); i++)
		{
			renderer.DrawSprite(ResourceManager::GetTexture("debugGreen"), glm::vec2(colliders_.at(i)->getPosX() + this->Position.x, colliders_.at(i)->getPosY() + this->Position.y),glm::vec2(colliders_.at(i)->getWidth(), colliders_.at(i)->getHeight()),0,glm::vec3(0,0,0));
		}
	}
	renderer.DrawSprite(this->Texture, this->Position, this->Size, this->Rotation, this->Color);
}

bool Sprite::collide(Sprite* otherSprite)
{
	for (int i = 0; i < this->colliders_.size(); i++)
	{
		//draw colliders if debug mode is set on
		if (collideDebug)
		{

		}
		if (colliders_.at(i)->getType() == "box")
		{
			for (int j = 0; j < otherSprite->colliders_.size(); j++)
			{
				if (otherSprite->colliders_.at(j)->getType() == "box")
				{
					// Collision x-axis?
					bool collisionX = ((this->Position.x + this->colliders_.at(i)->getPosX()) + (this->colliders_.at(i)->getWidth())) >= otherSprite->Position.x &&
						otherSprite->Position.x + otherSprite->colliders_.at(j)->getPosX() + otherSprite->colliders_.at(j)->getWidth() >= this->Position.x;
					// Collision y-axis?
					bool collisionY = (this->Position.y + this->colliders_.at(i)->getPosY()) + (this->Size.y + this->colliders_.at(i)->getHeight()) >= otherSprite->Position.y &&
						otherSprite->Position.y + otherSprite->colliders_.at(j)->getPosY() + otherSprite->Size.y + otherSprite->colliders_.at(j)->getHeight() >= this->Position.y;
					// Collision only if on both axes
					if (collisionX && collisionY)
					{
						return collisionX && collisionY;
					}
				}

				else if (otherSprite->colliders_.at(j)->getType() == "circle")
				{
					// Get center point circle first 
					glm::vec2 center(this->Position + glm::vec2(this->colliders_.at(i)->getPosX(), this->colliders_.at(i)->getPosY()) + this->colliders_.at(i)->getRadius());
					// Calculate AABB info (center, half-extents)
					glm::vec2 aabb_half_extents(otherSprite->Size.x / 2, otherSprite->Size.y / 2);
					glm::vec2 aabb_center(
						otherSprite->Position.x + otherSprite->colliders_.at(j)->getPosX() + aabb_half_extents.x,
						otherSprite->Position.y + otherSprite->colliders_.at(j)->getPosY() + aabb_half_extents.y
					);
					// Get difference vector between both centers
					glm::vec2 difference = center - aabb_center;
					glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
					// Add clamped value to AABB_center and we get the value of box closest to circle
					glm::vec2 closest = aabb_center + clamped;
					// Retrieve vector between center circle and closest point AABB and check if length <= radius
					difference = closest - center;
					if (glm::length(difference) < this->colliders_.at(i)->getRadius())
						return true;
				}

			}
			
		}
		else if (colliders_.at(i)->getType() == "circle")
		{
			// Get center point circle first 
			glm::vec2 center(this->Position + glm::vec2(this->colliders_.at(i)->getPosX(), this->colliders_.at(i)->getPosY()) + this->colliders_.at(i)->getRadius());
			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(otherSprite->Size.x / 2, otherSprite->Size.y / 2);
			glm::vec2 aabb_center(
				otherSprite->Position.x + aabb_half_extents.x,
				otherSprite->Position.y + aabb_half_extents.y
			);
			// Get difference vector between both centers
			glm::vec2 difference = center - aabb_center;
			glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
			// Add clamped value to AABB_center and we get the value of box closest to circle
			glm::vec2 closest = aabb_center + clamped;
			// Retrieve vector between center circle and closest point AABB and check if length <= radius
			difference = closest - center;
			if (glm::length(difference) < this->colliders_.at(i)->getRadius())
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
	//used throughout speed / angle calculations to 
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
	this->imgAngle = newAngle;
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

void Sprite::update()
{
	this->Position.x += this->dx;
	this->Position.y -= this->dy;
	std::cout << this->Position.x;
	std::cout << this->Position.y;
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
		std::cout << this->dx;
		if (this->dx == 0 && this->dy == 0)
		{
			std::cout << "bounce stop";
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
