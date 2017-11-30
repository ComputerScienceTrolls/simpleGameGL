#pragma once
#include "SensorActuators\AbstractActuator.h"
#include "AbstractScene.h"

class CameraActuator : public AbstractActuator
{
public:
	CameraActuator(std::string, AbstractScene*, std::string, int); 
	CameraActuator(std::string, AbstractScene*, std::string, int, int);
	virtual void run();
	~CameraActuator();

private:
	AbstractScene* parent;
	std::string condition;
	int Dt;
	int DX;
	int DY;
};

