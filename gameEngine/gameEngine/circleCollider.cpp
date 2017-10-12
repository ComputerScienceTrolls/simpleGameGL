#include "circleCollider.h"

circleCollider::circleCollider(std::string name, AbstractSprite &parent, float r):
	type("circle"), spriteParent(&parent), radius(r)
{
}

circleCollider::circleCollider(std::string name, AbstractSprite &parent, float r, int posX, int posY):
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
			glm::vec2 center(this->getSpritePos() + this->getRadius());

			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(otherColliders.at(i)->getSpriteSize().x / 2, otherColliders.at(i)->getSpriteSize().y / 2);
			glm::vec2 aabb_center(
				otherColliders.at(i)->getSpritePos().x + aabb_half_extents.x,
				otherColliders.at(i)->getSpritePos().y + aabb_half_extents.y
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

			/*
			int rectX = otherColliders.at(i)->getSpritePos().x + otherColliders.at(i)->getPosX();
			int rectY = otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY();
			int cDistanceX = std::abs(this->getSpritePos().x - otherColliders.at(i)->getSpritePos().x);
			int cDistanceY = std::abs(this->getSpritePos().y - otherColliders.at(i)->getSpritePos().y);

			if (cDistanceX > (rectX / 2 + this->getRadius()))
				return false;
			if (cDistanceY > (rectY / 2 + this->getRadius()))
				return false;

			if (cDistanceX <= (rectX / 2))
				return true;
			if (cDistanceY <= (rectY / 2))
				return true;

			int cornerDistance = std::pow(cDistanceX - rectX / 2, 2) + std::pow(cDistanceY - rectY / 2, 2);
			return (cornerDistance <= (std::pow(this->getRadius(), 2)));
			*/
			/*
			// Get center point circle first 
			glm::vec2 center(this->getSpritePos() + glm::vec2(this->getPosX(), this->getPosY()) + this->getRadius());
			
			//std::cout << "\nradius: " << this->getRadius();
			//std::cout << "\ncenterX: " << center.x;
			//std::cout << "\ncenterY: " << center.y;

			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents((otherColliders.at(i)->getSpriteSize().x + otherColliders.at(i)->getPosX()) / 2,( otherColliders.at(i)->getSpriteSize().y  + otherColliders.at(i)->getPosY())/ 2);
			glm::vec2 aabb_center(
				otherColliders.at(i)->getSpritePos().x  + otherColliders.at(i)->getPosX() +  aabb_half_extents.x,
				otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY() + aabb_half_extents.y
			);
			std::cout << "\n pos: " << this->getSpritePos().x;
			std::cout << "\n aabb: " << aabb_center.x;
			
			// Get difference vector between both centers
			glm::vec2 difference = center - aabb_center;
			std::cout << "\n diff: " << difference.x;
			glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
			std::cout << "\nclamp " << clamped.x;
			// Add clamped value to AABB_center and we get the value of box closest to circle
			glm::vec2 closest = aabb_center + clamped;
			// Retrieve vector between center circle and closest point AABB and check if length <= radius
			difference = closest - center;
			std::cout << "\n" << difference.x << ", " << difference.y << "\n";
			if (glm::length(difference) < this->getRadius())
				return true;
				*/
		}
		else if (otherColliders.at(i)->getType() == "circle")
		{
			int diffX = (this->getSpritePos().x + this->getPosX()) - (otherColliders.at(i)->getSpritePos().x + otherColliders.at(i)->getPosX());
			int diffY = (this->getSpritePos().y + this->getPosY()) - (otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY());
			int dist = std::sqrt((diffX * diffX) + (diffY * diffY));

			std::cout << "\n" << dist;
			std::cout << "\n" << this->getRadius();
			if (dist <= this->getRadius())
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

int circleCollider::getWidth()
{
	return this->radius*2;
}

int circleCollider::getHeight()
{
	return this->radius*2;
}

circleCollider::~circleCollider()
{
}
