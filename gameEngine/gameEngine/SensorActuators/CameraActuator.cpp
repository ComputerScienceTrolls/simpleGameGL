#include "CameraActuator.h"

CameraActuator::CameraActuator(std::string n, Camera *c, float dt, std::string con) :
	camera(c), condition(con), DT(dt)
{
	this->name = n;
}

CameraActuator::CameraActuator(std::string n, Camera *c, float x, float y, std::string con) :
	camera(c), condition(con), DX(x), DY(y)
{
	this->name = n;
	if (condition == "force")
	{
		angle = DX;
		force = DY;
	}
}

void CameraActuator::run()
{
	if (condition == "both")
	{
		camera->setPosX(DX);
		camera->setPosY(DY);
	}
	else if (condition == "x")
	{
		camera->setPosX(DX);
	}
	else if (condition == "y")
	{
		camera->setDY(DY);
	}
	else if (condition == "zoom")
	{
		camera->setZoom(glm::vec2(DT));
	}
	else if (condition == "zoomX")
	{
		camera->setZoomX(DT);
	}
	else if (condition == "zoomY")
	{
		camera->setZoomY(DT);
	}
	else if (condition == "zoomDX")
	{
		camera->changeZoomByX(DT);
	}
	else if (condition == "zoomDY")
	{
		camera->changeZoomByY(DT);
	}
	else if (condition == "bothDt")
	{
		camera->setDX(DX);
		camera->setDY(DY);
	}
	else if (condition == "dx")
	{
		camera->setDX(DT);
	}
	else if (condition == "dy")
	{
		camera->setDY(DT);
	}
	else if (condition == "flipdt")
	{
		camera->setDX(-camera->getDX());
		camera->setDY(-camera->getDY());
	}
	else if (condition == "flipdx")
	{
		camera->setPosX(-camera->getPosX());
	}
	else if (condition == "flipdy")
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
		camera->addForce(angle, force);
	}
	
}

CameraActuator::~CameraActuator()
{
}
