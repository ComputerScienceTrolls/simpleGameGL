#ifndef MOVINGSCENEOBJECT_H
#define MOVINGSCENEOBJECT_H

#include "SceneObject.h"

class MovingSceneObject : public virtual SceneObject
{
public:
	MovingSceneObject();

	//set methods
	virtual void setVelocity(glm::vec2);
	virtual void setDX(float);
	virtual void setDY(float);
	virtual void setSpeed(float);
	virtual void setMoveAngle(float);
	virtual void setBoundAction(std::string newAction);

	//get methods
	virtual glm::vec2 getVelocity();
	virtual glm::vec2 getLastPosition();
	virtual glm::vec2 getLastVelocity();
	virtual int getDX();
	virtual int getDY();
	virtual float getSpeed();
	virtual float getMoveAngle();
	virtual std::string getBoundAction();
	
	virtual void Update();
	bool checkBounds(double screenWidth, double screenHeight);

	//moving methods
	virtual void addForce(float angle, float mag);
	virtual void calcSpeedAngle();
	virtual void calcVector();
	virtual float angleTo(SceneObject*);
	virtual void followObject(SceneObject* o, float distance, float speed);

	virtual void setVisible(bool) {};
	virtual void setImageAngle(float angle);
	virtual glm::vec2 normalize(glm::vec2);

	~MovingSceneObject();

protected:
	glm::vec2 Velocity, lastPosition, lastVelocity, lastSize;
	float speed;
	float moveAngle;
	std::string boundAction;

private:
	glm::vec2 lastDir;
};

#endif