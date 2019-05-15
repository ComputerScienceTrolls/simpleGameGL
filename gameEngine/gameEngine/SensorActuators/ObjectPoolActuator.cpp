#include "ObjectPoolActuator.h"

ObjectPoolActuator::ObjectPoolActuator(std::string name, SceneObject *object, int numberOfObjectsInPool, SceneObject *so, std::string con) :
	SO(so), condition(con), force(-1)
{
	this->name = name;
	this->index = -1;

	pool.push_back(object);
	for (int i = 1; i< numberOfObjectsInPool; i++)
	{
		pool.push_back(new SceneObject(object));
	}
}

ObjectPoolActuator::ObjectPoolActuator(std::string name, Sprite *object, int numberOfObjectsInPool, SceneObject * so, std::string con) :
	SO(so), condition(con), force(-1)
{
	this->name = name;
	this->index = -1;

	std::vector<Sprite*> sprites;
	object->setBoundAction("DIE");
	sprites.push_back(object);
	for (int i = 1; i< numberOfObjectsInPool; i++)
	{
		Sprite* temp = new Sprite(object);
		//for better performance, assume object wants to be deactived once off screen.
		temp->setBoundAction("DIE");
		pool.push_back(temp);
	}
}

ObjectPoolActuator::ObjectPoolActuator(std::string name, Sprite * object, int numberOfObjectsInPool, SceneObject * so, float f, SceneObject *ft, std::string con) :
	SO(so), forceToward(ft), condition(con)
{
	this->name = name;
	this->index = -1;
	this->force = f-1;

	std::vector<Sprite*> sprites;
	object->setBoundAction("DIE");
	sprites.push_back(object);
	for (int i = 1; i< numberOfObjectsInPool; i++)
	{
		Sprite* temp = new Sprite(object);
		temp->setCollideDebug(true);
		//for better performance, assume object wants to be deactived once off screen.
		temp->setBoundAction("DIE");
		pool.push_back(temp);
	}
}

void ObjectPoolActuator::run()
{
	if (condition == "spawn")
	{
		SceneObject *temp = this->getObject();
		temp->setPosition(SO->getPosition());
	}
	else if (condition == "spriteSpawn")
	{
		Sprite *temp = dynamic_cast<Sprite*>(this->getObject());
		std::cout << SO->getPosition().x << "\n";
		temp->setPosition(SO->getPosition());
		temp->setVisible(true);
		temp->setActive(true);
	}
	else if (condition == "spriteSpawnForce")
	{
		Sprite *temp = dynamic_cast<Sprite*>(this->getObject());
		temp->setVelocity(glm::vec2(0));
		temp->setPosition(SO->getPosition());
		temp->setVisible(true);
		temp->setActive(true);
		temp->addForce(temp->angleTo(forceToward), force);
	}
	else if (condition == "spriteSpawnRotateForce")
	{
		Sprite *temp = dynamic_cast<Sprite*>(this->getObject());
		//clear motion
		temp->setVelocity(glm::vec2(0));
		//set positon to given spawn object
		temp->setCenter(SO->getCenter());
		//enable object
		temp->setVisible(true);
		temp->setActive(true);
		double degrees = double(forceToward->getRotation()) * (180 / 3.141592653589793238463);
		float h = forceToward->getHeight();
		temp->setCenter(degrees + 180, forceToward->getCenter(), int(h));
		//add force to direction of the given parent, then set the same angle
		//double degrees = double(forceToward->getRotation()) * ((180 / 3.141592653589793238463));
		temp->addForce(float(degrees) + 180, force);
		temp->setRotation(forceToward->getRotation());
	}
	else if (condition == "frontLauncher")
	{
		Sprite *temp = dynamic_cast<Sprite*>(this->getObject());
		//clear motion
		temp->setVelocity(glm::vec2(0));

		//enable object
		temp->setVisible(true);
		temp->setActive(true);

		//set temps position to the length of it's current rotation, so set it in front of the object
		double degrees = double(forceToward->getRotation()) * (180 / 3.141592653589793238463);
		float h = forceToward->getHeight();
		temp->setPosition(degrees + 180, forceToward->getCenter(), int(h));

		//add force to direction of the given parent, then set the same angle
		temp->addForce(float(degrees) + 180, force);
		temp->setRotation(forceToward->getRotation());
	}
}

ObjectPoolActuator::~ObjectPoolActuator()
{
}