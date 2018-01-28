#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include <alut.h>
#include <al.h>
#include <alc.h>
#include "QuadScene.h"
#include "SceneDirector.h"
#include "Sprite.h"
#include "RocketSprite.h"

#include "SensorActuators\CameraActuator.h"

#include "Observers/observerhandler.h"
#include "Observers/Observer.h"
#include "Observers/ColliderObserver.h"
#include "Observers/CheckBoundsObserver.h"
#include "Observers/CollisionGroupObserver.h"

#include "SensorActuators\MotionActuator.h"
#include "SensorActuators\PositionActuator.h"
#include "SensorActuators\CollisionSensor.h"
#include "SensorActuators\CheckBoundsSensor.h"
#include "SensorActuators\VisibilityActuator.h"
#include "SensorActuators\ActiveActuator.h"
#include "SensorActuators\KeyboardSensor.h"
#include "SensorActuators\SceneActuator.h"
#include "SensorActuators\SoundActuator.h"
#include "SensorActuators\AlwaysSensor.h"

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Scene mainScene("main",2000, 600);
Scene scene2 ("level2", 800, 600);
Scene scene3("levels3", 800, 600);

void ballColl2(Sprite *Ball, Sprite *Player)
{
	//check for collidition between ball and paddle
	if (Ball->collide(Player))
	{
		//Player->setDX(-Player->getDX());
		std::cout << "collision";
		//spriteMap["Paddle"]->setDX(-(spriteMap["Paddle"]->getDX()));
	}
}

void ColSpriteTest(Sprite *Ball, AbstractCollider *test)
{
	//check for collidition between ball and paddle
	if (test->collide(Ball))
	{
		//Player->setDX(-Player->getDX());
		std::cout << "collision";
		//spriteMap["Paddle"]->setDX(-(spriteMap["Paddle"]->getDX()));
	}
}

void test9()
{
	std::cout << "test\n";
}

void ballColl3(Sprite *Player, std::string name)
{
	//get all instances of name and check for collision with given sprite
	std::vector<AbstractSprite*> tempVec = mainScene.getSprite(name);
	for (int i = 0; i < tempVec.size(); i++)
	{
		if (Player->collide(tempVec.at(i)))
		{
			//Player->setDX(-Player->getDX());
			std::cout << "collision";
			//spriteMap["Paddle"]->setDX(-(spriteMap["Paddle"]->getDX()));
		}
	}
}

void checkCols(Sprite *s, int w, int h)
{
	s->checkBounds(w, h);
}

int main(int argc, char *argv[])
{
	//initiate openAl component
	alutInit(NULL, 0);
	
	//initiate main scene
	mainScene.Init();

	//set up sprites
	Sprite *rs2 = new Sprite("rocket", mainScene, glm::vec2(150, 300), glm::vec2(50, 35), "textures/RedRocket.png", glm::vec2(0,-1));
	Sprite *wave = new Sprite("wave", mainScene, glm::vec2(0, 0), glm::vec2(5, 10), "textures/paddle.png");
	SceneObject *spawnObject = new SceneObject();
	spawnObject->setParent(rs2);
	spawnObject->setPosition(glm::vec2(175,335));
	wave->setVisible(false);
	wave->setActive(false);
	//rs2->setRotation(3.14/2);
	rs2->setBoundAction("STOP");
	RocketSprite *rs = new RocketSprite("Rocket", mainScene);
	rs->setCollideDebug(true);
	BoxCollider *test55 = new BoxCollider("test44", mainScene, 50, 50, 100, 300);
	CircleCollider *test66 = new CircleCollider("test66", mainScene, 50, 200, 200);

	//set up colliders for sprites
	wave->addCircleCollider("test", 10, 0, 0);
	wave->setCollideDebug(true);
	
	//set up bound actions for sprites
	//Player->setBoundAction("STOP");

	//set up keyboard Sensors
	KeyboardSensor *ka = new KeyboardSensor("left",GLFW_KEY_A);
	KeyboardSensor *kd = new KeyboardSensor("right", GLFW_KEY_D);
	KeyboardSensor *kw = new KeyboardSensor("up", GLFW_KEY_W);
	KeyboardSensor *ks = new KeyboardSensor("down", GLFW_KEY_S);
	KeyboardSensor *kj = new KeyboardSensor("rleft", GLFW_KEY_J);
	KeyboardSensor *kl = new KeyboardSensor("rright", GLFW_KEY_L);
	KeyboardSensor *ki = new KeyboardSensor("rup", GLFW_KEY_I);
	KeyboardSensor *kk = new KeyboardSensor("rdown", GLFW_KEY_K);
	KeyboardSensor *kSpace = new KeyboardSensor("space", GLFW_KEY_SPACE, "clicked");
	
	
	//set up movement for player
	MotionActuator *rLeft = new MotionActuator("rotateLeft", rs2, -.01, "rotateBy");
	MotionActuator *rRight = new MotionActuator("rotateRight", rs2, .01, "rotateBy");
	MotionActuator *mUp = new MotionActuator("mup", rs2,0, .1, "forceForward");
	MotionActuator *mLeft = new MotionActuator("mleft", rs2, 180, .1, "force");
	MotionActuator *mRight = new MotionActuator("mright", rs2, 0, .1, "force");
	MotionActuator *mDown = new MotionActuator("motion5", rs2, 270, .1, "force");
	PositionActuator *rocketFront = new PositionActuator("rocketFront", wave, spawnObject);
	
	
	//set up sound 
	 //SoundActuator *Batman = new SoundActuator("sound/truth.wav");

	
	//will need later to change scenes
	//SceneActuator *s1 = new SceneActuator("scene1",&testScene, "next");
	//SceneActuator *s2 = new SceneActuator("scene2",&mainScene, "previous");
	//SceneActuator *s3 = new SceneActuator("scene3",&mainScene, "togglePause");
	
	
	//add actuators to the sensor
	//kSpace->addActuator(s3);
	ka->addActuator(mLeft);
	kd->addActuator(mRight);
	//ks->addActuator(s1);
	kw->addActuator(mUp);
	kj->addActuator(rLeft);
	kl->addActuator(rRight);
	//kk->addActuator(s1);
	//ki->addActuator(s1);

	
	//add sensors to scene 1
	mainScene.addSensor(ka);
	mainScene.addSensor(kd);
	mainScene.addSensor(kw);
	mainScene.addSensor(ks);
	mainScene.addSensor(kj);
	mainScene.addSensor(kl);
	mainScene.addSensor(ki);
	mainScene.addSensor(kk);
	mainScene.addSensor(kSpace);
	//mainScene.addObserver(colTest);
	
	//add sensors to scene 2
	
	
	//add sensors to scene 3

	//add scenes to the scene director
	SceneDirector::getInstance()->addScene(&scene2);
	SceneDirector::getInstance()->addScene(&scene3);


	//set camera witdth and height
	mainScene.setCameraHeight(600);
	mainScene.setCameraWidth(800);

	//start game 
	SceneDirector::getInstance()->Start();
	
	//delete items that are on heap that is used by openal
	alutExit();

	return 0;
}