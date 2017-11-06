#include "AbstractActuator.h"
#include "../AbstractScene.h"
#include "../SceneDirector.h"

#pragma once
class SceneActuator : public AbstractActuator
{
public:
	SceneActuator(AbstractScene* newScene);
	SceneActuator(AbstractScene* newScene, std::string condition);
	SceneActuator(std::string condition);
	virtual void run();
	~SceneActuator();

private:
	AbstractScene *scene;
	std::string condition;
};

