/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "sprite_renderer.h"
#include <iostream>
#include "ResourceManager.h"

SpriteRenderer::SpriteRenderer(Shader &shader)
{
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, GLfloat transparent)
{
	// Prepare transformations
	this->shader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finally translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);

	// Render textured quad
	this->shader.SetVector4f("spriteColor", glm::vec4(color,transparent));

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::DrawLine(std::vector<glm::vec2> vecs, GLfloat size, Texture2D &texture)
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
	this->shader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(vecs.at(2), 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finally translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * 2, 0.5f * 2, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * 2, -0.5f * 2, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(1,1, 1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);

	// Render textured quad
	this->shader.SetVector4f("spriteColor", glm::vec4(100,100,100,1));
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

void SpriteRenderer::initRenderData()
{
	// Configure VAO/VBO
	GLuint VBO;
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
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}