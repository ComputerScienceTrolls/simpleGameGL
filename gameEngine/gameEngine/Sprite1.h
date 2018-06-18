#pragma once
#include "Sprite.h"

class Sprite1 : public Sprite
{
public:
	Sprite1();
	Sprite1(std::string name, AbstractScene &scene, glm::vec2 pos, glm::vec2 size, GLchar* texture, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f));
	~Sprite1();
};

