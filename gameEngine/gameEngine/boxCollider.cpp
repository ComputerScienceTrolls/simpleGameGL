#include "boxCollider.h"


boxCollider::boxCollider(std::string newName, AbstractSprite &parent, int w, int h) :
	name(newName), offsetW(w), offsetH(h), posXOffset(0), posYOffset(0), type("box"), spriteParent(&parent)
{

}

boxCollider::boxCollider(std::string newName, AbstractSprite &parent,int w, int h, int posX, int posY) :
	name(newName), offsetW(w), offsetH(h), posXOffset(posX), posYOffset(posY), type("box"), spriteParent(&parent)
{

}

glm::vec2 boxCollider::getSpritePos()
{
	return spriteParent->getPosition();
}

glm::vec2 boxCollider::getSpriteSize()
{
	return spriteParent->getSize();
}

std::string boxCollider::getName()
{
	return this->name;
}

bool boxCollider::collide(std::vector<collider*> otherColliders)
{
	for (int i = 0; i < otherColliders.size(); i++)
	{
		if (otherColliders.at(i)->getType() == "box")
		{
			// Collision x-axis?
			bool collisionX = ((this->getSpritePos().x + this->getPosX()) + (this->getWidth())) >= otherColliders.at(i)->getSpritePos().x &&
				otherColliders.at(i)->getSpritePos().x + otherColliders.at(i)->getPosX() + otherColliders.at(i)->getWidth() >= this->getSpritePos().x + this->getPosX();
			// Collision y-axis?
			bool collisionY = ((this->getSpritePos().y + this->getPosY()) + (this->getHeight())) >= otherColliders.at(i)->getSpritePos().y &&
				otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY() + otherColliders.at(i)->getHeight() >= this->getSpritePos().y + this->getPosY();

			// Collision only if on both axes
			if (collisionX && collisionY)
			{
				return collisionX && collisionY;
			}
			
		}
		else if (otherColliders.at(i)->getType() == "circle")
		{
			// Get center point circle first 
			glm::vec2 center(otherColliders.at(i)->getSpritePos() + otherColliders.at(i)->getRadius());
			
			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(this->getSpriteSize().x / 2, this->getSpriteSize().y / 2);
			glm::vec2 aabb_center(
				this->getSpritePos().x + aabb_half_extents.x,
				this->getSpritePos().y + aabb_half_extents.y
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

glm::vec2 boxCollider::getSpriteCenterPos()
{
	return spriteParent->getRenderPosition();
}

std::string boxCollider::getType()
{
	return type;
}

boxCollider::~boxCollider()
{
}
