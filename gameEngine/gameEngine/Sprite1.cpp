#include "Sprite1.h"



Sprite1::Sprite1()
{
}


Sprite1::Sprite1(std::string n, AbstractScene & scene, glm::vec2 pos, glm::vec2 size, GLchar * texture, glm::vec2 velocity, glm::vec3 color)
{
	this->name = n;
	this->Center = pos;
	this->Size = size;
	this->lastSize = this->Size;
	this->Rotation = 0;
	this->lastRotation = this->Rotation;
	//center the postion based on the height and width of the sprite
	this->Position.x = this->Center.x - this->Size.x / 2;
	this->Position.y = this->Center.y - this->Size.y / 2;

	this->lastPosition = this->Position;

	this->textureFile = texture;
	this->Color = color;
	this->collideDebug = false;
	this->transparency = 1;

	BoxCollider *temp = new BoxCollider("default", *this, (int)size.x, (int)size.y);
	temp->setPosition(this->Position);
	colliders_.push_back(temp);

	//see if texture is already loaded
	if (ResourceManager::Textures[texture].Image_Format != 6407)
	{
		this->Texture = ResourceManager::GetTexture(texture);
	}
	else
	{
		//load texture
		ResourceManager::LoadTexture(texture, true, texture);
		this->Texture = ResourceManager::GetTexture(texture);
	}

	scene.addSprite(this);
	this->parentScene = &scene;

	this->active = true;
	this->visible = true;

}

Sprite1::~Sprite1()
{
}
