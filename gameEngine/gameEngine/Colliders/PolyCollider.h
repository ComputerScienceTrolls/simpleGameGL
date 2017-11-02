#include "collider.h"
#include "../AbstractSprite.h"
#include "Edge.h"
#include <iostream>
#include <vector>

class PolyCollider : public collider
{
public:
	PolyCollider(std::string name, AbstractSprite &parent, std::vector<glm::vec2>);
	virtual bool collide(std::vector<collider*> otherColliders);
	//virtual int getWidth();
	//virtual int getHeight();
	//virtual int getPosX();
	//virtual int getPosY();
	virtual bool getStaticState();
	virtual glm::vec2 getSpriteCenterPos();
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteSize();
	virtual std::string getName();
	double getDot(glm::vec2 a, glm::vec2 b);
	glm::vec2 normalize(glm::vec2 v);
	glm::vec2 getNormal(glm::vec2 v);
	std::string getType();
	virtual int getPosX();
	virtual int getPosY();
	Edge* createEdge(glm::vec2 p0, glm::vec2 p1);
	virtual std::vector<double> project(glm::vec2 axis);
	bool contains(double n, std::vector<double> range);
	bool overlap(std::vector<double> a, std::vector<double> b);
	
	virtual std::vector<glm::vec2> getVectrices();
	virtual std::vector<Edge*> getEdges();
	virtual void updateVecs();

private:
	int offsetH;
	int offsetW;
	int posXOffset;
	int posYOffset;
	std::string type;
	std::string name;
	bool staticState;
	AbstractSprite *spriteParent;
	std::vector<glm::vec2> vectrices;
	std::vector<Edge*> edges;
};
