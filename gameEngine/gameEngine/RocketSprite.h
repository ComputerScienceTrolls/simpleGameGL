#pragma once

#include "Sprite.h"

class RocketSprite : public Sprite
{
public:
	RocketSprite();
	RocketSprite(std::string n, AbstractScene &scene);
	~RocketSprite();
};

