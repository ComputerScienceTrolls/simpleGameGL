#include "SceneDirector.h"
#include <iostream>
std::auto_ptr<SceneDirector> SceneDirector::instance;

//default width and height
int WIDTH = 800;
int HEIGHT = 600;

double lastTime = glfwGetTime();
int nbFrames = 0;

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
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
}

/*
void SceneDirector::Update(float delta)
{
	currentScene->Update(delta);

	//check sensors 
	for (int i = 0; i < sensors.size(); i++)
	{
		sensors.at(i)->sense();
	}

	// Measure speed
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0)
	{ // If last prinf() was more than 1 sec ago
	  // printf and reset timer
		printf("%f ms/frame\n", 1000.0 / double(nbFrames));
		nbFrames = 0;
		lastTime += 1.0;
	}
}
*/

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
		currentScene->setRenderer(Renderer);
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

void SceneDirector::setSceneBackground(std::string n)
{
	currentScene->setBackground(n.c_str());
}

void SceneDirector::removeScene(std::string n)
{
	//get index of collider
	int index = -1;
	for (int i = 0; i < this->scenes.size(); i++)
	{
		if (this->scenes[i]->getName() == n)
		{
			index = i;
		}
	}

	//if found remove it from the vector
	if (index != -1)
	{
		std::cout << "deleting " << scenes.at(index)->getName();
		this->scenes.erase(scenes.begin() + index);
	}
	else
	{
		std::cout << "scene with the name of " << n << " not found";
	}
}

void SceneDirector::removeScene(int index)
{
	if (index > -1 && index <= sensors.size() - 1)
	{
		this->sensors.erase(sensors.begin() + index);
	}
	else
	{
		std::cout << "index is not in range";
	}
}

//sets the given scene, if it's not already in scene list, add it
void SceneDirector::setScene(AbstractScene *s)
{
	currentScene->Stop();
	currentScene = s;
	currentScene->setWindow(window);
	currentScene->setRenderer(Renderer);
	currentScene->Init();
	currentScene->reset();
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
		currentScene->setActive(false);
		currentScene = s;
		currentScene->setWindow(window);
		currentScene->setRenderer(Renderer);
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
	if (currentIndex != -1 && (currentIndex) < scenes.size()-1)
	{
		//stop currentScene
		currentScene->Stop();

		//assign new currentScene
		currentScene = scenes.at(currentIndex + 1);

		//init new currentScene
		currentScene->setWindow(window);
		currentScene->setRenderer(Renderer);
		//currentScene->Init();
		currentScene->reset();
		currentScene->Start();
	}
	else
	{
		std::cout << "Next: there is no Scene to jump to";
		std::cout << "\ncurrentIndex: " << currentIndex;
		std::cout << "\nsize: " << scenes.size();
	}
}

void SceneDirector::previousScene()
{
	int currentIndex = -1;
	for (int i = 0; i < scenes.size(); i++)
	{
		if (currentScene == scenes.at(i))
		{
			currentIndex = i;
		}
	}

	//make sure currentIndex and currentIndex-1 is in range
	if (currentIndex != -1 && currentIndex - 1 > -1)
	{
		//stop currentScene
		currentScene->Stop();

		//assign new currentScene
		currentScene = scenes.at(currentIndex - 1);

		//init new currentScene
		currentScene->setWindow(window);
		currentScene->setRenderer(Renderer);
		currentScene->Init();
		currentScene->reset();
		currentScene->Start();
	}
	else
	{
		std::cout << "Previous: there is no Scene to jump to";
		std::cout << "\ncurrentIndex: " << currentIndex;
		std::cout << "\nsize: " << scenes.size();
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

		// Update Game state
		this->Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		this->Render();

		glfwSwapBuffers(window);
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

void SceneDirector::addObserver(AbstractObserver * o)
{
	observers.push_back(o);
}

void SceneDirector::removeSensor(std::string name)
{
	int index = -1;
	for (int i = 0; i < this->sensors.size(); i++)
	{
		if (this->sensors[i]->getName() == name)
		{
			index = i;
		}
	}

	//if found remove it from the vector
	if (index != -1)
	{
		std::cout << "deleting " << this->sensors.at(index)->getName();
		this->sensors.erase(sensors.begin() + index);
	}
	else
	{
		std::cout << "Sensor with the name of " << name << " not found";
	}
}

void SceneDirector::removeSensor(int index)
{
	if (index > -1 && index <= sensors.size() - 1)
	{
		sensors.erase(sensors.begin() + index);
	}
	else
	{
		std::cout << "index is not in range";
	}
}

void SceneDirector::removeObserver(std::string name)
{
	//get index of collider
	int index = -1;
	for (int i = 0; i < observers.size(); i++)
	{
		if (observers[i]->getName() == name)
		{
			index = i;
		}
	}

	//if found remove it from the vector
	if (index != -1)
	{
		std::cout << "deleting " << observers.at(index)->getName();
		observers.erase(observers.begin() + index);
	}
	else
	{
		std::cout << "observer with the name of " << name << " not found";
	}
}

void SceneDirector::removeObserver(int index)
{
	if (index > -1 && index <= sensors.size() - 1)
	{
		observers.erase(observers.begin() + index);
	}
	else
	{
		std::cout << "index is not in range";
	}
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
	ResourceManager::Clear();
}
