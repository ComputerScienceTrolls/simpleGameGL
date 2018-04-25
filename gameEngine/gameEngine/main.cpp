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
#include "SpriteSheetSprite.h"

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
//Scene scene2 ("level2", 800, 600);
//Scene scene3("levels3", 800, 600);


int main(int argc, char *argv[])
{
	//initiate openAl component
	alutInit(NULL, 0);
	
	//initiate main scene
	mainScene.Init();

	
	//set up sprites
	Sprite *rocket = new Sprite("rocket", mainScene, glm::vec2(150, 300), glm::vec2(50, 35), "");
	rocket->setRotation(3.14 / 2);
	rocket->setCollideDebug(true);
	Sprite *wave = new Sprite("wave", mainScene, glm::vec2(0, 0), glm::vec2(20, 40), "");
	wave->hide();
	Sprite *Gui = new Sprite("fuel", mainScene, glm::vec2(150, 550), glm::vec2(300, 60), "");
	Sprite *health[6] = { new Sprite("empty", mainScene, glm::vec2(-1000, -1000), glm::vec2(30, 30), ""),
		new Sprite("health", mainScene, glm::vec2(50, 550), glm::vec2(50, 30), ""),//50
		new Sprite("health2", mainScene, glm::vec2(95, 550), glm::vec2(50, 30), ""),//95
		new Sprite("health3", mainScene, glm::vec2(145, 550), glm::vec2(50, 30), ""),//145
		new Sprite("health4", mainScene, glm::vec2(190, 550), glm::vec2(50, 30), ""),//190
		new Sprite("health5", mainScene, glm::vec2(235, 550), glm::vec2(52, 30), "")
	};

	SpriteSheetSprite *spriteSheetTest = new SpriteSheetSprite("spreadsheettest", mainScene, glm::vec2(150, 300), glm::vec2(202, 350), 1, 4, "textures/metal_spider.png");

	float test = spriteSheetTest->angleTo(health[0]);

	SceneObject *spawnObject = new SceneObject();
	spawnObject->setParent(rocket);
	spawnObject->setPosition(glm::vec2(rocket->getCenter().x, rocket->getCenter().y));
	wave->setVisible(false);

	rocket->setBoundAction("STOP");

	wave->setCollideDebug(true);
	
	//set up bound actions for sprites
	rocket->setBoundAction("STOP");


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
	AlwaysSensor *A = new AlwaysSensor();

	ActiveActuator *waveActive = new ActiveActuator("wave", wave, false);
	VisibilityActuator *waveVisible = new VisibilityActuator("wave", wave, false);
	PositionActuator *waveAfterHit = new PositionActuator("waveMove", wave, 10000, 10000);

	//set up actuators
	MotionActuator *rLeft = new MotionActuator("rotateLeft", rocket, -.1, "rotateBy");
	MotionActuator *rRight = new MotionActuator("rotateRight", rocket, .1, "rotateBy");
	MotionActuator *mUp = new MotionActuator("mup", rocket,0, .5, "forceForward");
	MotionActuator *clearWaveMotion = new MotionActuator("clearWaveMotion", wave, 0, "both");
	MotionActuator *rotWaveMotion = new MotionActuator("rotWaveMotion", wave, rocket);
	PositionActuator *rocketFront = new PositionActuator("rocketFront", wave, spawnObject);
	VisibilityActuator *waveVisibleTrue = new VisibilityActuator("visbleWave", wave, true);
	ActiveActuator *waveActiveTrue = new ActiveActuator("activeWave", wave, true);
	MotionActuator *waveMotion = new MotionActuator("waveMotion", wave, 10, rocket);
	SceneActuator *sceneAct1 = new SceneActuator("scene1", "next");
	
	//set up sound 
	//SoundActuator *shootSound = new SoundActuator("sound/shoot.wav", "");
	//SoundActuator *moveSound = new SoundActuator("sound/movement.wav","");
	//SoundActuator *music = new SoundActuator("sound/music.wav", "looping");

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
	kSpace->addActuator(waveVisibleTrue);
	kSpace->addActuator(waveActiveTrue);
	kSpace->addActuator(clearWaveMotion);
	kSpace->addActuator(rocketFront);
	kSpace->addActuator(rotWaveMotion);
	kSpace->addActuator(waveMotion);
	//kSpace->addActuator(shootSound);
	kw->addActuator(mUp);
	kw->addActuator(t);
	//kw->addActuator(moveSound);
	kj->addActuator(rLeft);
	kl->addActuator(rRight);
	//A->addActuator(music);
	
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


	//add scenes to the scene director
	//SceneDirector::getInstance()->addScene(&scene2);
	//SceneDirector::getInstance()->addScene(&scene3);


	//set camera witdth and height
	mainScene.setCameraHeight(600);
	mainScene.setCameraWidth(800);

	//start game 
	SceneDirector::getInstance()->Start();
	
	//delete items that are on heap that is used by openal
	alutExit();

	return 0;
}