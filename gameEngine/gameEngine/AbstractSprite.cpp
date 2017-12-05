#include "AbstractSprite.h"



AbstractSprite::AbstractSprite()
{
}


AbstractSprite::~AbstractSprite()
{
}

glm::vec2 AbstractSprite::getRenderPosition()
{
	return this->RenderPosition;
}

int AbstractSprite::getRenderPosX()
{
	return this->RenderPosition.x;
}

int AbstractSprite::getRenderPosY()
{
	return this->RenderPosition.y;
}

int AbstractSprite::getRenderDX()
{
	return this->RenderVelocity.x;
}

int AbstractSprite::getRenderDY()
{
	return this->RenderVelocity.x;
}

float AbstractSprite::getImgAngle()
{
	return this->imgAngle;
}

void AbstractSprite::setRenderPosition(glm::vec2 newRender)
{
	this->RenderPosition = newRender;
}

void AbstractSprite::setRenderPosX(int newX)
{
	this->RenderPosition.x = newX;
}

void AbstractSprite::setRenderPosY(int newY)
{
	this->RenderPosition.y = newY;
}

void AbstractSprite::setRenderDX(int newX)
{
	this->RenderVelocity.x = newX;
}

void AbstractSprite::setRenderDY(int newY)
{
	this->RenderVelocity.y = newY;
}

void AbstractSprite::setImgAngle(float newAngle)
{
	this->imgAngle = newAngle;
}
