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

#include "observerhandler.h"
#include "ColliderObserver.h"
#include "CheckBoundsObserver.h"

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

void ballColl2(Sprite *Ball, Sprite *Player)
{
	//check for collidition between ball and paddle
	if (Ball->collide(Player))
	{
		std::cout << "collision\n";
		//spriteMap["Paddle"]->setDX(-(spriteMap["Paddle"]->getDX()));
	}
}

void checkCols(Sprite *s, int w, int h)
{
	s->checkBounds(w, h);
}

int main(int argc, char *argv[])
{
	Scene mainScene(800, 600);
	mainScene.Init();

	ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("textures/face.png",true,"face");
	Sprite *Player = new Sprite("Paddle",mainScene, glm::vec2(600,300), glm::vec2(50, 10), "textures/paddle.png");
	Sprite *Ball = new Sprite("Ball",mainScene, glm::vec2(350,300), glm::vec2(50,50), "textures/face.png");

	Player->setCollideDebug(true);
	//Player->removeCollider("default");
	//Player->addCircleCollider("t", 50, 0, 0);

	//Ball->setSpeed(.1);
	Ball->setMoveAngle(90);
	//Ball->setState("Stuck", true);
	Ball->setBoundAction("BOUNCE");
	Player->setBoundAction("BOUNCE");
	Ball->setCollideDebug(true);
	Ball->removeCollider("default");
	//Ball->addBoxCollider("test",50,50,50,100);
	//Ball->addBoxCollider("test", 50, 50, -50, -100);
	Ball->addCircleCollider("f", 60, 0, 0);

	ObserverHandler *test = ObserverHandler::getInstance();
	ColliderObserver *colTest = new ColliderObserver(ballColl2, Ball, Player);

	for (int i = 0; i < 20; i++)
	{
		Sprite *temp2 = new Sprite("Ball", mainScene, glm::vec2(350 + (i*10), 300 + (i*10)), glm::vec2(i, i), "textures/face.png",glm::vec3(1.0f),glm::vec2(i,i));
		ColliderObserver *temp = new ColliderObserver(ballColl2, temp2, Player);
		CheckBoundsObserver *temp3 = new CheckBoundsObserver(checkCols, temp2, mainScene.Width, mainScene.Height);
		temp2->addForce((i * 1), i);
		temp2->setBoundAction("BOUNCE");
		test->addObserver(*temp);
	}
	test->addObserver(*colTest);
	
	mainScene.Start();
	
	

	return 0;
}