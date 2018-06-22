#ifndef ABSTRACT_SCENE_H
#define ABSTRACT_SCENE_H

#include "AbstractSprite.h"
#include "Observers/AbstractObserver.h"
#include "SensorActuators/AbstractSensor.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include "Camera.h"
#include "ParticleGenerator.h"

class AbstractScene
{
public:
	AbstractScene();
	virtual void Start();
	virtual void Stop();

	virtual void Init() = 0;
	virtual void Update(GLfloat dt) = 0;
	virtual void Render() = 0;
	virtual void reset();
	virtual Camera* getCamera();

	virtual void addSprite(AbstractSprite*);
	void addSensor(AbstractSensor*);
	void removeSensor(std::string name);
	void removeSensor(int index);
	void addObserver(AbstractObserver*);
	void removeObserver(std::string name);
	void removeObserver(int index);
	virtual void addSceneObject(SceneObject*);
	virtual void addMovingObject(MovingSceneObject*);
	virtual void addDrawObject(DrawSceneObject*);
	virtual void addCollider(AbstractCollider*);

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
	virtual void setName(std::string);
	virtual void setActive(bool);
	virtual void setVisible(bool state);
	virtual void setWindow(GLFWwindow *newWindow);
	virtual void setRenderer(Renderer *newRenderer);
	virtual void setParticle(ParticleGenerator *newParticle);
	virtual void setCameraWidth(int);
	virtual void setCameraHeight(int);
	virtual void setCameraPosX(float);
	virtual void setCameraPosY(float);
	virtual void setCameraDX(float);
	virtual void setCameraDY(float);
	virtual void setSprites(std::vector<AbstractSprite*> newVector);

	~AbstractScene();

protected:
	std::vector<AbstractSprite*> Sprites;
	std::vector<SceneObject*> SceneObjects;
	std::vector<MovingSceneObject*> MovingSceneObjects;
	std::vector<DrawSceneObject*> DrawSceneObjects;
	std::vector<AbstractSensor*> sensors;
	std::vector<AbstractCollider*> colliders;
	std::vector<AbstractObserver*> observers;
	Camera camera;
	bool active;
	bool visible;
	int height;
	int width;
	std::string name;
	GLFWwindow *window;
	Renderer *renderer;
	ParticleGenerator *particle;
};

#endif
