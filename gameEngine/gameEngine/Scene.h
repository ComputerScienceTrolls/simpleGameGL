#ifndef SCENE_H
#define SCENE_H

#include "AbstractScene.h"
#include "ResourceManager.h"
#include "sprite_renderer.h"
#include "AbstractSprite.h"
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
	std::vector<AbstractSprite*> Sprites;
	std::vector<AbstractSprite*> getSprite(std::string name);
	void addSensor(AbstractSensor*);
	void removeSensor(std::string name);
	void removeSensor(int index);
	void addObserver(AbstractObserver*);
	void removeObserver(std::string name);
	void removeObserver(int index);
	virtual void setVisible(bool state);

	//gets visible state of scene, determines if sprites are rendered on screen
	virtual bool getVisible();


	//get vector of Sprites;
	virtual std::vector<AbstractSprite*> getSprites();

	//set vector of Sprites;
	virtual void setSprites(std::vector<AbstractSprite*> newVector);

	virtual void addSprite(AbstractSprite*);

	virtual void addMovingObject(MovingSceneObject*);

	//set's Scene's background, get's image from filename you give to fill the scene
	void setBackground(char*);

	//get deleted state, deleting and reiniting sprites not working yet
	bool getDeleted();

	//set deleted state, deleting and reiniting sprites not working yet
	void setDeleted(bool);

	//sets all sprites back to their init states.
	void reset();

	void reInit();

private:
	SpriteRenderer  *Renderer;
	std::map<std::string, AbstractSprite*> spriteMap;
	std::vector<SceneObject*> SceneObjects;
	std::vector<MovingSceneObject*> MovingSceneObjects;
	std::vector<AbstractSensor*> sensors;
	std::vector<AbstractObserver*> observers;

	bool visible;
	bool deleted;
	glm::vec2 backgroundPos;
	int backgroundDX;
	int backgroundDY;
};
#endif