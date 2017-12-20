#include "Edge.h"
#include <iostream>

Edge::Edge(glm::vec2 p0, glm::vec2 p1, glm::vec2 d) :
	point1(p0), point2(p1), dir(d)
{
}

//update dir, assuming the edges points have moved
void Edge::updateDir()
{
	glm::vec2 newDir = { point2Pos.x - point1Pos.x, point2Pos.y - point1Pos.y };
	dir = newDir;
}

glm::vec2 Edge::getDir()
{
	return this->dir;
}

void Edge::setPoint1(glm::vec2 newPoint)
{
	point1 = newPoint;
}

void Edge::setPoint2(glm::vec2 newPoint)
{
	point2 = newPoint;
}

void Edge::setPoint1Pos(glm::vec2 newPoint)
{
	point1Pos = newPoint;
}

void Edge::setPoint2Pos(glm::vec2 newPoint)
{
	point2Pos = newPoint;
}

glm::vec2 Edge::getPoint1()
{
	return this->point1;
}

glm::vec2 Edge::getPoint2()
{
	return this->point2;
}

glm::vec2 Edge::getPoint1Pos()
{
	return this->point1Pos;
}

glm::vec2 Edge::getPoint2Pos()
{
	return this->point2Pos;
}

Edge::~Edge()
{
}
