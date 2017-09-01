#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

#include <iostream>
#include <vector>

#include "boxCollider.h"

#pragma once
class Sprite
{
public:
	// Object state
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	GLfloat     Rotation;
	GLboolean   IsSolid;
	GLboolean   Destroyed;
	// Render state
	Texture2D	Texture;
	// Constructor(s)
	Sprite();
	Sprite(glm::vec2 pos, glm::vec2 size, Texture2D Texture, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
	bool collide(Sprite * otherSprite);
	~Sprite();

private:
	collider *collider_;
	std::vector<collider*> colliders_;
};

