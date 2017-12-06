#include "Camera.h"

Camera::Camera(int w, int h)
{
	this->Size.x = w;
	this->Size.y = h;
	this->active = true;
}

Camera::Camera(int w, int h, int x, int y)
{
	this->Size.x = w;
	this->Size.y = h;
	this->Position.x = x;
	this->Position.y = y;
	this->Velocity.x = 0;
	this->Velocity.y = 0;
	this->active = false;
}

void Camera::Update()
{
	this->Position.x -= this->Velocity.x;
	this->Position.y += this->Velocity.y;

	//update Center
	this->Center.x -= this->Velocity.x;
	this->Center.y += this->Velocity.y;
}

Camera::~Camera()
{
}
