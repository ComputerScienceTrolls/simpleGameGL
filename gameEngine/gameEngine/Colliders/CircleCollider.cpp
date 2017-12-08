#include "CircleCollider.h"

//consturctor with no positon offset from sprite.
CircleCollider::CircleCollider(std::string name, AbstractSprite &parent, float r):
	spriteParent(&parent), radius(r), transparency(.15)
{
	this->Position.x = 0;
	this->Position.y = 0;
	this->Size.x = r*2;
	this->Size.y = r*2;
	this->type = "circle";
	this->active = true;
}

//consturctor with a position offset from it's sprite
CircleCollider::CircleCollider(std::string name, AbstractSprite &parent, float r, int posX, int posY) :
	spriteParent(&parent), radius(r), transparency(.15)
{
	this->Position.x = posX;
	this->Position.y = posY;
	this->Size.x = r*2;
	this->Size.y = r*2;
	this->type = "circle";
	this->active = true;
}

CircleCollider::CircleCollider(std::string n, AbstractScene &parent, float r) :
	radius(r), transparency(.15)
{
	this->Position.x = 0;
	this->Position.y = 0;
	this->name = n;
	this->Size.x = r * 2;
	this->Size.y = r * 2;
	this->type = "circle";
	this->active = true;

	parent.addMovingObject(this);
	parent.addDrawObject(this);
	parent.addSceneObject(this);
}

CircleCollider::CircleCollider(std::string n, AbstractScene &parent, float r, int posX, int posY) :
	radius(r), transparency(.15)
{
	this->name = n;
	this->type = "circle";
	this->Size.x = r * 2;
	this->Size.y = r * 2;
	this->Position.x = posX;
	this->Position.y = posY;
	this->active = true;

	parent.addMovingObject(this);
	parent.addDrawObject(this);
	parent.addSceneObject(this);
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
			int diffX = (this->getPosX()) - (otherColliders.at(i)->getPosX());
			int diffY = (this->getPosY()) - (otherColliders.at(i)->getPosY());

			int dist = std::sqrt((diffX * diffX) + (diffY * diffY));
			if (dist <= (this->getRadius() + otherColliders.at(i)->getRadius()))
				return true;
			else
				return false;
		}
		else if (otherColliders.at(i)->getType() == "staticCircle")
		{
			/*
			int diffX = this->getPosX() - (otherColliders.at(i)->getSpriteCenterPos().x + otherColliders.at(i)->getPosX());
			int diffY = this->getPosY() - (otherColliders.at(i)->getSpriteCenterPos().y + otherColliders.at(i)->getPosY());

			int dist = std::sqrt((diffX * diffX) + (diffY * diffY));
			if (dist <= (this->getRadius() + otherColliders.at(i)->getRadius()))
				return true;
			else
				return false;
			*/
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
		int diffX = (this->getSpriteCenterPos().x + this->getPosX()) - (otherCollider->getSpriteCenterPos().x + otherCollider->getPosX());
		int diffY = (this->getSpriteCenterPos().y + this->getPosY()) - (otherCollider->getSpriteCenterPos().y + otherCollider->getPosY());

		int dist = std::sqrt((diffX * diffX) + (diffY * diffY));
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
			int diffX = this->getPosX() - otherColliders.at(i)->getPosX();
			int diffY = this->getPosY() - otherColliders.at(i)->getPosY();

			int dist = std::sqrt((diffX * diffX) + (diffY * diffY));
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

void CircleCollider::Draw(SpriteRenderer & renderer, glm::vec2 camPos)
{
	//if spriteParent exists use it for rendering
	renderer.DrawSprite(ResourceManager::GetTexture("debugGreenCircle"), glm::vec2(this->getPosX() + camPos.x, this->getPosY() + camPos.y), glm::vec2(this->getWidth(), this->getHeight()), 0, glm::vec3(0, 255, 0), this->transparency);
}

CircleCollider::~CircleCollider()
{
}
