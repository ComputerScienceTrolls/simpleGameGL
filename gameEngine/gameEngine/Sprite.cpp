#include "Sprite.h"
#include "GameObject.h"



Sprite::Sprite()
	: Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Texture(), IsSolid(false), Destroyed(false)
{

}


Sprite::Sprite(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Texture(sprite), IsSolid(false), Destroyed(false)
{

}

void Sprite::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->Texture, this->Position, this->Size, this->Rotation, this->Color);
}

Sprite::~Sprite()
{
}
