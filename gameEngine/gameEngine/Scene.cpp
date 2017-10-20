#include "Scene.h"
#include "Sprite.h"
#include <iostream>

using namespace std;

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
//const GLuint SCREEN_WIDTH = 800;
// The height of the screen
//const GLuint SCREEN_HEIGHT = 600;
SpriteRenderer  *Renderer;

struct KeyHandler
{
	GLboolean Keys[1024];
}; 

KeyHandler keyHandler;

void Scene::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(Width, Height, "HelloWorld", nullptr, nullptr);
	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	glfwSetKeyCallback(window, key_callback);

	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));


	///* Test to see if works
	// Initialize OpenAL and clear the error bit. 
	alutInit(NULL, 0);
	//soundBuffer = alutCreateBufferHelloWorld();
	//alGenSources(1, &soundSource);
	alSourcei(soundSource, AL_BUFFER, soundBuffer);
	//alSourcePlay(soundSource);
	//std::cout << "uh";
	std::cout << this->loadWav("wavdata/CrowNoise.wav");
	std::cout << "\n";
	alSourcePlay(soundSource);
	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
}

Scene::Scene(GLuint width, GLuint height) :
	Width(width), Height(height), Keys()
{
	KeyHandler keyHandler;
	/*
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	*/
}

void Scene::Start()
{
	//setup SpriteMap
	for (int i = 0; i < Sprites.size(); i++)
	{
		spriteMap[Sprites.at(i)->getName()] = Sprites.at(i);
	}
	// OpenGL configuration
	glViewport(0, 0, Width, Height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Start Game within Menu State
	this->State = GAME_ACTIVE;


	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f;
		// Manage user input
		this->ProcessInput(deltaTime);

		// Update Game state
		this->Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		this->Render();

		glfwSwapBuffers(window);
	}
}

ALboolean Scene::loadWav(ALbyte *wavName)
{
	// Variables to load into.
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop = false;

	// Load wav data into a buffer.
	alGenBuffers(1, &soundBuffer);

	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	// Load any of your favourite wav song here
	alutCreateBufferFromFile(wavName);
	//alBufferData(soundBuffer, format, data, size, freq);
	//alutUnloadWAV(format, data, size, freq);

	// Bind the buffer with the source.
	alGenSources(1, &soundSource);

	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alSourcei(soundSource, AL_BUFFER, soundBuffer);
	alSourcef(soundSource, AL_PITCH, 1.0);
	alSourcef(soundSource, AL_GAIN, 1.0);
	//alSourcefv(soundSource, AL_POSITION, SourcePos);
	//alSourcefv(soundSource, AL_VELOCITY, soundSourceVel);
	alSourcei(soundSource, AL_LOOPING, loop);

	// Do another error check and return.
	if (alGetError() == AL_NO_ERROR)
		return AL_TRUE;

	return AL_FALSE;
}

void Scene::Stop()
{
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	alDeleteBuffers(1, &soundBuffer);
	alDeleteSources(1, &soundSource);
	alutExit();

	glfwTerminate();
}

void Scene::Update(GLfloat dt)
{
	//for each sprite in scene
	for (int i = 0; i < Sprites.size(); i++)
	{
		if (Sprites.at(i)->getState("active"))
		{
			Sprites.at(i)->update();
			Sprites.at(i)->checkBounds(Width, Height);
		}
	}
}

void Scene::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		// Move playerboard
		if (keyHandler.Keys[GLFW_KEY_A])
		{
			spriteMap["Paddle"]->addForce(180,.1f);
		}
		if (keyHandler.Keys[GLFW_KEY_D])
		{
			spriteMap["Paddle"]->addForce(0,.1f);
		}
		if (keyHandler.Keys[GLFW_KEY_W])
		{
			spriteMap["Paddle"]->addForce(90,.1f);
		}
		if (keyHandler.Keys[GLFW_KEY_S])
		{
			spriteMap["Paddle"]->addForce(270,.1f);
		}
		
	}
}

void Scene::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		//for each sprite in scene
		for (int i = 0; i < Sprites.size(); i++)
		{
			Sprites.at(i)->Draw(*Renderer);
			//Renderer->DrawSprite(Sprites.at(i)->getTexture(), Sprites.at(i)->getPosition(), Sprites.at(i)->getSize(), Sprites.at(i)->getRotation(), Sprites.at(i)->getColor());
		}
	}
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keyHandler.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			keyHandler.Keys[key] = GL_FALSE;
	}
}

Scene::~Scene()
{
}
