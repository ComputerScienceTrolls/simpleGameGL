#include "BoxCollider.h"

//constructor with no position offset
BoxCollider::BoxCollider(std::string newName, AbstractSprite &parent, int w, int h) :
	spriteParent(&parent), transparency(.15)
{
	this->name = newName;
	this->Size.x = w;
	this->Size.y = h;
	this->Position = glm::vec2(0,0);
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
	this->Size.x = w;
	this->Size.y = h;
	this->Position = glm::vec2(posX, posY);
	this->type = "box";
}

BoxCollider::BoxCollider(std::string n, AbstractScene &parent, int w, int h) :
	transparency(.15)
{
	this->name = n;
	this->active = true;
	this->Size.x = w;
	this->Size.y = h;
	this->type = "box";

	parent.addMovingObject(this);
	parent.addDrawObject(this);
	parent.addSceneObject(this);
}

BoxCollider::BoxCollider(std::string n, AbstractScene &parent, int w, int h, int posX, int posY) :
	transparency(.15)
{
	this->name = n;
	this->active = true;
	this->Size.x = w;
	this->Size.y = h;
	this->Position.x = posX;
	this->Position.y = posY;
	this->type = "box";

	parent.addMovingObject(this);
	parent.addDrawObject(this);
	parent.addSceneObject(this);
}

bool BoxCollider::collide(std::vector<AbstractCollider*> otherColliders)
{
	for (int i = 0; i < otherColliders.size(); i++)
	{
		if (otherColliders.at(i)->getType() == "box")
		{
			//get each boxes borders than compare them
			float thisLeft = this->getSpritePos().x + this->getPosX();
			float thisRight = thisLeft + this->getWidth();
			float thisTop = this->getSpritePos().y + this->getPosY();
			float thisBottom = thisTop + this->getHeight();

			float otherLeft = otherColliders.at(i)->getSpritePos().x + otherColliders.at(i)->getPosX();
			float otherRight = otherLeft + otherColliders.at(i)->getWidth();
			float otherTop = otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY();
			float otherBottom = otherTop + otherColliders.at(i)->getHeight();

			if (thisBottom >= otherTop)
			{
				if (thisTop <= otherBottom)
				{
					if (thisRight >= otherLeft)
					{
						if (thisLeft <= otherRight)
						{
							return true;
						}
					}
				}
			}//end of sudo and statement
		}

		else if (otherColliders.at(i)->getType() == "circle")
		{
			// Get center point circle first 
			glm::vec2 center(glm::vec2(otherColliders.at(i)->getPosX(), otherColliders.at(i)->getPosY()) + otherColliders.at(i)->getRadius());

			//std::cout << "sizey: " << otherColliders.at(i)->getSpriteSize().y;
			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(this->Size.x / 2, this->Size.y / 2);
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

bool BoxCollider::collide(AbstractCollider * otherCollider)
{
	if (otherCollider->getType() == "box")
	{
		//get each boxes borders than compare them
		float thisLeft = this->getSpritePos().x + this->getPosX();
		float thisRight = thisLeft + this->getWidth();
		float thisTop = this->getSpritePos().y + this->getPosY();
		float thisBottom = thisTop + this->getHeight();

		float otherLeft = otherCollider->getSpritePos().x + otherCollider->getPosX();
		float otherRight = otherLeft + otherCollider->getWidth();
		float otherTop = otherCollider->getSpritePos().y + otherCollider->getPosY();
		float otherBottom = otherTop + otherCollider->getHeight();

		if (thisBottom >= otherTop)
		{
			if (thisTop <= otherBottom)
			{
				if (thisRight >= otherLeft)
				{
					if (thisLeft <= otherRight)
					{
						return true;
					}
				}
			}
		}//end of sudo and statement
	}

	else if (otherCollider->getType() == "circle")
	{
		// Get center point circle first 
		glm::vec2 center(glm::vec2(otherCollider->getPosX(), otherCollider->getPosY()) + otherCollider->getRadius());

		//std::cout << "sizey: " << otherColliders.at(i)->getSpriteSize().y;
		// Calculate AABB info (center, half-extents)
		glm::vec2 aabb_half_extents(this->getSize().x / 2, this->getSize().y / 2);
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

		if (glm::length(difference) < otherCollider->getRadius())
			return true;
	}

	return false;
}

bool BoxCollider::collide(AbstractSprite * otherSprite)
{
	std::vector<AbstractCollider*> otherColliders = otherSprite->getColliders();

	for (int i = 0; i < otherColliders.size(); i++)
	{
		if (otherColliders.at(i)->getType() == "box")
		{
			//get each boxes borders than compare them
			float thisLeft = this->getSpritePos().x + this->getPosX();
			float thisRight = thisLeft + this->getWidth();
			float thisTop = this->getSpritePos().y + this->getPosY();
			float thisBottom = thisTop + this->getHeight();

			float otherLeft = otherColliders.at(i)->getSpritePos().x + otherColliders.at(i)->getPosX();
			float otherRight = otherLeft + otherColliders.at(i)->getWidth();
			float otherTop = otherColliders.at(i)->getSpritePos().y + otherColliders.at(i)->getPosY();
			float otherBottom = otherTop + otherColliders.at(i)->getHeight();

			if (thisBottom >= otherTop)
			{
				if (thisTop <= otherBottom)
				{
					if (thisRight >= otherLeft)
					{
						if (thisLeft <= otherRight)
						{
							return true;
						}
					}
				}
			}//end of sudo and statement
		}

		else if (otherColliders.at(i)->getType() == "circle")
		{
			// Get center point circle first 
			glm::vec2 center(glm::vec2(otherColliders.at(i)->getPosX(), otherColliders.at(i)->getPosY()) + otherColliders.at(i)->getRadius());

			//std::cout << "sizey: " << otherColliders.at(i)->getSpriteSize().y;
			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(this->getSize().x / 2, this->getSize().y / 2);
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

void BoxCollider::Draw(SpriteRenderer & renderer, glm::vec2 camPos)
{
	//if parentSprite exists use it for render calc
	renderer.DrawSprite(ResourceManager::GetTexture("debugGreen"), glm::vec2(this->getPosX() + camPos.x, this->getPosY() + camPos.y), glm::vec2(this->getWidth(), this->getHeight()), 0, glm::vec3(0, 255, 0), this->transparency);
}

BoxCollider::~BoxCollider()
{
}
