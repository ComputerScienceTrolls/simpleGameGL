#include "SensorActuatros\AbstractActuator.h"
#include "AbstractSprite.h"

class ActiveActuator : public AbstractActuator
{
public:
	ActiveActuator(AbstractSprite *s, bool con);
	virtual void run();
	~ActiveActuator();

private:
	AbstractSprite *sprite;
	bool state;
};

