#include "Camera.h"

Camera::Camera(int w, int h)
{
	this->width = w;
	this->height = h;
}

Camera::Camera(int w, int h, int x, int y) :
	width(w), height(h), posX(x), posY(y), dx(0), dy(0)
{
}

void Camera::setPosX(int newX)
{
	this->posX = newX;
}

void Camera::setPosY(int newY)
{
	this->posY = newY;
}

void Camera::setWidth(int newW)
{
	this->width = newW;
}

void Camera::setHeight(int newH)
{
	this->height = newH;
}

void Camera::setDX(int newDX)
{
	this->dx = newDX;
}

void Camera::setDY(int newDY)
{
	this->dy = newDY;
}

void Camera::setCameraForce(float angle, float thrust)
{
	//input angle is in degrees - convert to radians    
	angle = angle * 3.14 / 180;

	//calculate dx and dy
	double newDX = thrust * cos(angle);
	double newDY = thrust * sin(angle);

	this->dx += newDX;
	this->dy += newDY;

	//ensure speed and angle are updated
	//this->calcSpeedAngle();
}

int Camera::getPosX()
{
	return this->posX;
}

int Camera::getPosY()
{
	return this->posY;
}

int Camera::getDX()
{
	return this->dx;
}

int Camera::getDY()
{
	return this->dy;
}

int Camera::getWidth()
{
	return this->width;
}

int Camera::getHeight()
{
	return this->height;
}


Camera::~Camera()
{
}
