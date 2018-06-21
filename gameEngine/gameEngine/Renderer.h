/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Texture.h"
#include "Shader.h"


class Renderer
{
public:
	// Constructor (inits shaders/shapes)
	Renderer(Shader &shader, std::string type="sprite");
	// Destructor
	~Renderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f), GLfloat transparent = 1);
	void DrawLine(std::vector<glm::vec2> vecs, GLfloat size, Texture2D &texture);
	void DrawParticle(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, GLfloat transparent, float life);

	void setParticleShader(Shader &shader);

private:
	// Render state
	Shader spriteShader;
	Shader particleShader;
	GLuint quadVAO;
	GLuint VAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif
