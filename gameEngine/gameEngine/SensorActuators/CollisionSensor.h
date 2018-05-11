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
	CollisionSensorSpriteSpriteNoOneShot(AbstractSprite* oneSp, AbstractSprite* twoSp, std::vector<AbstractActuator*> acts)
	{
		oneS = oneSp;
		twoS = twoSp;
		actuators = &acts;
	};
	virtual void exec()
	{
		if (oneS->collide(twoS))
		{
			for (int i = 0; i < actuators->size(); i++)
			{
				actuators->at(i)->run();
			}
		}
	};
	~CollisionSensorSpriteSpriteNoOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractSprite *twoS;
	std::vector<AbstractActuator*> *actuators;

};

class CollisionSensorSpriteSpriteOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteSpriteOneShot(AbstractSprite* oneSp, AbstractSprite* twoSp, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneSp;
		twoS = twoSp;
		actuators = &acts;
		tapped = true;
	};
	virtual void exec()
	{
		if (tapped)
		{
			if (oneS->collide(twoS))
			{
				tapped = false;
				for (int i = 0; i < actuators->size(); i++)
				{
					actuators->at(i)->run();
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
	std::vector<AbstractActuator*> *actuators;
	bool tapped;

};

class CollisionSensorSpriteColliderNoOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteColliderNoOneShot(AbstractSprite* oneS, AbstractCollider* twoC, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneS;
		twoC = twoC;
		actuators = &acts;
	};
	virtual void exec()
	{
		if (oneS->collide(twoC))
		{
			for (int i = 0; i < actuators->size(); i++)
			{
				actuators->at(i)->run();
			}
		}
	};
	~CollisionSensorSpriteColliderNoOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> *actuators;
};

class CollisionSensorSpriteColliderOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteColliderOneShot(AbstractSprite* oneS, AbstractCollider* twoC, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneS;
		twoC = twoC;
		actuators = &acts;
		tapped = true;
	};
	virtual void exec()
	{
		if (tapped)
		{
			if (oneS->collide(twoC))
			{
				tapped = false;
				for (int i = 0; i < actuators->size(); i++)
				{
					actuators->at(i)->run();
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
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
};

class CollisionSensorColliderColliderNoOneShot : public CollisonSensorState
{
public:
	CollisionSensorColliderColliderNoOneShot(AbstractCollider* oneCo, AbstractCollider* twoCo, std::vector<AbstractActuator*> &acts)
	{
		oneC = oneCo;
		twoC = twoCo;
		actuators = &acts;
	};
	virtual void exec()
	{
		if (oneC->collide(twoC))
		{
			for (int i = 0; i < actuators->size(); i++)
			{
				actuators->at(i)->run();
			}
		}
	};
	~CollisionSensorColliderColliderNoOneShot() {};

private:
	AbstractCollider *oneC;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> *actuators;
};

class CollisionSensorColliderColliderOneShot : public CollisonSensorState
{
public:
	CollisionSensorColliderColliderOneShot(AbstractCollider* oneCo, AbstractCollider* twoCo, std::vector<AbstractActuator*> &acts)
	{
		oneC = oneCo;
		twoC = twoCo;
		actuators = &acts;
		tapped = true;
	};
	virtual void exec()
	{
		if (tapped)
		{
			if (oneC->collide(twoC))
			{
				tapped = false;
				for (int i = 0; i < actuators->size(); i++)
				{
					actuators->at(i)->run();
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
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
};


class CollisionSensorSpriteSceneNoOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteSceneNoOneShot(AbstractSprite* oneSp, AbstractScene* twoSc, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneSp;
		scene = twoSc;
		actuators = &acts;
	};
	virtual void exec()
	{
		for (int i = 0; i < scene->getColliders().size(); i++)
		{
			if (oneS->collide(scene->getColliders()[i]))
			{
				for (int j = 0; j < actuators->size(); j++)
				{
					actuators->at(j)->run();
				}
			}
		}
	};
	~CollisionSensorSpriteSceneNoOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractScene *scene;
	std::vector<AbstractActuator*> *actuators;
};

class CollisionSensorSpriteSceneOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteSceneOneShot(AbstractSprite* oneSp, AbstractScene* twoSc, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneSp;
		scene = twoSc;
		actuators = &acts;
		tapped = true;
	};
	virtual void exec()
	{
		for (int i = 0; i < scene->getColliders().size(); i++)
		{
			if (tapped)
			{
				if (oneS->collide(scene->getColliders()[i]))
				{
					tapped = false;
					for (int j = 0; j < actuators->size(); j++)
					{
						actuators->at(j)->run();
					}
				}
			}
			//else we are not colliding, reset tapped
			else
			{
				tapped = true;
			}
		}
	};
	~CollisionSensorSpriteSceneOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractScene *scene;
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
};