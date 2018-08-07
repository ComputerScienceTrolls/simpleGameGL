#include "AbstractScene.h"

AbstractScene::AbstractScene() :
	camera(0,0)
{
}

//set Scene's state to active alsnd visible
void AbstractScene::Start()
{
	// set active to true
	this->active = true;

	//set visible to true
	this->visible = true;
}

//set Scene's state to not active and not visible
void AbstractScene::Stop()
{
	this->active = false;
	this->visible = false;
}

//set new background with given file
void AbstractScene::setBackground(const char* newBackground)
{
	ResourceManager::LoadTexture(newBackground, GL_FALSE, "background");
}

//tell every Sprite to reset their inital texture, currently not working
void AbstractScene::reset()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->reset();
	}
}

Camera* AbstractScene::getCamera()
{
	return &this->camera;
}

//gets a vector of sprites that all share the given name
std::vector<AbstractSprite*> AbstractScene::getSprite(std::string name)
{
	std::vector<AbstractSprite*> tempVec;
	for (int i = 0; i < sprites.size(); i++)
	{
		if (sprites.at(i)->getName() == name)
			tempVec.push_back(sprites[i]);
	}
	return tempVec;
}

std::vector<AbstractCollider*> AbstractScene::getColliders()
{
	return this->colliders;
}

std::vector<DrawSceneObject*> AbstractScene::getDrawObjects()
{
	return this->DrawSceneObjects;
}

void AbstractScene::addSprite(AbstractSprite *newSprite)
{
	sprites.push_back(newSprite);
	MovingSceneObjects.push_back(newSprite);
	DrawSceneObjects.push_back(newSprite);
	SceneObjects.push_back(newSprite);
}

void AbstractScene::addSensor(AbstractSensor *s)
{
	this->sensors.push_back(s);
}

void AbstractScene::removeSensor(std::string name)
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

void AbstractScene::removeSensor(int index)
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

void AbstractScene::addObserver(AbstractObserver *o)
{
	this->observers.push_back(o);
}

void AbstractScene::removeObserver(std::string name)
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

void AbstractScene::removeObserver(int index)
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

void AbstractScene::addSceneObject(SceneObject *s)
{
	this->SceneObjects.push_back(s);
}

void AbstractScene::addMovingObject(MovingSceneObject *m)
{
	this->MovingSceneObjects.push_back(m);
}

void AbstractScene::addDrawObject(DrawSceneObject *d)
{
	this->DrawSceneObjects.push_back(d);
}

void AbstractScene::addCollider(AbstractCollider *c)
{
	this->colliders.push_back(c);
	this->MovingSceneObjects.push_back(c);
	this->DrawSceneObjects.push_back(c);
	this->SceneObjects.push_back(c);
}

int AbstractScene::getWidth()
{
	return this->width;
}

int AbstractScene::getHeight()
{
	return this->height;
}

std::string AbstractScene::getName()
{
	return this->name;
}

bool AbstractScene::getActive()
{
	return this->active;
}

bool AbstractScene::getVisible()
{
	return this->visible;
}

GLFWwindow * AbstractScene::getWindow()
{
	return this->window;
}

std::vector<AbstractSprite*> AbstractScene::getSprites()
{
	return this->sprites;
}

void AbstractScene::setSize(int w, int h)
{
	this->width = w;
	this->height = h;
}

void AbstractScene::setWidth(int w)
{
	this->width = w;
	glfwSetWindowSize(window, this->width, this->height);
}

void AbstractScene::setHeight(int h)
{
	this->height = h;
	glfwSetWindowSize(window, this->width, this->height);
}

void AbstractScene::setName(std::string newName)
{
	this->name = newName;
}

void AbstractScene::setActive(bool newState)
{
	this->active = newState;
}

void AbstractScene::setVisible(bool state)
{
	this->visible = state;
}

void AbstractScene::setCameraWidth(int newWidth)
{
	this->camera.setWidth(float(newWidth));

	glfwSetWindowSize(window, newWidth, int(camera.getHeight()));
}

void AbstractScene::setCameraHeight(int newHeight)
{
	this->camera.setHeight(float(newHeight));

	glfwSetWindowSize(window, int(camera.getWidth()), newHeight);
}

void AbstractScene::setCameraPosX(float newX)
{
	this->camera.setPosX(newX);
}

void AbstractScene::setCameraPosY(float newY)
{
	this->camera.setPosY(newY);
}

void AbstractScene::setCameraDX(float newDX)
{
	this->camera.setDX(newDX);
}

void AbstractScene::setCameraDY(float newDY)
{
	this->camera.setDY(newDY);
}

void AbstractScene::setSprites(std::vector<AbstractSprite*> newVector)
{
	this->sprites = newVector;
}

//sets GLFWwindow, then calls setSize in case GLFWwindow is not the right size
void AbstractScene::setWindow(GLFWwindow * newWindow)
{
	window = newWindow;
	//set window to scene's defined width and height
	setSize(this->width, this->height);
	glfwSetWindowSize(window, int(this->camera.getWidth()), int(this->camera.getHeight()));
}

void AbstractScene::setRenderer(SpriteRenderer * newRenderer)
{
	this->Renderer = newRenderer;
}

AbstractScene::~AbstractScene()
{
}
