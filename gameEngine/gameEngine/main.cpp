/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Sprite.h"


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

int main(int argc, char *argv[])
{
	Scene *mainScene = new Scene(800, 600);
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
	Sprite *Player = new Sprite(*mainScene, glm::vec2(10,10), glm::vec2(10, 10), ResourceManager::GetTexture("paddle"));

	mainScene->Start();
	std::cout << mainScene->Sprites.at(0)->Position.x;
	
	

	return 0;
}