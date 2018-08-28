#include "Scene.h"
#include <iostream>

#include "KeyHandler.h"
#include <mutex>
#include <list>

std::mutex threadMutex;
// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Scene::Scene(std::string n, GLuint w, GLuint h) :
	initilized(false)
{
	this->name = n;
	this->width = w;
	this->height = h;
	this->camera = new Camera(w, h);
	this->camera->setZoom(glm::vec2(1));
	this->camera->setName("camera");
	this->background = new MovingSceneObject();
	this->background->setName("background");

	this->MovingSceneObjects.push_back(this->camera);
	this->MovingSceneObjects.push_back(this->background);
	this->SceneObjects.push_back(this->camera);
	this->SceneObjects.push_back(this->background);
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
		projection = glm::ortho(0.0f, this->camera->getWidth() * this->camera->getZoom().x, this->camera->getHeight() * this->camera->getZoom().y, 0.0f, -1.0f, 1.0f);
		projection = glm::translate(projection, glm::vec3(camera->getPosition(), 0.0f));
		projection = glm::translate(projection, glm::vec3(0.5f * this->camera->getWidth(), 0.5f * this->camera->getHeight(), 0.0f)); // Move origin of rotation to center of quad
		projection = glm::rotate(projection, this->camera->getRotation(), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
		projection = glm::translate(projection, glm::vec3(-0.5f * this->camera->getWidth(), -0.5f * this->camera->getHeight(), 0.0f)); // Move origin back
		ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
		
		Texture2D tempTexture = ResourceManager::GetTexture("background" + std::to_string(sceneCount));
		Renderer->DrawSprite(tempTexture, background->getPosition(), glm::vec2(this->width, this->height), 0.0f);
		for (int i = 0; i < DrawSceneObjects.size(); i++)
		{
			DrawSceneObjects.at(i)->Draw(*Renderer);
		}
	}
}

//assuming these sprites don't have a scene, used for loading a lot of sprites via threading or just batching.
void Scene::loadSprites(std::vector<AbstractSprite*> sps)
{
	threadMutex.lock();
	sprites.insert(sprites.end(), sps.begin(), sps.end());
	MovingSceneObjects.insert(MovingSceneObjects.end(), sps.begin(), sps.end());
	DrawSceneObjects.insert(DrawSceneObjects.end(), sps.begin(), sps.end());
	SceneObjects.insert(SceneObjects.end(), sps.begin(), sps.end());
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
	//GarbageCollector::getInstance()->addGarbage(SceneObjects);
	std::cout << sceneNumber;

	std::list<std::unique_ptr<SceneObject*>> garbage;
	for (int i = 0; i < SceneObjects.size(); i++)
	{
		garbage.push_back(std::make_unique<SceneObject*>(SceneObjects[i]));
	}
	//for (int i = 0; i < MovingSceneObjects.size(); i++)
	//{
	//	std::list<SceneObject*>::iterator findIter = std::find(garbage.begin(), garbage.end(), MovingSceneObjects[i]);
	//	if (findIter == garbage.end())
	//	{
	//		garbage.push_back(MovingSceneObjects[i]);
	//	}
	//}
	//for (int i = 0; i < DrawSceneObjects.size(); i++)
	//{
	//	std::list<SceneObject*>::iterator findIter = std::find(garbage.begin(), garbage.end(), DrawSceneObjects[i]);
	//	if (findIter == garbage.end())
	//	{
	//		garbage.push_back(DrawSceneObjects[i]);
	//	}
	////}

	//while (garbage.size() > 1)
	//{
	//	SceneObject *temp = garbage.front();
	//	garbage.remove(garbage.front());
	//	delete temp;
	//}
	/*
	for (std::vector< AbstractSprite* >::iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		//find the sprite in the Scene,Moving, and Draw Object vectors and remove them
		for (int i = 0; i < SceneObjects.size(); i++)
		{
				if (SceneObjects[i] == (*it))
					SceneObjects[i] = nullptr;
		}
		for (int i = 0; i < DrawSceneObjects.size(); i++)
		{
			if (DrawSceneObjects[i] == (*it))
				DrawSceneObjects[i] = nullptr;
		}
		for (int i = 0; i < MovingSceneObjects.size(); i++)
		{
			if (MovingSceneObjects[i] == (*it))
				MovingSceneObjects[i] = nullptr;
		}
		delete (*it);
		
	}
	sprites.clear();

	for (std::vector< SceneObject* >::iterator it = SceneObjects.begin(); it != SceneObjects.end(); ++it)
	{
		if ((*it) != nullptr)
			delete (*it);
	}
	SceneObjects.clear();
	
	int i = 0;
	for (std::vector< MovingSceneObject* >::iterator it = MovingSceneObjects.begin(); it != MovingSceneObjects.end(); ++it)
	{
		i++;
		if ((*it) != nullptr && i > 1)
			delete (*it);

	}
	*/
	//AbstractSprite **as = sprites.data();
	//delete[] as;

	//MovingSceneObject **mso = MovingSceneObjects.data();
	//delete[] mso;
	////MovingSceneObjects.clear();

	//DrawSceneObject **dso = DrawSceneObjects.data();
	//delete[] dso;

	//AbstractCollider **c = colliders.data();
	//delete[] c;

	//AbstractSensor **s = sensors.data();
	//delete[] s;

	//AbstractObserver **o = observers.data();
	//delete[] o;

	/*
	
	for (std::vector< DrawSceneObject* >::iterator it = DrawSceneObjects.begin(); it != DrawSceneObjects.end(); ++it)
	{
		if ((*it) != nullptr)
			delete (*it);
	}
	DrawSceneObjects.clear();

	for (std::vector< AbstractCollider* >::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		if ((*it) != nullptr)
			delete (*it);
	}
	colliders.clear();

	for (std::vector< AbstractSensor* >::iterator it = sensors.begin(); it != sensors.end(); ++it)
	{
		if ((*it) != nullptr)
			delete (*it);
	}
	sensors.clear();

	for (std::vector< AbstractObserver* >::iterator it = observers.begin(); it != observers.end(); ++it)
	{
		if ((*it) != nullptr)
			delete (*it);
	}
	observers.clear();
	*/
}
