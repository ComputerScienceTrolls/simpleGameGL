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

DrawSceneObject::~DrawSceneObject()
{
}
