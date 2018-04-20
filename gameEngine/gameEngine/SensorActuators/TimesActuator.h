#include "AbstractActuator.h"
#include "../AbstractSprite.h"
#include "../AbstractScene.h"
#include <vector>

class TimesActuator : public AbstractActuator
{
public:
	TimesActuator(std::string name, AbstractSprite* s, int index, std::string condition);
	TimesActuator(std::string name, AbstractScene *o, int index, std::string condition);
	void addActuator(AbstractActuator *);
	void run();
	~TimesActuator();

private:
	std::vector<AbstractActuator*> actuators;
	int index;
	int currentIndex;
	std::string condition;
	AbstractScene *mainScene;
	AbstractSprite *sprite;
};

