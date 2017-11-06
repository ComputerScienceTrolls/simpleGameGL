#include "Scene.h"
#include <iostream>

#include "KeyHandler.h"

using namespace std;

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
//const GLuint SCREEN_WIDTH = 800;
// The height of the screen
//const GLuint SCREEN_HEIGHT = 600;
SpriteRenderer  *Renderer;

void Scene::Init()
{	
	SceneDirector *temp = SceneDirector::getInstance();
	if (temp->getNumberOfScenes() < 1)
	{
		temp->addScene(this);
	}
	glfwSetKeyCallback(window, key_callback);
	/*
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(Width, Height, "HelloWorld", nullptr, nullptr);
	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
	
	glfwSetKeyCallback(window, key_callback);
	
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
	*/
}

void Scene::initRenderer()
{
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
}

void Scene::setActive(bool state)
{
	this->active = state;
}

bool Scene::getActive()
{
	return this->active;
}

Scene::Scene(GLuint width, GLuint height) :
	Width(width), Height(height)
{
	//see if SceneDirector has any Scenes in it, if it doesn't, make this scene it's current Scene
	/*
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	*/
}

void Scene::Start()
{
	//setup SpriteMap
	for (int i = 0; i < Sprites.size(); i++)
	{
		spriteMap[Sprites.at(i)->getName()] = Sprites.at(i);
	}
	/*
	// OpenGL configuration
	glViewport(0, 0, Width, Height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	*/

	// set active to true
	this->setActive(true);

	/*
	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f;
		// Manage user input
		this->ProcessInput(deltaTime);

		// Update Game state
		this->Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		this->Render();

		glfwSwapBuffers(window);
	}
	*/
}

void Scene::Stop()
{
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	//glfwTerminate();
}

void Scene::Update(GLfloat dt)
{
	if (this->active)
	{
		//for each sprite in scene
		for (int i = 0; i < Sprites.size(); i++)
		{
			if (Sprites.at(i)->getState("active"))
			{
				Sprites.at(i)->update();
				Sprites.at(i)->checkBounds(Width, Height);
				/*
				if (Sprites.at(i)->getName() == "Paddle")
				{
				std::vector<AbstractSprite*> tempVec = this->getSprite("Ball");
				for (int j = 0; j < tempVec.size(); j++)
				{
				//std::cout << "step2";
				if (Sprites.at(i)->collide(tempVec.at(j)))
				{
				std::cout << "collision3";
				}
				}
				}
				*/
			}
		}
		for (int i = 0; i < Sensors.size(); i++)
		{
			Sensors.at(i)->sense();
		}

		//may not be good design but... we need to check for Sensors of SceneDirector,
		SceneDirector::getInstance()->checkSensors();
	}
}

std::vector<AbstractSprite*> Scene::getSprite(std::string name)
{
	std::vector<AbstractSprite*> tempVec;
	for (int i = 0; i < Sprites.size(); i++)
	{
		if (Sprites.at(i)->getName() == name)
			tempVec.push_back(Sprites[i]);
	}
	return tempVec;
}

GLFWwindow * Scene::getWindow()
{
	return this->window;
}

void Scene::setWindow(GLFWwindow * newWindow)
{
	window = newWindow;
}

void Scene::addSensor(AbstractSensor *s)
{
	Sensors.push_back(s);
}

void Scene::ProcessInput(GLfloat dt)
{
}

void Scene::Render()
{
	if (this->active)
	{
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		//for each sprite in scene
		for (int i = 0; i < Sprites.size(); i++)
		{
			Sprites.at(i)->Draw(*Renderer);
			//Renderer->DrawSprite(Sprites.at(i)->getTexture(), Sprites.at(i)->getPosition(), Sprites.at(i)->getSize(), Sprites.at(i)->getRotation(), Sprites.at(i)->getColor());
		}
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			KeyHandler::getInstance()->Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			KeyHandler::getInstance()->Keys[key] = GL_FALSE;
	}
}

Scene::~Scene()
{
}
