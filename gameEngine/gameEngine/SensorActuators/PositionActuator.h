#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class PositionActuator : public AbstractActuator
{
public:
	PositionActuator(std::string name, AbstractSprite*, int newX, int newY);
	PositionActuator(std::string name, AbstractSprite*, int newX, std::string condition);
	PositionActuator(std::string name, AbstractSprite*, std::string condition);
	PositionActuator(std::string name, SceneObject*, SceneObject*);
	void run();
	~PositionActuator();

private:
	AbstractSprite *sprite;
	int x;
	int y;
	int d;
	std::string condition;
	SceneObject *one;
	SceneObject *two;
};

