#pragma once
#include "AbstractSensor.h"
#include "../AbstractSprite.h"
#include "../AbstractScene.h"
#include "../Scene.h"
#include "AbstractActuator.h"
#include "ObjectPoolActuator.h"
#include "CollisionSensorStates/CollisionSensorState.h"
#include "CollisionSensorStates/CollisionSensorColliderColliderNoOneShot.h"
#include "CollisionSensorStates/CollisionSensorColliderColliderOneShot.h"
#include "CollisionSensorStates/CollisionSensorSpriteColliderNoOneShot.h"
#include "CollisionSensorStates/CollisionSensorSpriteColliderOneShot.h"
#include "CollisionSensorStates/CollisionSensorSpriteSceneNoOneShot.h"
#include "CollisionSensorStates/CollisionSensorSpriteSceneOneShot.h"
#include "CollisionSensorStates/CollisionSensorSpriteSpriteGroupNoOneShot.h"
#include "CollisionSensorStates/CollisionSensorSpriteSpriteGroupOneShot.h"
#include "CollisionSensorStates/CollisionSensorSpriteSpriteNoOneShot.h"
#include "CollisionSensorStates/CollisionSensorSpriteSpriteOneShot.h"
#include "CollisionSensorStates/CollisionSensorSpriteObjectPoolOneShot.h"

class CollisionSensor : public AbstractSensor
{
public:
	CollisionSensor(std::string name, AbstractSprite*, AbstractSprite*, bool oneShot = false);
	CollisionSensor(std::string name, AbstractSprite*, std::vector<AbstractSprite*>, bool oneShot = false);
	CollisionSensor(std::string name, AbstractSprite*, AbstractCollider*, bool oneShot = false);
	CollisionSensor(std::string name, AbstractCollider*, AbstractCollider*, bool oneShot = false);
	CollisionSensor(std::string name, AbstractSprite*, Scene*, bool oneShot = false);
	CollisionSensor(std::string name, AbstractSprite*, ObjectPoolActuator*, bool oneShot = false);
	void sense();
	~CollisionSensor();

private:
	bool oneShot;
	CollisionSensorState *myState;
};
