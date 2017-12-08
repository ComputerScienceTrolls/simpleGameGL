#include "AbstractActuator.h"
#include "../MovingSceneObject.h"
#include "../AbstractSprite.h"

class MotionActuator : public AbstractActuator
{
public:
	MotionActuator(std::string name, MovingSceneObject*, int newDX, int newDY);
	MotionActuator(std::string name, MovingSceneObject*, double newAngle, double newForce, std::string condition = "force");
	MotionActuator(std::string name, MovingSceneObject*, int newDX, std::string condition);
	MotionActuator(std::string name, MovingSceneObject*, std::string condition);
	void run();
	~MotionActuator();

private:
	MovingSceneObject *object;
	int DX;
	int DY;
	int DT;
	double force;
	double angle;
	std::string condition;
};

