#include "AbstractActuator.h"
#include "../AbstractScene.h"
#include "../SceneObject.h"

class CameraActuator : public AbstractActuator
{
public:
	CameraActuator(std::string, Camera*, float, std::string);
	CameraActuator(std::string, Camera*, float, float, std::string con = "both");
	CameraActuator(std::string, Camera*, SceneObject*);
	virtual void run();
	~CameraActuator();

private:
	Camera* camera;
	SceneObject *object;
	std::string condition;
	float DT;
	float DX;
	float DY;
	float force;
	float angle;
};

