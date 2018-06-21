#ifndef DRAWSCENEOBJECT_H
#define DRAWSCENEOBJECT_H

#include "SceneObject.h"
#include "Renderer.h"

class DrawSceneObject : public virtual SceneObject
{
	class SpriteRender;

public:
	DrawSceneObject();
	virtual void setTransparency(float);
	virtual float getTransparency();
	virtual void setColor(glm::vec3);
	virtual glm::vec3 getColor();

	virtual void Draw(Renderer &renderer) = 0;
	~DrawSceneObject();

protected:
	GLfloat transparency;
	glm::vec3 Color;
};

#endif