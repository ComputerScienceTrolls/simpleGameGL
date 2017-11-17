#ifndef SCENEDIRECTOR_H
#define SCENEDIRECTOR_H
#include "AbstractScene.h"
#include <vector>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ResourceManager.h"

#include "SensorActuators\AbstractSensor.h"
#include "Observers\AbstractObserver.h"

class SceneDirector
{
public:
	static SceneDirector* getInstance();
	void addScene(AbstractScene* s);
	AbstractScene* getScene(std::string);
	AbstractScene* getScene(int);
	void removeScene(std::string);
	void removeScene(int);
	void setScene(AbstractScene *s);
	void setScenePause(AbstractScene *s);
	void nextScene();
	void previousScene();
	int getNumberOfScenes();
	AbstractScene* getCurrentScene();
	void Start();
	void Update(float delta);
	void Render();
	void addSensor(AbstractSensor *s);
	void addObserver(AbstractObserver *o);
	void removeSensor(std::string);
	void removeSensor(int);
	void removeObserver(std::string);
	void removeObserver(int);
	void checkSensors();
	void pauseScene(AbstractScene *s);
	void unpauseScene(AbstractScene *s);
	~SceneDirector();

private:
	SceneDirector();
	GLFWwindow* window;
	static std::auto_ptr<SceneDirector> instance;
	std::vector<AbstractScene*> scenes;
	AbstractScene *currentScene;
	std::vector<AbstractSensor*> sensors;
	std::vector<AbstractObserver*> observers;
};

#endif