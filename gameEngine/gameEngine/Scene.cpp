#include "Scene.h"
#include <iostream>

#include "KeyHandler.h"
#include <mutex>

std::mutex threadMutex;
// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Scene::Scene(std::string n, GLuint w, GLuint h) :
	initilized(false)
{
	this->name = n;
	this->width = w;
	this->height = h;
	this->camera.setHeight(float(h));
	this->camera.setWidth(float(w));
	this->camera.setZoom(glm::vec2(1));

	this->MovingSceneObjects.push_back(&this->camera);
	this->MovingSceneObjects.push_back(&this->background);
}

//if SceneDirector doesn't have a scene yet, assign this one, init keycallback
void Scene::Init()
{
	if (!initilized)
	{
		SceneDirector *temp = SceneDirector::getInstance();
		if (temp->getNumberOfScenes() < 1)
		{
			temp->addScene(this);
		}
		glfwSetKeyCallback(window, key_callback);
		ResourceManager::LoadTexture("textures/BGSpace001.png", GL_FALSE, "background");
		initilized = true;
	}

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
				MovingSceneObjects.at(i)->checkBounds(this->width, this->height);
				MovingSceneObjects.at(i)->Update();

				if (MovingSceneObjects.at(i)->getDebug())
				{
					std::cout << "Name:" << MovingSceneObjects.at(i)->getName() << std::endl;
					std::cout << "Bound Action:" << MovingSceneObjects.at(i)->getBoundAction() << std::endl;
					std::cout << "Pos:" << MovingSceneObjects.at(i)->getPosition().x << ", " << MovingSceneObjects.at(i)->getPosition().y << std::endl;
					std::cout << "Size:" << MovingSceneObjects.at(i)->getSize().x << ", " << MovingSceneObjects.at(i)->getSize().y << std::endl;
					std::cout << "Rotation:" << MovingSceneObjects.at(i)->getRotation() << std::endl;
				}
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
		glm::mat4 projection;
		projection = glm::ortho(0.0f, this->camera.getWidth() * this->camera.getZoom().x, this->camera.getHeight() * this->camera.getZoom().y, 0.0f, -1.0f, 1.0f);
		projection = glm::translate(projection, glm::vec3(camera.getPosition(), 0.0f));
		projection = glm::translate(projection, glm::vec3(0.5f * this->camera.getWidth(), 0.5f * this->camera.getHeight(), 0.0f)); // Move origin of rotation to center of quad
		projection = glm::rotate(projection, this->camera.getRotation(), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
		projection = glm::translate(projection, glm::vec3(-0.5f * this->camera.getWidth(), -0.5f * this->camera.getHeight(), 0.0f)); // Move origin back
		ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
		
		//Texture2D tempTexture = ResourceManager::GetTexture("background");
		//renderer->DrawSprite(tempTexture, background.getPosition(), glm::vec2(this->width, this->height), 0.0f);
		for (int i = 0; i < DrawSceneObjects.size(); i++)
		{
			DrawSceneObjects.at(i)->Draw(*renderer);
		}
	}
}

//assuming these sprites don't have a scene, used for loading a lot of sprites via threading or just batching.
void Scene::loadSprites(std::vector<AbstractSprite*> sprites)
{
	threadMutex.lock();
	Sprites.insert(Sprites.end(), sprites.begin(), sprites.end());
	MovingSceneObjects.insert(MovingSceneObjects.end(), sprites.begin(), sprites.end());
	DrawSceneObjects.insert(DrawSceneObjects.end(), sprites.begin(), sprites.end());
	SceneObjects.insert(SceneObjects.end(), sprites.begin(), sprites.end());
	threadMutex.unlock();
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

Scene::~Scene()
{
}
