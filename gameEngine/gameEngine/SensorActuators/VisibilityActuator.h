#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class VisibilityActuator : public AbstractActuator
{
public:
	VisibilityActuator(AbstractSprite *s, bool);
	virtual void run();
	~VisibilityActuator();

private:
	AbstractSprite *sprite;
	bool state;
};

