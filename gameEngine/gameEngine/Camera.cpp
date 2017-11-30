#include "Camera.h"

Camera::Camera(int w, int h)
{
	this->width = w;
	this->height = h;
}

Camera::Camera(int w, int h, int x, int y)
{
	this->width = w;
	this->height = h;
	this->posX = x;
	this->posY = y;
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

int Camera::getPosX()
{
	return this->posX;
}

int Camera::getPosY()
{
	return this->posY;
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
