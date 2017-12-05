#pragma once
#include "SceneObject.h"

class MovingSceneObject : public SceneObject
{
public:
	MovingSceneObject();

	//set methods
	virtual void setRenderPosition(glm::vec2);
	virtual void setRenderPosX(int);
	virtual void setRenderPosY(int);
	virtual void setRenderDX(int);
	virtual void setRenderDY(int);
	virtual void setVelocity(glm::vec2);
	virtual void setDX(float);
	virtual void setDY(float);
	virtual void setSpeed(float);
	virtual void setMoveAngle(float);

	//get methods
	virtual glm::vec2 getRenderPosition();
	virtual int getRenderPosX();
	virtual int getRenderPosY();
	virtual int getRenderDX();
	virtual int getRenderDY();
	virtual glm::vec2 getVelocity();
	virtual int getDX();
	virtual int getDY();
	virtual float getSpeed();
	virtual float getMoveAngle();
	
	virtual void Update() {};

	//moving methods
	virtual void addForce(float angle, float mag);
	virtual void calcSpeedAngle();
	virtual void calcVector();

	~MovingSceneObject();

protected:
	glm::vec2 RenderPosition;
	glm::vec2 RenderVelocity;
	glm::vec2 Velocity;
	float speed;
	float moveAngle;
};
