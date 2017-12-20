#include "Camera.h"

Camera::Camera(int w, int h)
{
	this->Size.x = w;
	this->Size.y = h;
	this->active = true;
	this->Zoom.x = 1;
	this->Zoom.y = 1;
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
	this->Zoom.x = 1;
	this->Zoom.y = 1;
}

void Camera::setZoom(glm::vec2 newZoom)
{
	this->Zoom = newZoom;
}

void Camera::setZoomX(float newX)
{
	this->Zoom.x = newX;
}

void Camera::setZoomY(float newY)
{
	this->Zoom.y = newY;
}

void Camera::changeZoomByX(float dx)
{
	this->Zoom.x += dx;
}

void Camera::changeZoomByY(float dy)
{
	this->Zoom.y += dy;
}

glm::vec2 Camera::getZoom()
{
	return this->Zoom;
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
