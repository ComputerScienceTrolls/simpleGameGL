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
#include "Colliders/BoxCollider.h"
#include "Colliders/CircleCollider.h"
#include "Colliders/StaticBoxCollider.h"
#include "Colliders/StaticCircleCollider.h"
#include "Colliders/PolyCollider.h"
#include "AbstractScene.h"

#pragma once
class Sprite : public AbstractSprite
{
public:
	Sprite(std::string n, AbstractScene &scene);
	Sprite(std::string name, AbstractScene &scene, glm::vec2 pos, glm::vec2 size, GLchar* texture, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f));
	virtual void Draw(SpriteRenderer &renderer);
	virtual bool collide(AbstractSprite * otherSprite);
	virtual bool collide(Sprite * otherSprite);
	void setVelocity(GLfloat dt);
	virtual void update();
	void setState(std::string key, bool state);
	bool getState(std::string key);
	void setBoundAction(std::string newAction);
	bool checkBounds(double screenWidth, double screenHeight);
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
	virtual std::vector<AbstractCollider*> getColliders();
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
	virtual void setColliders(std::vector<AbstractCollider*>);
	virtual void setName(std::string);
	virtual void addBoxCollider(std::string name, int w, int h, int posX, int posY);
	virtual void addBoxCollider(std::string name, int w, int h);
	virtual void addStaticBoxCollider(std::string name, int w, int h, int posX, int posY);
	virtual void addCircleCollider(std::string name, double r, int posX, int posY);
	virtual void addStaticCircleCollider(std::string name, double r, int posX, int posY);
	virtual void addPolyCollider(std::string name, std::vector<glm::vec2> verticies);
	virtual void removeCollider(std::string name);
	virtual void setRenderPosX(int);
	virtual void setRenderPosY(int);
	virtual glm::vec2 getRenderPos();
	virtual void setRenderDX(int);
	virtual void setRenderDY(int);

	virtual void reset();
	virtual void reInit();
	~Sprite();

private:
	AbstractCollider *collider_;
	std::vector<AbstractCollider*> colliders_;
	float speed;
	float moveAngle;
	float imgAngle;
	bool collideDebug;
	glm::vec2   Position, Size, Velocity, Center, RenderPosition;
	glm::vec2   initPosition, initSize, initVelocity, initCenter;
	Texture2D	Texture;
	GLfloat dx;
	GLfloat dy;
	int renderDX;
	int renderDY;
	char* textureFile;
	glm::vec3   Color;
	GLfloat     Rotation;
	Texture2D	initTexture;
	char* initTextureFile;
	glm::vec3 initColor;
	GLfloat initRotation;
	std::map<std::string , bool> states;
	GLfloat transparency;
	std::string boundAction;
	AbstractScene *parentScene;
	std::string name;
	bool visible;
	bool active;
	int resetCounter;

};

