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
#include "SceneDirector.h"
#include "Sprite.h"

#include "Observers/observerhandler.h"
#include "Observers/ColliderObserver.h"
#include "Observers/CheckBoundsObserver.h"
#include "Observers/CollisionGroupObserver.h"

#include "SensorActuators\MotionActuator.h"
#include "SensorActuators\PositionActuator.h"
#include "SensorActuators\CollisionSensor.h"
#include "SensorActuators\CheckBoundsSensor.h"
#include "SensorActuators\VisibilityActuator.h"
#include "SensorActuators\ActiveActuator.h"
#include "SensorActuators\KeyboardSensor.h"

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Scene mainScene(800, 600);
Scene testScene(800, 600);

void ballColl2(Sprite *Ball, Sprite *Player)
{
	//check for collidition between ball and paddle
	if (Ball->collide(Player))
	{
		//Player->setDX(-Player->getDX());
		std::cout << "collision";
		//spriteMap["Paddle"]->setDX(-(spriteMap["Paddle"]->getDX()));
	}
}

void ballColl3(Sprite *Player, std::string name)
{
	//get all instances of name and check for collision with given sprite
	std::vector<AbstractSprite*> tempVec = mainScene.getSprite(name);
	for (int i = 0; i < tempVec.size(); i++)
	{
		if (Player->collide(tempVec.at(i)))
		{
			//Player->setDX(-Player->getDX());
			std::cout << "collision";
			//spriteMap["Paddle"]->setDX(-(spriteMap["Paddle"]->getDX()));
		}
	}

}

void checkCols(Sprite *s, int w, int h)
{
	s->checkBounds(w, h);
}

int main(int argc, char *argv[])
{
	mainScene.Init();
	mainScene.initRenderer();

	ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("textures/face.png",true,"face");
	Sprite *Player = new Sprite("Paddle",mainScene, glm::vec2(150,500), glm::vec2(50, 10), "textures/paddle.png");
	Sprite *Ball = new Sprite("Ball",mainScene, glm::vec2(300,340), glm::vec2(60,60), "textures/face.png");
	//std::cout << Player->getPosition().x;
	//std::cout << "\n" << Player->getCenter().x;
	Player->setCollideDebug(true);
	Player->removeCollider("default");
	std::vector<glm::vec2> vecTest1;
	vecTest1.push_back(glm::vec2(10,10));
	vecTest1.push_back(glm::vec2(0, 20));
	vecTest1.push_back(glm::vec2(20, 20));
	std::vector<glm::vec2> vecTest2;
	vecTest2.push_back(glm::vec2(10, 10));
	vecTest2.push_back(glm::vec2(0, 20));
	vecTest2.push_back(glm::vec2(20, 20));
	Player->addPolyCollider("test1", vecTest1);
	Ball->addPolyCollider("test2", vecTest2);
	Ball->addForce(0, 3);
	//Player->addCircleCollider("test", 50, 0, 0);
	//Ball->addStaticCircleCollider("t", 50, 50, 100);
	//Ball->addStaticBoxCollider("t2", 50, 50, 100,200);

	//Ball->setSpeed(.1);
	Ball->setMoveAngle(90);
	//Ball->setState("Stuck", true);
	//Ball->setBoundAction("BOUNCE");
	Player->setBoundAction("BOUNCE");
	Ball->setCollideDebug(true);
	Ball->removeCollider("default");
	//Ball->addBoxCollider("test",50,50,50,100);
	//Ball->addBoxCollider("test", 50, 50, -50, -100);
	//Ball->addCircleCollider("f", 80, 300, 10);

	ObserverHandler *test = ObserverHandler::getInstance();
	ColliderObserver *colTest = new ColliderObserver(ballColl2, Ball, Player);
	
	KeyboardSensor *kLeft = new KeyboardSensor(GLFW_KEY_A);
	KeyboardSensor *kRight = new KeyboardSensor(GLFW_KEY_D);
	KeyboardSensor *kUp = new KeyboardSensor(GLFW_KEY_W);
	KeyboardSensor *kDown = new KeyboardSensor(GLFW_KEY_S);
	//CollisionSensor *t2 = new CollisionSensor(Player,Ball);
	//CheckBoundsSensor *t2 = new CheckBoundsSensor(Player, 800, 600);
	//MotionActuator *m2 = new MotionActuator(Player, .05,.05);
	MotionActuator *mLeft = new MotionActuator(Player, 180, .1, "force");
	MotionActuator *mRight = new MotionActuator(Player, 0, .1, "force");
	MotionActuator *mUp = new MotionActuator(Player, 90, .1, "force");
	MotionActuator *mDown = new MotionActuator(Player, 270, .1, "force");
	//PositionActuator *p1 = new PositionActuator(Player, 50,50);
	VisibilityActuator *v1 = new VisibilityActuator(Player, false);
	//ActiveActuator *a1 = new ActiveActuator(Player, false);

	kLeft->addActuator(mLeft);
	kRight->addActuator(mRight);
	kUp->addActuator(mUp);
	kDown->addActuator(mDown);
	mainScene.addSensor(kLeft);
	mainScene.addSensor(kRight);
	mainScene.addSensor(kUp);
	mainScene.addSensor(kDown);
	/*
	for (int i = 0; i < 5; i++)
	{
		Sprite *temp2 = new Sprite("Ball", mainScene, glm::vec2(350 + (i*70), 300 + (i*70)), glm::vec2(10 * i, 10 * i), "textures/face.png",glm::vec3(1.0f),glm::vec2(i,i));
		//ColliderObserver *temp = new ColliderObserver(ballColl2, Player, Ball);
		//CheckBoundsObserver *temp3 = new CheckBoundsObserver(checkCols, temp2, mainScene.Width, mainScene.Height);
		temp2->addForce((i * 1), i);
		temp2->setBoundAction("BOUNCE");
		CollisionSensor *t1 = new CollisionSensor(Player, temp2);
		MotionActuator *m1 = new MotionActuator(Player, "flip");
		t1->addActuator(m1);
		mainScene.addSensor(t1);
		//test->addObserver(*temp);
	}
	*/
	//CollisionGroupObserver *temp = new CollisionGroupObserver(ballColl3, Player, "Ball");
	test->addObserver(*colTest);
	
	/*
	for (int i = 0; i < 50; i++)
	{
		Sprite *temp2 = new Sprite("Ball", mainScene, glm::vec2(350 + (i * 10), 300 + (i * 10)), glm::vec2(i, i), "textures/face.png", glm::vec3(1.0f), glm::vec2(i, i));
		//ColliderObserver *temp = new ColliderObserver(ballColl2, temp2, Player);
		//CheckBoundsObserver *temp3 = new CheckBoundsObserver(checkCols, temp2, mainScene.Width, mainScene.Height);
		temp2->addForce((i * 1), i);
		temp2->setBoundAction("BOUNCE");
		//test->addObserver(*temp);
	}
	*/
	
	//test->addObserver(*colTest);
	AbstractScene *test4 = SceneDirector::getInstance()->getCurrentScene();
	test4->Start();
	
	return 0;
}