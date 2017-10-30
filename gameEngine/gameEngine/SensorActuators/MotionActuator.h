#include "AbstractActuator.h"
#include "../AbstractSprite.h"

class MotionActuator : public AbstractActuator
{
public:
	MotionActuator(AbstractSprite*, int newDX, int newDY);
	MotionActuator(AbstractSprite*, double newAngle, double newForce, std::string condition = "force");
	MotionActuator(AbstractSprite*, int newDX, std::string condition);
	MotionActuator(AbstractSprite*, std::string condition);
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

