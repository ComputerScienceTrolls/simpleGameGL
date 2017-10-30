#include "collider.h"
#include "../AbstractSprite.h"
#include <iostream>
#include <vector>
class PolyCollider
{
public:
	PolyCollider();
	virtual bool collide(std::vector<collider*> otherColliders);
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPosX();
	virtual int getPosY();
	virtual bool getStaticState();
	virtual glm::vec2 getSpriteCenterPos();
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteSize();
	virtual std::string getName();
	std::string getType();
	~PolyCollider();

private:
	int offsetH;
	int offsetW;
	int posXOffset;
	int posYOffset;
	std::string type;
	std::string name;
	bool staticState;
	AbstractSprite *spriteParent;
};
