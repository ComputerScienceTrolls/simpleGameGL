#include "Scene.h"
#include "Sprite.h"

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
//const GLuint SCREEN_WIDTH = 800;
// The height of the screen
//const GLuint SCREEN_HEIGHT = 600;
SpriteRenderer  *Renderer;

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
}

Scene::Scene(GLuint width, GLuint height) :
	Width(width), Height(height)
{
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

void Scene::Stop()
{
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
}

void Scene::Update(GLfloat dt)
{
	//for each sprite in scene
	for (int i = 0; i < Sprites.size(); i++)
	{
		std::cout << "I dance on the graves of my enemies";
		Renderer->DrawSprite(Sprites.at(i)->Texture, Sprites.at(i)->Position, Sprites.at(i)->Size, Sprites.at(i)->Rotation, Sprites.at(i)->Color);
	}

}

void Scene::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
	}
}

void Scene::Render()
{
	if (this->State == GAME_ACTIVE)
	{

	}
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		//if (action == GLFW_PRESS)
			//Breakout.Keys[key] = GL_TRUE;
		//else if (action == GLFW_RELEASE)
			//Breakout.Keys[key] = GL_FALSE;
	}
}

Scene::~Scene()
{
}
