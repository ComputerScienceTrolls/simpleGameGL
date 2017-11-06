#include "SceneDirector.h"
#include <iostream>
std::auto_ptr<SceneDirector> SceneDirector::instance;

//default width and height
int WIDTH = 800;
int HEIGHT = 600;

SceneDirector::SceneDirector()
 {
	std::cout << "hello darkness my old friend";
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "HelloWorld", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
	
}

void SceneDirector::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "HelloWorld", nullptr, nullptr);
	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
}

SceneDirector* SceneDirector::getInstance()
{
	if (instance.get() == nullptr)
	{
		instance.reset(new SceneDirector());
	}

	return instance.get();
}

void SceneDirector::addScene(AbstractScene *s)
{
	scenes.push_back(s);
	//if scenes is empy, make new scene the currentScene
	if (scenes.size() < 2)
	{
		std::cout << "\ntest";
		currentScene = s;
		currentScene->setWindow(window);
	}
}

AbstractScene* SceneDirector::getScene(std::string)
{
	return nullptr;
}

AbstractScene* SceneDirector::getScene(int i)
{
	return scenes.at(i);
}

void SceneDirector::removeScene(std::string)
{
}

void SceneDirector::removeScene(int)
{
}

void SceneDirector::setScene(std::string)
{
}

void SceneDirector::nextScene()
{
	int currentIndex = -1;
	for (int i = 0; i < scenes.size(); i++)
	{
		if (currentScene == scenes.at(i))
		{
			currentIndex = i;
		}
	}

	//make sure currentIndex and currentIndex+1 is in range
	if (currentIndex != -1 && !currentIndex < 0 && !currentIndex > scenes.size() - 1 && !currentIndex + 1 > scenes.size() - 1)
	{
		currentScene = scenes.at(currentIndex + 1);
	}
	else
	{
		std::cout << "there is no Scene to jump to";
	}
	
}

void SceneDirector::start()
{

}

int SceneDirector::getNumberOfScenes()
{
	return scenes.size();
}

AbstractScene* SceneDirector::getCurrentScene()
{
	return this->currentScene;
}

SceneDirector::~SceneDirector()
{
	std::cout << "is this?";
}
