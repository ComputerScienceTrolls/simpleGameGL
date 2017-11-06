#include "AbstractSensor.h"
#include "AbstractActuator.h"
#include "../KeyHandler.h"

#include <GLFW/glfw3.h>
#include <vector>

class KeyboardSensor : public AbstractSensor
{
public:
	KeyboardSensor(int key, std::string con = "na");
	virtual void sense();
	void addActuator(AbstractActuator*);
	~KeyboardSensor();

private:
	int key;
	std::string condition;
	bool oneShot;
	std::vector<AbstractActuator*> actuators;
};

