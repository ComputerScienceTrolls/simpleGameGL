#pragma once
//#include "../StaticCollider.h"
#include "../ResourceManager.h"
#include "../SceneObject.h"
#include "AbstractCollider.h"

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

