#include "AbstractActuator.h"
#include "../AbstractScene.h"
#include "../SceneDirector.h"

#pragma once
class SceneActuator : public AbstractActuator
{
public:
	SceneActuator(std::string name, AbstractScene* newScene);
	SceneActuator(std::string name, AbstractScene* newScene, std::string condition);
	SceneActuator(std::string name, std::string condition);
	virtual void run();
	~SceneActuator();

private:
	AbstractScene *scene;
	std::string condition;
};

