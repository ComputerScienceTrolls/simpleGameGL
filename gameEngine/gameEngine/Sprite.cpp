#include "Sprite.h"

//pie constant for math
const double PI = 3.141592653589793238463;

Sprite::Sprite()
{
}

Sprite::Sprite(Sprite * copySprite)
{
	this->parentScene = copySprite->parentScene;
	this->Color = copySprite->Color;
	this->Texture = copySprite->Texture;
	this->collideDebug = copySprite->collideDebug;
	this->transparency = copySprite->transparency;
	this->name = copySprite->name;
	this->Center = copySprite->Center;
	this->Size = copySprite->Size;
	this->lastSize = copySprite->Size;
	this->Position = copySprite->Position;
	this->lastPosition = copySprite->lastPosition;
	this->Velocity = copySprite->Velocity;
	this->Rotation = copySprite->Rotation;
	this->lastRotation = copySprite->lastRotation;
	this->speed = copySprite->speed;
	this->moveAngle = copySprite->moveAngle;
	this->imgAngle = copySprite->imgAngle;
	
	this->active = copySprite->active;
	this->visible = copySprite->visible;

	this->initCenter = copySprite->initCenter;
	this->initColor = copySprite->initColor;
	this->initPosition = copySprite->initPosition;
	this->initRotation = copySprite->initRotation;
	this->initSize = copySprite->initSize;
	this->initTexture = copySprite->initTexture;
	this->initTextureFile = copySprite->initTextureFile;
	this->Velocity = copySprite->Velocity;

	this->parentScene->addSprite(this);
}

//empty sprite
Sprite::Sprite(std::string n, AbstractScene &scene)
	: parentScene(&scene), Color(1.0f), Texture(), collideDebug(false), transparency(1)
{
	this->name = n;
	this->Center = glm::vec2(10);
	this->Size = glm::vec2(0);
	this->lastSize = this->Size;
	this->Position.x = this->Center.x - this->Size.x / 2;
	this->Position.y = this->Center.y - this->Size.y / 2;
	this->lastPosition = this->Position;
	this->Velocity = glm::vec2(0);
	this->Rotation = 0;
	this->lastRotation = Rotation;
	this->speed = 10;
	this->moveAngle = 0;
	this->imgAngle = 0;
	//give default box collider
	BoxCollider *temp = new BoxCollider("default",*this, 1, 1);
	colliders_.push_back(temp);

	//texture for collider debug
	ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
	ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");

	scene.addSprite(this);

	this->active = true;
	this->visible = true;

	//init init vars, for restarting scenes
	initCenter = Center;
	initColor = Color;
	initPosition = Position;
	initRotation = Rotation;
	initSize = Size;
	initTexture = Texture;
	initTextureFile = textureFile;
	initVelocity = Velocity;
}

//make given pos the center of the sprite, so calc the real pos, setup given texture, setup collider texture, add sprite to scene, set velocity, and init initvalues
Sprite::Sprite(std::string n, AbstractScene &scene, glm::vec2 pos, glm::vec2 size, GLchar* texture, glm::vec2 velocity, glm::vec3 color)
	: parentScene(&scene), textureFile(texture), Color(color), collideDebug(false), transparency(1)
{
	this->name = n;
	this->Center = pos;
	this->Size = size;
	this->lastSize = this->Size;
	this->Velocity = velocity;
	this->Rotation = 0;
	this->lastRotation = this->Rotation;
	//center the postion based on the height and width of the sprite
	this->Position.x = this->Center.x - this->Size.x/2;
	this->Position.y = this->Center.y - this->Size.y/2;
	
	this->lastPosition = this->Position;

	BoxCollider *temp = new BoxCollider("default",*this, (int)size.x, (int)size.y);
	temp->setPosition(this->Position);
	colliders_.push_back(temp);

	//see if texture is already loaded
	//std::cout << ResourceManager::Textures["wut"].Image_Format << "\n";
	if (ResourceManager::Textures[texture].Image_Format != 6407)
	{
		std::cout << "using already loaded Texture";
		this->Texture = ResourceManager::GetTexture(texture);
	}
	else
	{
		std::cout << "loaded new Texture\n";
		//load texture
		ResourceManager::LoadTexture(texture, true, texture);
		this->Texture = ResourceManager::GetTexture(texture);
	}

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}

	scene.addSprite(this);

	this->active = true;
	this->visible = true;

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
}

//if visible true, draw sprite, draw collider(s) if collideDebug true.
void Sprite::Draw(SpriteRenderer &renderer)
{
	if (visible)
	{
		Texture2D tempTexture = this->getTexture();
		renderer.DrawSprite(tempTexture, this->Position, this->getSize(), this->getRotation(), this->getColor(), this->transparency);
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
		//AbstractCollider* test = otherSprite->getColliders().at(i);
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

bool Sprite::collide(AbstractCollider * otherCollider)
{
	for (int i = 0; i < this->colliders_.size(); i++)
	{
		if (this->colliders_.at(i)->collide(otherCollider))
		{
			return true;
		}
	}
	return false;
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
	temp->setPosition(this->Position);
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

void Sprite::setVisible(bool newVisible)
{
	this->visible = newVisible;
}

//add circle collider to sprite, auto recenter circle before placing
void Sprite::addCircleCollider(std::string name, float r, int posX, int posY)
{
	float r2 = r * 2;
	//if doesn't fit to sprite, we need to recenter the circle
	int diffY = 0;
	int diffX = 0;
	if (r2 != this->getSize().x || r2 != this->getSize().y)
	{
		//get x and y offset
		diffX = int(r - this->getSize().x/2);
		diffY = int(r - this->getSize().y/2);
	}
	CircleCollider *temp = new CircleCollider(name, *this, r, (int)this->Position.x + posX - diffX, (int)this->Position.y + posY - diffY);
	this->colliders_.push_back(temp);
}

//add a poly collider to the sprite, takes a list of verticies
void Sprite::addPolyCollider(std::string name, std::vector<glm::vec2> verticies)
{
	PolyCollider *temp = new PolyCollider(name, *this, verticies);
	this->colliders_.push_back(temp);
}

//called every cycle as long sprite is active, sets position and center based on dx and dy. Check bounds
void Sprite::Update()
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
		for (int i = 0; i < colliders_.size(); i++)
		{
			colliders_[i]->changePositionBy(diffPos);
			colliders_[i]->setSize(colliders_.at(i)->getSize() + diffSize);
		}

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->changePositionBy(diffPos);
			children[i]->setSize(children.at(i)->getSize() + diffSize);
		}
	}

	lastPosition = Position;
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

Texture2D Sprite::getTexture()
{
	return this->Texture;
}

glm::vec3 Sprite::getColor()
{
	return this->Color;
}

bool Sprite::getVisible()
{
	return this->visible;
}

std::vector<AbstractCollider*> Sprite::getColliders()
{
	return this->colliders_;
}

void Sprite::setTexture(Texture2D newTexture)
{
	this->Texture = newTexture;
}

void Sprite::setColor(glm::vec3 newColor)
{
	this->Color = newColor;
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
