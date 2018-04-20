#include "AbstractActuator.h"
#include "../MovingSceneObject.h"
#include "../AbstractSprite.h"
#include "../ObjectPoolSpawner.h"

class MotionActuator : public AbstractActuator
{
public:
	MotionActuator(std::string name, MovingSceneObject*, float newDX, float newDY);
	MotionActuator(std::string name, MovingSceneObject*, float newAngle, float newForce, std::string condition = "force");
	MotionActuator(std::string name, MovingSceneObject*, float newDX, std::string condition);
	MotionActuator(std::string name, MovingSceneObject*, float distance, float speed, SceneObject* o, std::string condition = "followObject");
	MotionActuator(std::string name, MovingSceneObject*, float speed, SceneObject*);
	MotionActuator(std::string name, ObjectPoolSpawner*, float speed, SceneObject*);
	MotionActuator(std::string name, MovingSceneObject*, SceneObject*);
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
	ObjectPoolSpawner *objectPool;
	std::string condition;
};

