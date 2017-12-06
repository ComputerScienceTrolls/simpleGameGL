#include "AbstractScene.h"

AbstractScene::AbstractScene() :
	camera(0,0)
{
}

Camera* AbstractScene::getCamera()
{
	return &this->camera;
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

GLFWwindow * AbstractScene::getWindow()
{
	return this->window;
}

void AbstractScene::setSize(int w, int h)
{
	this->width = w;
	this->height = h;
	glfwSetWindowSize(window, this->width, this->height);
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

void AbstractScene::setCameraWidth(int newWidth)
{
	this->camera.setWidth(newWidth);

	glfwSetWindowSize(window, newWidth, camera.getHeight());
}

void AbstractScene::setCameraHeight(int newHeight)
{
	this->camera.setHeight(newHeight);

	glfwSetWindowSize(window, camera.getWidth(), newHeight);
}

void AbstractScene::setCameraPosX(int newX)
{
	this->camera.setPosX(newX);
}

void AbstractScene::setCameraPosY(int newY)
{
	this->camera.setPosY(newY);
}

void AbstractScene::setCameraDX(int newDX)
{
	this->camera.setDX(newDX);
}

void AbstractScene::setCameraDY(int newDY)
{
	this->camera.setDY(newDY);
}


void AbstractScene::changeCameraByX(int x)
{
	/*
	//move all sprites by x
	for (int i = 0; i < Sprites.size(); i++)
	{
		Sprites[i]->setPosition(glm::vec2(Sprites.at(i)->getPosition().x + x, Sprites.at(i)->getPosition().y));
	}

	//move the background
	backgroundPos.x = backgroundPos.x + x;
	*/
}

void AbstractScene::changeCameraByY(int y)
{
	/*
	//move all sprites by y
	for (int i = 0; i < Sprites.size(); i++)
	{
		Sprites[i]->setRenderPosY(1);
		//Sprites[i]->setPosition(glm::vec2(Sprites.at(i)->getPosition().x , Sprites.at(i)->getPosition().y + y));
	}
	*/
}

//sets GLFWwindow, then calls setSize in case GLFWwindow is not the right size
void AbstractScene::setWindow(GLFWwindow * newWindow)
{
	window = newWindow;
	//set window to scene's defined width and height
	setSize(this->width, this->height);
}

AbstractScene::~AbstractScene()
{
}
