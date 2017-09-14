#include "SpriteFactory.h"



SpriteFactory::SpriteFactory()
{
}

Sprite* SpriteFactory::createSprite()
{
	return new Sprite();
}


SpriteFactory::~SpriteFactory()
{
}
