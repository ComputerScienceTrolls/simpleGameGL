#include "AbstractActuator.h"
#include "../MovingSceneObject.h"
#include "../AbstractSprite.h"
#include "ObjectPoolActuator.h"

//enum for conditions so we can use a switch statement since if/else branch would be less efficient with this number of conditions
enum string_code
{
	cBoth, cX, cY, cFlip, cFlipX, cFlipY, cMultiply, cChangeByX, cChangeByY, cRotate, cRotateBy,
	cAngleTo, cForce, cForceForward, cFollowObject, cForceTowards, cForceTowardPool, cSetInFront
};

class MotionActuator : public AbstractActuator
{
public:
	MotionActuator(std::string name, MovingSceneObject*, float newDX, float newDY);
	MotionActuator(std::string name, MovingSceneObject*, float newAngle, float newForce, std::string condition = "force");
	MotionActuator(std::string name, MovingSceneObject*, float newDX, std::string condition);
	MotionActuator(std::string name, MovingSceneObject*, float distance, float speed, SceneObject* o, std::string condition = "followObject");
	MotionActuator(std::string name, MovingSceneObject*, float speed, SceneObject*);
	MotionActuator(std::string name, ObjectPoolActuator*, float speed, SceneObject*);
	MotionActuator(std::string name, MovingSceneObject*, SceneObject*, std::string condition);
	MotionActuator(std::string name, MovingSceneObject*, std::string condition);
	void run();
	~MotionActuator();

private:
	MovingSceneObject *object;
	float DX;
	float DY;
	float DT;
	float force;
	float angle;
	float distance;
	SceneObject *anotherObject;
	ObjectPoolActuator *objectPool;
	std::string condition;
	string_code conditionEnum;
};

