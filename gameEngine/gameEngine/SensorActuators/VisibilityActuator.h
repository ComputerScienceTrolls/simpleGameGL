#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class VisibilityActuator : public AbstractActuator
{
public:
	VisibilityActuator(std::string name, AbstractSprite *s, bool);
	VisibilityActuator(std::string name, DrawSceneObject* dso, bool);
	VisibilityActuator(std::string name, DrawSceneObject* dso, char *con);
	virtual void run();
	~VisibilityActuator();

private:
	AbstractSprite *sprite;
	DrawSceneObject *dso;
	bool state;
	std::string con;
};

