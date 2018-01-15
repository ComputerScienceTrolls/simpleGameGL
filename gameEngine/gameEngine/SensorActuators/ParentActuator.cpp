#include "ParentActuator.h"

ParentActuator::ParentActuator(std::string name, SceneObject * p, SceneObject * c, std::string con) :
	parent(p), child(c), condition(con)
{
}

void ParentActuator::run()
{
	if (condition == "attach")
	{
		child->setParent(parent);
	}
	if (condition == "detach")
	{
		parent->removeChild(child);
	}
}

ParentActuator::~ParentActuator()
{
}
