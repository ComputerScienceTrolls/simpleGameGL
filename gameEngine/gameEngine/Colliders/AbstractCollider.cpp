#include "AbstractCollider.h"

AbstractCollider::AbstractCollider()
{
}

std::string AbstractCollider::getType()
{
	return this->type;
}

int AbstractCollider::getWidth()
{
	return this->offsetW;
}

int AbstractCollider::getHeight()
{
	return this->offsetH;
}

int AbstractCollider::getPosX()
{
	return this->posXOffset;
}

int AbstractCollider::getPosY()
{
	return this->posYOffset;
}

std::string AbstractCollider::getName()
{
	return this->name;
}

AbstractCollider::~AbstractCollider()
{
}
