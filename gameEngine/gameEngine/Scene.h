#ifndef SCENE_H
#define SCENE_H

#include "AbstractScene.h"
#include "ResourceManager.h"
#include "sprite_renderer.h"
#include "AbstractSprite.h"
#include "SceneDirector.h"

#include "SensorActuators\AbstractSensor.h"

#include <vector>

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Scene : public AbstractScene
{
public:
	Scene(GLuint width, GLuint height);
	virtual void Start();
	virtual void Stop();
	~Scene();
	// Initialize game state (load all shaders/textures/levels)
	virtual void Init();
	virtual void Update(GLfloat dt);
	virtual void Render();
	std::vector<AbstractSprite*> getSprite(std::string name);
	std::vector<AbstractSprite*> Sprites;
	virtual GLFWwindow* getWindow();
	virtual void setWindow(GLFWwindow *newWindow);
	void addSensor(AbstractSensor*);
	virtual void setActive(bool state);
	virtual bool getActive();
	void setSize(int width, int height);
	int getWidth();
	int getHeight();
	void setWidth(int);
	void setHeight(int);
	void setBackground(char*);

private:
	std::map<std::string, AbstractSprite*> spriteMap;
	std::vector<AbstractSensor*> Sensors;
	GLFWwindow* window;
	bool active;
	int height;
	int width;
};
#endif