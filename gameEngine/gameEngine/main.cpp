#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"

#include "SceneDirector.h"
#include "Sprite.h"

#include "ObjectPool.h"

#include "SensorActuators/CameraActuator.h"

#include "Observers/ObserverHandler.h"
#include "Observers/Observer.h"
#include "Observers/ColliderObserver.h"
#include "Observers/CheckBoundsObserver.h"
#include "Observers/CollisionGroupObserver.h"

#include "SensorActuators/MotionActuator.h"
#include "SensorActuators/PositionActuator.h"
#include "SensorActuators/CollisionSensor.h"
#include "SensorActuators/CheckBoundsSensor.h"
#include "SensorActuators/VisibilityActuator.h"
#include "SensorActuators/ActiveActuator.h"
#include "SensorActuators/KeyboardSensor.h"
#include "SensorActuators/SceneActuator.h"
#include "SensorActuators/SoundActuator.h"
#include "SensorActuators/AlwaysSensor.h"
#include "SensorActuators/TimesActuator.h"
#include "SensorActuators/ObjectPoolActuator.h"

#include "BoxColliderAsync.h"
#include "Particle.h"

#include <thread>

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Scene mainScene("main",800, 600);
Scene scene2 ("level2", 800, 600);
Scene scene3("levels3", 800, 600);


int main(int argc, char *argv[])
{	
	//initiate main scene
	mainScene.Init();

	
	//set up sprites
	Sprite *rs2 = new Sprite("rocket", mainScene, glm::vec2(150, 300), glm::vec2(50, 35), "textures/Rocket001_off.png");
	rs2->removeCollider("default");
	std::vector<glm::vec2> rsPolyColVerts;
	rsPolyColVerts.push_back(glm::vec2(0, 0));
	rsPolyColVerts.push_back(glm::vec2(50, 500));
	rsPolyColVerts.push_back(glm::vec2(100, 10));
	
	//rs2->addPolyCollider("poly", rsPolyColVerts);
	rs2->setRotation(float(3.14 / 2));
	rs2->removeCollider("default");

	std::vector<glm::vec2> testv;
	testv.push_back(glm::vec2(0,0));
	testv.push_back(glm::vec2(10, 10));
	testv.push_back(glm::vec2(0, 10));
	testv.push_back(glm::vec2(0, 0));

	rs2->addPolyCollider("test", testv);
	rs2->setCollideDebug(true);
	Sprite *rCopy = new Sprite(rs2);
	rCopy->setPosX(200);
	Sprite *rocketGoal = new Sprite("rocketGoal", mainScene, glm::vec2(750, 25), glm::vec2(50, 35), "textures/Rocket001_off.png");
	rocketGoal->setRotation(float(3.14/2));
	Sprite *wave = new Sprite("wave", mainScene, glm::vec2(0, 0), glm::vec2(20, 40), "textures/fullSignal.png");
	//wave->removeCollider("default");
	wave->hide();
	Sprite *Gui = new Sprite("fuel", mainScene, glm::vec2(150, 550), glm::vec2(300, 60), "textures/fuel_bar.png");

	PolyCollider *polyWantsACracker = new PolyCollider("poly", rsPolyColVerts);
	mainScene.addCollider(polyWantsACracker);

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

	//remove the default colliders from the rocks and add a poly collider
	for (int i = 0; i < sizeof(Rocks) / sizeof(Rocks[0]); i++)
	{
		Rocks[i]->removeCollider("default");
		std::vector<glm::vec2> temp;
		temp.push_back(glm::vec2(0, 0));
		temp.push_back(glm::vec2(100, 100));
		temp.push_back(glm::vec2(100, 0));

		Rocks[i]->addPolyCollider("test", temp);
	}

	/*
	std::thread th([]()
	{
		std::vector<AbstractSprite*> sprites;
		for (unsigned int i = 0; i < 200; i++)
		{
			Sprite *temp = new Sprite("test", glm::vec2(200), glm::vec2(10), "textures/fullSignal.png", glm::vec2(.1 *i, .01 *i));
			temp->setBoundAction("DIE");
			sprites.push_back(temp);
		}
		mainScene.loadSprites(sprites);
	});

	std::thread th2([]()
	{
		std::vector<AbstractSprite*> sprites;
		for (unsigned int i = 0; i < 198; i++)
		{
			Sprite *temp = new Sprite("test", glm::vec2(200), glm::vec2(10), "textures/fullSignal.png", glm::vec2(.01 *i, .1 *i));
			temp->setBoundAction("DIE");
			sprites.push_back(temp);
		}
		mainScene.loadSprites(sprites);
	});

	std::thread th3([]()
	{
		std::vector<AbstractSprite*> sprites;
		for (unsigned int i = 0; i < 20; i++)
		{
			Sprite *temp = new Sprite("test", glm::vec2(200), glm::vec2(10), "textures/fullSignal.png", glm::vec2(.01 *i, .01 *i));
			temp->setBoundAction("DIE");
			sprites.push_back(temp);
		}
		mainScene.loadSprites(sprites);
	});

	std::thread th4([]()
	{
		std::vector<AbstractSprite*> sprites;
		for (unsigned int i = 0; i < 20; i++)
		{
			Sprite *temp = new Sprite("test", glm::vec2(200), glm::vec2(10), "textures/fullSignal.png", glm::vec2(.01 *i, .01 *i));
			temp->setBoundAction("DIE");
			sprites.push_back(temp);
		}
		mainScene.loadSprites(sprites);
	});

	std::thread th5([]()
	{
		std::vector<AbstractSprite*> sprites;
		for (unsigned int i = 0; i < 20; i++)
		{
			Sprite *temp = new Sprite("test", glm::vec2(200), glm::vec2(10), "textures/fullSignal.png", glm::vec2(.01 *i, .01 *i));
			temp->setBoundAction("DIE");
			sprites.push_back(temp);
		}
		mainScene.loadSprites(sprites);
	});

	th5.detach();
	std::thread th6([]()
	{
		std::vector<AbstractSprite*> sprites;
		for (unsigned int i = 0; i < 20; i++)
		{
			Sprite *temp = new Sprite("test", glm::vec2(200), glm::vec2(10), "textures/fullSignal.png", glm::vec2(.01 *i, .01 *i));
			temp->setBoundAction("DIE");
			sprites.push_back(temp);
		}
		mainScene.loadSprites(sprites);
	});

	th6.detach();
	th.detach();
	th2.detach();
	th3.detach();
	th4.detach(); 
	
	std::vector<AbstractSprite*> sprites;
	for (unsigned int i = 0; i < 150; i++)
	{
		Sprite *temp = new Sprite("test", glm::vec2(200), glm::vec2(10), "textures/fullSignal.png", glm::vec2(-.01 *i, -.01 *i));
		temp->setBoundAction("DIE");
		sprites.push_back(temp);
	}
	mainScene.loadSprites(sprites);
	*/
	
	/*
	for (unsigned int i = 0; i < 0; i++)
	{
		Sprite *temp = new Sprite("test", mainScene, glm::vec2(200), glm::vec2(10), "textures/fullSignal.png", glm::vec2(.01 *i, .01 *i));
	
		temp->setBoundAction("BOUNCE");
		
		CollisionSensor *temp2 = new CollisionSensor("signals", temp, Rocks[0], true);
		CollisionSensor *temp3 = new CollisionSensor("signals", temp, Rocks[1], true);
		CollisionSensor *temp4 = new CollisionSensor("signals", temp, Rocks[2], true);
		CollisionSensor *temp5 = new CollisionSensor("signals", temp, Rocks[3], true);
		CollisionSensor *temp6 = new CollisionSensor("signals", temp, Rocks[4], true);
		CollisionSensor *temp7 = new CollisionSensor("signals", temp, Rocks[5], true);
		CollisionSensor *temp8 = new CollisionSensor("signals", temp, Rocks[6], true);
		MotionActuator *temp9 = new MotionActuator("signalsMot", temp, "flipy");
		
		temp2->addActuator(temp9);
		temp3->addActuator(temp9);
		temp4->addActuator(temp9);
		temp5->addActuator(temp9);
		temp6->addActuator(temp9);
		temp7->addActuator(temp9);
		temp8->addActuator(temp9);

		mainScene.addSensor(temp2);
		mainScene.addSensor(temp3);
		mainScene.addSensor(temp4);
		mainScene.addSensor(temp5);
		mainScene.addSensor(temp6);
		mainScene.addSensor(temp7);
		mainScene.addSensor(temp8);
		
	}
	*/

	GLuint nr_particles = 500;
	std::vector<Particle> particles;

	for (GLuint i = 0; i < nr_particles; ++i)
	particles.push_back(Particle());

	Rocks[2]->setRotation(float(3.14));
	
	for (int i = 0; i < 8; i++)
	{
		Rocks[i]->setCollideDebug(true);
	}
	
	SceneObject *spawnObject = new SceneObject();
	spawnObject->setPosition(glm::vec2(rs2->getPosition().x + rs2->getSize().x/2, rs2->getPosition().y - rs2->getSize().y / 2));
	std::cout << "\ntest: " << rs2->getPosX();
	std::cout << "\ntest2: " << spawnObject->getPosX();
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
	/*CollisionSensor *RocksCol[8] = { new CollisionSensor("c1", rs2, Rocks[0], true),
		new CollisionSensor("c2", rs2, Rocks[1], true),
		new CollisionSensor("c3", rs2, Rocks[2], true),
		new CollisionSensor("c4", rs2, Rocks[3], true),
		new CollisionSensor("c5", rs2, Rocks[4], true),
		new CollisionSensor("c6", rs2, Rocks[5], true),
		new CollisionSensor("c7", rs2, Rocks[6], true),
		new CollisionSensor("c8", rs2, Rocks[7], true)
	};*/

	std::vector<AbstractSprite*> rockVector;
	rockVector.push_back(Rocks[0]);
	rockVector.push_back(Rocks[1]);
	rockVector.push_back(Rocks[2]);
	rockVector.push_back(Rocks[3]);
	rockVector.push_back(Rocks[4]);
	rockVector.push_back(Rocks[5]);
	rockVector.push_back(Rocks[6]);
	rockVector.push_back(Rocks[7]);

	std::cout << rockVector.at(0)->getName() << "\n" << rockVector.at(1)->getName() << "\n" << rockVector.at(2)->getName();

	CollisionSensor *rocketRocksCollsionSensor =  new CollisionSensor("rockgroup", rs2, rockVector);

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
	AlwaysSensor *Always = new AlwaysSensor();
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


	rocketRocksCollsionSensor->addActuator(RocksMot[0]);
	rocketRocksCollsionSensor->addActuator(RocksMot[1]);
	rocketRocksCollsionSensor->addActuator(RocksMot[2]);
	rocketRocksCollsionSensor->addActuator(RocksMot[3]);
	rocketRocksCollsionSensor->addActuator(RocksMot[4]);
	rocketRocksCollsionSensor->addActuator(RocksMot[5]);
	rocketRocksCollsionSensor->addActuator(RocksMot[6]);
	rocketRocksCollsionSensor->addActuator(RocksMot[7]);

	RocksWaveCol[0]->addActuator(waveVisible);
	RocksWaveCol[1]->addActuator(waveVisible);
	RocksWaveCol[2]->addActuator(waveVisible);
	RocksWaveCol[3]->addActuator(waveVisible);
	RocksWaveCol[4]->addActuator(waveVisible);
	RocksWaveCol[5]->addActuator(waveVisible);
	RocksWaveCol[6]->addActuator(waveVisible);

	RocksWaveCol[0]->addActuator(waveAfterHit);
	RocksWaveCol[1]->addActuator(waveAfterHit);
	RocksWaveCol[2]->addActuator(waveAfterHit);
	RocksWaveCol[3]->addActuator(waveAfterHit);
	RocksWaveCol[4]->addActuator(waveAfterHit);
	RocksWaveCol[5]->addActuator(waveAfterHit);
	RocksWaveCol[6]->addActuator(waveAfterHit);
	RocksWaveCol[7]->addActuator(waveAfterHit);

	//set up actuators
	MotionActuator *rLeft = new MotionActuator("rotateLeft", rs2, float(-.1), "rotateBy");
	MotionActuator *rRight = new MotionActuator("rotateRight", rs2, float(.1), "rotateBy");
	MotionActuator *keepSpawnerInFrontOfRocket = new MotionActuator("keepSpawnerInFrontOfRocket", rs2, spawnObject, "setInFront");
	MotionActuator *mUp = new MotionActuator("mup", rs2,.5, "forceForward");
	ObjectPoolActuator *rocketBullets = new ObjectPoolActuator("test", wave, 10, spawnObject, 10, rs2, "spriteSpawnRotateForce");
	SceneActuator *sceneAct1 = new SceneActuator("scene1", "next");
	
	//set up sound 
	SoundActuator *shootSound = new SoundActuator("sound/shoot.wav", "");
	SoundActuator *moveSound = new SoundActuator("sound/movement.wav","");
	SoundActuator *music = new SoundActuator("sound/music.wav", "looping");

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

	//add actuators to the sensor
	kSpace->addActuator(rocketBullets);
	kSpace->addActuator(shootSound);
	kw->addActuator(mUp);
	kw->addActuator(t);
	kw->addActuator(moveSound);
	kj->addActuator(rLeft);
	kl->addActuator(rRight);
	goal1->addActuator(sceneAct1);
	//A->addActuator(music);
	//Always->addActuator(keepSpawnerInFrontOfRocket);
	
	//add sensors to scene 1
	//mainScene.addSensor(A);
	mainScene.addSensor(ka);
	mainScene.addSensor(kd);
	mainScene.addSensor(kw);
	mainScene.addSensor(ks);
	mainScene.addSensor(kj);
	mainScene.addSensor(kl);
	mainScene.addSensor(ki);
	mainScene.addSensor(kk);
	mainScene.addSensor(kSpace);
	mainScene.addSensor(rocketRocksCollsionSensor);

	mainScene.addSensor(RocksWaveCol[0]);
	mainScene.addSensor(RocksWaveCol[1]);
	mainScene.addSensor(RocksWaveCol[2]);
	mainScene.addSensor(RocksWaveCol[3]);
	mainScene.addSensor(RocksWaveCol[4]);
	mainScene.addSensor(RocksWaveCol[5]);
	mainScene.addSensor(RocksWaveCol[6]);
	mainScene.addSensor(RocksWaveCol[7]);

	SceneDirector::getInstance()->addSensor(goal1);

	//add scenes to the scene director
	SceneDirector::getInstance()->addScene(&scene2);
	SceneDirector::getInstance()->addScene(&scene3);

	//set camera witdth and height
	mainScene.setCameraHeight(600);
	mainScene.setCameraWidth(800);

	//start game 
	SceneDirector::getInstance()->Start();

	return 0;
}
