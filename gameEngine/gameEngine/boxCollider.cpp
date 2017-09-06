#include "boxCollider.h"


boxCollider::boxCollider(int w, int h) :
	offsetW(w), offsetH(h), posXOffset(0), posYOffset(0), type("box")
{

}

boxCollider::boxCollider(int w, int h, int posX, int posY) :
	offsetW(w), offsetH(h), posXOffset(posX), posYOffset(posY), type("box")
{

}

bool boxCollider::collide()
{
	return false;
}

int boxCollider::getWidth()
{
	return offsetW;
}

int boxCollider::getHeight()
{
	return offsetH;
}

int boxCollider::getPosX()
{
	return posXOffset;
}

int boxCollider::getPosY()
{
	return posYOffset;
}

std::string boxCollider::getType()
{
	return type;
}

boxCollider::~boxCollider()
{
}
