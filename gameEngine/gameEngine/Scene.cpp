#include "Scene.h"
#include <iostream>

#include "KeyHandler.h"

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Scene::Scene(std::string n, GLuint w, GLuint h)
{
	this->name = n;
	this->width = w;
	this->height = h;
	this->camera.setHeight(h);
	this->camera.setWidth(w);

	this->MovingSceneObjects.push_back(&this->camera);
	this->MovingSceneObjects.push_back(&this->background);
}

//if SceneDirector doesn't have a scene yet, assign this one, init keycallback, setup shader and Renderer.
void Scene::Init()
{
	SceneDirector *temp = SceneDirector::getInstance();
	if (temp->getNumberOfScenes() < 1)
	{
		temp->addScene(this);
	}
	glfwSetKeyCallback(window, key_callback);
	// Load shaders
	//ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
}

//if Scene is active, tell Sprites to update and check Sensors.
void Scene::Update(GLfloat dt)
{
	if (this->active)
	{
		//for each sprite in scene
		for (int i = 0; i < MovingSceneObjects.size(); i++)
		{
			if (MovingSceneObjects.at(i)->getActive())
			{
				MovingSceneObjects.at(i)->Update();
				MovingSceneObjects.at(i)->checkBounds(this->width, this->height);
			}
		}

		for (int i = 0; i < sensors.size(); i++)
		{
			sensors.at(i)->sense();
		}

		for (int i = 0; i < observers.size(); i++)
		{
			observers.at(i)->Notify();
		}
	}
}

//renders background and all sprites, if visible state is true
void Scene::Render()
{
	if (this->visible)
	{
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), background.getPosition() + this->camera.getPosition(), glm::vec2(this->width, this->height), 0.0f);
		//give camera's pos so Sprite's can render accordingly
		for (int i = 0; i < DrawSceneObjects.size(); i++)
		{
			DrawSceneObjects.at(i)->Draw(*Renderer, this->camera.getPosition());
		}
	}
}

//event called every time a key is pressed, check for exit, update KeyHandler singleton keys.
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

//set new background with given file
void Scene::setBackground(char* newBackground)
{
	ResourceManager::LoadTexture(newBackground, GL_FALSE, "background");
}


Scene::~Scene()
{
}