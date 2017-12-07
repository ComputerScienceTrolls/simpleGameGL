#pragma once
#include "SceneObject.h"

class DrawSceneObject
{
	class SpriteRender;

public:
	DrawSceneObject();
	virtual void Draw(SpriteRenderer &renderer, glm::vec2) = 0;
	~DrawSceneObject();
};

