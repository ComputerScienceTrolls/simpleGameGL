#pragma once
#include "AbstractCollider.h"
class StaticBoxCollider : public AbstractCollider
{
public:
	StaticBoxCollider(std::string name, int w, int h, int posX, int posY);
	virtual bool collide(std::vector<AbstractCollider*>);
	virtual std::string getType();
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPosX();
	virtual int getPosY();
	virtual std::string getName();
	~StaticBoxCollider();

private:
	int width;
	int height;
	int posXOffset;
	int posYOffset;
	std::string type;
	std::string name;
};

