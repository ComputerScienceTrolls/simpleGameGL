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
	// Collision x-axis?
	bool collisionX = ((this->Position.x + this->collider_->getPosX())+ (this->collider_->getWidth())) >= otherSprite->Position.x &&
		otherSprite->Position.x + otherSprite->collider_->getPosX() + otherSprite->collider_->getWidth() >= this->Position.x;
	// Collision y-axis?
	bool collisionY = this->Position.y + this->Size.y >= otherSprite->Position.y &&
		otherSprite->Position.y + otherSprite->Size.y >= this->Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}

Sprite::~Sprite()
{
}
