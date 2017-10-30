#include "CollisionSensor.h"

class AbstractFactory
{
public:
	AbstractFactory();
	virtual CollisionSensor createCollisionSensor() = 0;
	~AbstractFactory();
};

