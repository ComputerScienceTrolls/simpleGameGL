#pragma once
#include <vector>

#include "collider.h"
#include "sprite_renderer.h"

class AbstractSprite
{
public:
	AbstractSprite();
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
	virtual void update() {};
	virtual void addForce(float angle, float mag) {};
	virtual void calcSpeedAngle() {};
	virtual void calcVector() {};
	virtual void setSpeed(float newSpeed) {};
	virtual void setImgAngle(float newAngle) {};
	virtual void setMoveAngle(float newAngle) {};
	virtual bool collide(AbstractSprite*) { return false; };
	virtual glm::vec2 getPosition() { return glm::vec2(); };
	virtual glm::vec2 getSize() { return glm::vec2(); };
	virtual glm::vec2 getVelocity() { return glm::vec2(); };
	virtual glm::vec3 getColor() { return glm::vec3(); };
	virtual Texture2D getTexture() { return Texture2D(); };
	virtual GLfloat getRotation() { return 0; };
	virtual std::vector<collider*> getColliders() = 0;
	virtual std::string getName() = 0;
	virtual GLfloat getDX() = 0;
	virtual bool getState(std::string) = 0;
	virtual void setPosition(glm::vec2) {};
	virtual void setTexture(Texture2D test) {};
	virtual void setSize(glm::vec2) {};
	virtual void setVelocity(glm::vec2) {};
	virtual void setColor(glm::vec3) {};
	virtual	void setRotation(GLfloat) {};
	virtual void setState(std::string, bool) {};
	virtual void setColliders(std::vector<collider*>) = 0;
	virtual void setName(std::string) {};

	~AbstractSprite();

private:
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	GLfloat     Rotation;
};

