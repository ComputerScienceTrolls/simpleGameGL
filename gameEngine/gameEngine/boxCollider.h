#pragma once
#include "collider.h"

class boxCollider : public collider
{
	class Sprite;
public:
	boxCollider (int w, int h);
	boxCollider(int w, int h, int posX, int posY);
	virtual bool collide();
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPosX();
	virtual int getPosY();
	~boxCollider();

private:
	int offsetH;
	int offsetW;
	int posXOffset;
	int posYOffset;
};

