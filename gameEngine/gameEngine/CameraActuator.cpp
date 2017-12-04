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
		camera->setDY(DY);
	}
	else if (condition == "x")
	{
		camera->setDX(DT);
	}
	else if (condition == "y")
	{
		camera->setDY(DT);
	}
	else if (condition == "flip")
	{
		camera->setDX(-camera->getDX());
		camera->setDY(-camera->getDY());
	}
	else if (condition == "flipx")
	{
		camera->setPosX(-camera->getPosX());
	}
	else if (condition == "flipy")
	{
		camera->setPosY(-camera->getPosX());
	}
	else if (condition == "multiply")
	{
		camera->setDX(camera->getDX() * DT);
		camera->setDY(camera->getDY() * DT);
	}
	else if (condition == "force")
	{
		camera->setCameraForce(angle, force);
	}
	
}

CameraActuator::~CameraActuator()
{
}
