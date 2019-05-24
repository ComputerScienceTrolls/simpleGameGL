#include "CircleCollider.h"

CircleCollider::CircleCollider(CircleCollider* copy)
{
	this->active = copy->active;
	this->name = copy->name;
	this->Position = copy->Position;
	this->type = copy->type;
	this->transparency = copy->transparency;
	this->setBoundAction(copy->getBoundAction());
	this->Size = copy->Size;
	this->Center = copy->Center;
	this->visible = copy->visible;

	if (copy->getScene())
	{
		copy->getScene()->addMovingObject(this);
		copy->getScene()->addDrawObject(this);
		copy->getScene()->addSceneObject(this);
	}

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
}

//consturctor with no positon offset from sprite.
CircleCollider::CircleCollider(std::string name, AbstractSprite &parent, float r):
	radius(r)
{
	this->Center.x = 0;
	this->Center.y = 0;
	this->Position.x = this->Center.x - this->Size.x / 2;
	this->Position.y = this->Center.y - this->Size.y / 2;
	this->Size.x = r*2;
	this->Size.y = r*2;
	this->type = "circle";
	this->active = true;
	this->transparency = float(.15);
	
	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
}

//consturctor with a position offset from it's sprite
CircleCollider::CircleCollider(std::string n, AbstractSprite &parent, float r, float posX, float posY) :
	radius(r)
{
	this->name = n;
	this->Center.x = posX;
	this->Center.y = posY;
	this->Position.x = this->Center.x - this->Size.x / 2;
	this->Position.y = this->Center.y - this->Size.y / 2;
	this->Size.x = r*2;
	this->Size.y = r*2;
	this->type = "circle";
	this->active = true;
	this->transparency = float(.15);

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
}

CircleCollider::CircleCollider(std::string n, AbstractScene &parent, float r) :
	radius(r)
{
	this->Center.x = 0;
	this->Center.y = 0;
	this->Position.x = this->Center.x - this->Size.x / 2;
	this->Position.y = this->Center.y - this->Size.y / 2;
	this->name = n;
	this->Size.x = r * 2;
	this->Size.y = r * 2;
	this->type = "circle";
	this->active = true;
	this->transparency = float(.15);

	parent.addMovingObject(this);
	parent.addDrawObject(this);
	parent.addSceneObject(this);

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
}

CircleCollider::CircleCollider(std::string n, AbstractScene &parent, float r, float posX, float posY) :
	radius(r)
{
	this->name = n;
	this->type = "circle";
	this->Size.x = r * 2;
	this->Size.y = r * 2;
	this->Position.x = float(posX);
	this->Position.y = float(posY);
	this->active = true;
	this->transparency = float(.15);

	parent.addMovingObject(this);
	parent.addDrawObject(this);
	parent.addSceneObject(this);

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
}

bool CircleCollider::collide(std::vector<AbstractCollider*> otherColliders)
{
	for (int i = 0; i < otherColliders.size(); i++)
	{
		//if other collider is a box and if not static
		if (otherColliders.at(i)->getType() == "box" || otherColliders.at(i)->getType() == "staticBox")
		{
			// Get center point circle first 
			glm::vec2 center(glm::vec2(this->getPosX(), this->getPosY()) + this->getRadius());

			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(otherColliders.at(i)->getSize().x / 2, otherColliders.at(i)->getSize().y / 2);
			glm::vec2 aabb_center(
				otherColliders.at(i)->getPosX() + aabb_half_extents.x,
				otherColliders.at(i)->getPosY() + aabb_half_extents.y
			);
			// Get difference vector between both centers
			glm::vec2 difference = center - aabb_center;
			glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
			// Add clamped value to AABB_center and we get the value of box closest to circle
			glm::vec2 closest = aabb_center + clamped;

			// Retrieve vector between center circle and closest point AABB and check if length <= radius
			difference = closest - center;
			if (glm::length(difference) < this->getRadius())
				return true;
		}
		//if other collider is a circle and static is false
		else if (otherColliders.at(i)->getType() == "circle")
		{
			float diffX = (this->getPosX()) - (otherColliders.at(i)->getPosX());
			float diffY = (this->getPosY()) - (otherColliders.at(i)->getPosY());

			double dist = std::sqrt((diffX * diffX) + (diffY * diffY));
			if (dist <= (this->getRadius() + otherColliders.at(i)->getRadius()))
				return true;
			else
				return false;
		}
	}
	return false;
}

bool CircleCollider::collide(AbstractCollider * otherCollider)
{
	//if other collider is a box and if not static
	if (otherCollider->getType() == "box")
	{
		// Get center point circle first 
		glm::vec2 center(glm::vec2(this->getPosX(), this->getPosY()) + this->getRadius());

		// Calculate AABB info (center, half-extents)
		glm::vec2 aabb_half_extents(otherCollider->getSize().x / 2, otherCollider->getSize().y / 2);
		glm::vec2 aabb_center(
			otherCollider->getPosX() + aabb_half_extents.x,
			otherCollider->getPosY() + aabb_half_extents.y
		);
		// Get difference vector between both centers
		glm::vec2 difference = center - aabb_center;
		glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
		// Add clamped value to AABB_center and we get the value of box closest to circle
		glm::vec2 closest = aabb_center + clamped;

		// Retrieve vector between center circle and closest point AABB and check if length <= radius
		difference = closest - center;
		if (glm::length(difference) < this->getRadius())
			return true;
	}
	//if other collider is a circle and static is false
	else if (otherCollider->getType() == "circle")
	{
		float diffX = (this->getSpriteCenterPos().x + this->getPosX()) - (otherCollider->getSpriteCenterPos().x + otherCollider->getPosX());
		float diffY = (this->getSpriteCenterPos().y + this->getPosY()) - (otherCollider->getSpriteCenterPos().y + otherCollider->getPosY());

		//float diffX = (this->Center.x + this->getPosX()) - (otherCollider->getCenter().x + otherCollider->getPosX());
		//float diffY = (this->Center.y + this->getPosY()) - (otherCollider->getCenter().y + otherCollider->getPosY());

		double dist = std::sqrt((diffX * diffX) + (diffY * diffY));
		if (dist <= (this->getRadius() + otherCollider->getRadius()))
			return true;
		else
			return false;
	}
	return false;
}

bool CircleCollider::collide(AbstractSprite * otherSprite)
{
	std::vector<AbstractCollider*> otherColliders = otherSprite->getColliders();

	for (int i = 0; i < otherColliders.size(); i++)
	{
		//if other collider is a box and if not static
		if (otherColliders.at(i)->getType() == "box")
		{
			// Get center point circle first 
			glm::vec2 center(glm::vec2(this->getPosX(), this->getPosY()) + this->getRadius());

			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(otherColliders.at(i)->getSize().x / 2, otherColliders.at(i)->getSize().y / 2);
			glm::vec2 aabb_center(
				otherColliders.at(i)->getPosX() + aabb_half_extents.x,
				 otherColliders.at(i)->getPosY() + aabb_half_extents.y
			);
			// Get difference vector between both centers
			glm::vec2 difference = center - aabb_center;
			glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
			// Add clamped value to AABB_center and we get the value of box closest to circle
			glm::vec2 closest = aabb_center + clamped;

			// Retrieve vector between center circle and closest point AABB and check if length <= radius
			difference = closest - center;
			if (glm::length(difference) < this->getRadius())
				return true;
		}

		//if other collider is a circle and static is false
		else if (otherColliders.at(i)->getType() == "circle")
		{
			float diffX = this->getPosX() - otherColliders.at(i)->getPosX();
			float diffY = this->getPosY() - otherColliders.at(i)->getPosY();

			double dist = std::sqrt((diffX * diffX) + (diffY * diffY));
			if (dist <= (this->getRadius() + otherColliders.at(i)->getRadius()))
				return true;
			else
				return false;
		}
	}
	return false;
}

float CircleCollider::getRadius()
{
	return radius;
}

void CircleCollider::Draw(AbstractRenderer *renderer)
{
	SpriteRenderer *sp = static_cast<SpriteRenderer*>(renderer);
	Texture2D tempTexture = ResourceManager::GetTexture("debugGreenCircle");
	sp->DrawSprite(tempTexture, this->Position, this->Size, 0, glm::vec3(0, 255, 0), this->transparency);
}

AbstractCollider* CircleCollider::clone()
{
	return new CircleCollider(this);
}

CircleCollider::~CircleCollider()
{

}
