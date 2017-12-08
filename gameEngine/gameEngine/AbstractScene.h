#ifndef ABSTRACT_SCENE_H
#define ABSTRACT_SCENE_H

#include "AbstractSprite.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include "Camera.h"

class AbstractScene
{
public:
	AbstractScene();
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Init() {};
	virtual void ProcessInput(GLfloat dt) {};
	virtual void Update(GLfloat dt) {};
	virtual void Render() {};
	virtual std::vector<AbstractSprite*> getSprites() = 0;
	virtual void setSprites(std::vector<AbstractSprite*>) = 0;
	virtual void addSprite(AbstractSprite*) = 0;
	virtual void addSceneObject(SceneObject*) = 0;
	virtual void addMovingObject(MovingSceneObject*) = 0;
	virtual void addDrawObject(DrawSceneObject*) = 0;
	virtual void reInit() {};
	virtual void reset() {};
	virtual Camera* getCamera();
	virtual void setDeleted(bool) {};
	virtual bool getDeleted() { return false; };

	virtual int getWidth();
	virtual int getHeight();
	virtual std::string getName();
	virtual bool getActive();
	virtual GLFWwindow* getWindow();

	virtual void setSize(int, int);
	virtual void setWidth(int);
	virtual void setHeight(int);
	virtual void setName(std::string);
	virtual void setActive(bool);
	virtual void setWindow(GLFWwindow *newWindow);
	virtual void setCameraWidth(int);
	virtual void setCameraHeight(int);
	virtual void setCameraPosX(int);
	virtual void setCameraPosY(int);
	virtual void setCameraDX(int);
	virtual void setCameraDY(int);
	virtual void changeCameraByX(int);
	virtual void changeCameraByY(int);


	~AbstractScene();

protected:
	Camera camera;
	bool active;
	int height;
	int width;
	std::string name;
	GLFWwindow* window;
};

#endif