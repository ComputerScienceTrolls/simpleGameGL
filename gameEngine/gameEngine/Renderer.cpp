/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Renderer.h"
#include <iostream>

Renderer::Renderer(Shader &shader, std::string type)
{
	if (type == "sprite")
	{
		this->spriteShader = shader;
	}
	else if (type == "particle")
	{
		this->particleShader = shader;
	}
	this->initRenderData();
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Renderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, GLfloat transparent)
{
	// Prepare transformations
	this->spriteShader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finally translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	this->spriteShader.SetMatrix4("model", model);

	// Render textured quad
	this->spriteShader.SetVector4f("spriteColor", glm::vec4(color,transparent));

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
void Renderer::DrawLine(std::vector<glm::vec2> vecs, GLfloat size, Texture2D &texture)
{
	// Prepare transformations
	
	/*glLineWidth(size);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE);
	for (int i = 0; i < vecs.size(); i++)
	{
		glVertex3f(vecs.at(i).x, vecs.at(i).y, 5);
	}
	glEnd()
	*/
	//int numberOfVecs = vecs.size();
	//GLuint vertexbuffer;
	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, vecs.size(), &vecs, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	this->spriteShader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(vecs.at(2), 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finally translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * 2, 0.5f * 2, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * 2, -0.5f * 2, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(1,1, 1.0f)); // Last scale

	this->spriteShader.SetMatrix4("model", model);

	// Render textured quad
	this->spriteShader.SetVector4f("spriteColor", glm::vec4(100,100,100,1));
	// Draw the line !
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->quadVAO);
	texture.Bind();
	glDrawArrays(GL_LINES, 0, vecs.size()); // 2 indices for the 2 end points of 1 line
	glBindVertexArray(0);

	//glDisableVertexAttribArray(0);


	//this->shader.SetVector3f("lineColor", glm::vec3(glm::vec3(0)));
	//glActiveTexture(GL_TEXTURE0);
	//texture.Bind();
	//glBindVertexArray(this->quadVAO);
	//glDrawArrays(GL_LINES, 0, vecs.size());
	//glBindVertexArray(0);

}

void Renderer::DrawParticle(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, GLfloat transparent, float life)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	particleShader.Use();
	if (life > 0.0f)
	{
		particleShader.SetVector2f("offset", position);
		particleShader.SetVector4f("color", glm::vec4(color,transparent));
		texture.Bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::setParticleShader(Shader &shader)
{
	this->particleShader = shader;
}

void Renderer::initRenderData()
{
	// Configure VAO/VBO
	GLuint SVBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &SVBO);

	glBindBuffer(GL_ARRAY_BUFFER, SVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Set up mesh and attribute properties
	GLuint VBO;
	GLfloat particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// Set mesh attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
}