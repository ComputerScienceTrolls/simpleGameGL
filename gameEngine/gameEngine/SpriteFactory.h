#include "Sprite.h"

#pragma once
class SpriteFactory
{
public:
	SpriteFactory();
	Sprite* createSprite();
	~SpriteFactory();
};

