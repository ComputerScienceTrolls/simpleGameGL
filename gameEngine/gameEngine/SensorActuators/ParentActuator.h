#include "AbstractActuator.h"
#include "../SceneObject.h"

class ParentActuator : AbstractActuator
{
public:
	ParentActuator(std::string name, SceneObject*p, SceneObject*c, std::string con);
	virtual void run();
	~ParentActuator();

private:
	SceneObject *parent;
	SceneObject *child;
	std::string condition;
};

