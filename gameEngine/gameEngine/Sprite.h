#ifndef SPRITE_H
#define SPRITE_H

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
#include "Colliders/PolyCollider.h"
#include "AbstractScene.h"

class Sprite : public AbstractSprite
{
public:
	Sprite();
	Sprite(std::string n, AbstractScene &scene);
	Sprite(std::string name, AbstractScene &scene, glm::vec2 pos, glm::vec2 size, GLchar* texture, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f));
	virtual void Draw(SpriteRenderer &renderer);
	virtual bool collide(AbstractSprite *otherSprite);
	virtual bool collide(Sprite *otherSprite);
	virtual bool collide(AbstractCollider *otherCollider);
	virtual void Update();
	void hide();
	virtual void setCollideDebug(bool state);

	virtual Texture2D getTexture();
	virtual glm::vec3 getColor();
	virtual bool getVisible();
	virtual std::vector<AbstractCollider*> getColliders();
	virtual void setTexture(Texture2D);
	virtual void setColor(glm::vec3);
	virtual void setColliders(std::vector<AbstractCollider*>);
	virtual void setName(std::string);
	virtual void addBoxCollider(std::string name, int w, int h, int posX, int posY);
	virtual void addBoxCollider(std::string name, int w, int h);
	virtual void addCircleCollider(std::string name, double r, int posX, int posY);
	virtual void addPolyCollider(std::string name, std::vector<glm::vec2> verticies);
	virtual void removeCollider(std::string name);
	virtual void setVisible(bool);

	virtual void reset();
	virtual void reInit();
	~Sprite();

protected:
	glm::vec2	lastPosition, lastSize;
	float lastRotation;
	AbstractCollider *collider_;
	std::vector<AbstractCollider*> colliders_;
	Texture2D	Texture;
	bool collideDebug;
	bool visible;

private:
	glm::vec2   initPosition, initSize, initVelocity, initCenter;
	char* textureFile;
	glm::vec3   Color;
	Texture2D	initTexture;
	char* initTextureFile;
	glm::vec3 initColor;
	GLfloat initRotation;
	std::map<std::string , bool> states;
	GLfloat transparency;
	AbstractScene *parentScene;
	int resetCounter;

};

#endif