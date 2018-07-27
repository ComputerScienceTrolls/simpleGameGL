#ifndef COLLISIONSENSORSTATE_H
#define COLLISIONSENSORSTATE_H

class CollisionSensorState
{
public:
	CollisionSensorState() {};
	virtual void exec() = 0;
	~CollisionSensorState() {};
};

#endif