#pragma once

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
	virtual void Start() {};
	virtual void Stop() {};
	virtual void Init() {};
	virtual void ProcessInput(GLfloat dt) {};
	virtual void Update(GLfloat dt) {};
	virtual void Render() {};
	virtual GLFWwindow* getWindow() = 0;
	virtual void setWindow(GLFWwindow *newWindow) {};
	virtual void setActive(bool) {};
	virtual bool getActive() { return false; };
	virtual void setDeleted(bool) {};
	virtual bool getDeleted() { return false; };
	virtual int getWidth() { return 0; };
	virtual int getHeight() { return 0; };
	virtual void setCameraWidth(int) = 0;
	virtual void setCameraHeight(int) = 0;
	virtual void setCameraPosX(int) = 0;
	virtual void setCameraPosY(int) = 0;
	virtual void setCameraDX(int) = 0;
	virtual void setCameraDY(int) = 0;
	virtual std::vector<AbstractSprite*> getSprites() = 0;
	virtual void setSprites(std::vector<AbstractSprite*>) = 0;
	virtual void addSprite(AbstractSprite*) = 0;
	virtual void reInit() {};
	virtual void reset() {};
	virtual void setName(std::string) = 0;
	virtual std::string getName() = 0;
	virtual Camera getCamera();
	~AbstractScene();

protected:
	Camera camera;
};

