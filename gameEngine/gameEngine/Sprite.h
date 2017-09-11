#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "ResourceManager.h"
#include <math.h>

#include <iostream>
#include <vector>
#include <map>

#include "boxCollider.h"

#pragma once
class Scene;
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
	Sprite(Scene *scene, glm::vec2 pos, glm::vec2 size, Texture2D Texture, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
	bool collide(Sprite * otherSprite);
	void setVelocity(GLfloat dt);
	void update();
	void setState(std::string key, bool state);
	bool getState(std::string key);
	void setBoundAction(std::string newAction);
	void checkBounds(double screenWidth, double screenHeight);
	void hide();
	void setCollideDebug(bool state);
	void setDX(float newDx);
	void setDY(float newDy);
	void addForce(float angle, float mag);
	void calcSpeedAngle();
	void calcVector();
	void setSpeed(float newSpeed);
	void setImgAngle(float newAngle);
	void setMoveAngle(float newAngle);
	~Sprite();

private:
	collider *collider_;
	std::vector<collider*> colliders_;
	float dx;
	float dy;
	float speed;
	float moveAngle;
	float imgAngle;
	bool collideDebug;
	std::map<std::string , bool> states;
	std::string boundAction;
	

};

