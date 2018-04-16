#include "AbstractActuator.h"
#include "../Sprite.h"
#include "../ObjectPool.h"

class PositionActuator : public AbstractActuator
{
public:
	PositionActuator(std::string name, Sprite*, int newX, int newY);
	PositionActuator(std::string name, Sprite*, int newX, std::string condition);
	PositionActuator(std::string name, Sprite*, std::string condition);
	PositionActuator(std::string name, SceneObject*, SceneObject*);
	PositionActuator(std::string name, ObjectPool<SceneObject>*, SceneObject*);
	PositionActuator(std::string name, ObjectPool<Sprite>*, SceneObject*);
	void run();
	~PositionActuator();

private:
	Sprite *sprite;
	int x;
	int y;
	int d;
	std::string condition;
	SceneObject *one;
	SceneObject *two;
	ObjectPool<SceneObject>	*OPSO;
	ObjectPool<Sprite>	*OPS;
};

