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

#include "SensorActuators\CameraActuator.h"

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


void ColSpriteTest(Sprite *Ball, AbstractCollider *test)
{
	//check for collidition between ball and paddle
	if (test->collide(Ball))
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
	//Sprite *trigger = new Sprite("trigger",mainScene);
	Ball->removeCollider("default");
	BoxCollider *test55 = new BoxCollider("test44", mainScene, 50, 50, 100, 300);
	CircleCollider *test66 = new CircleCollider("test66", mainScene, 50, 200, 200);

	test66->addForce(0, 1);
	//Player->removeCollider("default");
	//test55->addForce(270, .5);
	//trigger->addBoxCollider("test", 50, 50,150,250);
	//trigger->addForce(0, 2);
	//trigger->addCircleCollider("test2", 50, 10, 40);
	//Ball->addForce(270, 1);
	//Player->addForce(270, 1);
	//trigger->addStaticBoxCollider("test3", 50, 40, 100, 400);
	//trigger->addStaticCircleCollider("test4", 20, 100, 100);
	//trigger->addBoxCollider("test5", 600, 4, 0, 550);
	//trigger->setSpeed(.5);
	//trigger->setCollideDebug(true);
	Player->addCircleCollider("test", 50, 0, 0);
	Player->setCollideDebug(true);
	Ball->setCollideDebug(true);
	//Ball->setState("Stuck", true);
	//Ball->setBoundAction("BOUNCE");
	//Ball->addBoxCollider("test",50,50,50,100);
	//Ball->addBoxCollider("test", 50, 50, -50, -100);

	//Ball->addCircleCollider("f", 50, 50, 50);

	ObserverHandler *test = ObserverHandler::getInstance();
	ColliderObserver *colTest = new ColliderObserver("uh", ColSpriteTest, Player, test66);
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
	KeyboardSensor *kg = new KeyboardSensor("space", GLFW_KEY_G, "clicked");
	KeyboardSensor *kh = new KeyboardSensor("space", GLFW_KEY_H, "clicked");
	//CollisionSensor *t2 = new CollisionSensor("colSensor1", Player, trigger);
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
	CameraActuator *z = new CameraActuator("z", mainScene.getCamera(), 2, "zoom");
	CameraActuator *z2 = new CameraActuator("z2", mainScene.getCamera(), .5, "zoom");
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
	kg->addActuator(z);
	kh->addActuator(z2);
	kUp->addActuator(mUp);
	kDown->addActuator(mDown);
	cKeydown->addActuator(cDown);
	cKeyLeft->addActuator(cLeft);
	cKeyRight->addActuator(cRight);
	cKeyUp->addActuator(cUp);
	//t2->addActuator(m2);
	SceneDirector::getInstance()->addSensor(kSpace);
	SceneDirector::getInstance()->addSensor(kArrowLeft);
	SceneDirector::getInstance()->addSensor(kArrowRight);
	mainScene.addSensor(kLeft);
	mainScene.addSensor(kRight);
	mainScene.addSensor(kUp);
	mainScene.addSensor(kDown);
	//mainScene.addSensor(t2);
	mainScene.addSensor(cKeydown);
	mainScene.addSensor(cKeyUp);
	mainScene.addSensor(cKeyRight);
	mainScene.addSensor(kg);
	mainScene.addSensor(kh);
	mainScene.addSensor(cKeyLeft);
	mainScene.addObserver(colTest);

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

	//col test scene
	Sprite *colTester1 = new Sprite("colTester1", testScene, glm::vec2(100, 100), glm::vec2(50, 10), "textures/paddle.png", glm::vec2(0, -1));
	Sprite *colTester2 = new Sprite("colTester2", testScene, glm::vec2(500, 500), glm::vec2(50, 10), "textures/paddle.png", glm::vec2(0, 1));
	BoxCollider *colTester3 = new BoxCollider("colTester3", testScene, 50, 50, 500, 100);
	CircleCollider *colTester4 = new CircleCollider("colTester4", testScene, 50, 100, 500);
	BoxCollider *colTester5 = new BoxCollider("colTester5", testScene, 25, 25, 300, 100);
	BoxCollider *colTester6 = new BoxCollider("colTester6", testScene, 25, 25, 300, 300);
	CircleCollider *colTester7 = new CircleCollider("colTester7", testScene, 25, 200, 100);
	CircleCollider *colTester8 = new CircleCollider("colTester8", testScene, 25, 200, 200);

	colTester1->setBoundAction("BOUNCE");
	colTester2->setBoundAction("BOUNCE");
	colTester3->setBoundAction("BOUNCE");
	colTester4->setBoundAction("BOUNCE");
	colTester5->setBoundAction("BOUNCE");
	colTester6->setBoundAction("BOUNCE");
	colTester7->setBoundAction("BOUNCE");
	colTester8->setBoundAction("BOUNCE");

	colTester3->setCenter(glm::vec2(500, 100));
	colTester4->setCenter(glm::vec2(100, 500));
	colTester2->removeCollider("default");
	colTester2->setCenter(glm::vec2(500, 500));
	colTester2->setCollideDebug(true);
	colTester2->addCircleCollider("tester2", 50, 0, 0);
	colTester3->addForce(270, 1);
	colTester1->setCollideDebug(true);
	colTester1->setCenter(glm::vec2(100, 100));
	colTester4->addForce(90, 1);
	colTester5->addForce(270, 1);
	colTester6->addForce(90, 1);
	colTester7->addForce(270, 1);
	colTester8->addForce(90, 1);

	//col test scene
	Sprite *colTester11 = new Sprite("colTester1", testScene, glm::vec2(100, 100), glm::vec2(50, 10), "textures/paddle.png", glm::vec2(0, -1));
	Sprite *colTester21 = new Sprite("colTester2", testScene, glm::vec2(500, 500), glm::vec2(50, 10), "textures/paddle.png", glm::vec2(0, 1));
	BoxCollider *colTester31 = new BoxCollider("colTester3", testScene, 50, 50, 500, 100);
	CircleCollider *colTester41 = new CircleCollider("colTester4", testScene, 50, 100, 500);
	BoxCollider *colTester51 = new BoxCollider("colTester5", testScene, 25, 25, 300, 100);
	BoxCollider *colTester61 = new BoxCollider("colTester6", testScene, 25, 25, 300, 300);
	CircleCollider *colTester71 = new CircleCollider("colTester7", testScene, 25, 200, 100);
	CircleCollider *colTester81 = new CircleCollider("colTester8", testScene, 25, 200, 200);

	colTester11->setBoundAction("BOUNCE");
	colTester21->setBoundAction("BOUNCE");
	colTester31->setBoundAction("BOUNCE");
	colTester41->setBoundAction("BOUNCE");
	colTester51->setBoundAction("BOUNCE");
	colTester61->setBoundAction("BOUNCE");
	colTester71->setBoundAction("BOUNCE");
	colTester81->setBoundAction("BOUNCE");

	colTester31->setCenter(glm::vec2(500, 100));
	colTester41->setCenter(glm::vec2(100, 500));
	colTester21->removeCollider("default");
	colTester21->setCenter(glm::vec2(500, 500));
	colTester21->setCollideDebug(true);
	colTester21->addCircleCollider("tester2", 50, 0, 0);
	colTester31->addForce(270, 1);
	colTester11->setCollideDebug(true);
	colTester11->setCenter(glm::vec2(100, 100));
	colTester41->addForce(90, 1);
	colTester51->addForce(270, 1);
	colTester61->addForce(90, 1);
	colTester71->addForce(270, 1);
	colTester81->addForce(90, 1);

	//col test scene
	Sprite *colTester111 = new Sprite("colTester1", testScene, glm::vec2(100, 100), glm::vec2(50, 10), "textures/paddle.png", glm::vec2(0, -1));
	Sprite *colTester211 = new Sprite("colTester2", testScene, glm::vec2(500, 500), glm::vec2(50, 10), "textures/paddle.png", glm::vec2(0, 1));
	BoxCollider *colTester311 = new BoxCollider("colTester3", testScene, 50, 50, 500, 100);
	CircleCollider *colTester411 = new CircleCollider("colTester4", testScene, 50, 100, 500);
	BoxCollider *colTester511 = new BoxCollider("colTester5", testScene, 25, 25, 300, 100);
	BoxCollider *colTester611 = new BoxCollider("colTester6", testScene, 25, 25, 300, 300);
	CircleCollider *colTester711 = new CircleCollider("colTester7", testScene, 25, 200, 100);
	CircleCollider *colTester811 = new CircleCollider("colTester8", testScene, 25, 200, 200);

	colTester111->setBoundAction("BOUNCE");
	colTester211->setBoundAction("BOUNCE");
	colTester311->setBoundAction("BOUNCE");
	colTester411->setBoundAction("BOUNCE");
	colTester511->setBoundAction("BOUNCE");
	colTester611->setBoundAction("BOUNCE");
	colTester711->setBoundAction("BOUNCE");
	colTester811->setBoundAction("BOUNCE");

	colTester311->setCenter(glm::vec2(500, 100));
	colTester411->setCenter(glm::vec2(100, 500));
	colTester211->removeCollider("default");
	colTester211->setCenter(glm::vec2(500, 500));
	colTester211->setCollideDebug(true);
	colTester211->addCircleCollider("tester2", 50, 0, 0);
	colTester311->addForce(270, 1);
	colTester111->setCollideDebug(true);
	colTester111->setCenter(glm::vec2(100, 100));
	colTester411->addForce(90, 1);
	colTester511->addForce(270, 1);
	colTester611->addForce(90, 1);
	colTester711->addForce(270, 1);
	colTester811->addForce(90, 1);

	for (int i = 0; i < 25; i++)
	{
		new Sprite("colTester2", testScene, glm::vec2(500, 500), glm::vec2(50, 10), "textures/paddle.png", glm::vec2(0, 1));
	}

	CollisionSensor *t1 = new CollisionSensor("colSensor1", colTester2, colTester3, true);
	CollisionSensor *t2 = new CollisionSensor("colSensor2", colTester1, colTester4, true);
	CollisionSensor *t3 = new CollisionSensor("colSensor3", colTester5, colTester6, true);
	CollisionSensor *t4 = new CollisionSensor("colSensor4", colTester7, colTester8, true);
	MotionActuator *m1 = new MotionActuator("m1", colTester1, "flip");
	MotionActuator *m3 = new MotionActuator("m2", colTester2, "flip");
	MotionActuator *m4 = new MotionActuator("m3", colTester3, "flip");
	MotionActuator *m5 = new MotionActuator("m4", colTester4, "flip");
	MotionActuator *m6 = new MotionActuator("m6", colTester5, "flip");
	MotionActuator *m7 = new MotionActuator("m7", colTester6, "flip");
	MotionActuator *m8 = new MotionActuator("m8", colTester7, "flip");
	MotionActuator *m9 = new MotionActuator("m9", colTester8, "flip");

	t1->addActuator(m3);
	t1->addActuator(m4);
	t2->addActuator(m1);
	t2->addActuator(m5);
	t3->addActuator(m6);
	t3->addActuator(m7);
	testScene.addSensor(t1);
	testScene.addSensor(t2);
	
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