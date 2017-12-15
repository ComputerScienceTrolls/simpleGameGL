#ifndef QUAD_SCENE_H
#define QUAD_SCENE_H

#include "Scene.h"
#include "MovingSceneObject.h"
#include "DrawSceneObject.h"

class QuadScene : public Scene
{
public:
	QuadScene() {};
	QuadScene(std::string name, GLuint width, GLuint height, AbstractSprite *target, int divisions);

	virtual void Update();

	~QuadScene();

private:
	AbstractSprite *target;
	std::vector<glm::vec2> posQuads;
	std::vector<glm::vec2> sizeQuads;
	std::vector<std::vector<MovingSceneObject*>> movingQuads;
	std::vector<std::vector<DrawSceneObject*>> drawQuads;
	int quad;
};

#endif