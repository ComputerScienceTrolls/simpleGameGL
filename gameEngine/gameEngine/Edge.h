#pragma once

#include <glm/glm.hpp>

class Edge
{
public:
	Edge(glm::vec2 p0, glm::vec2 p1, glm::vec2 dir);
	glm::vec2 getDir();
	~Edge();

private:
	glm::vec2 point1;
	glm::vec2 point2;
	glm::vec2 dir;
};

