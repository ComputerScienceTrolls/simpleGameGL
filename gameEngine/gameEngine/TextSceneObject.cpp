#include "TextSceneObject.h"

TextSceneObject::TextSceneObject()
{
}

TextSceneObject::TextSceneObject(AbstractScene *scene, std::string t, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, std::string f, int fSize)
{
	this->Position.x = x;
	this->Position.y = y;
	this->Size = glm::vec2(scale);
	this->Color = color;
	this->visible = true;

	this->text = t;
	this->font = f;
	this->fontSize = fSize;

	scene->addTextObject(this);
	scene->addMovingObject(this);

	this->Velocity = glm::vec2(0, 0);
}

void TextSceneObject::Draw(AbstractRenderer *renderer)
{
	TextRenderer *tr = static_cast<TextRenderer*>(renderer);

	if (this->visible)
	{
		if (tr->currentFont != font || tr->currentFontSize != fontSize)
		{
			tr->Load(font, fontSize);
		}
		tr->RenderText(text, Position.x, Position.y, Size.x/10, Color);
	}
}

TextSceneObject::~TextSceneObject()
{
}
