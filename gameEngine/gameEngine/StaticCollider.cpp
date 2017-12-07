#include "StaticCollider.h"


StaticCollider::StaticCollider()
{
}


StaticCollider::~StaticCollider()
{
}

void StaticCollider::setType(std::string newType)
{
	this->type = newType;
}

std::string StaticCollider::getType()
{
	return this->type;
}
