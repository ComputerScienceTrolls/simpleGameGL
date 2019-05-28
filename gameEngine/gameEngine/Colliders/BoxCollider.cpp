#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(BoxCollider* copy)
{
	this->active = copy->active;
	this->name = copy->name;
	this->Position = copy->Position;
	this->type = copy->type;
	this->transparency = copy->transparency;
	this->setBoundAction(copy->getBoundAction());
	this->Size = copy->Size;
	this->Center = copy->Center;
	this->visible = copy->visible;

	//if (copy->getScene())
	//{
		copy->getScene()->addMovingObject(this);
		copy->getScene()->addDrawObject(this);
		copy->getScene()->addSceneObject(this);
		
		this->setScene(copy->getScene());
	//}

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
}

//constructor with no position offset
BoxCollider::BoxCollider(std::string newName, AbstractSprite *parent, int w, int h)
{
	this->name = newName;
	this->Size.x = float(w);
	this->Size.y = float(h);
	this->Position = glm::vec2(0,0);
	this->type = "box";
	this->transparency = float(.15);
	//this->setBoundAction("STOP");

	//if (parent->getScene())
		this->setScene(parent->getScene());

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
}

//consturctor with a positon offset
BoxCollider::BoxCollider(std::string newName, AbstractSprite *parent,int w, int h, int posX, int posY)
{
	this->name = newName;
	this->Size.x = float(w);
	this->Size.y = float(h);
	this->Center.x = float(posX);
	this->Center.y = float(posY);
	this->Position.x = this->Center.x - this->Size.x / 2;
	this->Position.y = this->Center.y - this->Size.y / 2;
	this->type = "box";
	this->transparency = float(.15);
	this->setBoundAction("STOP");

	if (parent->getScene())
		this->setScene(parent->getScene());

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
}

//constructor with just a parent scene no parent sprite.
BoxCollider::BoxCollider(std::string n, AbstractScene *parent, int w, int h)
{
	this->name = n;
	this->active = true;
	this->Size.x = float(w);
	this->Size.y = float(h);
	this->type = "box";
	this->transparency = float(.15);
	//this->setBoundAction("STOP");

	this->setScene(parent);
	parent->addMovingObject(this);
	parent->addDrawObject(this);
	parent->addSceneObject(this);

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
}

BoxCollider::BoxCollider(std::string n, AbstractScene *parent, int w, int h, int posX, int posY)
{
	this->name = n;
	this->active = true;
	this->Size.x = float(w);
	this->Size.y = float(h);
	this->Center.x = float(posX);
	this->Center.y = float(posY);
	this->Position.x = this->Center.x - this->Size.x / 2;
	this->Position.y = this->Center.y - this->Size.y / 2;
	this->type = "box";
	this->transparency = GLfloat(.15);
//	this->setBoundAction("STOP");

	parent->addMovingObject(this);
	parent->addDrawObject(this);
	parent->addSceneObject(this);

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
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

void BoxCollider::Draw(AbstractRenderer *renderer)
{
	SpriteRenderer *sp = static_cast<SpriteRenderer*>(renderer);
	//if parentSprite exists use it for render calc
	Texture2D tempTexture = ResourceManager::GetTexture("debugGreen");
	sp->DrawSprite(tempTexture, this->Position, this->Size, this->Rotation, glm::vec3(0, 255, 0), this->transparency);
}

AbstractCollider* BoxCollider::clone()
{
	//BoxCollider* clone = new BoxCollider("clone", this->getScene(),0, 0);
	BoxCollider* clone = new BoxCollider();
	//clone->name = "clone";
	clone->setPosition(this->Position);
	clone->setCenter(this->Center);
	clone->setSize(this->Size);
	clone->setName(this->name + "_clone");
	clone->setTransparency(this->transparency);
	clone->setBoundAction(this->getBoundAction());
	//clone->Size = this->Size;
	//clone->active = this->active;
	//clone->name = this->name;
	//clone->Center = this->Center;
	//clone->Position = this->Position;
	clone->type = this->type;
	//clone->transparency = this->transparency;
	//clone->setBoundAction(this->getBoundAction());
	//clone->Size = this->Size;
	//clone->Center = this->Center;
	clone->setVisible(this->visible);

	return clone;

	//return new BoxCollider(this);
}

BoxCollider::~BoxCollider()
{
	std::cout << "box collidier destroyed " << this->name << "\n";
}
