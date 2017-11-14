#include "StaticBoxCollider.h"

StaticBoxCollider::StaticBoxCollider(std::string name, int w, int h, int posX, int posY):
	name(name), width(w), height(h), posXOffset(posX), posYOffset(posY), type("staticBox")
{
}

bool StaticBoxCollider::collide(std::vector<AbstractCollider*> otherColliders)
{
	for (int i = 0; i < otherColliders.size(); i++)
	{
		if (otherColliders.at(i)->getType() == "box")
		{
			// Collision x-axis?
			bool collisionX = (this->getPosX() + this->getWidth() >= otherColliders.at(i)->getSpritePos().x &&
				otherColliders.at(i)->getSpritePos().x + otherColliders.at(i)->getPosX() + otherColliders.at(i)->getWidth() >= this->getPosX());
			// Collision y-axis?
			bool collisionY = (this->getPosY() + (this->getHeight())) >= otherColliders.at(i)->getSpritePos().y &&
				otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY() + otherColliders.at(i)->getHeight() >= this->getPosY();

			// Collision only if on both axes
			if (collisionX && collisionY)
			{
				return collisionX && collisionY;
			}
		}
		else if (otherColliders.at(i)->getType() == "staticBox")
		{
			// Collision x-axis?
			bool collisionX = (this->getPosX() + this->getWidth() >= otherColliders.at(i)->getPosX() + otherColliders.at(i)->getWidth() >= this->getPosX());
			// Collision y-axis?
			bool collisionY = (this->getPosY() + (this->getHeight())) >= otherColliders.at(i)->getPosY() + otherColliders.at(i)->getHeight() >= this->getPosY();

			// Collision only if on both axes
			if (collisionX && collisionY)
			{
				return collisionX && collisionY;
			}
		}
		else if (otherColliders.at(i)->getType() == "circle")
		{
			// Get center point circle first 
			glm::vec2 center(otherColliders.at(i)->getSpritePos() + glm::vec2(otherColliders.at(i)->getPosX(), otherColliders.at(i)->getPosY()) + otherColliders.at(i)->getRadius());
			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(this->getWidth() / 2, this->getHeight() / 2);
			glm::vec2 aabb_center(
				this->getPosX() + aabb_half_extents.x,
				this->getPosY() + aabb_half_extents.y
			);
			// Get difference vector between both centers
			glm::vec2 difference = center - aabb_center;
			//std::cout << "\n diffx " << difference.x;
			//std::cout << "\n diffy " << difference.y;
			glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
			// Add clamped value to AABB_center and we get the value of box closest to circle
			glm::vec2 closest = aabb_center + clamped;

			//std::cout << "\n clamped " << aabb_half_extents.x;

			// Retrieve vector between center circle and closest point AABB and check if length <= radius
			difference = closest - center;

			if (glm::length(difference) < otherColliders.at(i)->getRadius())
				return true;
		}
		else if(otherColliders.at(i)->getType() == "staticCircle")
		{
			// Get center point circle first 
			glm::vec2 center(glm::vec2(otherColliders.at(i)->getPosX(), otherColliders.at(i)->getPosY()) + otherColliders.at(i)->getRadius());

			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(this->getWidth() / 2, this->getHeight() / 2);
			glm::vec2 aabb_center(
				this->getPosX() + aabb_half_extents.x,
				this->getPosY() + aabb_half_extents.y
			);
			// Get difference vector between both centers
			glm::vec2 difference = center - aabb_center;
			glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
			// Add clamped value to AABB_center and we get the value of box closest to circle
			glm::vec2 closest = aabb_center + clamped;

			// Retrieve vector between center circle and closest point AABB and check if length <= radius
			difference = closest - center;

			if (glm::length(difference) < otherColliders.at(i)->getRadius())
				return true;
		}
	}

	return false;
}

std::string StaticBoxCollider::getType()
{
	return this->type;
}

int StaticBoxCollider::getWidth()
{
	return this->width;
}

int StaticBoxCollider::getHeight()
{
	return this->height;
}

int StaticBoxCollider::getPosX()
{
	return this->posXOffset;
}

int StaticBoxCollider::getPosY()
{
	return this->posYOffset;
}

std::string StaticBoxCollider::getName()
{
	return this->name;
}

StaticBoxCollider::~StaticBoxCollider()
{
}
