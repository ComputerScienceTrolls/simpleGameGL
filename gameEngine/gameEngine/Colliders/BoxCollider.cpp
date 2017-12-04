#include "BoxCollider.h"

//constructor with no position offset
BoxCollider::BoxCollider(std::string newName, AbstractSprite &parent, int w, int h) :
	spriteParent(&parent), transparency(.15)
{
	this->name = newName;
	this->offsetW = w;
	this->offsetH = h;
	this->posXOffset = 0;
	this->posYOffset = 0;
	this->type = "box";
}

//consturctor with a positon offset
BoxCollider::BoxCollider(std::string newName, AbstractSprite &parent,int w, int h, int posX, int posY) :
	spriteParent(&parent), transparency(.15)
{
	this->name = newName;
	this->offsetW = w;
	this->offsetH = h;
	this->posXOffset = posX;
	this->posYOffset = posY;
	this->type = "box";
}

bool BoxCollider::collide(std::vector<AbstractCollider*> otherColliders)
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
			glm::vec2 center(otherColliders.at(i)->getSpritePos() + glm::vec2(otherColliders.at(i)->getPosX(), otherColliders.at(i)->getPosY()) + otherColliders.at(i)->getRadius());

			//std::cout << "sizey: " << otherColliders.at(i)->getSpriteSize().y;
			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(this->getSpriteSize().x / 2, this->getSpriteSize().y / 2);
			glm::vec2 aabb_center(
				this->getSpritePos().x + this->getPosX() + aabb_half_extents.x,
				this->getSpritePos().y + this->getPosY() + aabb_half_extents.y
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

		else if (otherColliders.at(i)->getType() == "staticBox")
		{
			// Collision x-axis?
			bool collisionX = ((this->getSpritePos().x + this->getPosX()) + (this->getWidth())) >= otherColliders.at(i)->getPosX() &&
				otherColliders.at(i)->getSpritePos().x + otherColliders.at(i)->getPosX() + otherColliders.at(i)->getWidth() >= this->getSpritePos().x + this->getPosX();
			// Collision y-axis?
			bool collisionY = ((this->getSpritePos().y + this->getPosY()) + (this->getHeight())) >= otherColliders.at(i)->getPosY() &&
				otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY() + otherColliders.at(i)->getHeight() >= this->getSpritePos().y + this->getPosY();

			// Collision only if on both axes
			if (collisionX && collisionY)
			{
				return collisionX && collisionY;
			}
		}

		else if (otherColliders.at(i)->getType() == "staticCircle")
		{
			// Get center point circle first 
			glm::vec2 center(glm::vec2(otherColliders.at(i)->getPosX(), otherColliders.at(i)->getPosY()) + otherColliders.at(i)->getRadius());

			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(this->getSpriteSize().x / 2, this->getSpriteSize().y / 2);
			glm::vec2 aabb_center(
				this->getSpritePos().x + this->getPosX() + aabb_half_extents.x,
				this->getSpritePos().y + this->getPosY() + aabb_half_extents.y
			);
			// Get difference vector between both centers
			glm::vec2 difference = center - aabb_center;
			glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
			// Add clamped value to AABB_center and we get the value of box closest to circle
			glm::vec2 closest = aabb_center + clamped;

			// Retrieve vector between center circle and closest point AABB and check if length <= radius
			difference = closest - center;
			//std::cout << "\n" << difference.y;
			//std::cout << "\n" << glm::length(difference);
			std::cout << "\n R" << otherColliders.at(i)->getRadius();
			if (glm::length(difference) < otherColliders.at(i)->getRadius())
				return true;
		}
	}

	return false;

}

bool BoxCollider::getStaticState()
{
	return this->staticState;
}

glm::vec2 BoxCollider::getSpriteCenterPos()
{
	return spriteParent->getCenter();
}

glm::vec2 BoxCollider::getSpritePos()
{
	return spriteParent->getPosition();
}

glm::vec2 BoxCollider::getSpriteSize()
{
	return spriteParent->getSize();
}

glm::vec2 BoxCollider::getRenderPos()
{
	return spriteParent->getRenderPosition();
}

void BoxCollider::Draw(SpriteRenderer & renderer)
{
	renderer.DrawSprite(ResourceManager::GetTexture("debugGreen"), glm::vec2(this->getPosX() + spriteParent->getPosition().x + spriteParent->getRenderPosition().x, this->getPosY() + spriteParent->getPosition().y + spriteParent->getRenderPosition().y), glm::vec2(this->getWidth(), this->getHeight()), 0, glm::vec3(0, 255, 0), this->transparency);
}

BoxCollider::~BoxCollider()
{
}
