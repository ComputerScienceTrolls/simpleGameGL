#ifndef STATIC_COLLIDER_H
#define STATIC_COLLIDER_H

#include "SceneObject.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class StaticCollider : SceneObject
{
public:
	StaticCollider();
	virtual void setType(std::string);
	virtual std::string getType();

	virtual void collide() = 0;

	~StaticCollider();

protected:
	std::string type;
};

#endif