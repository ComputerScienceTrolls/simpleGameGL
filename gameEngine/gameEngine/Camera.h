#pragma once
#include <math.h>
#include "MovingSceneObject.h"

class Camera : public MovingSceneObject
{
public:
	Camera(int w, int h);
	Camera(int w, int h, int posX, int posY);

	//override update because we need to inverse x and y since we're really pushing objects
	virtual void Update();

	~Camera();

};

