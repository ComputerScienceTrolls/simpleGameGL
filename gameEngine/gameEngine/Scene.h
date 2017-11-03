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

	// Game state
	GameState	State;
	GLuint	Width, Height;
	// Constructor/Destructor
	Scene(GLuint width, GLuint height);
	virtual void Start();
	virtual void Stop();
	~Scene();
	// Initialize game state (load all shaders/textures/levels)
	virtual void Init();
	// GameLoop
	virtual void ProcessInput(GLfloat dt);
	virtual void Update(GLfloat dt);
	virtual void Render();
	std::vector<AbstractSprite*> getSprite(std::string name);
	std::vector<AbstractSprite*> Sprites;
	virtual GLFWwindow* getWindow();
	virtual void setWindow(GLFWwindow *newWindow);
	void addSensor(AbstractSensor*);

private:
	std::map<std::string, AbstractSprite*> spriteMap;
	std::vector<AbstractSensor*> Sensors;
	GLFWwindow* window;
};
#endif