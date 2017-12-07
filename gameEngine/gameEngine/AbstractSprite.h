#ifndef ABSTRACT_SPRITE_H
#define ABSTRACT_SPRITE_H

#include <vector>

#include "Colliders/AbstractCollider.h"
#include "MovingSceneObject.h"

class AbstractSprite : public MovingSceneObject
{
public:
	AbstractSprite();
	bool collideDebug;
	Texture2D	Texture;
	virtual void Draw(SpriteRenderer &renderer, glm::vec2) {};
	virtual bool checkBounds(double screenWidth, double screenHeight) = 0;
	virtual void hide() {};
	virtual void setCollideDebug(bool state) {};
	virtual void Update() {};
	virtual bool collide(AbstractSprite*) { return false; };

	//get methods
	virtual glm::vec3 getColor() { return glm::vec3(); };
	virtual Texture2D getTexture() { return Texture2D(); };
	virtual std::vector<AbstractCollider*> getColliders() = 0;
	virtual bool getVisible() = 0;
	virtual float getImgAngle();

	//set methods
	virtual void setTexture(Texture2D test) {};
	virtual void setColor(glm::vec3) {};
	virtual void setVisible(bool) = 0;
	virtual void setColliders(std::vector<AbstractCollider*>) = 0;
	virtual void setImgAngle(float newAngle);

	virtual void reset() {};
	virtual void reInit() {};

	~AbstractSprite();

protected:
	glm::vec3   Color;
	float imgAngle;
};

#endif