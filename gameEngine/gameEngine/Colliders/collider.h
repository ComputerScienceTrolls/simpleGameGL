#pragma once

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

//only Needed for poly collider
#include "Edge.h"

class collider
{
	class SpriteRender;
public:
	collider();
	virtual bool collide(std::vector<collider*>) { return false; };
	virtual std::string getType() = 0;
	virtual int getWidth() { return 0; }
	virtual int getHeight() { return 0; }
	virtual int getPosX() = 0;
	virtual int getPosY() = 0;
	virtual glm::vec2 getSpriteCenterPos() { return glm::vec2(0, 0); };
	virtual glm::vec2 getSpritePos() { return glm::vec2(0, 0); };
	virtual glm::vec2 getSpriteSize() { return glm::vec2(0, 0); };
	virtual std::string getName() = 0;

	//needed for poly collider
	virtual std::vector<double> project(glm::vec2) { return std::vector<double>(); }
	virtual std::vector<glm::vec2> getVerticies() { return std::vector<glm::vec2>(); }
	virtual std::vector<Edge*> getEdges() { return std::vector<Edge*>(); }
	virtual void updateVecs() {  }

	//needed for circle collider
	virtual float getRadius() {return 0;};
	~collider();

private:
	SpriteRender *render;
};

