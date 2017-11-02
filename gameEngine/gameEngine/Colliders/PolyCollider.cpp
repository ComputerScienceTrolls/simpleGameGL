#include "PolyCollider.h"

PolyCollider::PolyCollider(std::string n, AbstractSprite &parent, std::vector<glm::vec2> vecs) :
	name(n), spriteParent(&parent), vectrices(vecs)
{
	if (vecs.size() < 2)
	{
		std::cout << "cannot create a poly collider with only 1 vector";
	}
	else
	{
		for (int i = 0; i < vecs.size(); i++)
		{
			//if last one, connect it to the first vec
			Edge *temp;
			if (i == vecs.size() - 1)
			{
				temp = createEdge(vecs.at(i), vecs.at(0));
			}
			else
			{
				temp = createEdge(vecs.at(i), vecs.at(i + 1));
			}
			edges.push_back(temp);
		}
	}
}

void PolyCollider::updateVecs()
{

}

bool PolyCollider::collide(std::vector<collider*> otherColliders)
{
	//we need to update the vecs based on each sprite's movement
	updateVecs();
	for (int i = 0; i < otherColliders.size(); i++)
	{
		//we need to update otherCollidiers vecs based on it's 
		for (int j = 0; j < this->vectrices.size(); j++)
		{
			//get dir of the current edge
			glm::vec2 tempDir = this->edges[j]->getDir();

			//get normal of that dir
			tempDir = getNormal(tempDir);

			//find the projection of this polygon on the axis
			std::vector<double> thisProj = project(tempDir);
			std::vector<double> otherProj = otherColliders.at(i)->project(tempDir);
			if (!overlap(thisProj, otherProj))
			{
				return false;
			}
		}

		//now do it the other way
		for (int j = 0; j < otherColliders.at(i)->getVerticies().size(); j++)
		{
			glm::vec2 tempDir = otherColliders.at(i)->getEdges().at(j)->getDir();
			tempDir = getNormal(tempDir);
			std::vector<double> thisProj = otherColliders.at(i)->project(tempDir);
			std::vector<double> otherProj = otherColliders.at(i)->project(tempDir);
			if (!overlap(thisProj, otherProj))
			{
				return false;
			}
		}

		return true;
	}
	
	return false;
}

bool PolyCollider::getStaticState()
{
	return false;
}

glm::vec2 PolyCollider::getSpriteCenterPos()
{
	return this->spriteParent->getCenter();
}

glm::vec2 PolyCollider::getSpritePos()
{
	return this->spriteParent->getPosition();
}

glm::vec2 PolyCollider::getSpriteSize()
{
	return this->spriteParent->getSize();
}

std::string PolyCollider::getName()
{
	return this->name;
}

double PolyCollider::getDot(glm::vec2 a, glm::vec2 b)
{
	return a.x*b.x + a.y*b.y;
}

glm::vec2 PolyCollider::normalize(glm::vec2 v)
{
	double mag = std::sqrt(v.x*v.x + v.y*v.y);
	glm::vec2 temp = { v.x / mag, v.y / mag };
	return temp;
}

glm::vec2 PolyCollider::getNormal(glm::vec2 v)
{
	glm::vec2 temp = { v.y, -v.x };
	return temp;
}

std::string PolyCollider::getType()
{
	return this->type;
}

int PolyCollider::getPosX()
{
	return 0;
}

int PolyCollider::getPosY()
{
	return 0;
}

Edge* PolyCollider::createEdge(glm::vec2 p0, glm::vec2 p1)
{
	glm::vec2 dir = { p1.x - p0.x, p1.y - p0.y };
	Edge *edge = new Edge(p0, p1, dir);
	return edge;
}

std::vector<double> PolyCollider::project(glm::vec2 axis)
{
	axis = normalize(axis);
	double min = getDot(vectrices.at(0),axis);
	//min and max are the start and finish points
	double max = min;

	for (int i = 0; i < vectrices.size(); i++)
	{
		//find the projection of every point on the polygon onto the line.
		double proj = getDot(vectrices.at(i), axis);
		if (proj < min)
		{
			min = proj;
		}
		else if (proj > max)
		{
			max = proj;
		}
	}

	std::vector<double> tempVec;
	tempVec.push_back(min);
	tempVec.push_back(max);

	return tempVec;
}

bool PolyCollider::contains(double n, std::vector<double> range)
{
	double a = range[0];
	double b = range[1];

	if (b < a)
	{
		a = b;
		b = range[0];
	}

	return (n >= a && n <= b);
}

bool PolyCollider::overlap(std::vector<double> a, std::vector<double> b)
{
	if (contains(a[0], b))
		return true;
	else if (contains(a[1], b))
	{
		return true;
	}
	else if (contains(b[0],a))
	{
		return true;
	}
	else if (contains(b[1],a))
	{
		return true;
	}

	return false;
}

std::vector<glm::vec2> PolyCollider::getVectrices()
{
	return this->vectrices;
}

std::vector<Edge*> PolyCollider::getEdges()
{
	return this->edges;
}
