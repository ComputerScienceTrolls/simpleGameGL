#pragma once
#include "SceneObject.h"

class DrawSceneObject : public virtual SceneObject
{
	class SpriteRender;

public:
	DrawSceneObject();
	virtual void setTransparency(float);
	virtual float getTransparency();

	virtual void Draw(SpriteRenderer &renderer, glm::vec2, glm::vec2) = 0;
	~DrawSceneObject();

protected:
	GLfloat transparency;
};

