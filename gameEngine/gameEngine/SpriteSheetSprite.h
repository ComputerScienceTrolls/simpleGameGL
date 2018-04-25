#pragma once
#include "Sprite.h"
class SpriteSheetSprite :public Sprite
{
public:
	SpriteSheetSprite();
	SpriteSheetSprite(std::string name, AbstractScene &scene, glm::vec2 pos, glm::vec2 size, int vFrames, int hFrames, GLchar* texture, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f));
	~SpriteSheetSprite();

private:
	int vFrames;
	int hFrames;
	std::vector<Sprite*> sprites;
};

