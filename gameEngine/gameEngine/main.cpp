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


// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

int main(int argc, char *argv[])
{
	Scene mainScene(800, 600);
	mainScene.Init();

	ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("textures/face.png",true,"face");
	Sprite *Player = new Sprite("Paddle",mainScene, glm::vec2(400,300), glm::vec2(50, 10), "textures/paddle.png");
	Sprite *Ball = new Sprite("Ball",mainScene, glm::vec2(300,250), glm::vec2(25,25), "textures/face.png");

	Ball->setSpeed(.5);
	Ball->setMoveAngle(90);
	Ball->setState("Stuck", true);
	Ball->setBoundAction("BOUNCE");
	Player->setBoundAction("BOUNCE");
	Ball->setCollideDebug(true);
	Ball->addBoxCollider("test", 100, 100, 0, 0);

	
	mainScene.Start();
	
	

	return 0;
}