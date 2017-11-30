#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class VisibilityActuator : public AbstractActuator
{
public:
	VisibilityActuator(std::string name, AbstractSprite *s, bool);
	virtual void run();
	~VisibilityActuator();

private:
	AbstractSprite *sprite;
	bool state;
};

