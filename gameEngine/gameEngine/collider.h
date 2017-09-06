#pragma once

#include <iostream>

class collider
{
	class Sprite;
public:
	collider();
	virtual bool collide(Sprite *sprite) { return false; };
	virtual std::string getType() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getPosX() = 0;
	virtual int getPosY() = 0;

	//needed for circle collider
	virtual float getRadius() {return 0;};
	~collider();

};

