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

	ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
	Sprite *Player = new Sprite(mainScene, glm::vec2(10,10), glm::vec2(10, 10), ResourceManager::GetTexture("paddle"));
	return 0;
}