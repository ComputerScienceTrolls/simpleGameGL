#ifndef DRAWSCENEOBJECT_H
#define DRAWSCENEOBJECT_H

#include "SceneObject.h"
#include "AbstractRenderer.h"
//#include "sprite_renderer.h"
//#include "TextRenderer.h"

class DrawSceneObject : public virtual SceneObject
{

public:
	DrawSceneObject();
	virtual void setTransparency(float);
	virtual float getTransparency();
	virtual void setColor(glm::vec3);
	virtual glm::vec3 getColor();

	//virtual void Draw(SpriteRenderer &renderer) = 0;
	//virtual void Draw(TextRenderer &renderer) {};
	virtual void Draw(AbstractRenderer *renderer) = 0;
	virtual ~DrawSceneObject();

protected:
	GLfloat transparency;
	bool visible;
	glm::vec3 Color;
};

#endif