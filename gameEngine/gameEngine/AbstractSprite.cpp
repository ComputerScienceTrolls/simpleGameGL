#include "AbstractSprite.h"



AbstractSprite::AbstractSprite()
{
}


AbstractSprite::~AbstractSprite()
{
}

float AbstractSprite::getImgAngle()
{
	return this->imgAngle;
}

void AbstractSprite::setImgAngle(float newAngle)
{
	this->imgAngle = newAngle;
}
