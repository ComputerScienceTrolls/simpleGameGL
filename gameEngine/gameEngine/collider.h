#pragma once

#include <iostream>
#include <vector>

#include <glm/glm.hpp>


class collider
{
	class SpriteRender;
public:
	collider();
	virtual bool collide(std::vector<collider*>) { return false; };
	virtual std::string getType() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getPosX() = 0;
	virtual int getPosY() = 0;
	virtual glm::vec2 getSpritePos() = 0; //{ return glm::vec2(); };
	virtual glm::vec2 getSpriteSize() = 0; //{ return glm::vec2(); };

	//needed for circle collider
	virtual float getRadius() {return 0;};
	~collider();

private:
	SpriteRender *render;

};

