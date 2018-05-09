#pragma once
#include "AbstractSensor.h"
#include "../AbstractSprite.h"
#include "../AbstractScene.h"
#include "../Scene.h"
#include "AbstractActuator.h"

class CollisonSensorState
{
public:
	CollisonSensorState() {};
	virtual void exec() = 0;
	~CollisonSensorState() {};
};

class CollisionSensor : public AbstractSensor
{
public:
	CollisionSensor(std::string name, AbstractSprite*, AbstractSprite*, bool oneShot = false);
	CollisionSensor(std::string name, AbstractSprite*, AbstractCollider*, bool oneShot = false);
	CollisionSensor(std::string name, AbstractCollider*, AbstractCollider*, bool oneShot = false);
	CollisionSensor(std::string name, AbstractSprite*, Scene*, bool oneShot = false);
	void sense();
	~CollisionSensor();

private:
	AbstractSprite *oneS;
	AbstractSprite *twoS;
	AbstractCollider *oneC;
	AbstractCollider *twoC;
	AbstractScene *scene;
	bool oneShot;
	bool allInScene;
	CollisonSensorState *myState;
};

class CollisionSensorSpriteSpriteNoOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteSpriteNoOneShot(AbstractSprite* oneS, AbstractSprite* twoS, std::vector<AbstractActuator*> actuators)
	{
		oneS = oneS;
		twoS = twoS;
		actuators = actuators;
	};
	virtual void exec()
	{
		if (oneS->collide(twoS))
		{
			for (int i = 0; i < actuators.size(); i++)
			{
				actuators.at(i)->run();
			}
		}
	};
	~CollisionSensorSpriteSpriteNoOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractSprite *twoS;
	std::vector<AbstractActuator*> actuators;

};

class CollisionSensorSpriteSpriteOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteSpriteOneShot(AbstractSprite* oneSp, AbstractSprite* twoS, std::vector<AbstractActuator*> actuators)
	{
		oneS = oneSp;
		twoS = twoS;
		actuators = actuators;
		tapped = true;
	};
	virtual void exec()
	{
		if (tapped)
		{
			if (oneS->collide(twoS))
			{
				tapped = false;
				for (int i = 0; i < actuators.size(); i++)
				{
					actuators.at(i)->run();
				}

			}
		}
		//else we are not colliding, reset tapped
		else
		{
			tapped = true;
		}
	};
	~CollisionSensorSpriteSpriteOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractSprite *twoS;
	std::vector<AbstractActuator*> actuators;
	bool tapped;

};

class CollisionSensorSpriteColliderNoOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteColliderNoOneShot(AbstractSprite* oneS, AbstractCollider* twoC, std::vector<AbstractActuator*> actuators)
	{
		oneS = oneS;
		twoC = twoC;
		actuators = actuators;
	};
	virtual void exec()
	{
		if (oneS->collide(twoC))
		{
			for (int i = 0; i < actuators.size(); i++)
			{
				actuators.at(i)->run();
			}
		}
	};
	~CollisionSensorSpriteColliderNoOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> actuators;
};

class CollisionSensorSpriteColliderOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteColliderOneShot(AbstractSprite* oneS, AbstractCollider* twoC, std::vector<AbstractActuator*> actuators)
	{
		oneS = oneS;
		twoC = twoC;
		actuators = actuators;
		tapped = true;
	};
	virtual void exec()
	{
		if (tapped)
		{
			if (oneS->collide(twoC))
			{
				tapped = false;
				for (int i = 0; i < actuators.size(); i++)
				{
					actuators.at(i)->run();
				}
			}
		}
		//else we are not colliding, reset tapped
		else
		{
			tapped = true;
		}
	};
	~CollisionSensorSpriteColliderOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> actuators;
	bool tapped;
};

class CollisionSensorColliderColliderNoOneShot : public CollisonSensorState
{
public:
	CollisionSensorColliderColliderNoOneShot(AbstractCollider* oneC, AbstractCollider* twoC, std::vector<AbstractActuator*> actuators)
	{
		oneC = oneC;
		twoC = twoC;
		actuators = actuators;
	};
	virtual void exec()
	{
		if (oneC->collide(twoC))
		{
			for (int i = 0; i < actuators.size(); i++)
			{
				actuators.at(i)->run();
			}
		}
	};
	~CollisionSensorColliderColliderNoOneShot() {};

private:
	AbstractCollider *oneC;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> actuators;
};

class CollisionSensorColliderColliderOneShot : public CollisonSensorState
{
public:
	CollisionSensorColliderColliderOneShot(AbstractCollider* oneC, AbstractCollider* twoC, std::vector<AbstractActuator*> actuators)
	{
		oneC = oneC;
		twoC = twoC;
		actuators = actuators;
		tapped = true;
	};
	virtual void exec()
	{
		if (tapped)
		{
			if (oneC->collide(twoC))
			{
				tapped = false;
				for (int i = 0; i < actuators.size(); i++)
				{
					actuators.at(i)->run();
				}
			}
		}
		//else we are not colliding, reset tapped
		else
		{
			tapped = true;
		}
	};
	~CollisionSensorColliderColliderOneShot() {};

private:
	AbstractCollider *oneC;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> actuators;
	bool tapped;
};
