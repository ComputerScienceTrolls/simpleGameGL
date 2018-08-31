#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class SceneObject
{
public:
	SceneObject();
	SceneObject(std::string name, glm::vec2 Pos = glm::vec2(0), glm::vec2 Size = glm::vec2(0));
	SceneObject(SceneObject* copy);

	//set methods
	virtual void setPosition(glm::vec2);
	virtual void setPosition(double degrees, glm::vec2, int amount);
	virtual void setPosX(float);
	virtual void setPosY(float);
	virtual void setCenter(glm::vec2);
	virtual void setCenter(double degrees, glm::vec2, int amount);
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

	virtual void setParent(SceneObject*);
	virtual void removeChild(SceneObject*);
	virtual SceneObject* getParent();
	virtual void addChildObject(SceneObject*);

	//pie constant for math
	const double PI = 3.141592653589793238463;

	virtual ~SceneObject();

protected:
	glm::vec2 Position, Center, Size;
	std::vector<SceneObject*> children;
	GLfloat Rotation;
	std::string name;
	bool active;
	SceneObject *parent;
};

#endif