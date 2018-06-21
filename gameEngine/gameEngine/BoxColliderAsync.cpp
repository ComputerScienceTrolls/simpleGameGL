#include "BoxColliderAsync.h"
#include <thread>

//constructor with no position offset
BoxColliderAsync::BoxColliderAsync(std::string newName, AbstractSprite &parent, AbstractCollider *otherC, int w, int h) :
	spriteParent(&parent)
{
	this->name = newName;
	this->Size.x = float(w);
	this->Size.y = float(h);
	this->Position = glm::vec2(0, 0);
	this->type = "box";
	this->transparency = float(.15);
	this->setBoundAction("STOP");
	
	this->oc = otherC;

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}

	//std::thread test(&BoxColliderAsync::checkOverlap);
}

void BoxColliderAsync::checkOverlap()
{
	if (oc->getType() == "box")
	{
		//get each boxes borders than compare them
		float thisLeft = this->getSpritePos().x + this->getPosX();
		float thisRight = thisLeft + this->getWidth();
		float thisTop = this->getSpritePos().y + this->getPosY();
		float thisBottom = thisTop + this->getHeight();

		float otherLeft = oc->getSpritePos().x + oc->getPosX();
		float otherRight = otherLeft + oc->getWidth();
		float otherTop = oc->getSpritePos().y + oc->getPosY();
		float otherBottom = otherTop + oc->getHeight();

		if (thisBottom >= otherTop)
		{
			if (thisTop <= otherBottom)
			{
				if (thisRight >= otherLeft)
				{
					if (thisLeft <= otherRight)
					{
						overlap = true;
					}
				}
			}
		}//end of sudo and statement
	}
	overlap = false;
}

void BoxColliderAsync::Draw(Renderer & renderer)
{
}
