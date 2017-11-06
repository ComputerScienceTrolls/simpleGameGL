#ifndef SCENEDIRECTOR_H
#define SCENEDIRECTOR_H
#include "AbstractScene.h"
#include <vector>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class SceneDirector
{
public:
	static SceneDirector* getInstance();
	void addScene(AbstractScene* s);
	AbstractScene* getScene(std::string);
	AbstractScene* getScene(int);
	void removeScene(std::string);
	void removeScene(int);
	void setScene(std::string);
	void nextScene();
	int getNumberOfScenes();
	AbstractScene* getCurrentScene();
	void start();

	void init();
	~SceneDirector();

private:
	SceneDirector();
	GLFWwindow* window;
	static std::auto_ptr<SceneDirector> instance;
	std::vector<AbstractScene*> scenes;
	AbstractScene *currentScene;
};

#endif