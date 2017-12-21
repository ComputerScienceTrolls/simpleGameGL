#ifndef SCENE_H
#define SCENE_H

#include "AbstractScene.h"
#include "ResourceManager.h"
#include "sprite_renderer.h"
#include "AbstractSprite.h"
#include "SceneDirector.h"

#include <vector>

// Scene holds all sprite set to it, determines when they are drawn and updated.
class Scene : public AbstractScene
{
public:
	Scene() { };
	Scene(std::string name, GLuint width, GLuint height);
	~Scene();
	virtual void Init();
	virtual void Update(GLfloat dt);
	virtual void Render();

	//set's Scene's background, get's image from filename you give to fill the scene
	void setBackground(char*);


protected:
	std::map<std::string, AbstractSprite*> spriteMap;
	MovingSceneObject background;
	bool initilized;
};
#endif