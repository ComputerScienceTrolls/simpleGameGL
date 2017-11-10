#include "SceneActuator.h"
#include <iostream>

SceneActuator::SceneActuator(AbstractScene * newScene) :
	scene(newScene), condition("na")
{
}

SceneActuator::SceneActuator(AbstractScene * newScene, std::string con) :
	scene(newScene), condition(con)
{
}

SceneActuator::SceneActuator(std::string con) :
	condition(con)
{
}

void SceneActuator::run()
{
	if (condition == "na")
	{
		SceneDirector::getInstance()->setScene(scene);
	}
	else if (condition == "next")
	{
		SceneDirector::getInstance()->nextScene();
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
			std::cout << "\ntest\n";
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
