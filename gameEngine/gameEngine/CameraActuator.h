#pragma once
#include "SensorActuators\AbstractActuator.h"
#include "AbstractScene.h"

class CameraActuator : public AbstractActuator
{
public:
	CameraActuator(std::string, Camera*, std::string, int); 
	CameraActuator(std::string, Camera*, std::string, int, int);
	CameraActuator(std::string n, Camera *s, double newAngle, double newForce, std::string con);
	virtual void run();
	~CameraActuator();

private:
	Camera* camera;
	std::string condition;
	int DT;
	int DX;
	int DY;
	float force;
	float angle;
};

