#include "ParticleRenderer.h"
#include "ResourceManager.h"

ParticleRenderer::ParticleRenderer(std::string shaderName)
{
	this->shader = ResourceManager::GetShader(shaderName);
	this->initRenderData();
}

void ParticleRenderer::DrawParticle(Texture2D & texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, GLfloat transparent)
{
	this->shader.SetVector2f("offset", position);
	this->shader.SetVector4f("color", glm::vec4(color, transparent));
	texture.Bind();
	//glBindVertexArray(particleVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void ParticleRenderer::initRenderData()
{
}

ParticleRenderer::~ParticleRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}