#include "CameraActuator.h"

CameraActuator::CameraActuator(std::string n, Camera *c, std::string con, int dt) :
	camera(c), condition(con), DT(dt)
{
	this->name = n;
}

CameraActuator::CameraActuator(std::string n, Camera *c, std::string con, int x, int y) :
	camera(c), condition(con), DX(x), DY(y)
{
	this->name = n;
}

CameraActuator::CameraActuator(std::string n, Camera *c, double newAngle, double newForce, std::string con) :
	camera(c), force(newForce), angle(newAngle), condition(con)
{
	this->name = n;
}

void CameraActuator::run()
{
if (condition == "both")
	{
		camera->setDX(DX);
		parent->setCameraDY(DY);
	}
	else if (condition == "x")
	{
		parent->setCameraDX(DT);
	}
	else if (condition == "y")
	{
		parent->setCameraDY(DT);
	}
	else if (condition == "flip")
	{
		parent->setCameraDX(-parent->getCamera().getDX());
		parent->setCameraDY(-parent->getCamera().getDY());
	}
	else if (condition == "flipx")
	{
		parent->setCameraPosX(-parent->getCamera().getPosX());
	}
	else if (condition == "flipy")
	{
		parent->setCameraPosX(-parent->getCamera().getPosX());
	}
	else if (condition == "multiply")
	{
		parent->setCameraDX(parent->getCamera().getDX() * DT);
		parent->setCameraDY(parent->getCamera().getDY() * DT);
	}
	else if (condition == "force")
	{
		parent->setCameraForce(angle, force);
	}
	
}

CameraActuator::~CameraActuator()
{
}
