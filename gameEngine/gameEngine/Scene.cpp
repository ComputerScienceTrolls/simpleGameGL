#include "Scene.h"
#include <iostream>

#include "KeyHandler.h"

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

SpriteRenderer  *Renderer;

void Scene::Init()
{	
	SceneDirector *temp = SceneDirector::getInstance();
	if (temp->getNumberOfScenes() < 1)
	{
		temp->addScene(this);
	}
	glfwSetKeyCallback(window, key_callback);
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
}

Scene::Scene(GLuint w, GLuint h) :
	width(w), height(h)
{
}

void Scene::setBackground(char* newBackground)
{
	ResourceManager::LoadTexture(newBackground, GL_FALSE, "background");
}

void Scene::setActive(bool state)
{
	this->active = state;
}

bool Scene::getActive()
{
	return this->active;
}

void Scene::setSize(int w, int h)
{
	glfwSetWindowSize(window, w, h);
	this->width = w;
	this->height = h;
}

int Scene::getWidth()
{
	return this->width;
}

int Scene::getHeight()
{
	return this->height;
}

void Scene::setWidth(int w)
{
	this->width = w;
	glfwSetWindowSize(window, this->width, this->height);
}

void Scene::setHeight(int h)
{
	this->height = h;
	glfwSetWindowSize(window, this->width, this->height);
}

void Scene::Start()
{
	//setup SpriteMap
	for (int i = 0; i < Sprites.size(); i++)
	{
		spriteMap[Sprites.at(i)->getName()] = Sprites.at(i);
	}

	// set active to true
	this->setActive(true);
}

void Scene::Stop()
{
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();
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
				Sprites.at(i)->checkBounds(this->width, this->height);
			}
		}
		for (int i = 0; i < Sensors.size(); i++)
		{
			Sensors.at(i)->sense();
		}
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
	//set window to scene's defined width and height
	setSize(this->width, this->height);
}

void Scene::addSensor(AbstractSensor *s)
{
	Sensors.push_back(s);
}

void Scene::Render()
{
	if (this->active)
	{
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);
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
