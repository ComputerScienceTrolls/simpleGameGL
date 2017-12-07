#ifndef STATIC_COLLIDER_H
#define STATIC_COLLIDER_H

#include "SceneObject.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class StaticCollider : public SceneObject
{
public:
	StaticCollider();
	virtual void setType(std::string);
	virtual std::string getType();

	//virtual void collide(std::vector<AbstractCollider*>) = 0;

	~StaticCollider();

protected:
	std::string type;
};

#endif