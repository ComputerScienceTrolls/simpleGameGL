#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "ResourceManager.h"
#include <math.h>

#include <iostream>
#include <vector>
#include <map>

#include "AbstractSprite.h"
#include "Colliders/boxCollider.h"
#include "Colliders/circleCollider.h"
#include "Colliders/staticBoxCollider.h"
#include "Colliders/staticCircleCollider.h"
#include "Scene.h"

#pragma once
class Scene;
class Sprite : AbstractSprite
{
public:
	// Object state
	//glm::vec2   Position, Size, Velocity;
	//glm::vec3   Color;
	//GLfloat     Rotation;
	GLboolean   IsSolid;
	GLboolean   Destroyed;
	// Constructor(s)
	Sprite();
	Sprite(std::string name, Scene &scene, glm::vec2 pos, glm::vec2 size, GLchar* texture, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
	bool collide(AbstractSprite * otherSprite);
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
	virtual glm::vec2 getPosition();
	virtual glm::vec2 getCenter();
	virtual glm::vec2 getSize();
	virtual Texture2D getTexture();
	virtual glm::vec2 getVelocity();
	virtual glm::vec3 getColor();
	virtual GLfloat getRotation();
	virtual std::vector<collider*> getColliders();
	virtual std::string getName();
	virtual GLfloat getDX();
	virtual GLfloat getDY();
	virtual void setPosition(glm::vec2);
	virtual void setCenter(glm::vec2);
	virtual void setSize(glm::vec2);
	virtual void setTexture(Texture2D);
	virtual void setVelocity(glm::vec2);
	virtual void setColor(glm::vec3);
	virtual void setRotation(GLfloat);
	virtual void setColliders(std::vector<collider*>);
	virtual void setName(std::string);
	virtual void addBoxCollider(std::string name, int w, int h, int posX, int posY);
	virtual void setColliderPredictive(std::string name, bool predictive);
	virtual void addBoxCollider(std::string name, int w, int h);
	virtual void addStaticBoxCollider(std::string name, int w, int h, int posX, int posY);
	virtual void addCircleCollider(std::string name, double r, int posX, int posY);
	virtual void addStaticCircleCollider(std::string name, double r, int posX, int posY);
	virtual void removeCollider(std::string name);
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
	glm::vec2   Position, Size, Velocity, Center;
	Texture2D	Texture;
	glm::vec3   Color;
	GLfloat     Rotation;
	std::map<std::string , bool> states;
	std::string boundAction;
	Scene *parentScene;
	std::string name;
	

};

