#pragma once
#include "collider.h"
#include <iostream>

class boxCollider : public collider
{
	class SpriteRender;

public:
	boxCollider (int w, int h);
	boxCollider(int w, int h, int posX, int posY);
	virtual bool collide();
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPosX();
	virtual int getPosY();
	std::string getType();
	~boxCollider();

private:
	int offsetH;
	int offsetW;
	int posXOffset;
	int posYOffset;
	std::string type;
	SpriteRender *renderer;
};

