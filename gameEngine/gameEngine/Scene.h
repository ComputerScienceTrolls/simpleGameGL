#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ResourceManager.h"
#include "sprite_renderer.h"
#include "AbstractSprite.h"

#include "alut.h"
#include <cstdlib>

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
class Scene
{
public:

	// Game state
	GameState	State;
	GLboolean	Keys[1024];
	GLuint	Width, Height;
	// Constructor/Destructor
	Scene(GLuint width, GLuint height);
	void Start();
	void Stop();
	~Scene();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	ALboolean loadWav(ALbyte* fileName);
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	//void CheckCollisions();
	void Render();

	std::vector<AbstractSprite*> Sprites;
	GLFWwindow* window;

private:
	std::map<std::string, AbstractSprite*> spriteMap;
	std::map<std::string, ALuint> soundBuffers;
	ALuint soundBuffer;
	ALuint soundSource;
};
#endif