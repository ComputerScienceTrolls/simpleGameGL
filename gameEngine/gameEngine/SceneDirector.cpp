#include "SceneDirector.h"
#include <iostream>
std::auto_ptr<SceneDirector> SceneDirector::instance;

//default width and height
int WIDTH = 800;
int HEIGHT = 600;

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

SceneDirector::SceneDirector()
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

void SceneDirector::checkSensors()
{
	for (int i = 0; i < sensors.size(); i++)
	{
		sensors.at(i)->sense();
	}
}

void SceneDirector::pauseScene(AbstractScene * s)
{
	//find scene given
	bool found = false;
	for (int i = 0; i < scenes.size(); i++)
	{
		if (s == scenes.at(i))
		{
			found = true;
			scenes[i]->setActive(false);
		}
	}

	if (!found)
	{
		std::cout << "pauseSence: no scene found";
	}
}

void SceneDirector::unpauseScene(AbstractScene * s)
{
	//find scene given
	bool found = false;
	for (int i = 0; i < scenes.size(); i++)
	{
		if (s == scenes.at(i))
		{
			found = true;
			scenes[i]->setActive(true);
		}
	}

	if (!found)
	{
		std::cout << "pauseSence: no scene found";
	}
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

//sets the given scene, if it's not already in scene list, add it
void SceneDirector::setScene(AbstractScene *s)
{
	currentScene->Stop();
	currentScene = s;
	currentScene->setWindow(window);
	currentScene->Init();
	currentScene->initRenderer();
	currentScene->Start();

	bool found = false;
	for (int i = 0; i < scenes.size(); i++)
	{
		if (s = scenes.at(i))
		{
			found = true;
		}
	}
	if (!found)
	{
		scenes.push_back(s);
	}
}

//sets to scene, but only pauses old scene, if scene doens't exist in scenes, add it.
void SceneDirector::setScenePause(AbstractScene * s)
{
	//if scene is already the currentScene, do nothing
	if (currentScene != s)
	{
		std::cout << "\n test \n";
		currentScene->setActive(false);
		currentScene = s;
		currentScene->setWindow(window);
		//currentScene->Init();
		//currentScene->initRenderer();
		currentScene->Start();

		bool found = false;
		for (int i = 0; i < scenes.size(); i++)
		{
			if (s = scenes.at(i))
			{
				found = true;
			}
		}
		if (!found)
		{
			scenes.push_back(s);
		}
	}
	else
		std::cout << "ru ro";
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
	std::cout << "\ncurrentIndex: " << currentIndex;
	std::cout << "\nsize: " << scenes.size();
	//make sure currentIndex and currentIndex+1 is in range
	if (currentIndex != -1 && !currentIndex + 1 > scenes.size()-1)
	{
		//stop currentScene
		currentScene->Stop();

		//assign new currentScene
		currentScene = scenes.at(currentIndex + 1);

		//init new currentScene
		currentScene->setWindow(window);
		currentScene->Init();
		currentScene->initRenderer();
		currentScene->Start();
	}
	else
	{
		std::cout << "there is no Scene to jump to";
	}
	
}

void SceneDirector::Start()
{
	// OpenGL configuration
	glViewport(0, 0, 800, 600);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	//tell currentScene to set to active
	currentScene->Start();

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f;
		// Manage user input
		//this->ProcessInput(deltaTime);

		// Update Game state
		this->Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		this->Render();

		glfwSwapBuffers(window);
	}
}

void SceneDirector::Update(float delta)
{
	currentScene->Update(delta);

	//check sensors 
	for (int i = 0; i < sensors.size(); i++)
	{
		sensors.at(i)->sense();
	}
}

void SceneDirector::Render()
{
	currentScene->Render();
}

void SceneDirector::addSensor(AbstractSensor * s)
{
	sensors.push_back(s);
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
	glfwTerminate();
}
