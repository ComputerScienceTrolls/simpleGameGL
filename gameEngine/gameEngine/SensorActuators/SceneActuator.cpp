#include "SceneActuator.h"
#include <iostream>

//constructor that isn't given a condition
SceneActuator::SceneActuator(std::string n, AbstractScene * newScene) :
	scene(newScene), condition("na")
{
	this->name = n;
}

//constructor that is given a condition
SceneActuator::SceneActuator(std::string n, AbstractScene * newScene, std::string con) :
	scene(newScene), condition(con)
{
	this->name = n;
}

//constructor that is only given a condition, can only use next, previous, or pause/toggle pause command
SceneActuator::SceneActuator(std::string n, std::string con) :
	condition(con)
{
	this->name = n;
	if (con == "next" || con == "previous" || con == "pause" || con == "togglePause")
	{
		std::cout << con << " not a command that can be used without a given scene\ncommands that work without a given scene are next, previous, pause, and togglePause";
	}
}

//run command based on given condition, if none given assume set given scene
void SceneActuator::run()
{
	if (condition == "na")
	{
		SceneDirector::getInstance()->setScene(scene);
	}
	else if (condition == "next")
	{
		SceneDirector::getInstance()->nextScene();
		SceneDirector::getInstance()->setSceneBackground("textures/BG.png");
	}
	else if (condition == "previous")
	{
		SceneDirector::getInstance()->previousScene();
	}
	else if (condition == "setPause")
	{
		SceneDirector::getInstance()->setScenePause(scene);
	}
	else if (condition == "pause")
	{
		SceneDirector::getInstance()->pauseScene(scene);
	}
	else if (condition == "togglePause")
	{
		if (scene->getActive())
		{
			SceneDirector::getInstance()->pauseScene(scene);
		}
		else
		{
			SceneDirector::getInstance()->unpauseScene(scene);
		}
	}
	else
	{
		std::cout << "\n SceneActurator is set to run but not doing anything, something went wrong";
	}
	
}

SceneActuator::~SceneActuator()
{
}
