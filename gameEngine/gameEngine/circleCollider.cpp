#include "circleCollider.h"

circleCollider::circleCollider(AbstractSprite &parent, float r):
	type("circle"), spriteParent(&parent), radius(r)
{
}

circleCollider::circleCollider(AbstractSprite &parent, float r, int posX, int posY):
	posXOffset(posX), posYOffset(posY), type("circle"), spriteParent(&parent), radius(r)
{
}

bool circleCollider::collide(std::vector<collider*> otherColliders)
{
	for (int i = 0; i < otherColliders.size(); i++)
	{
		if (otherColliders.at(i)->getType() == "box")
		{
			// Get center point circle first 
			glm::vec2 center(this->getSpritePos() + glm::vec2(this->getPosX(), this->getPosY()) + this->getRadius());
			
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
		else if (otherColliders.at(i)->getType() == "circle")
		{
			int diffX = this->getPosX() - otherColliders.at(i)->getSpritePos().x;
			int diffY = this->getPosY() - otherColliders.at(i)->getSpritePos().y;
			int dist = std::sqrt((diffX * diffX) + (diffY * diffY));

			if (dist >= this->getRadius())
				return true;
			else
				return false;

		}
	}

	return false;
}

float circleCollider::getRadius()
{
	return radius;
}

int circleCollider::getPosX()
{
	return posXOffset;
}

int circleCollider::getPosY()
{
	return posYOffset;
}

std::string circleCollider::getType()
{
	return this->type;
}

glm::vec2 circleCollider::getSpriteSize()
{
	return spriteParent->getSize();
}

std::string circleCollider::getName()
{
	return this->name;
}

glm::vec2 circleCollider::getSpritePos()
{
	return spriteParent->getPosition();
}

circleCollider::~circleCollider()
{
}
