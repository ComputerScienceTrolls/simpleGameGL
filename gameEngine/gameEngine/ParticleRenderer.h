#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"

class ParticleRenderer
{
public:
	ParticleRenderer(Shader &shader);
	void DrawParticle(Texture2D &texture, glm::vec2 pos, glm::vec2 size, GLfloat rotate, glm::vec3 color, GLfloat transparent);
	~ParticleRenderer();

private:
	Shader shader;
	GLuint quadVAO;
	void initRenderData();
};

