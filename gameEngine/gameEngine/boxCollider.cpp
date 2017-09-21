#include "boxCollider.h"


boxCollider::boxCollider(Sprite &parent, int w, int h) :
	offsetW(w), offsetH(h), posXOffset(0), posYOffset(0), type("box"), spriteParent(&parent)
{

}

boxCollider::boxCollider(Sprite &parent,int w, int h, int posX, int posY) :
	offsetW(w), offsetH(h), posXOffset(posX), posYOffset(posY), type("box"), spriteParent(&parent)
{

}

glm::vec2 boxCollider::getSpritesPos()
{
	return this->spriteParent->getPosition();
}

glm::vec2 boxCollider::getSpriteSize()
{
	return this->spriteParent->getSize();
}

bool boxCollider::collide(std::vector<collider*> otherColliders)
{
	if (this->getType() == "box")
	{
		for (int j = 0; j < otherColliders.size(); j++)
		{
			if (otherColliders.at(j)->getType() == "box")
			{
				// Collision x-axis?
				bool collisionX = ((this->getSpritePos().x + this->getPosX()) + (this->getWidth())) >= otherColliders.at(j)->getSpritePos().x &&
					otherColliders.at(j)->getSpritePos().x + otherColliders.at(j)->getPosX() + otherColliders.at(j)->getWidth() >= this->getSpritePos().x;
				// Collision y-axis?
				bool collisionY = (this->getSpritePos().y + this->getPosY()) + (this->getSpriteSize().y + this->getHeight()) >= otherColliders.at(j)->getSpritePos().y &&
					otherColliders.at(j)->getSpritePos().y + otherColliders.at(j)->getPosY() + otherColliders.at(j)->getSpriteSize().y + otherColliders.at(j)->getHeight() >= this->getSpritePos().y;
				// Collision only if on both axes
				if (collisionX && collisionY)
				{
					return collisionX && collisionY;
				}
			}
			/*
			else if (otherColliders.at(j)->getType() == "circle")
			{
				// Get center point circle first 
				glm::vec2 center(this->getSpritePos() + glm::vec2(this->getPosX(), this->getPosY()) + this->getRadius());
				// Calculate AABB info (center, half-extents)
				glm::vec2 aabb_half_extents(otherColliders.at(j)->getSpriteSize().x / 2, otherColliders.at(j)->getSpriteSize().y / 2);
				glm::vec2 aabb_center(
					otherSprite->getPosition().x + otherSprite->getColliders().at(j)->getPosX() + aabb_half_extents.x,
					otherSprite->getPosition().y + otherSprite->getColliders().at(j)->getPosY() + aabb_half_extents.y
				);
				// Get difference vector between both centers
				glm::vec2 difference = center - aabb_center;
				glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
				// Add clamped value to AABB_center and we get the value of box closest to circle
				glm::vec2 closest = aabb_center + clamped;
				// Retrieve vector between center circle and closest point AABB and check if length <= radius
				difference = closest - center;
				if (glm::length(difference) < this->getColliders().at(i)->getRadius())
					return true;
			}
			*/

		}

	}
	/*
	else if (colliders_.at(i)->getType() == "circle")
	{
		// Get center point circle first 
		glm::vec2 center(this->Position + glm::vec2(this->colliders_.at(i)->getPosX(), this->colliders_.at(i)->getPosY()) + this->colliders_.at(i)->getRadius());
		// Calculate AABB info (center, half-extents)
		glm::vec2 aabb_half_extents(otherSprite->getSize().x / 2, otherSprite->getSize().y / 2);
		glm::vec2 aabb_center(
			otherSprite->getPosition().x + aabb_half_extents.x,
			otherSprite->getPosition().y + aabb_half_extents.y
		);
		// Get difference vector between both centers
		glm::vec2 difference = center - aabb_center;
		glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
		// Add clamped value to AABB_center and we get the value of box closest to circle
		glm::vec2 closest = aabb_center + clamped;
		// Retrieve vector between center circle and closest point AABB and check if length <= radius
		difference = closest - center;
		if (glm::length(difference) < this->colliders_.at(i)->getRadius())
			return true;
	}
	*/
}

int boxCollider::getWidth()
{
	return offsetW;
}

int boxCollider::getHeight()
{
	return offsetH;
}

int boxCollider::getPosX()
{
	return posXOffset;
}

int boxCollider::getPosY()
{
	return posYOffset;
}

std::string boxCollider::getType()
{
	return type;
}

boxCollider::~boxCollider()
{
}
