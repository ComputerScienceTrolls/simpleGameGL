#include "ParticleRenderer.h"

ParticleRenderer::ParticleRenderer(Shader &shader)
{
	this->shader = shader;
	this->initRenderData();
}

void ParticleRenderer::Init()
{
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

void ParticleRenderer::DrawParticle(Texture2D & texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, GLfloat transparent, float life)
{
	// Use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->shader.Use();
	{
		if (life > 0.0f)
		{
			this->shader.SetVector2f("offset", position);
			this->shader.SetVector4f("color", glm::vec4(color, transparent));
			texture.Bind();
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	// Don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleRenderer::initRenderData()
{
}

ParticleRenderer::~ParticleRenderer()
{
	glDeleteVertexArrays(1, &this->VAO);
}