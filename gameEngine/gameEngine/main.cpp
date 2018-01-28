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
	Sprite *rocketGoal = new Sprite("rocketGoal", mainScene, glm::vec2(750, 25), glm::vec2(50, 35), "textures/Rocket001_off.png");
	rocketGoal->setRotation(3.14/2);
	Sprite *wave = new Sprite("wave", mainScene, glm::vec2(0, 0), glm::vec2(5, 10), "textures/paddle.png");
	Sprite *Gui = new Sprite("fuel", mainScene, glm::vec2(150, 550), glm::vec2(300, 60), "textures/fuel_bar.png");
	Sprite *health[5] = { new Sprite("health", mainScene, glm::vec2(50, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//50
		new Sprite("health2", mainScene, glm::vec2(95, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//95
		new Sprite("health3", mainScene, glm::vec2(145, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//145
		new Sprite("health4", mainScene, glm::vec2(190, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//190
		new Sprite("health5", mainScene, glm::vec2(235, 550), glm::vec2(52, 30), "textures/fuel_block.png")
	};
	Sprite *Rocks[7] = { new Sprite("Rock1", mainScene, glm::vec2(50, 50), glm::vec2(100, 100), "textures/rock.png"),
		new Sprite("Rock2", mainScene, glm::vec2(50, 160), glm::vec2(100, 100), "textures/rock2.png"),
		new Sprite("Rock3", mainScene, glm::vec2(50, 270), glm::vec2(100, 100), "textures/rock3.png"),
		new Sprite("Rock4", mainScene, glm::vec2(50, 380), glm::vec2(100, 100), "textures/rock.png"),
		new Sprite("Rock5", mainScene, glm::vec2(50, 490), glm::vec2(100, 100), "textures/rock3.png"),
		new Sprite("Rock6", mainScene, glm::vec2(300, 50), glm::vec2(400, 100), "textures/rock3.png"),
		new Sprite("Rock7", mainScene, glm::vec2(350, 260), glm::vec2(110, 300), "textures/rock2.png")
	};
	
	for (int i = 0; i < 7; i++)
	{
		Rocks[i]->setCollideDebug(true);
	}
	
	SceneObject *spawnObject = new SceneObject();
	spawnObject->setParent(rs2);
	spawnObject->setPosition(glm::vec2(175,316));
	wave->setVisible(false);
	//wave->setActive(false);
	//rs2->setRotation(3.14/2);
	rs2->setBoundAction("STOP");

	//set up colliders for sprites
	wave->addCircleCollider("test", 10, 0, 0);
	wave->setCollideDebug(true);
	
	//set up bound actions for sprites
	rs2->setBoundAction("STOP");

	//collision sensors
	CollisionSensor *RocksCol[7] = { new CollisionSensor("c1", rs2, Rocks[0]),
		new CollisionSensor("c1", rs2, Rocks[1]),
		new CollisionSensor("c1", rs2, Rocks[2]),
		new CollisionSensor("c1", rs2, Rocks[3]),
		new CollisionSensor("c1", rs2, Rocks[4]),
		new CollisionSensor("c1", rs2, Rocks[5]),
		new CollisionSensor("c1", rs2, Rocks[6])
	};

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
	
	//CollisionSensor *waveCol = new CollisionSensor("waveCol", wave, , true);
	
	//motion acts for rocks col
	MotionActuator *RocksMot[7] = {
		new MotionActuator("rock1", Rocks[0],"flipx"),
		new MotionActuator("rock1", Rocks[1],"flipx"),
		new MotionActuator("rock1", Rocks[2],"flipx"),
		new MotionActuator("rock1", Rocks[3],"flipx"),
		new MotionActuator("rock1", Rocks[4],"flipy"),
		new MotionActuator("rock1", Rocks[5],"flipx"),
		new MotionActuator("rock1", Rocks[6],"flipx"),
	};

	RocksCol[0]->addActuator(RocksMot[0]);
	RocksCol[1]->addActuator(RocksMot[1]);
	RocksCol[2]->addActuator(RocksMot[2]);
	RocksCol[3]->addActuator(RocksMot[3]);
	RocksCol[4]->addActuator(RocksMot[4]);
	RocksCol[5]->addActuator(RocksMot[5]);
	RocksCol[6]->addActuator(RocksMot[6]);

	//set up actuators
	MotionActuator *rLeft = new MotionActuator("rotateLeft", rs2, -.1, "rotateBy");
	MotionActuator *rRight = new MotionActuator("rotateRight", rs2, .1, "rotateBy");
	MotionActuator *mUp = new MotionActuator("mup", rs2,0, .1, "forceForward");
	MotionActuator *mLeft = new MotionActuator("mleft", rs2, 180, .1, "force");
	MotionActuator *mRight = new MotionActuator("mright", rs2, 0, .1, "force");
	MotionActuator *mDown = new MotionActuator("motion5", rs2, 270, .1, "force");
	MotionActuator *clearWaveMotion = new MotionActuator("clearWaveMotion", wave, 0, "both");
	PositionActuator *rocketFront = new PositionActuator("rocketFront", wave, spawnObject);
	VisibilityActuator *waveVisible = new VisibilityActuator("visbleWave", wave, true);
	VisibilityActuator *v1 = new VisibilityActuator("visible1", health[0], false);
	MotionActuator *waveMotion = new MotionActuator("waveMotion", wave, 10, rs2);
	
	
	//set up sound 
	 //SoundActuator *Batman = new SoundActuator("sound/truth.wav");

	
	//will need later to change scenes
	//SceneActuator *s1 = new SceneActuator("scene1",&testScene, "next");
	//SceneActuator *s2 = new SceneActuator("scene2",&mainScene, "previous");
	//SceneActuator *s3 = new SceneActuator("scene3",&mainScene, "togglePause");
	
	
	//add actuators to the sensor
	kSpace->addActuator(clearWaveMotion);
	kSpace->addActuator(rocketFront);
	kSpace->addActuator(waveVisible);
	kSpace->addActuator(waveMotion);
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
	mainScene.addSensor(RocksCol[0]);
	mainScene.addSensor(RocksCol[1]);
	mainScene.addSensor(RocksCol[2]);
	mainScene.addSensor(RocksCol[3]);
	mainScene.addSensor(RocksCol[4]);
	mainScene.addSensor(RocksCol[5]);
	mainScene.addSensor(RocksCol[6]);
	
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