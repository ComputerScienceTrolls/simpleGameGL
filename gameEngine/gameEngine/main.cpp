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
#include "SensorActuators\TimesActuator.h"

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Scene mainScene("main",800, 600);
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
	Sprite *rs2 = new Sprite("rocket", mainScene, glm::vec2(150, 300), glm::vec2(50, 35), "textures/Rocket001_off.png");
	rs2->setRotation(3.14 / 2);
	rs2->setCollideDebug(true);
	Sprite *rocketGoal = new Sprite("rocketGoal", mainScene, glm::vec2(750, 25), glm::vec2(50, 35), "textures/Rocket001_off.png");
	rocketGoal->setRotation(3.14/2);
	Sprite *wave = new Sprite("wave", mainScene, glm::vec2(0, 0), glm::vec2(20, 40), "textures/fullSignal.png");
	//wave->removeCollider("default");
	wave->hide();
	Sprite *Gui = new Sprite("fuel", mainScene, glm::vec2(150, 550), glm::vec2(300, 60), "textures/fuel_bar.png");
	Sprite *health[6] = { new Sprite("empty", mainScene, glm::vec2(-1000, -1000), glm::vec2(30, 30), "textures/fuel_block.png"),
		new Sprite("health", mainScene, glm::vec2(50, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//50
		new Sprite("health2", mainScene, glm::vec2(95, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//95
		new Sprite("health3", mainScene, glm::vec2(145, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//145
		new Sprite("health4", mainScene, glm::vec2(190, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//190
		new Sprite("health5", mainScene, glm::vec2(235, 550), glm::vec2(52, 30), "textures/fuel_block.png")
	};
	Sprite *Rocks[8] = { new Sprite("Rock1", mainScene, glm::vec2(50, 50), glm::vec2(100, 100), "textures/rock.png"),
		new Sprite("Rock2", mainScene, glm::vec2(50, 160), glm::vec2(100, 100), "textures/rock2.png"),
		new Sprite("Rock3", mainScene, glm::vec2(50, 270), glm::vec2(100, 100), "textures/rock3.png"),
		new Sprite("Rock4", mainScene, glm::vec2(50, 380), glm::vec2(100, 100), "textures/rock.png"),
		new Sprite("Rock5", mainScene, glm::vec2(50, 490), glm::vec2(100, 100), "textures/rock3.png"),
		new Sprite("Rock6", mainScene, glm::vec2(270, 50), glm::vec2(335, 100), "textures/rock3.png"),
		new Sprite("Rock7", mainScene, glm::vec2(350, 260), glm::vec2(110, 300), "textures/rock2.png"),
		new Sprite("Rock8", mainScene, glm::vec2(350, 425), glm::vec2(40, 20), "textures/rock.png")

	};
	Rocks[2]->setRotation(3.14);
	
	for (int i = 0; i < 8; i++)
	{
		Rocks[i]->setCollideDebug(true);
	}
	
	SceneObject *spawnObject = new SceneObject();
	spawnObject->setParent(rs2);
	spawnObject->setPosition(glm::vec2(rs2->getCenter().x, rs2->getCenter().y));
	wave->setVisible(false);
	//wave->setActive(false);
	//rs2->setRotation(3.14/2);
	rs2->setBoundAction("STOP");

	//set up colliders for sprites
	//wave->addCircleCollider("test", 10, 0, 0);
	wave->setCollideDebug(true);
	
	//set up bound actions for sprites
	rs2->setBoundAction("STOP");

	//collision sensors
	CollisionSensor *goal1 = new CollisionSensor("goal1", wave, rocketGoal, true);
	CollisionSensor *RocksCol[8] = { new CollisionSensor("c1", rs2, Rocks[0], true),
		new CollisionSensor("c2", rs2, Rocks[1], true),
		new CollisionSensor("c3", rs2, Rocks[2], true),
		new CollisionSensor("c4", rs2, Rocks[3], true),
		new CollisionSensor("c5", rs2, Rocks[4], true),
		new CollisionSensor("c6", rs2, Rocks[5], true),
		new CollisionSensor("c7", rs2, Rocks[6], true),
		new CollisionSensor("c8", rs2, Rocks[7], true)
	};

	CollisionSensor *RocksWaveCol[8] = { new CollisionSensor("w1", wave, Rocks[0], true),
		new CollisionSensor("c2", wave, Rocks[1], true),
		new CollisionSensor("c3", wave, Rocks[2], true),
		new CollisionSensor("c4", wave, Rocks[3], true),
		new CollisionSensor("c5", wave, Rocks[4], true),
		new CollisionSensor("c6", wave, Rocks[5], true),
		new CollisionSensor("c7", wave, Rocks[6], true),
		new CollisionSensor("c8", wave, Rocks[7], true)
	};


	//set up keyboard Sensors
	KeyboardSensor *ka = new KeyboardSensor("left",GLFW_KEY_A);
	KeyboardSensor *kd = new KeyboardSensor("right", GLFW_KEY_D);
	KeyboardSensor *kw = new KeyboardSensor("up", GLFW_KEY_W, "clicked");
	KeyboardSensor *ks = new KeyboardSensor("down", GLFW_KEY_S);
	KeyboardSensor *kj = new KeyboardSensor("rleft", GLFW_KEY_J);
	KeyboardSensor *kl = new KeyboardSensor("rright", GLFW_KEY_L);
	KeyboardSensor *ki = new KeyboardSensor("rup", GLFW_KEY_I);
	KeyboardSensor *kk = new KeyboardSensor("rdown", GLFW_KEY_K);
	KeyboardSensor *kSpace = new KeyboardSensor("space", GLFW_KEY_SPACE, "clicked");
	
	//CollisionSensor *waveCol = new CollisionSensor("waveCol", wave, , true);
	
	//motion acts for rocks col
	MotionActuator *RocksMot[8] = {
		new MotionActuator("rock1", rs2,"flipx"),
		new MotionActuator("rock1", rs2,"flipx"),
		new MotionActuator("rock1", rs2,"flipx"),
		new MotionActuator("rock1", rs2,"flipx"),
		new MotionActuator("rock1", rs2,"flipx"),
		new MotionActuator("rock1", rs2,"flipy"),
		new MotionActuator("rock1", rs2,"flipx"),
		new MotionActuator("rock1", rs2,"flipy")
	};

	ActiveActuator *waveActive = new ActiveActuator("wave", wave, false);
	VisibilityActuator *waveVisible = new VisibilityActuator("wave", wave, false);
	PositionActuator *waveAfterHit = new PositionActuator("waveMove", wave, 10000, 10000);


	RocksCol[0]->addActuator(RocksMot[0]);
	RocksCol[1]->addActuator(RocksMot[1]);
	RocksCol[2]->addActuator(RocksMot[2]);
	RocksCol[3]->addActuator(RocksMot[3]);
	RocksCol[4]->addActuator(RocksMot[4]);
	RocksCol[5]->addActuator(RocksMot[5]);
	RocksCol[6]->addActuator(RocksMot[6]);
	RocksCol[7]->addActuator(RocksMot[7]);

	RocksWaveCol[0]->addActuator(waveVisible);
	RocksWaveCol[1]->addActuator(waveVisible);
	RocksWaveCol[2]->addActuator(waveVisible);
	RocksWaveCol[3]->addActuator(waveVisible);
	RocksWaveCol[4]->addActuator(waveVisible);
	RocksWaveCol[5]->addActuator(waveVisible);
	RocksWaveCol[6]->addActuator(waveVisible);
	RocksWaveCol[7]->addActuator(waveVisible);

	/*RocksWaveCol[0]->addActuator(waveActive);
	RocksWaveCol[1]->addActuator(waveActive);
	RocksWaveCol[2]->addActuator(waveActive);
	RocksWaveCol[3]->addActuator(waveActive);
	RocksWaveCol[4]->addActuator(waveActive);
	RocksWaveCol[5]->addActuator(waveActive);
	RocksWaveCol[6]->addActuator(waveActive);
	RocksWaveCol[7]->addActuator(waveActive);
	*/

	RocksWaveCol[0]->addActuator(waveAfterHit);
	RocksWaveCol[1]->addActuator(waveAfterHit);
	RocksWaveCol[2]->addActuator(waveAfterHit);
	RocksWaveCol[3]->addActuator(waveAfterHit);
	RocksWaveCol[4]->addActuator(waveAfterHit);
	RocksWaveCol[5]->addActuator(waveAfterHit);
	RocksWaveCol[6]->addActuator(waveAfterHit);
	RocksWaveCol[7]->addActuator(waveAfterHit);



	//set up actuators
	MotionActuator *rLeft = new MotionActuator("rotateLeft", rs2, -.1, "rotateBy");
	MotionActuator *rRight = new MotionActuator("rotateRight", rs2, .1, "rotateBy");
	MotionActuator *mUp = new MotionActuator("mup", rs2,0, .5, "forceForward");
	MotionActuator *mLeft = new MotionActuator("mleft", rs2, 180, .1, "force");
	MotionActuator *mRight = new MotionActuator("mright", rs2, 0, .1, "force");
	MotionActuator *mDown = new MotionActuator("motion5", rs2, 270, .1, "force");
	MotionActuator *clearWaveMotion = new MotionActuator("clearWaveMotion", wave, 0, "both");
	MotionActuator *rotWaveMotion = new MotionActuator("rotWaveMotion", wave, rs2);
	PositionActuator *rocketFront = new PositionActuator("rocketFront", wave, spawnObject);
	VisibilityActuator *waveVisibleTrue = new VisibilityActuator("visbleWave", wave, true);
	ActiveActuator *waveActiveTrue = new ActiveActuator("activeWave", wave, true);
	MotionActuator *waveMotion = new MotionActuator("waveMotion", wave, 10, rs2);
	SceneActuator *sceneAct1 = new SceneActuator("scene1", "next");

	VisibilityActuator *v[6] = { new VisibilityActuator("visible1", health[5], false),
		new VisibilityActuator("visible2", health[4], false),
		new VisibilityActuator("visible3", health[3], false),
		new VisibilityActuator("visible4", health[2], false),
		new VisibilityActuator("visible5", health[1], false),
		new VisibilityActuator("visible6", health[0], false)
		
	};
	VisibilityActuator *v2[5] = { new VisibilityActuator("visible6", health[5], true),
		new VisibilityActuator("visible7", health[4], true),
		new VisibilityActuator("visible8", health[3], true),
		new VisibilityActuator("visible9", health[2], true),
		new VisibilityActuator("visible10", health[1], true)
	};
	//MotionActuator *waveMotion = new MotionActuator("waveMotion", wave, 10, rs2);
	TimesActuator *t = new TimesActuator("health", &mainScene, 6,"reset");
	t->addActuator(v[0]);
	t->addActuator(v[1]);
	t->addActuator(v[2]);
	t->addActuator(v[3]);
	t->addActuator(v[4]);
	t->addActuator(v[5]);
	t->addActuator(v2[0]);
	t->addActuator(v2[1]);
	t->addActuator(v2[2]);
	t->addActuator(v2[3]);
	t->addActuator(v2[4]);
	
	
	//set up sound 
	 //SoundActuator *Batman = new SoundActuator("sound/truth.wav");

	
	//will need later to change scenes
	//SceneActuator *s1 = new SceneActuator("scene1",&testScene, "next");
	//SceneActuator *s2 = new SceneActuator("scene2",&mainScene, "previous");
	//SceneActuator *s3 = new SceneActuator("scene3",&mainScene, "togglePause");
	
	
	//add actuators to the sensor
	kSpace->addActuator(waveVisibleTrue);
	kSpace->addActuator(waveActiveTrue);
	kSpace->addActuator(clearWaveMotion);
	kSpace->addActuator(rocketFront);
	kSpace->addActuator(rotWaveMotion);
	kSpace->addActuator(waveMotion);
	ka->addActuator(mLeft);
	kd->addActuator(mRight);
	//ks->addActuator(s1);
	kw->addActuator(mUp);
	kw->addActuator(t);
	kj->addActuator(rLeft);
	kl->addActuator(rRight);
	//kk->addActuator(s1);
	//ki->addActuator(s1);
	goal1->addActuator(sceneAct1);
	
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
	mainScene.addSensor(RocksCol[0]);
	mainScene.addSensor(RocksCol[1]);
	mainScene.addSensor(RocksCol[2]);
	mainScene.addSensor(RocksCol[3]);
	mainScene.addSensor(RocksCol[4]);
	mainScene.addSensor(RocksCol[5]);
	mainScene.addSensor(RocksCol[6]);
	mainScene.addSensor(RocksCol[7]);

	mainScene.addSensor(RocksWaveCol[0]);
	mainScene.addSensor(RocksWaveCol[1]);
	mainScene.addSensor(RocksWaveCol[2]);
	mainScene.addSensor(RocksWaveCol[3]);
	mainScene.addSensor(RocksWaveCol[4]);
	mainScene.addSensor(RocksWaveCol[5]);
	mainScene.addSensor(RocksWaveCol[6]);
	mainScene.addSensor(RocksWaveCol[7]);

	SceneDirector::getInstance()->addSensor(goal1);
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