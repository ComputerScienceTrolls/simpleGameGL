#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class MotionActuator : public AbstractActuator
{
public:
	MotionActuator(std::string name, AbstractSprite*, int newDX, int newDY);
	MotionActuator(std::string name, AbstractSprite*, double newAngle, double newForce, std::string condition = "force");
	MotionActuator(std::string name, AbstractSprite*, int newDX, std::string condition);
	MotionActuator(std::string name, AbstractSprite*, std::string condition);
	void run();
	~MotionActuator();

private:
	AbstractSprite *sprite;
	int DX;
	int DY;
	int DT;
	double force;
	double angle;
	std::string condition;
};

