#pragma once
#include "SceneObject.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

class MovingSceneObject : public SceneObject
{
public:
	MovingSceneObject();
	virtual void setPosition(glm::vec2);
	virtual void setRenderPosition(glm::vec2);
	virtual void setVelocity(glm::vec2);
	~MovingSceneObject();

protected:
	glm::vec2 RenderPosiiton;
	glm::vec2 Position;
	glm::vec2 Velocity;
};

