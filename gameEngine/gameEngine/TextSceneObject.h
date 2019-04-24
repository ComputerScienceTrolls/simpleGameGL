#pragma once
#include "AbstractScene.h"
#include "AbstractTextSceneObject.h"
#include "TextRenderer.h"

class TextSceneObject : public AbstractTextSceneObject, public virtual MovingSceneObject
{
public:
	TextSceneObject();
	TextSceneObject(AbstractScene *scene, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f, 1.0f, 0), std::string font = "fonts/OCRAEXT.TTF", int fontSize = 24);
	virtual void Draw(AbstractRenderer *renderer);
	~TextSceneObject();

private:

	
};

