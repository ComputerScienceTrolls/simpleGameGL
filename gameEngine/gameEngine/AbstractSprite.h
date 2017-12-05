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
	virtual bool collide(AbstractSprite*) { return false; };

	//get methods
	virtual glm::vec2 getRenderPosition();
	virtual int getRenderPosX();
	virtual int getRenderPosY();
	virtual int getRenderDX();
	virtual int getRenderDY();
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
	virtual void setRenderPosition(glm::vec2);
	virtual void setRenderPosX(int);
	virtual void setRenderPosY(int);
	virtual void setRenderDX(int);
	virtual void setRenderDY(int);
	virtual void setImgAngle(float newAngle);

	virtual void reset() {};
	virtual void reInit() {};

	~AbstractSprite();

protected:
	glm::vec2 RenderPosition;
	glm::vec2 RenderVelocity;
	glm::vec3   Color;
	float imgAngle;
};

