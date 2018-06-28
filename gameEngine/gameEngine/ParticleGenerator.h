/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"
#include "MovingSceneObject.h"
#include "DrawSceneObject.h"
#include "Particle.h"


// ParticleGenerator acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class ParticleGenerator : public DrawSceneObject
{
public:
	// Constructor
	ParticleGenerator(Shader shader, Texture2D texture, GLuint amount);
	// Update all particles
	void Update(GLfloat dt, MovingSceneObject &object, GLuint newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	// Render all particles
	virtual void Draw(Renderer &renderer);
private:
	// State
	std::vector<Particle> particles;
	GLuint amount;
	// Render state
	Shader shader;
	Texture2D texture;
	GLuint VAO;
	// Initializes buffer and vertex attributes
	void init();
	// Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
	GLuint firstUnusedParticle();
	// Respawns particle
	void respawnParticle(Particle &particle, MovingSceneObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif