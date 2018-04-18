#include "ObjectPoolSpawner.h"

ObjectPoolSpawner::ObjectPoolSpawner(std::string name, SceneObject *object, int numberOfObjectsInPool, SceneObject *so) :
	SO(so)
{
	this->name = name;
	this->index = -1;

	pool.push_back(object);
	for (int i = 1; i< numberOfObjectsInPool; i++)
	{
		pool.push_back(new SceneObject(object));
	}
}

ObjectPoolSpawner::ObjectPoolSpawner(std::string name, Sprite *object, int numberOfObjectsInPool, SceneObject * so) :
	SO(so)
{
	this->name = name;
	this->index = -1;

	std::vector<Sprite*> test;
	for (int i = 0; i< numberOfObjectsInPool; i++)
	{
		Sprite* temp = new Sprite(object);
		temp->setDebugMode(true);
		test.push_back(temp);
	}
	pool.push_back(object);
	for (int i = 1; i< numberOfObjectsInPool; i++)
	{
		pool.push_back(test.at(1));
	}
}

void ObjectPoolSpawner::run()
{
	//SceneObject *temp = this->getObject();
	Sprite *temp = dynamic_cast<Sprite*>(this->getObject());
	//std::cout << temp->getPosition().x << "\n";
	std::cout << SO->getPosition().x << "\n";
	temp->setPosition(SO->getPosition());
	std::cout << "wut " << temp->getPosX() << "\n";
}

ObjectPoolSpawner::~ObjectPoolSpawner()
{
}