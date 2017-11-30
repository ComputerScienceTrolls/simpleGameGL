#ifndef SCENE_H
#define SCENE_H

#include "AbstractScene.h"
#include "ResourceManager.h"
#include "sprite_renderer.h"
#include "AbstractSprite.h"
#include "Camera.h"
#include "SceneDirector.h"
#include "Observers\AbstractObserver.h"

#include "SensorActuators\AbstractSensor.h"

#include <vector>

// Scene holds all sprite set to it, determines when they are drawn and updated.
class Scene : public AbstractScene
{
public:
	Scene(std::string name, GLuint width, GLuint height);
	~Scene();
	virtual void Start();
	virtual void Stop();
	virtual void Init();
	virtual void Update(GLfloat dt);
	virtual void Render();
	std::vector<AbstractSprite*> getSprite(std::string name);
	std::vector<AbstractSprite*> Sprites;
	virtual GLFWwindow* getWindow();
	virtual void setWindow(GLFWwindow *newWindow);
	void addSensor(AbstractSensor*);
	void removeSensor(std::string name);
	void removeSensor(int index);
	void addObserver(AbstractObserver*);
	void removeObserver(std::string name);
	void removeObserver(int index);
	virtual void setActive(bool state);
	virtual void setVisible(bool state);

	//gets active state of scene, determines if sprites are updated and Sensors are checked
	virtual bool getActive();

	//gets visible state of scene, determines if sprites are rendered on screen
	virtual bool getVisible();

	//sets Scene's size
	void setSize(int width, int height);

	//get vector of Sprites;
	virtual std::vector<AbstractSprite*> getSprites();

	//set vector of Sprites;
	virtual void setSprites(std::vector<AbstractSprite*> newVector);

	virtual void addSprite(AbstractSprite*);

	//returns Scene's width
	int getWidth();

	//returns Scene's height
	int getHeight();

	//sets Scene's width
	void setWidth(int);

	//sets Scene's height
	void setHeight(int);

	//set's Scene's background, get's image from filename you give to fill the scene
	void setBackground(char*);

	//get deleted state, deleting and reiniting sprites not working yet
	bool getDeleted();

	//set deleted state, deleting and reiniting sprites not working yet
	void setDeleted(bool);

	//sets all sprites back to their init states.
	void reset();

	void reInit();

	std::string getName();
	
	void setName(std::string);
	virtual void changeCameraByX(int);
	virtual void changeCameraByY(int);
	virtual void setCameraDX(int);
	virtual void setCameraDY(int);
	virtual void setCameraWidth(int);
	virtual void setCameraHeight(int);
	virtual void setCameraPosX(int);
	virtual void setCameraPosY(int);

private:
	SpriteRenderer  *Renderer;
	std::map<std::string, AbstractSprite*> spriteMap;
	std::vector<AbstractSensor*> sensors;
	std::vector<AbstractObserver*> observers;
	GLFWwindow* window;
	bool active;
	bool visible;
	bool deleted;
	int height;
	int width;
	std::string name;
	glm::vec2 backgroundPos;
	Camera camera;
};
#endif