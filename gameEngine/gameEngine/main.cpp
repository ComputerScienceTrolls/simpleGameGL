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

#include "CameraActuator.h"

#include "Observers/observerhandler.h"
#include "Observers/Observer.h"
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
#include "SensorActuators\SceneActuator.h"

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Scene mainScene("main",2000, 600);
Scene testScene("test",700, 700);
Scene testScene2("test",700, 700);
Scene testScene3("test",700, 700);
Scene testScene4("test",700, 700);
Scene testScene5("test",700, 700);

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

void test9()
{
	std::cout << "test\n";
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

	//ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
	//ResourceManager::LoadTexture("textures/face.png",true,"face");
	Sprite *Player = new Sprite("Paddle",mainScene, glm::vec2(150,500), glm::vec2(50, 10), "textures/paddle.png");
	Sprite *Ball = new Sprite("Ball",mainScene, glm::vec2(300,340), glm::vec2(60,60), "textures/greenCircle.png");
	Sprite *Player2 = new Sprite("Paddle", testScene, glm::vec2(300, 500), glm::vec2(100, 10), "textures/paddle.png", glm::vec2(1,0));
	Sprite *trigger = new Sprite("trigger",mainScene);
	BoxCollider *test55 = new BoxCollider("collider", mainScene, 50, 10);
	trigger->addBoxCollider("test", 50, 50);
	//trigger->addCircleCollider("test2", 50, 10, 40);
	//Ball->addForce(270, 1);
	//Player->addForce(270, 1);
	//trigger->addStaticBoxCollider("test3", 50, 40, 100, 400);
	//trigger->addStaticCircleCollider("test4", 20, 100, 100);
	//trigger->addBoxCollider("test5", 600, 4, 0, 550);
	//trigger->setSpeed(.5);
	trigger->setCollideDebug(true);
	//Player->addCircleCollider("test", 10, 0, 0);
	Player->setCollideDebug(true);
	//Ball->addStaticCircleCollider("t", 50, 50, 100);
	//Ball->addStaticBoxCollider("t2", 50, 50, 100,200);

	//Ball->setState("Stuck", true);
	//Ball->setBoundAction("BOUNCE");
	//Ball->addBoxCollider("test",50,50,50,100);
	//Ball->addBoxCollider("test", 50, 50, -50, -100);
	//Ball->addCircleCollider("f", 80, 300, 10);

	ObserverHandler *test = ObserverHandler::getInstance();
	ColliderObserver *colTest = new ColliderObserver("uh",ballColl2, trigger, Player);
	Observer *simplyObserver = new Observer("observer1", test9);
	
	KeyboardSensor *kLeft = new KeyboardSensor("kleft", GLFW_KEY_A);
	KeyboardSensor *kRight = new KeyboardSensor("kright", GLFW_KEY_D);
	KeyboardSensor *kUp = new KeyboardSensor("kup", GLFW_KEY_W);
	KeyboardSensor *kDown = new KeyboardSensor("kdown", GLFW_KEY_S);
	KeyboardSensor *kArrowLeft = new KeyboardSensor("left",GLFW_KEY_LEFT);
	KeyboardSensor *kArrowRight = new KeyboardSensor("right",GLFW_KEY_RIGHT);
	KeyboardSensor *cKeyLeft = new KeyboardSensor("cleft", GLFW_KEY_KP_4);
	KeyboardSensor *cKeyRight = new KeyboardSensor("cright", GLFW_KEY_KP_6);
	KeyboardSensor *cKeyUp = new KeyboardSensor("cup", GLFW_KEY_KP_8);
	KeyboardSensor *cKeydown = new KeyboardSensor("cdown", GLFW_KEY_KP_5);
	KeyboardSensor *kSpace = new KeyboardSensor("space", GLFW_KEY_SPACE, "clicked");
	CollisionSensor *t2 = new CollisionSensor("colSensor1", Player,trigger);
	//CheckBoundsSensor *t2 = new CheckBoundsSensor(Player, 800, 600);
	MotionActuator *m2 = new MotionActuator("motion1", Player,"flip");
	MotionActuator *mLeft = new MotionActuator("motion2", Player, 180, .1, "force");
	MotionActuator *mRight = new MotionActuator("motion3", Player, 0, .1, "force");
	MotionActuator *mUp = new MotionActuator("motion4", Player, 90, .1, "force");
	MotionActuator *mDown = new MotionActuator("motion5", Player, 270, .1, "force");
	CameraActuator *cLeft = new CameraActuator("cLeft", mainScene.getCamera(), 180, .1, "force");
	CameraActuator *cRight = new CameraActuator("cRight", mainScene.getCamera(),0,.1,"force");
	CameraActuator *cDown = new CameraActuator("cDown", mainScene.getCamera(), 270, .1, "force");
	CameraActuator *cUp = new CameraActuator("cUp", mainScene.getCamera(), 90, .1, "force");
	//PositionActuator *p1 = new PositionActuator(Player, 50,50);
	VisibilityActuator *v1 = new VisibilityActuator("visible1",Player, false);
	SceneActuator *s1 = new SceneActuator("scene1",&testScene, "next");
	SceneActuator *s2 = new SceneActuator("scene2",&mainScene, "previous");
	SceneActuator *s3 = new SceneActuator("scene3",&mainScene, "togglePause");
	//ActiveActuator *a1 = new ActiveActuator(Player, false);

	kSpace->addActuator(s3);
	kArrowLeft->addActuator(s1);
	kArrowRight->addActuator(s2);
	kLeft->addActuator(mLeft);
	kRight->addActuator(mRight);
	kUp->addActuator(mUp);
	kDown->addActuator(mDown);
	cKeydown->addActuator(cDown);
	cKeyLeft->addActuator(cLeft);
	cKeyRight->addActuator(cRight);
	cKeyUp->addActuator(cUp);
	t2->addActuator(m2);
	SceneDirector::getInstance()->addSensor(kSpace);
	SceneDirector::getInstance()->addSensor(kArrowLeft);
	SceneDirector::getInstance()->addSensor(kArrowRight);
	mainScene.addSensor(kLeft);
	mainScene.addSensor(kRight);
	mainScene.addSensor(kUp);
	mainScene.addSensor(kDown);
	mainScene.addSensor(t2);
	mainScene.addSensor(cKeydown);
	mainScene.addSensor(cKeyUp);
	mainScene.addSensor(cKeyRight);
	mainScene.addSensor(cKeyLeft);

	//testScene.setBackground("textures/face.png");
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
	//ColliderObserver *temp = new ColliderObserver("ballCol", ballColl2, Player, Ball);
	//mainScene.addObserver(temp);
	//mainScene.removeObserver("ballCol");

	
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
	SceneDirector::getInstance()->addScene(&testScene);
	SceneDirector::getInstance()->addScene(&testScene2);
	SceneDirector::getInstance()->addScene(&testScene3);
	SceneDirector::getInstance()->addScene(&testScene4);
	mainScene.setCameraHeight(500);
	mainScene.setCameraWidth(800);
	
	SceneDirector::getInstance()->Start();
	
	return 0;
}