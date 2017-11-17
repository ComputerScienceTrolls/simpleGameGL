#include "AbstractSensor.h"
#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class CheckBoundsSensor : public AbstractSensor
{
public:
	CheckBoundsSensor(std::string, AbstractSprite* one, int w, int h);
	void sense();
	void addActuator(AbstractActuator*);
	std::string getName();
	void setName(std::string);
	~CheckBoundsSensor();

private:
	AbstractSprite *sprite;
	int screenW;
	int screenH;
	std::vector<AbstractActuator*> actuators;
	std::string name;
};

