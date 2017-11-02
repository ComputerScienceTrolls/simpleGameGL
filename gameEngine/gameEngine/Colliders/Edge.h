#pragma once

#include <glm/glm.hpp>

class Edge
{
public:
	Edge(glm::vec2 p0, glm::vec2 p1, glm::vec2 dir);
	glm::vec2 getDir();
	void setPoint1(glm::vec2 newPoint);
	void setPoint2(glm::vec2 newPoint);
	void setPoint1Pos(glm::vec2 newPoint);
	void setPoint2Pos(glm::vec2 newPoint);
	void updateDir();
	glm::vec2 getPoint1();
	glm::vec2 getPoint2();
	glm::vec2 getPoint1Pos();
	glm::vec2 getPoint2Pos();
	~Edge();

private:
	glm::vec2 point1;
	glm::vec2 point1Pos;
	glm::vec2 point2;
	glm::vec2 point2Pos;
	glm::vec2 dir;
};

