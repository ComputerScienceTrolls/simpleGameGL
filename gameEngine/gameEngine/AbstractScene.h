#ifndef ABSTRACT_SCENE_H
#define ABSTRACT_SCENE_H

#include "AbstractSprite.h"
#include "Observers/AbstractObserver.h"
#include "SensorActuators/AbstractSensor.h"
#include "ResourceManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include "Camera.h"

class AbstractScene
{
public:
	AbstractScene();
	static int sceneCount;
	virtual void Start();
	virtual void Stop();

	virtual void Init() = 0;
	virtual void Update(GLfloat dt) = 0;
	virtual void Render() = 0;
	virtual void reset();
	virtual Camera* getCamera();

	virtual void addSprite(AbstractSprite*);
	virtual void addSensor(AbstractSensor*);
	virtual void addSceneObject(SceneObject*);
	virtual void addMovingObject(MovingSceneObject*);
	virtual void addDrawObject(DrawSceneObject*);
	virtual void addCollider(AbstractCollider*);
	virtual void addObserver(AbstractObserver*);
	virtual void removeSensor(std::string name);
	virtual void removeSensor(int index);
	virtual void removeObserver(std::string name);
	virtual void removeObserver(int index);

	virtual int getCount();
	virtual int getWidth();
	virtual int getHeight();
	virtual std::string getName();
	virtual bool getActive();
	virtual bool getVisible();
	virtual GLFWwindow* getWindow();
	virtual std::vector<AbstractSprite*> getSprites();
	std::vector<AbstractSprite*> getSprite(std::string name);
	virtual std::vector<AbstractCollider*> getColliders();
	virtual std::vector<DrawSceneObject*> getDrawObjects();

	//set's Scene's background, get's image from filename you give to fill the scene
	void setBackground(const char*);

	virtual void setSize(int, int);
	virtual void setWidth(int);
	virtual void setHeight(int);
	virtual void setBackground(std::string);
	virtual void setName(std::string);
	virtual void setActive(bool);
	virtual void setVisible(bool state);
	virtual void setWindow(GLFWwindow *newWindow);
	virtual void setRenderer(SpriteRenderer *newRenderer);
	virtual void setCameraWidth(int);
	virtual void setCameraHeight(int);
	virtual void setCameraPosX(float);
	virtual void setCameraPosY(float);
	virtual void setCameraDX(float);
	virtual void setCameraDY(float);
	virtual void setSprites(std::vector<AbstractSprite*> newVector);

	virtual ~AbstractScene();

protected:
	std::vector<SceneObject*> SceneObjects;
	std::vector<MovingSceneObject*> MovingSceneObjects;
	std::vector<DrawSceneObject*> DrawSceneObjects;
	std::vector<AbstractSprite*> sprites;
	std::vector<AbstractSensor*> sensors;
	std::vector<AbstractCollider*> colliders;
	std::vector<AbstractObserver*> observers;
	Camera *camera;
	bool active;
	bool visible;
	int height;
	int width;
	std::string name;
	GLFWwindow *window;
	SpriteRenderer  *Renderer;
	int sceneNumber;
};

#endif
