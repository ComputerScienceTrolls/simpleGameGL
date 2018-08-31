#pragma once

#include <string>
#include <glm/vec3.hpp>

#include "AbstractRenderer.h"
#include "DrawSceneObject.h"

class AbstractTextSceneObject : virtual public DrawSceneObject
{
public:
	AbstractTextSceneObject();
	virtual void Draw(AbstractRenderer *renderer) = 0;
	~AbstractTextSceneObject();

protected:
	std::string text;
	std::string font;
	int fontSize;
};

