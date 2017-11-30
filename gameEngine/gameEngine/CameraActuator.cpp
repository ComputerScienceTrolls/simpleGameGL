#include "CameraActuator.h"

CameraActuator::CameraActuator(std::string n, AbstractScene *p, std::string con, int dt) :
	parent(p), condition(con), Dt(dt)
{
	this->name = n;
}

CameraActuator::CameraActuator(std::string n, AbstractScene *p, std::string con, int x, int y) :
	parent(p), condition(con), DX(x), DY(y)
{
	this->name = n;
}

void CameraActuator::run()
{
	if (condition == "move")
	{
		parent->setCameraPosX(Dt);
	}
	else if (condition == "movex")
	{
		//parent->setCameraPosX
	}
}

CameraActuator::~CameraActuator()
{
}
