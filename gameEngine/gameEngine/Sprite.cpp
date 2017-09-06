#include "Sprite.h"

Sprite::Sprite()
	: Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Texture(), IsSolid(false), Destroyed(false)
{
	//give default box collider
	boxCollider *temp = new boxCollider(1, 1);

}


Sprite::Sprite(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Texture(sprite), IsSolid(false), Destroyed(false)
{
	boxCollider *temp = new boxCollider(size.x, size.y);
	collider_ = temp;
}

void Sprite::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->Texture, this->Position, this->Size, this->Rotation, this->Color);
}

bool Sprite::collide(Sprite* otherSprite)
{
	for (int i = 0; i < this->colliders_.size(); i++)
	{
		if (colliders_.at(i)->getType() == "box")
		{
			for (int j = 0; j < otherSprite->colliders_.size(); j++)
			{
				if (colliders_.at(j)->getType() == "box")
				{
					// Collision x-axis?
					bool collisionX = ((this->Position.x + this->colliders_.at(i)->getPosX()) + (this->colliders_.at(i)->getWidth())) >= otherSprite->Position.x &&
						otherSprite->Position.x + otherSprite->colliders_.at(j)->getPosX() + otherSprite->colliders_.at(j)->getWidth() >= this->Position.x;
					// Collision y-axis?
					bool collisionY = (this->Position.y + this->colliders_.at(i)->getPosY()) + (this->Size.y + this->colliders_.at(i)->getHeight()) >= otherSprite->Position.y &&
						otherSprite->Position.y + otherSprite->colliders_.at(j)->getPosY() + otherSprite->Size.y + otherSprite->colliders_.at(j)->getHeight() >= this->Position.y;
					// Collision only if on both axes
					if (collisionX && collisionY)
						return collisionX && collisionY;
				}

				else if (colliders_.at(j)->getType() == "circle")
				{
					// Get center point circle first 
					glm::vec2 center(this->Position + glm::vec2(this->colliders_.at(i)->getPosX(), this->colliders_.at(i)->getPosY()) + this->colliders_.at(i)->getRadius());
					// Calculate AABB info (center, half-extents)
					glm::vec2 aabb_half_extents(otherSprite->Size.x / 2, otherSprite->Size.y / 2);
					glm::vec2 aabb_center(
						otherSprite->Position.x + otherSprite->colliders_.at(j)->getPosX() + aabb_half_extents.x,
						otherSprite->Position.y + otherSprite->colliders_.at(j)->getPosY() + aabb_half_extents.y
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

			}
			
		}
		else if (colliders_.at(i)->getType() == "circle")
		{
			// Get center point circle first 
			glm::vec2 center(this->Position + glm::vec2(this->colliders_.at(i)->getPosX(), this->colliders_.at(i)->getPosY()) + this->colliders_.at(i)->getRadius());
			// Calculate AABB info (center, half-extents)
			glm::vec2 aabb_half_extents(otherSprite->Size.x / 2, otherSprite->Size.y / 2);
			glm::vec2 aabb_center(
				otherSprite->Position.x + aabb_half_extents.x,
				otherSprite->Position.y + aabb_half_extents.y
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
			std::cout << "circle collision detected";
		}
	}
	//if we get here, no collision detected, return false
	return false;
}

Sprite::~Sprite()
{
}
