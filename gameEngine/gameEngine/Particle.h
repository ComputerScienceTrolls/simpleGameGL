#pragma once
#include "MovingSceneObject.h"
#include "DrawSceneObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture.h"

class Particle : virtual public MovingSceneObject, virtual public DrawSceneObject
{
public:
	Particle(MovingSceneObject *object, glm::vec2 offset, glm::vec2 size, GLchar* texture, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f), float life = 10);
	//Particle(int life);
	virtual void Update();
	virtual void Draw(Renderer &renderer);

	float getLife();
	float getDelta();

	void setLife(float);
	void setDelta(float);

	~Particle();

private:
	float life;
	float delta;
	Texture2D texture;
	glm::vec2 offset;
};

