#pragma once

#include "sprite_renderer.h"

class AbstractSprite
{
public:
	AbstractSprite();
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	GLfloat     Rotation;
	GLboolean   IsSolid;
	GLboolean   Destroyed;
	bool collideDebug;
	// Render state
	Texture2D	Texture;
	virtual void Draw(SpriteRenderer &renderer) {};
	virtual void checkBounds(double screenWidth, double screenHeight) {};
	virtual void hide() {};
	virtual void setCollideDebug(bool state) {};
	virtual void setDX(float newDx) {};
	virtual void setDY(float newDy) {};
	virtual void addForce(float angle, float mag) {};
	virtual void calcSpeedAngle() {};
	virtual void calcVector() {};
	virtual void setSpeed(float newSpeed) {};
	virtual void setImgAngle(float newAngle) {};
	virtual void setMoveAngle(float newAngle) {};
	~AbstractSprite();
};

