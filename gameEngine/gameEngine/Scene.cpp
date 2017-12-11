#include "Scene.h"
#include <iostream>

#include "KeyHandler.h"

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Scene::Scene(std::string n, GLuint w, GLuint h) :
	deleted(false), backgroundPos(0), backgroundDX(0), backgroundDY(0)
{
	this->name = n;
	this->width = w;
	this->height = h;
	this->camera.setHeight(h);
	this->camera.setWidth(w);
	
	this->MovingSceneObjects.push_back(&this->camera);
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

//set Scene's state to active alsnd visible, then tell every Sprite to start in their initial state, init spriteMap
void Scene::Start()
{
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
		//update backgroundPos by it's DX and DY
		backgroundPos.x += backgroundDX;
		backgroundPos.y += backgroundDY;

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
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), backgroundPos + this->camera.getPosition(), glm::vec2(this->width, this->height), 0.0f);
		//give camera's pos so Sprite's can render accordingly
		for (int i = 0; i < DrawSceneObjects.size(); i++)
		{
			DrawSceneObjects.at(i)->Draw(*Renderer, glm::vec2(this->camera.getPosX(), this->camera.getPosY()));
		}
	}
}

//tell every Sprite to reset their inital texture, currently not working
void Scene::reset()
{
	for (int i = 0; i < Sprites.size(); i++)
	{
		Sprites[i]->reset();
	}
}

//tell every Sprite to reInit their inital texture, currently not working
void Scene::reInit()
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
	sensors.push_back(s);
}

void Scene::removeSensor(std::string name)
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

void Scene::removeSensor(int index)
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

void Scene::addObserver(AbstractObserver *o)
{
	observers.push_back(o);
}

void Scene::removeObserver(std::string name)
{
	//get index of collider
	int index = -1;
	for (int i = 0; i < this->observers.size(); i++)
	{
		if (this->observers[i]->getName() == name)
		{
			index = i;
		}
	}

	//if found remove it from the vector
	if (index != -1)
	{
		std::cout << "deleting " << this->observers.at(index)->getName();
		this->observers.erase(this->observers.begin() + index);
	}
	else
	{
		std::cout << "observer with the name of " << name << " not found";
	}
}

void Scene::removeObserver(int index)
{
	if (index > -1 && index <= observers.size() - 1)
	{
		this->observers.erase(observers.begin() + index);
	}
	else
	{
		std::cout << "index is not in range";
	}
}

//set new background with given file
void Scene::setBackground(char* newBackground)
{
	ResourceManager::LoadTexture(newBackground, GL_FALSE, "background");
}

//set visible state
void Scene::setVisible(bool state)
{
	this->visible = state;
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

std::vector<AbstractSprite*> Scene::getSprites()
{
	return this->Sprites;
}

void Scene::setSprites(std::vector<AbstractSprite*> newVector)
{
	this->Sprites = newVector;
}

void Scene::addSprite(AbstractSprite *newSprite)
{
	Sprites.push_back(newSprite);
	MovingSceneObjects.push_back(newSprite);
	DrawSceneObjects.push_back(newSprite);
	SceneObjects.push_back(newSprite);
}

void Scene::addSceneObject(SceneObject *newObject)
{
	SceneObjects.push_back(newObject);
}

void Scene::addMovingObject(MovingSceneObject *newObject)
{
	MovingSceneObjects.push_back(newObject);
}

void Scene::addDrawObject(DrawSceneObject *newObject)
{
	DrawSceneObjects.push_back(newObject);
}

Scene::~Scene()
{
}
