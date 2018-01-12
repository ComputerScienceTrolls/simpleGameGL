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
}

CameraActuator::CameraActuator(std::string, Camera *c, SceneObject *s) :
	camera(c), object(s)
{
}

void CameraActuator::run()
{
	if (condition == "zoom")
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
	else if (condition == "zoomDT")
	{
		camera->changeZoomByX(DT);
		camera->changeZoomByY(DT);
	}
	else if (condition == "zoomBoth")
	{
		camera->changeZoomByX(DX);
		camera->changeZoomByY(DY);
	}
	else if (condition == "followObject")
	{
		//camera->setParent()
	}
	
}

CameraActuator::~CameraActuator()
{
}
