#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include "MovingSceneObject.h"

class Camera : public MovingSceneObject
{
public:
	Camera(int w, int h);
	Camera(int w, int h, int posX, int posY);

	virtual void setZoom(glm::vec2);
	virtual void setZoomX(float);
	virtual void setZoomY(float);
	virtual void changeZoomByX(float);
	virtual void changeZoomByY(float);
	virtual glm::vec2 getZoom();

	//override update because we need to inverse x and y since we're really pushing objects
	virtual void Update();

	~Camera();

private:
	glm::vec2 Zoom;

};
#endif
