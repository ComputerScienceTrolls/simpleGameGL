#include "Scene.h"
#include <iostream>

#include "KeyHandler.h"

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Scene::Scene(GLuint w, GLuint h) :
	width(w), height(h), deleted(false)
{
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
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
}

//set Scene's state to active and visible, then tell every Sprite to start in their initial state, init spriteMap
void Scene::Start()
{
	//setup SpriteMap
	for (int i = 0; i < Sprites.size(); i++)
	{
		//reset every sprite
		Sprites.at(i)->reset();
		spriteMap[Sprites.at(i)->getName()] = Sprites.at(i);
	}

	// set active to true
	this->active = true;

	//set visible to true
	this->visible = true;
}

//set Scene's state to not active and not visible
void Scene::Stop()
{
	this->active = false;
	this->visible = false;
	// Delete all resources as loaded using the resource manager

	//tell all sprites to delete their textures
	//for (int i = 0; i < Sprites.size(); i++)
	//{
	//	Texture2D temp = Sprites[i]->getTexture();
	//	glDeleteTextures(1, &temp.ID);
	//}
	//this->deleted = true;
	//ResourceManager::Clear();
}

//if Scene is active, tell Sprites to update and check Sensors.
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
			}
		}
		for (int i = 0; i < Sensors.size(); i++)
		{
			Sensors.at(i)->sense();
		}
	}
}

//renders background and all sprites, if visible state is true
void Scene::Render()
{
	if (this->visible)
	{
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);
		for (int i = 0; i < Sprites.size(); i++)
		{
			Sprites.at(i)->Draw(*Renderer);
		}
	}
}

//tell every Sprite to reInit their inital texture, currently not working
void Scene::reset()
{
	for (int i = 0; i < Sprites.size(); i++)
	{
		Sprites[i]->reInit();
	}
	this->deleted = false;
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

//gets a vector of sprites that all share the given name
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

//add sensor to vector of Sensors
void Scene::addSensor(AbstractSensor *s)
{
	Sensors.push_back(s);
}

//set new background with given file
void Scene::setBackground(char* newBackground)
{
	ResourceManager::LoadTexture(newBackground, GL_FALSE, "background");
}

//set active state
void Scene::setActive(bool state)
{
	this->active = state;
}

//set visible state
void Scene::setVisible(bool state)
{
	this->visible = state;
}

//get active state
bool Scene::getActive()
{
	return this->active;
}

//get visible state
bool Scene::getVisible()
{
	return this->visible;
}

//set deleted state, deleting and reInit is not currently working
void Scene::setDeleted(bool b)
{
	this->deleted = b;
}

//return deleted state, deleting and reInit is not currently working
bool Scene::getDeleted()
{
	return this->deleted;
}

//set width and height, then resize window
void Scene::setSize(int w, int h)
{
	glfwSetWindowSize(window, w, h);
	this->width = w;
	this->height = h;
}

std::vector<AbstractSprite*> Scene::getSprites()
{
	return this->Sprites;
}

void Scene::setSprites(std::vector<AbstractSprite*> newVector)
{
	this->Sprites = newVector;
}

//get Scene's width
int Scene::getWidth()
{
	return this->width;
}

//get Scene's height
int Scene::getHeight()
{
	return this->height;
}

//set Scene's width, resize window
void Scene::setWidth(int w)
{
	this->width = w;
	glfwSetWindowSize(window, this->width, this->height);
}

//set Scene's height, resize window
void Scene::setHeight(int h)
{
	this->height = h;
	glfwSetWindowSize(window, this->width, this->height);
}

//returns GLFWwindow assigned to this scene
GLFWwindow * Scene::getWindow()
{
	return this->window;
}

//sets GLFWwindow, then calls setSize in case GLFWwindow is not the right size
void Scene::setWindow(GLFWwindow * newWindow)
{
	window = newWindow;
	//set window to scene's defined width and height
	setSize(this->width, this->height);
}

Scene::~Scene()
{
}
