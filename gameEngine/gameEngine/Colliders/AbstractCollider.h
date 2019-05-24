#ifndef ABSTRACT_COLLIDER_H
#define ABSTRACT_COLLIDER_H

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include "../sprite_renderer.h"
#include "../MovingSceneObject.h"
#include "../DrawSceneObject.h"

//only Needed for poly collider
#include "Edge.h"

class AbstractSprite;
class AbstractCollider : virtual public MovingSceneObject, virtual public DrawSceneObject
{
	class SpriteRender;
public:
	AbstractCollider();
	virtual bool collide(std::vector<AbstractCollider*>) = 0;// { return false; };
	virtual bool collide(AbstractCollider*) = 0;// { return false; };
	virtual bool collide(AbstractSprite*) = 0;// { return false; };
	virtual glm::vec2 getSpriteCenterPos() { return glm::vec2(0, 0); };
	virtual glm::vec2 getSpritePos() { return glm::vec2(0, 0); };
	virtual glm::vec2 getSpriteSize() { return glm::vec2(0, 0); };

	//virtual void Draw(SpriteRenderer &renderer) = 0;
	//virtual void Update() {};

	//needed for poly collider
	virtual std::vector<double> project(glm::vec2) { return std::vector<double>(); }
	virtual std::vector<glm::vec2> getVerticies() { return std::vector<glm::vec2>(); }
	virtual std::vector<Edge*> getEdges() { return std::vector<Edge*>(); }
	virtual void updateVecs() {  }

	//needed for circle collider
	virtual float getRadius() {return 0;};

	//only in Abstract Collider
	virtual std::string getType();

	virtual AbstractCollider* clone() = 0;

	virtual ~AbstractCollider();

protected:
	std::string type;

private:
	SpriteRender *render;
};

#endif