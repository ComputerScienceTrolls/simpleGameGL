#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class PositionActuator : public AbstractActuator
{
public:
	PositionActuator(AbstractSprite*, int newX, int newY);
	PositionActuator(AbstractSprite*, int newX, std::string condition);
	PositionActuator(AbstractSprite*, std::string condition);
	void run();
	~PositionActuator();

private:
	AbstractSprite *sprite;
	int x;
	int y;
	int d;
	std::string condition;
};

