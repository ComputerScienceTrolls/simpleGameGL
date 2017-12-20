#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

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
	virtual void setPosX(float);
	virtual void setPosY(float);
	virtual void setCenter(glm::vec2);
	virtual void setSize(glm::vec2);
	virtual void setWidth(float);
	virtual void setHeight(float);
	virtual void changeWidthBy(float);
	virtual void changeHeightBy(float);
	virtual void setName(std::string);
	virtual void setRotation(GLfloat);
	virtual void setActive(bool);

	//get methods
	virtual glm::vec2 getPosition();
	virtual float getPosX();
	virtual float getPosY();
	virtual glm::vec2 getCenter();
	virtual glm::vec2 getSize();
	virtual float getWidth();
	virtual float getHeight();
	virtual std::string getName();
	virtual GLfloat getRotation();
	virtual bool getActive();

	virtual void changePositionBy(glm::vec2);
	virtual void changeXBy(float);
	virtual void changeYBy(float);

	~SceneObject();

protected:
	glm::vec2 Position, Center, Size;
	GLfloat Rotation;
	std::string name;
	bool active;
};

#endif