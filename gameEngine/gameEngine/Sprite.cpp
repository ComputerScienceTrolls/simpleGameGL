#include "Sprite.h"

//pie constant for math
const double PI = 3.141592653589793238463;

//empty sprite
Sprite::Sprite(std::string n, AbstractScene &scene)
	: name(n), parentScene(&scene), Position(10, 10), Size(0, 0), Velocity(glm::vec2(0.0f, 0.0f)), Color(1.0f), Rotation(0.0f), Texture(), dx(0), dy(0), speed(10), moveAngle(0), imgAngle(0), collideDebug(false), transparency(1)
{
	//give default box collider
	BoxCollider *temp = new BoxCollider("default",*this, 1, 1);
	colliders_.push_back(temp);

	//texture for collider debug
	ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
	ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");

	scene.addSprite(this);
	/*
	//add Sprite to Scene, get Sprites, add new sprite.
	std::vector<AbstractSprite*> tempSprites = scene.getSprites();
	tempSprites.push_back(this);

	tempSprites.back()->setPosition(this->Position);
	tempSprites.back()->setCenter(this->Center);
	tempSprites.back()->setSize(this->Size);
	tempSprites.back()->setVelocity(this->Velocity);
	tempSprites.back()->setColor(this->Color);
	tempSprites.back()->setRotation(this->Rotation);
	tempSprites.back()->setTexture(this->Texture);
	tempSprites.back()->IsSolid = this->IsSolid;
	tempSprites.back()->Destroyed = this->Destroyed;
	tempSprites.back()->collideDebug = this->collideDebug;

	//set new vector back to the scene
	scene.setSprites(tempSprites);
	*/
	this->setState("active", true);
	this->setState("visible", true);

	//init init vars, for restarting scenes
	initCenter = Center;
	initColor = Color;
	initPosition = Position;
	initRotation = Rotation;
	initSize = Size;
	initTexture = Texture;
	initTextureFile = textureFile;
	initVelocity = Velocity;

	this->setBoundAction("STOP");
}

//make given pos the center of the sprite, so calc the real pos, setup given texture, setup collider texture, add sprite to scene, set velocity, and init initvalues
Sprite::Sprite(std::string n, AbstractScene &scene, glm::vec2 pos, glm::vec2 size, GLchar* texture, glm::vec2 velocity, glm::vec3 color)
	:name(n), parentScene(&scene), Center(pos), Size(size), textureFile(texture), Velocity(velocity), Color(color), Rotation(0.0f), collideDebug(false), transparency(1), RenderPosition(0), renderDX(0), renderDY(0)
{
	//center the postion based on the height and width of the sprite
	this->Position.x = this->Center.x - this->Size.x/2;
	this->Position.y = this->Center.y - this->Size.y/2;

	BoxCollider *temp = new BoxCollider("default",*this, size.x, size.y);
	colliders_.push_back(temp);

	//load texture
	ResourceManager::LoadTexture(texture,true,texture);
	this->Texture = ResourceManager::GetTexture(texture);
	
	//texture for collider debug
	ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
	ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");

	//add Sprite to Scene, get Sprites, add new sprite.
	std::vector<AbstractSprite*> tempSprites = scene.getSprites();
	tempSprites.push_back(this);

	tempSprites.back()->setPosition(this->Position);
	tempSprites.back()->setCenter(this->Center);
	tempSprites.back()->setSize(this->Size);
	tempSprites.back()->setVelocity(this->Velocity);
	tempSprites.back()->setColor(this->Color);
	tempSprites.back()->setRotation(this->Rotation);
	tempSprites.back()->setTexture(this->Texture);
	tempSprites.back()->IsSolid = this->IsSolid;
	tempSprites.back()->Destroyed = this->Destroyed;
	tempSprites.back()->collideDebug = this->collideDebug;

	//set new vector back to the scene
	scene.setSprites(tempSprites);
	
	this->setState("active", true);
	this->setState("visible", true);

	//set up velocity
	this->dx = Velocity.x;
	this->dy = Velocity.y;
	
	//init init vars, for restarting scenes
	initCenter = Center;
	initColor = Color;
	initPosition = Position;
	initRotation = Rotation;
	initSize = Size;
	initTexture = Texture;
	initTextureFile = textureFile;
	initVelocity = Velocity;

	resetCounter = 0;

	this->setBoundAction("STOP");
}

//if visible true, draw sprite, draw collider(s) if collideDebug true.
void Sprite::Draw(SpriteRenderer &renderer)
{
	if (getState("visible"))
	{
		renderer.DrawSprite(this->getTexture(), this->getPosition() + RenderPosition, this->getSize(), this->getRotation(), this->getColor(), this->transparency);
	}
	//check if collideDebug is true, if so draw all colliders
	
	if (collideDebug)
	{
		for (int i = 0; i < colliders_.size(); i++)
		{
			colliders_.at(i)->Draw(renderer);
		}
	}
}

//iterate through all this sprite's colliders, and have it check if it's colliding with another specified sprite's colliders
bool Sprite::collide(AbstractSprite* otherSprite)
{
	for (int i = 0; i < this->colliders_.size(); i++)
	{
		AbstractCollider* test = otherSprite->getColliders().at(i);
		if (this->colliders_.at(i)->collide(otherSprite->getColliders()))
		{
			return true;
		}
	}
	//if we get here, no collision detected, return false
	return false;
}

//iterate through all this sprite's colliders, and have it check if it's colliding with another specified sprite's colliders
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

//multiple the velocity by a given float.
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

//set Sprite's dx
void Sprite::setDX(float newDx)
{
	this->dx = newDx;
}

//set Sprite's dy
void Sprite::setDY(float newDy)
{
	this->dy = newDy;
}

//set Sprite's dx and dy based on angle and thrust/magnitude
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

//opposite of calcVector:
//sets speed and moveAngle based on dx, dy
void Sprite::calcSpeedAngle()
{
	this->speed = std::sqrt((this->dx * this->dx) + (this->dy * this->dy));
	this->moveAngle = std::atan2(this->dy, this->dx);
}

//used throughout speed angle calculations to 
//recalculate dx and dy based on speed and angle
void Sprite::calcVector()
{
	this->dx = this->speed * std::cos(this->moveAngle);
	this->dy = this->speed * std::sin(this->moveAngle);
}

//set new speed and recalc the vector
void Sprite::setSpeed(float newSpeed)
{
	this->speed = newSpeed;
	this->calcVector();
}

//set rotation to new angle, don't calc change
void Sprite::setImgAngle(float newAngle)
{
	this->Rotation = newAngle;
}

//set move angle, angle the sprite will move
void Sprite::setMoveAngle(float newAngle)
{
	this->moveAngle = newAngle;
	this->calcVector();
}

//add box collider to the sprite. with pos offset from sprite
void Sprite::addBoxCollider(std::string name, int w, int h, int posX, int posY)
{
	BoxCollider *temp = new BoxCollider(name, *this, w, h, posX, posY);
	this->colliders_.push_back(temp);
}

//add box collider to the sprite. pos is assumed on sprite
void Sprite::addBoxCollider(std::string name, int w, int h)
{
	BoxCollider *temp = new BoxCollider(name, *this, w, h);
	this->colliders_.push_back(temp);
}

//add static(none moving) box collider to the sprite.
void Sprite::addStaticBoxCollider(std::string name, int w, int h, int posX, int posY)
{
	StaticBoxCollider *temp = new StaticBoxCollider(name, w, h, posX, posY);
	this->colliders_.push_back(temp);
}

//removes collider from sprite with given name, if multiple with name only gets last one
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

void Sprite::setRenderPosX(int newX)
{
	this->RenderPosition.x = newX;
}

void Sprite::setRenderPosY(int newY)
{
	this->RenderPosition.y = newY;
}

void Sprite::setRenderDX(int newDX)
{
	this->renderDX = newDX;
}

void Sprite::setRenderDY(int newDY)
{
	this->renderDY = newDY;
}

//add circle collider to sprite, auto recenter circle before placing
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
	CircleCollider *temp = new CircleCollider(name, *this, r, posX - diffX, posY - diffY);
	this->colliders_.push_back(temp);
}

//add a static(none moving) circle collider to the sprite, auto recenter circle before placing
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
	StaticCircleCollider *temp = new StaticCircleCollider(name, r, posX - diffX, posY - diffY);
	this->colliders_.push_back(temp);
}

//add a poly collider to the sprite, takes a list of verticies
void Sprite::addPolyCollider(std::string name, std::vector<glm::vec2> verticies)
{
	PolyCollider *temp = new PolyCollider(name, *this, verticies);
	this->colliders_.push_back(temp);
}

//called every cycle as long sprite is active, sets position and center based on dx and dy. Check bounds
void Sprite::update()
{
	std::cout << this->dx;
	this->Position.x += this->dx;
	this->Position.y -= this->dy;

	//update RenderPos based on RenderDX and DY
	this->RenderPosition.x += this->renderDX;
	this->RenderPosition.y += this->renderDY;

	//update Center
	this->Center.x += this->dx;
	this->Center.y -= this->dy;

	this->checkBounds(parentScene->getWidth(),parentScene->getHeight());
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

//checks if sprite is on screen, if off screen do something based on Sprite's boundaction
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
			this->setSpeed(0);
			this->active = false;
			this->visible = false;
		}

	}
	else {
		//keep on going forever
	}
	return true;
}

//hide the sprite, by moving it far far away
void Sprite::hide()
{
	this->Position.x = 10000;
	this->Position.y = 10000;
}

//reset Sprite's inital values
void Sprite::reset()
{
	this->Position = initPosition;
	this->Velocity = initVelocity;
	this->Rotation = initRotation;
	this->Center = initCenter;
	this->Color = initColor;
	this->Texture = initTexture;
	this->textureFile = initTextureFile;

	this->dx = Velocity.x;
	this->dy = Velocity.y;
}

//does not currently work, reload inital texture and assign it
void Sprite::reInit()
{
	std::cout << "\nuh oops\n";
	resetCounter++;
	//load texture
	std::string temp(textureFile + std::to_string(resetCounter));
	const char* temp2 = temp.c_str();
	std::cout << temp2;
	ResourceManager::LoadTexture(textureFile, true, temp2);
	this->Texture = ResourceManager::GetTexture(temp2);
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

std::vector<AbstractCollider*> Sprite::getColliders()
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

void Sprite::setColliders(std::vector<AbstractCollider*> newColliders)
{
	this->colliders_ = newColliders;
}

void Sprite::setName(std::string newName)
{
	this->name = newName;
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
