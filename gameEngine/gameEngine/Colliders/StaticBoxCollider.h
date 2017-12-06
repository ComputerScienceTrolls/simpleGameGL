#pragma once
#include "AbstractCollider.h"
#include "../ResourceManager.h"

class StaticBoxCollider : public AbstractCollider
{
public:
	StaticBoxCollider(std::string name, int w, int h, int posX, int posY);
	virtual bool collide(std::vector<AbstractCollider*>);
	virtual void Draw(SpriteRenderer &renderer, glm::vec2);
	~StaticBoxCollider();

private:
	GLfloat transparency;
};

