#include "AbstractScene.h"

AbstractScene::AbstractScene() :
	camera(0,0)
{
}

Camera AbstractScene::getCamera()
{
	return this->camera;
}

AbstractScene::~AbstractScene()
{
}
