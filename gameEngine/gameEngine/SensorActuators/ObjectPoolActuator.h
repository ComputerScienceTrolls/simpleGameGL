#pragma once
#include "AbstractActuator.h"
#include "../ObjectPool.h"
#include "../SceneObject.h"
#include "../Sprite.h"

class ObjectPoolActuator: public ObjectPool<SceneObject>, public AbstractActuator
{
public:
	ObjectPoolActuator(std::string name, SceneObject *object, int numberOfObjectsInPool, SceneObject *SO, std::string con="spawn");
	ObjectPoolActuator(std::string name, Sprite *object, int numberOfObjectsInPool, SceneObject *SO, std::string con = "spriteSpawn");
	ObjectPoolActuator(std::string name, Sprite *object, int numberOfObjectsInPool, SceneObject *SO, float force, SceneObject *forceToward, std::string con = "spriteSpawnForce");
	virtual void run();
	~ObjectPoolActuator();

private:
	SceneObject *SO;
	SceneObject *forceToward;
	std::string condition;
	float force;
};

