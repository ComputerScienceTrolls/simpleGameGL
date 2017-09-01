#pragma once
class collider
{
	class Sprite;
public:
	collider();
	virtual bool collide(Sprite *sprite) { return false; };
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getPosX() = 0;
	virtual int getPosY() = 0;
	~collider();

};

