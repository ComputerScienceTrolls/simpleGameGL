#include "RocketSprite.h"

RocketSprite::RocketSprite()
{
}

RocketSprite::RocketSprite(std::string n, AbstractScene & scene)
{
	this->name = n;
	this->Center = glm::vec2(250, 400);
	this->Size = glm::vec2(10,30);
	this->lastSize = this->Size;
	//this->Velocity = glm::vec2(0,9.8);
	this->Rotation = 0;
	this->lastRotation = this->Rotation;
	//center the postion based on the height and width of the sprite
	this->Position.x = this->Center.x - this->Size.x / 2;
	this->Position.y = this->Center.y - this->Size.y / 2;

	this->lastPosition = this->Position;

	BoxCollider *temp = new BoxCollider("default", *this, this->Size.x, this->Size.y);
	temp->setPosition(this->Position);
	glm::vec2 test2 = temp->getPosition();
	colliders_.push_back(temp);

	//load texture
	ResourceManager::LoadTexture("textures/RedRocket.png", true, "textures/RedRocket.png");
	this->Texture = ResourceManager::GetTexture("textures/RedRocket.png");

	//texture for collider debug
	ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
	ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	
	this->active = true;
	this->visible = true;
	
	scene.addSprite(this);
}

RocketSprite::~RocketSprite()
{
}
