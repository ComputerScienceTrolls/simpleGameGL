#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class ActiveActuator : public AbstractActuator
{
public:
	ActiveActuator(std::string name, AbstractSprite *s, bool con);
	virtual void run();
	~ActiveActuator();

private:
	AbstractSprite *sprite;
	bool state;
};

