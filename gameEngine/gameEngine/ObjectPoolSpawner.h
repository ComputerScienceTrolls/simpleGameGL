#pragma once
#include "ObjectPool.h"
#include "./SensorActuators/AbstractActuator.h"
#include "SceneObject.h"
#include "Sprite.h"

class ObjectPoolSpawner : public ObjectPool<SceneObject>, public AbstractActuator
{
public:
	ObjectPoolSpawner(std::string name, SceneObject *object, int numberOfObjectsInPool, SceneObject *SO);
	ObjectPoolSpawner(std::string name, Sprite *object, int numberOfObjectsInPool, SceneObject *SO);
	virtual void run();
	~ObjectPoolSpawner();

private:
	SceneObject *SO;
};

