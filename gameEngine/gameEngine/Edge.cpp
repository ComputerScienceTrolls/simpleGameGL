#include "Edge.h"

Edge::Edge(glm::vec2 p0, glm::vec2 p1, glm::vec2 d) :
	point1(p0), point2(p1), dir(d)
{
}

glm::vec2 Edge::getDir()
{
	return this->dir;
}

Edge::~Edge()
{
}
