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

#include "Observers/observerhandler.h"
#include "Observers/ColliderObserver.h"
#include "Observers/CheckBoundsObserver.h"
#include "Observers/CollisionGroupObserver.h"




// Example 2 ---------------------------------------------------------

#include "alut.h"
#include <cstdlib>
#include <conio.h>
#include "al.h"
#include "alc.h"

using namespace std;


// Buffers to hold sound data.
ALuint Buffer;

// Sources are points of emitting sound.
ALuint Source;

/*
* These are 3D cartesian vector coordinates. A structure or class would be
* a more flexible of handling these, but for the sake of simplicity we will
* just leave it as is.
*/

// Position of the source sound.
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

// Velocity of the source sound.
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };

// Position of the Listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// Velocity of the Listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
// Also note that these should be units of '1'.
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

/*
* ALboolean LoadALData()
*
*         This function will load our sample data from the disk using the Alut
*         utility and send the data into OpenAL as a buffer. A source is then
*         also created to play that buffer.
*/
ALboolean LoadALData()
{


	Buffer = alutCreateBufferFromFile("wavdata/CrowNoise.wav");
	// Bind the buffer with the source.
	alGenSources(1, &Source);

	alSourcei(Source, AL_BUFFER, Buffer);


	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alSourcei(Source, AL_BUFFER, Buffer);
	alSourcef(Source, AL_PITCH, 1.0);
	alSourcef(Source, AL_GAIN, 1.0);
	alSourcefv(Source, AL_POSITION, SourcePos);
	alSourcefv(Source, AL_VELOCITY, SourceVel);
	alSourcei(Source, AL_LOOPING, AL_TRUE);

	// Do another error check and return.
	if (alGetError() == AL_NO_ERROR)
		return AL_TRUE;

	return AL_FALSE;
}

/*
* void SetListenerValues()
*
*         We already defined certain values for the Listener, but we need
*         to tell OpenAL to use that data. This function does just that.
*/
void SetListenerValues()
{
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

/*
* void KillALData()
*
*         We have allocated memory for our buffers and sources which needs
*         to be returned to the system. This function frees that memory.
*/
void KillALData()
{
	alDeleteBuffers(1, &Buffer);
	alDeleteSources(1, &Source);
	alutExit();
}


//-----------------------------------------------------------------



// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Scene mainScene(800, 600);

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
	/*

	Scene mainScene(800, 600);

	mainScene.Init();

	ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("textures/face.png",true,"face");
	Sprite *Player = new Sprite("Paddle",mainScene, glm::vec2(0,0), glm::vec2(50, 10), "textures/paddle.png");
	Sprite *Ball = new Sprite("Ball",mainScene, glm::vec2(300,340), glm::vec2(60,60), "textures/face.png");
	//std::cout << Player->getPosition().x;
	//std::cout << "\n" << Player->getCenter().x;
	Player->setCollideDebug(true);
	Player->removeCollider("default");
	Player->addCircleCollider("test", 50, 0, 0);
	//Ball->addStaticCircleCollider("t", 50, 50, 100);
	Ball->addStaticBoxCollider("t2", 50, 50, 100,200);

	//Ball->setSpeed(.1);
	Ball->setMoveAngle(90);
	//Ball->setState("Stuck", true);
	//Ball->setBoundAction("BOUNCE");
	//Player->setBoundAction("BOUNCE");
	Ball->setCollideDebug(true);
	//Ball->removeCollider("default");
	//Ball->addBoxCollider("test",50,50,50,100);
	//Ball->addBoxCollider("test", 50, 50, -50, -100);
	//Ball->addCircleCollider("f", 80, 300, 10);

	ObserverHandler *test = ObserverHandler::getInstance();
	ColliderObserver *colTest = new ColliderObserver(ballColl2, Ball, Player);
	
	for (int i = 0; i < 15; i++)
	{
		Sprite *temp2 = new Sprite("Ball", mainScene, glm::vec2(350 + (i*10), 300 + (i*10)), glm::vec2(i, i), "textures/face.png",glm::vec3(1.0f),glm::vec2(i,i));
		//ColliderObserver *temp = new ColliderObserver(ballColl2, Player, Ball);
		//CheckBoundsObserver *temp3 = new CheckBoundsObserver(checkCols, temp2, mainScene.Width, mainScene.Height);
		temp2->addForce((i * 1), i);
		temp2->setBoundAction("BOUNCE");
		//test->addObserver(*temp);
	}
	CollisionGroupObserver *temp = new CollisionGroupObserver(ballColl3, Player, "Ball");
	test->addObserver(*temp);
	
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
	
	test->addObserver(*colTest);
	
	mainScene.Start();
	
	

	return 0;
}