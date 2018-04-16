#include "AbstractCollider.h"

AbstractCollider::AbstractCollider()
{
}

std::string AbstractCollider::getType()
{
	return this->type;
}

AbstractCollider::~AbstractCollider()
{
}
