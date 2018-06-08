#pragma once
#include "Scene.h"

#include "SensorActuators/MotionActuator.h"
#include "SensorActuators/PositionActuator.h"
#include "SensorActuators/CollisionSensor.h"
#include "SensorActuators/CheckBoundsSensor.h"
#include "SensorActuators/VisibilityActuator.h"
#include "SensorActuators/ActiveActuator.h"
#include "SensorActuators/KeyboardSensor.h"
#include "SensorActuators/SceneActuator.h"
#include "SensorActuators/SoundActuator.h"
#include "SensorActuators/AlwaysSensor.h"
#include "SensorActuators/TimesActuator.h"
#include "SensorActuators/ObjectPoolActuator.h"

#include "Sprite.h"

class Scene1 : public Scene
{
public:
	Scene1();
	Scene1(std::string name, GLuint width, GLuint height);
	virtual void loadContents();
	~Scene1();
};

