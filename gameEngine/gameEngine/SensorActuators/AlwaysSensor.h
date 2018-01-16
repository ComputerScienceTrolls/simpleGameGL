#include "AbstractSensor.h"

class AlwaysSensor :  public AbstractSensor
{
public:
	AlwaysSensor();
	virtual void sense();
	~AlwaysSensor();
};

