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

}

Scene::Scene(GLuint width, GLuint height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(width, height, "HelloWorld", nullptr, nullptr);
	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	glfwSetKeyCallback(window, key_callback);

	// OpenGL configuration
	glViewport(0, 0, width, height);
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

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
}

void Scene::Update(GLfloat dt)
{

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
