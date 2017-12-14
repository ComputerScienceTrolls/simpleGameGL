#include "QuadScene.h"


QuadScene::QuadScene(std::string n, GLuint w, GLuint h, AbstractSprite *t, int divisions) :
	target(t), quad(divisions)
{
	this->name = n;
	this->width = w;
	this->height = h;
	this->camera.setHeight(h);
	this->camera.setWidth(w);

	int squarefootage = h * w;
	int divWidth = w / divisions;
	int divHeight = h / divisions;
	for (int i = 0; i < divisions; i++)
	{
		if (i == 0)
			posQuads.push_back(glm::vec2(divWidth, divHeight));
		else
			posQuads.push_back(glm::vec2(divWidth, divHeight) + sizeQuads.front());
		sizeQuads.push_back(glm::vec2(divWidth,divHeight));
		movingQuads.push_back(std::vector<MovingSceneObject*>());
		drawQuads.push_back(std::vector<DrawSceneObject*>());
	}

	this->MovingSceneObjects.push_back(&this->camera);
	this->MovingSceneObjects.push_back(&this->background);
}

void QuadScene::Update()
{
	if (this->active)
	{
		//for each sprite in scene
		for (int i = 0; i < MovingSceneObjects.size(); i++)
		{
			if (MovingSceneObjects.at(i)->getActive())
			{
				MovingSceneObjects.at(i)->Update();
				MovingSceneObjects.at(i)->checkBounds(this->width, this->height);

				//move object to proper quad vector
				for (int j = 0; j < quad; j++)
				{
					if (MovingSceneObjects[i]->getPosition().x + MovingSceneObjects[i]->getSize().x < posQuads.at(i).x + sizeQuads.at(i).x)
					{
						if (MovingSceneObjects[i]->getPosition().y + MovingSceneObjects[i]->getSize().y < posQuads.at(i).y + sizeQuads.at(i).y)
						{
							movingQuads[j].push_back(MovingSceneObjects[i]);
						}
					}
				}
			}
		}

		for (int i = 0; i < sensors.size(); i++)
		{
			sensors.at(i)->sense();
		}

		for (int i = 0; i < observers.size(); i++)
		{
			observers.at(i)->Notify();
		}
	}
}

QuadScene::~QuadScene()
{
}
