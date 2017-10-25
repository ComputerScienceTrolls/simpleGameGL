/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "ResourceManager.h"
#include "sprite_renderer.h"
#include "Sprite.h"


// Game-related State data
SpriteRenderer  *Renderer;
Sprite      *Player;
Sprite		*Ball;


// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 12.5f;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("textures/face.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// Load levels
	GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
	GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
	GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
	GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;
	// Configure game objects
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new Sprite(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new Sprite(ballPos, glm::vec2(25,25), ResourceManager::GetTexture("face"));
	Ball->setSpeed(1);
	Ball->setMoveAngle(90);
	Ball->setState("Stuck", true);
	Ball->setBoundAction("BOUNCE");
	Player->setBoundAction("STOP");
	Ball->setCollideDebug(true);
}

void Game::Update(GLfloat dt)
{
	if (!Ball->getState("Stuck"))
	{	
		Ball->checkBounds(this->Width, this->Height);
		Ball->update();
	}
	Player->checkBounds(this->Width, this->Height);
	Player->update();
	CheckCollisions();

}

void Game::CheckCollisions()
{
	//checkcollisions for each block in the level
	for (int i = 0; i < this->Levels[this->Level].Bricks.size(); i++)
	{
		Sprite *currentBrick = &this->Levels[this->Level].Bricks[i];
		if (!currentBrick->Destroyed)
		{
			if (Ball->collide(currentBrick))
			{
				currentBrick->hide();
				//if (!currentBrick.IsSolid)
					//currentBrick.Destroyed = GL_TRUE;
			}
		}
	}
}


void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		// Move playerboard
		if (this->Keys[GLFW_KEY_A])
		{
			Player->Position.x -= 1;
			if (Ball->getState("Stuck"))
				Ball->Position.x -= 1;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			Player->Position.x += 1;
			if (Ball->getState("Stuck"))
				Ball->Position.x += 1;
		}
		if (this->Keys[GLFW_KEY_W])
		{
			Player->Position.y -= 1;
		}
		if (this->Keys[GLFW_KEY_S])
		{
			Player->Position.y += 1;
		}
		if (this->Keys[GLFW_KEY_SPACE])
			Ball->setState("Stuck", false);
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// Draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
		// Draw player
		Player->Draw(*Renderer);
		Ball->Draw(*Renderer);
	}
}