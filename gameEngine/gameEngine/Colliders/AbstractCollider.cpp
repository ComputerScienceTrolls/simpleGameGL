#include "AbstractCollider.h"

AbstractCollider::AbstractCollider()
{
}

std::string AbstractCollider::getType()
{
	return this->type;
}

std::string AbstractCollider::getName()
{
	return this->name;
}

AbstractCollider::~AbstractCollider()
{
}
