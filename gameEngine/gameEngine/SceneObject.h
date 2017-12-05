#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "sprite_renderer.h"

class SceneObject
{
public:
	SceneObject();

	//set methods
	virtual void setPosition(glm::vec2);
	virtual void setCenter(glm::vec2);
	virtual void setSize(glm::vec2);
	virtual void setName(std::string);
	virtual void setRotation(GLfloat);
	virtual void setActive(bool);

	//get methods
	virtual glm::vec2 getPosition();
	virtual glm::vec2 getCenter();
	virtual glm::vec2 getSize();
	virtual std::string getName();
	virtual GLfloat getRotation();
	virtual bool getActive();

	virtual void Update() {};
	virtual void Draw(SpriteRenderer &renderer) {};
	//virtual void reset() {};
	//virtual void reInit() {};

	~SceneObject();

protected:
	glm::vec2 Position, Center, Size;
	GLfloat Rotation;
	std::string name;
	bool active;
};

