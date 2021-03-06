#include "PolyCollider.h"
#include "../ResourceManager.h"

PolyCollider::PolyCollider(std::string n, AbstractSprite &parent, std::vector<glm::vec2> vecs) :
	spriteParent(&parent), offsetVectrices(vecs)
{

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
		ResourceManager::LoadTexture("textures/greenCircle.png", true, "debugGreenCircle");
	}
	this->name = n;
	this->type = "Poly";
	//get the vertex that is the most left, right, up, and down so we can get the poly con's "size" and box
	float minX = 10000;
	float maxX = 0;
	float minY = 10000;
	float maxY = 0;
	if (vecs.size() < 2)
	{
		std::cout << "cannot create a poly collider with only 1 vector";
	}
	else
	{
		for (unsigned int i = 0; i < vecs.size(); i++)
		{
			if (vecs.at(i).x < minX)
			{
				minX = vecs.at(i).x;
				this->minXPoint = vecs.at(i);
			}
			if (vecs.at(i).x > maxX)
			{
				maxX = vecs.at(i).x;
			}
			if (vecs.at(i).y < minY)
			{
				minY = vecs.at(i).y;
				this->minYPoint = vecs.at(i);
			}
			if (vecs.at(i).y > maxY)
			{
				maxY = vecs.at(i).y;
			}

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

		//store vectrices with the offset of the parent's pos, so we know it's true positon for collision
		for (unsigned int i = 0; i < vecs.size(); i++)
		{
			vectrices.push_back(vecs.at(i) + spriteParent->getPosition());
		}

		//set width and height from our mins and maxs
		this->Size.x = maxX - minX;
		this->Size.y = maxY - minY;
	}

	//make sure collider textures are not already loaded
	if (ResourceManager::Textures["textures/green.png"].Image_Format == 6407)
	{
		//texture for collider debug
		ResourceManager::LoadTexture("textures/green.png", true, "debugGreen");
	}
}

PolyCollider::PolyCollider(std::string n, std::vector<glm::vec2> vecs):
	offsetVectrices(vecs)
{
	this->name = n;
	this->type = "Poly";
	//get the vertex that is the most left, right, up, and down so we can get the poly con's "size" and box
	float minX = 10000;
	float maxX = 0;
	float minY = 10000;
	float maxY = 0;
	if (vecs.size() < 2)
	{
		std::cout << "cannot create a poly collider with only 1 vector";
	}
	else
	{
		for (unsigned int i = 0; i < vecs.size(); i++)
		{
			if (vecs.at(i).x < minX)
			{
				minX = vecs.at(i).x;
				this->minXPoint = vecs.at(i);
			}
			if (vecs.at(i).x > maxX)
			{
				maxX = vecs.at(i).x;
			}
			if (vecs.at(i).y < minY)
			{
				minY = vecs.at(i).y;
				this->minYPoint = vecs.at(i);
			}
			if (vecs.at(i).y > maxY)
			{
				maxY = vecs.at(i).y;
			}

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

		//store vectrices with the offset of the parent's pos, so we know it's true positon for collision
		if (spriteParent)
		{
			for (unsigned int i = 0; i < vecs.size(); i++)
			{
				vectrices.push_back(vecs.at(i) + spriteParent->getPosition());
			}
		}
		else
		{
			for (unsigned int i = 0; i < vecs.size(); i++)
			{
				vectrices.push_back(vecs.at(i));
			}
		}

		//set width and height from our mins and maxs
		this->Size.x = maxX - minX;
		this->Size.y = maxY - minY;
	}
}

//update every vertex based on the sprite's pos
void PolyCollider::updateVecs()
{
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		float tempX = edges[i]->getPoint1().x + spriteParent->getPosition().x;
		float tempY = edges[i]->getPoint1().y + spriteParent->getPosition().y;

		edges[i]->setPoint1Pos(glm::vec2(tempX, tempY));

		tempX = edges[i]->getPoint2().x + spriteParent->getPosition().x;
		tempY = edges[i]->getPoint2().y + spriteParent->getPosition().y;
		edges[i]->setPoint2Pos(glm::vec2(tempX, tempY));

		edges[i]->updateDir();
	}

	if (spriteParent)
		this->Position = this->minXPoint + spriteParent->getPosition();

	for (unsigned int i = 0; i < vectrices.size(); i++)
	{
		for (unsigned int i = 0; i < vectrices.size(); i++)
		{
			vectrices[i] = offsetVectrices.at(i) + spriteParent->getPosition();
		}
	}

}

bool PolyCollider::collide(std::vector<AbstractCollider*> otherColliders)
{
	//we need to update the vecs based on each sprite's position
	updateVecs();
	for (unsigned int i = 0; i < otherColliders.size(); i++)
	{
		if (otherColliders.at(i)->getType() == "Poly")
		{
			//we need to update otherCollidiers vecs based on it's sprite's position
			otherColliders.at(i)->updateVecs();
			for (unsigned int j = 0; j < this->vectrices.size(); j++)
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
			for (unsigned int j = 0; j < otherColliders.at(i)->getVerticies().size(); j++)
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

//returns dot product of the two vertexs
double PolyCollider::getDot(glm::vec2 a, glm::vec2 b)
{
	return a.x*b.x + a.y*b.y;
}

//return the normalaized vertex of the given vertex
glm::vec2 PolyCollider::normalize(glm::vec2 v)
{
	double mag = std::sqrt(v.x*v.x + v.y*v.y);
	glm::vec2 temp = { v.x / mag, v.y / mag };
	return temp;
}

//return the normal vector of the given vertex
glm::vec2 PolyCollider::getNormal(glm::vec2 v)
{
	glm::vec2 temp = { v.y, -v.x };
	return temp;
}

std::string PolyCollider::getType()
{
	return this->type;
}

//not sure how to draw lines yet, need to figure out before trying to draw but need to implement pure virtual function
void PolyCollider::Draw(SpriteRenderer & renderer)
{
	//line just to prevent warning of unused var
	//renderer = renderer;

	std::vector<glm::vec2> points;
	for (int i = 0; i < edges.size(); i++)
	{
		points.push_back(glm::vec2(edges.at(i)->getPoint1().x, edges.at(i)->getPoint1().y));
		//points.push_back(glm::vec2(edges.at(i)->getPoint2().x, edges.at(i)->getPoint2().y));
	}
	Texture2D tempTexture = ResourceManager::GetTexture("debugGreen");
	renderer.DrawLine(points, 2.5, tempTexture);
	renderer.DrawSprite(tempTexture, this->Position, this->Size, this->Rotation, glm::vec3(0, 255, 0), .25);
}

//create an edge from two given vertexs.
Edge* PolyCollider::createEdge(glm::vec2 p0, glm::vec2 p1)
{
	glm::vec2 dir = { p1.x - p0.x, p1.y - p0.y };
	Edge *edge = new Edge(p0, p1, dir);
	return edge;
}

//return the two vertex that are the projection from the axis
std::vector<double> PolyCollider::project(glm::vec2 axis)
{
	axis = normalize(axis);
	//create tmp vector for vectrices + spritePos
	std::vector<glm::vec2> tmpVec;

	double min = getDot(vectrices.at(0), axis);
	//min and max are the start and finish points
	double max = min;

	for (unsigned int i = 0; i < vectrices.size(); i++)
	{
		//find the projection of every point on the polygon onto the line.
		double proj = getDot(vectrices.at(i), axis);
		//std::cout << "\nproj: " << proj;
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

//returns if projection is contained 
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

//checks if projections overlap or not
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

std::vector<glm::vec2> PolyCollider::getOffsetVectrices()
{
	return this->offsetVectrices;
}

std::vector<Edge*> PolyCollider::getEdges()
{
	return this->edges;
}
