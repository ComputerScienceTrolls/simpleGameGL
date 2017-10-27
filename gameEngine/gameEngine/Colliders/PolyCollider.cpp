#include "PolyCollider.h"

PolyCollider::PolyCollider(std::vector<glm::vec2>)
{
}

bool PolyCollider::collide(std::vector<collider*> otherColliders)
{
	return false;
}

bool PolyCollider::getStaticState()
{
	return false;
}

glm::vec2 PolyCollider::getSpriteCenterPos()
{
	return this->spriteParent->getCenter();
}

glm::vec2 PolyCollider::getSpritePos()
{
	return this->spriteParent->getPosition();
}

glm::vec2 PolyCollider::getSpriteSize()
{
	return this->spriteParent->getSize();
}

std::string PolyCollider::getName()
{
	return this->name;
}

std::string PolyCollider::getType()
{
	return this->type;
}
