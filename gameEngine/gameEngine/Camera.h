#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include "MovingSceneObject.h"

class Camera : public MovingSceneObject
{
public:
	Camera(int w, int h);
	Camera(int w, int h, float posX, float posY);

	virtual void setZoom(glm::vec2);
	virtual void setZoomX(float);
	virtual void setZoomY(float);
	virtual void changeZoomByX(float);
	virtual void changeZoomByY(float);
	virtual glm::vec2 getZoom();

	//override these so we can properly round the float to an int before returning
	virtual float getWidth();
	virtual float getHeight();

	//override update because we need to inverse x and y since we're really pushing objects
	virtual void Update();
	//override changes of position for same reason
	virtual void changePositionBy(glm::vec2);

	~Camera();

private:
	glm::vec2 Zoom;
	int width;
	int height;

};
#endif
