#include "AbstractSensor.h"

class AlwaysSensor :  public AbstractSensor
{
public:
	AlwaysSensor();
	AlwaysSensor(std::string name);
	virtual void sense();
	~AlwaysSensor();
};

