#pragma once
#include <vector>

#include "Colliders/AbstractCollider.h"
#include "MovingSceneObject.h"

class AbstractSprite : public MovingSceneObject
{
public:
	AbstractSprite();
	bool collideDebug;
	Texture2D	Texture;
	virtual void Draw(SpriteRenderer &renderer) {};
	virtual bool checkBounds(double screenWidth, double screenHeight) = 0;
	virtual void hide() {};
	virtual void setCollideDebug(bool state) {};
	virtual void Update() {};
	virtual void setImgAngle(float newAngle) {};
	virtual bool collide(AbstractSprite*) { return false; };
	virtual glm::vec3 getColor() { return glm::vec3(); };
	virtual Texture2D getTexture() { return Texture2D(); };
	virtual std::vector<AbstractCollider*> getColliders() = 0;
	virtual bool getVisible() = 0;
	virtual void setTexture(Texture2D test) {};
	virtual void setColor(glm::vec3) {};
	virtual void setVisible(bool) = 0;
	virtual void setColliders(std::vector<AbstractCollider*>) = 0;

	virtual void reset() {};
	virtual void reInit() {};

	~AbstractSprite();

private:
	glm::vec3   Color;
};

