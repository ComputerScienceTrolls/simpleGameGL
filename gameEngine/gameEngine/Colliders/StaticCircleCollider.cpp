#include "StaticCircleCollider.h"

StaticCircleCollider::StaticCircleCollider(std::string name, float r):
	name(name), radius(r), type("staticCircle")
{
}

StaticCircleCollider::StaticCircleCollider(std::string name, float r, int posX, int posY):
	name(name), radius(r), posXOffset(posX), posYOffset(posY), type("staticCircle")
{
}

bool StaticCircleCollider::collide(std::vector<AbstractCollider*> otherColliders)
{
	for (int i = 0; i < otherColliders.size(); i++)
	{
		//if other collider is a box and if not static
		if (otherColliders.at(i)->getType() == "box")
		{
			// Get center point circle first 
			glm::vec2 center(glm::vec2(this->getPosX(), this->getPosY()) + this->getRadius());

			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(otherColliders.at(i)->getSpriteSize().x / 2, otherColliders.at(i)->getSpriteSize().y / 2);
			glm::vec2 aabb_center(
				otherColliders.at(i)->getSpritePos().x + otherColliders.at(i)->getPosX() + aabb_half_extents.x,
				otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY() + aabb_half_extents.y
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
		//if other collider is a box and this collider is static
		else if (otherColliders.at(i)->getType() == "staticBox")
		{
			// Get center point circle first 
			glm::vec2 center(glm::vec2(this->getPosX(), this->getPosY()) + this->getRadius());

			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(otherColliders.at(i)->getSpriteSize().x / 2, otherColliders.at(i)->getSpriteSize().y / 2);
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
			int diffX = this->getPosX() - (otherColliders.at(i)->getSpritePos().x + otherColliders.at(i)->getPosX());
			int diffY = this->getPosY() - (otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY());
			std::cout << "\n diffX " << diffX;
			std::cout << "\n diffY " << diffY;
			int dist = std::sqrt((diffX * diffX) + (diffY * diffY));
			if (dist <= (this->getRadius() + otherColliders.at(i)->getRadius()))
				return true;
			else
				return false;
		}
		else if (otherColliders.at(i)->getType() == "staticCircle")
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

int StaticCircleCollider::getWidth()
{
	return this->radius*2;
}

int StaticCircleCollider::getHeight()
{
	return this->radius*2;
}

float StaticCircleCollider::getRadius()
{
	return this->radius;
}

int StaticCircleCollider::getPosX()
{
	return this->posXOffset;
}

int StaticCircleCollider::getPosY()
{
	return this->posYOffset;
}

std::string StaticCircleCollider::getType()
{
	return this->type;
}

std::string StaticCircleCollider::getName()
{
	return this->name;
}
