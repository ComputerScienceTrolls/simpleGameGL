#pragma once
#include "AbstractActuator.h"
#include "../AbstractScene.h"

class CameraActuator : public AbstractActuator
{
public:
	CameraActuator(std::string, Camera*, float, std::string);
	CameraActuator(std::string, Camera*, float, float, std::string con = "both");
	virtual void run();
	~CameraActuator();

private:
	Camera* camera;
	std::string condition;
	float DT;
	float DX;
	float DY;
	float force;
	float angle;
};

