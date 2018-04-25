#include "SpriteSheetSprite.h"



SpriteSheetSprite::SpriteSheetSprite()
{
}

SpriteSheetSprite::SpriteSheetSprite(std::string n, AbstractScene &scene, glm::vec2 pos, glm::vec2 size,int vFrames, int hFrames, GLchar *texture, glm::vec2 velocity, glm::vec3 color) 
{

	//create a sprite for each cell of the sprite sheet
	for (int i = 0; i < vFrames; i++)
	{
		for (int j = 0; j < hFrames; j++)
		{
			sprites.push_back(new Sprite(n  + std::to_string(i + j), scene, pos, size, texture, vFrames, hFrames, velocity, color));
			Texture2D temp = sprites.back()->getTexture();
			GLuint test = size.x / hFrames;
			temp.Width = test;
			std::cout << test;
			std::cout << temp.Width;
			//sprites.back()->setTexture(temp);
			sprites.back()->setVisible(false);
		}
	}

	//only show first sprite in spritesheet
	Texture2D temp2 = sprites[3]->getTexture();
	sprites[3]->setVisible(true);
	sprites[1]->setVisible(true);
	sprites[3]->setVelocity(glm::vec2(0, .1));
}

SpriteSheetSprite::~SpriteSheetSprite()
{
}
