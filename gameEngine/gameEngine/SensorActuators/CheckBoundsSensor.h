#include "AbstractSensor.h"
#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class CheckBoundsSensor : public AbstractSensor
{
public:
	CheckBoundsSensor(std::string name, AbstractSprite* one, int w, int h);
	void sense();
	~CheckBoundsSensor();

private:
	AbstractSprite *sprite;
	int screenW;
	int screenH;
};

