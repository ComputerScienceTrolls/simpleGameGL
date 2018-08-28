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
	~KeyboardSensor();
	
private:
	int key;
	std::string condition;
	bool oneShot;
};

