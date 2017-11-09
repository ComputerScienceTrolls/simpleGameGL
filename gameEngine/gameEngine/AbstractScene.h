#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
	virtual void reset() {};
	~AbstractScene();
};

