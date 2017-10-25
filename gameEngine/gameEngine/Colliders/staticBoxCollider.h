#pragma once
#include "collider.h"
class staticBoxCollider : public collider
{
public:
	staticBoxCollider(std::string name, int w, int h, int posX, int posY);
	virtual bool collide(std::vector<collider*>);
	virtual std::string getType();
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPosX();
	virtual int getPosY();
	virtual std::string getName();
	~staticBoxCollider();

private:
	int width;
	int height;
	int posXOffset;
	int posYOffset;
	std::string type;
	std::string name;
};

