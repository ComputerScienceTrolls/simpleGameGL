#include "DrawSceneObject.h"

DrawSceneObject::DrawSceneObject()
{
}

void DrawSceneObject::setTransparency(float newT)
{
	this->transparency = newT;
}

float DrawSceneObject::getTransparency()
{
	return this->transparency;
}

void DrawSceneObject::setVisible(bool nV)
{
	this->visible = nV;
}

bool DrawSceneObject::getVisible()
{
	return this->visible;
}

void DrawSceneObject::setColor(glm::vec3 C)
{
	this->Color = C;
}

glm::vec3 DrawSceneObject::getColor()
{
	return this->Color;
}

DrawSceneObject::~DrawSceneObject()
{
}
