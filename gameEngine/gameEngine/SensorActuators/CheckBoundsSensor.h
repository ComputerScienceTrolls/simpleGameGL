#include "AbstractSensor.h"
#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class CheckBoundsSensor : public AbstractSensor
{
public:
	CheckBoundsSensor(AbstractSprite* one, int w, int h);
	void sense();
	void addActuator(AbstractActuator*);
	~CheckBoundsSensor();

private:
	AbstractSprite *sprite;
	int screenW;
	int screenH;
	std::vector<AbstractActuator*> actuators;
};

