#include "AbstractSensor.h"
#include "AbstractActuator.h"
#include "../KeyHandler.h"

#include <GLFW/glfw3.h>
#include <vector>

class KeyboardSensor : public AbstractSensor
{
public:
	KeyboardSensor(std::string n, int key, std::string con = "na");
	virtual void sense();
	void addActuator(AbstractActuator*);
	std::string getName();
	void setName(std::string);
	~KeyboardSensor();

private:
	int key;
	std::string condition;
	std::string name;
	bool oneShot;
	std::vector<AbstractActuator*> actuators;
};

