#include "Sprite.h"
#include "Observers/observerhandler.h"

//pie constant for math
const double PI = 3.141592653589793238463;


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
	: Center(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), IsSolid(false), Destroyed(false), collideDebug(false)
{
	//std::cout << "\n" << this->Size.x/2;
	//center the postion based on the height and width of the sprite
	this->Position.x = this->Center.x - this->Size.x/2;
	this->Position.y = this->Center.y - this->Size.y/2;
	//std::cout << "\n posx " << this->Position.x;
	//std::cout << "\n posy " << this->Position.y;
	//std::cout << "\n renderposx " << this->RenderPosition.x;
	//std::cout << "\n renderposy " << this->RenderPosition.y;

	boxCollider *temp = new boxCollider("default",*this, size.x, size.y);
	colliders_.push_back(temp);

	this->name = name;

	//load texture
	ResourceManager::LoadTexture(texture,true,texture);
	this->Texture = ResourceManager::GetTexture(texture);
	
	//texture for collider debug
	ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
	ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");

	//add Sprite to Scene
	scene.Sprites.push_back(this);

	scene.Sprites.back()->setPosition(this->Position);
	scene.Sprites.back()->setCenter(this->Center);
	scene.Sprites.back()->setSize(this->Size);
	scene.Sprites.back()->setVelocity(this->Velocity);
	scene.Sprites.back()->setColor(this->Color);
	scene.Sprites.back()->setRotation(this->Rotation);
	scene.Sprites.back()->setTexture(this->Texture);
	scene.Sprites.back()->IsSolid = this->IsSolid;
	scene.Sprites.back()->Destroyed = this->Destroyed;
	scene.Sprites.back()->collideDebug = this->collideDebug;
	
	this->setState("active", true);
	this->setState("visible", true);
	
}

void Sprite::Draw(SpriteRenderer &renderer)
{
	GLfloat t = 1;
	if (getState("visible"))
	{
		renderer.DrawSprite(this->getTexture(), this->getPosition(), this->getSize(), this->getRotation(), this->getColor(), t);
	}
	//check if collideDebug is true, if so draw all colliders
	
	if (collideDebug)
	{
		for (int i = 0; i < getColliders().size(); i++)
		{
			//std::cout << "width: " << getColliders().at(i)->getWidth();
			t = .15;

			//see which texture to use, if circle or box, if collider is static we need to exclude the position of the sprite
			if (getColliders().at(i)->getType() == "box")
			{
				renderer.DrawSprite(ResourceManager::GetTexture("debugGreen"), glm::vec2(getColliders().at(i)->getPosX() + this->getPosition().x, getColliders().at(i)->getPosY() + this->getPosition().y), glm::vec2(getColliders().at(i)->getWidth(), getColliders().at(i)->getHeight()), 0, glm::vec3(0, 255, 0), t);
			}
			else if (getColliders().at(i)->getType() == "staticBox")
			{
				renderer.DrawSprite(ResourceManager::GetTexture("debugGreen"), glm::vec2(getColliders().at(i)->getPosX(), getColliders().at(i)->getPosY()), glm::vec2(getColliders().at(i)->getWidth(), getColliders().at(i)->getHeight()), 0, glm::vec3(0, 255, 0), t);
			}
			else if (getColliders().at(i)->getType() == "circle")
			{
				renderer.DrawSprite(ResourceManager::GetTexture("debugGreenCircle"), glm::vec2(getColliders().at(i)->getPosX() + this->getPosition().x, getColliders().at(i)->getPosY() + this->getPosition().y), glm::vec2(getColliders().at(i)->getWidth(), getColliders().at(i)->getHeight()), 0, glm::vec3(0, 255, 0), t);
			}
			else if (getColliders().at(i)->getType() == "staticCircle")
			{
				renderer.DrawSprite(ResourceManager::GetTexture("debugGreenCircle"), glm::vec2(getColliders().at(i)->getPosX(), getColliders().at(i)->getPosY()), glm::vec2(getColliders().at(i)->getWidth(), getColliders().at(i)->getHeight()), 0, glm::vec3(0, 255, 0), t);
			}
		}
	}
	//renderer.DrawSprite(this->Texture, this->Position, this->Size, this->Rotation, this->Color);
}

//iterate through all this sprite's colliders, and have it check if it's colliding with another specified sprite's colliders
bool Sprite::collide(AbstractSprite* otherSprite)
{
	std::cout << otherSprite->getColliders().size();
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

bool Sprite::collide(Sprite* otherSprite)
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

glm::vec2 Sprite::getCenter()
{
	return this->Center;
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

void Sprite::setCenter(glm::vec2 newCenter)
{
	this->Center = newCenter;
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

void Sprite::addStaticBoxCollider(std::string name, int w, int h, int posX, int posY)
{
	staticBoxCollider *temp = new staticBoxCollider(name, w, h, posX, posY);
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

void Sprite::addCircleCollider(std::string name, double r, int posX, int posY)
{
	double r2 = r * 2;
	//if doesn't fit to sprite, we need to recenter the circle
	int diffY = 0;
	int diffX = 0;
	if (r2 != this->getSize().x || r2 != this->getSize().y)
	{
		//get x and y offset
		diffX = r - this->getSize().x/2;
		diffY = r - this->getSize().y/2;
	}
	circleCollider *temp = new circleCollider(name, *this, r, posX - diffX, posY - diffY);
	this->colliders_.push_back(temp);
}

void Sprite::addStaticCircleCollider(std::string name, double r, int posX, int posY)
{
	double r2 = r * 2;
	//if doesn't fit to sprite, we need to recenter the circle
	int diffY = 0;
	int diffX = 0;
	if (r2 != this->getSize().x || r2 != this->getSize().y)
	{
		//get x and y offset
		diffX = r - this->getSize().x / 2;
		diffY = r - this->getSize().y / 2;
	}
	staticCircleCollider *temp = new staticCircleCollider(name, r, posX - diffX, posY - diffY);
	this->colliders_.push_back(temp);
}

void Sprite::addPolyCollider(std::string name, std::vector<glm::vec2> verticies)
{
	PolyCollider *temp = new PolyCollider(name, *this, verticies);
	this->colliders_.push_back(temp);
}

void Sprite::update()
{
	this->Position.x += this->dx;
	this->Position.y -= this->dy;

	//update Center
	this->Center.x += this->dx;
	this->Center.y -= this->dy;

	//run Observer
	//std::cout << ObserverHandler::getInstance()->getNumberOfObservers();
	ObserverHandler::getInstance()->NotifyObservers();
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

bool Sprite::checkBounds(double screenWidth, double screenHeight)
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
	return true;
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
	//delete colliders
	for (int i = 0; i < colliders_.size(); i++)
	{
		delete colliders_.at(i);
	}
}
