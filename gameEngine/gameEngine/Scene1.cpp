#include "Scene1.h"

Scene1::Scene1()
{
	
}

Scene1::Scene1(std::string n, GLuint w, GLuint h)
{
	this->initilized = false;
	this->name = n;
	this->width = w;
	this->height = h;
	this->camera = new Camera(w, h);
	this->camera->setZoom(glm::vec2(1));

	this->MovingSceneObjects.push_back(this->camera);
	this->MovingSceneObjects.push_back(this->background);

}

void Scene1::loadContents()
{
	//set up sprites
	Sprite *rs2 = new Sprite("rocket", this, glm::vec2(150, 300), glm::vec2(50, 35), "textures/Rocket001_off.png");
	rs2->removeCollider("default");
	std::vector<glm::vec2> rsPolyColVerts;
	rsPolyColVerts.push_back(glm::vec2(0, 0));
	rsPolyColVerts.push_back(glm::vec2(50, 500));
	rsPolyColVerts.push_back(glm::vec2(100, 10));

	rs2->setRotation(float(3.14 / 2));
	rs2->removeCollider("default");

	std::vector<glm::vec2> testv;
	testv.push_back(glm::vec2(0, 0));
	testv.push_back(glm::vec2(10, 10));
	testv.push_back(glm::vec2(0, 10));
	testv.push_back(glm::vec2(0, 0));

	rs2->addPolyCollider("test", testv);
	rs2->setCollideDebug(true);
	Sprite *rCopy = new Sprite(rs2);
	rCopy->setPosX(200);
	Sprite *rocketGoal = new Sprite("rocketGoal", this, glm::vec2(750, 25), glm::vec2(50, 35), "textures/Rocket001_off.png");
	rocketGoal->setRotation(float(3.14 / 2));
	Sprite *wave = new Sprite("wave", this, glm::vec2(0, 0), glm::vec2(20, 40), "textures/fullSignal.png");
	wave->hide();
	Sprite *Gui = new Sprite("fuel", this, glm::vec2(150, 550), glm::vec2(300, 60), "textures/fuel_bar.png");

	PolyCollider *polyWantsACracker = new PolyCollider("poly", rsPolyColVerts);
	this->addCollider(polyWantsACracker);

	Sprite *health[6] = { new Sprite("empty", this, glm::vec2(-1000, -1000), glm::vec2(30, 30), "textures/fuel_block.png"),
		new Sprite("health", this, glm::vec2(50, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//50
		new Sprite("health2", this, glm::vec2(95, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//95
		new Sprite("health3", this, glm::vec2(145, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//145
		new Sprite("health4", this, glm::vec2(190, 550), glm::vec2(50, 30), "textures/fuel_block.png"),//190
		new Sprite("health5", this, glm::vec2(235, 550), glm::vec2(52, 30), "textures/fuel_block.png")
	};
	Sprite *Rocks[8] = { new Sprite("Rock1", this, glm::vec2(50, 50), glm::vec2(100, 100), "textures/rock.png"),
		new Sprite("Rock2", this, glm::vec2(50, 160), glm::vec2(100, 100), "textures/rock2.png"),
		new Sprite("Rock3", this, glm::vec2(50, 270), glm::vec2(100, 100), "textures/rock3.png"),
		new Sprite("Rock4", this, glm::vec2(50, 380), glm::vec2(100, 100), "textures/rock.png"),
		new Sprite("Rock5", this, glm::vec2(50, 490), glm::vec2(100, 100), "textures/rock3.png"),
		new Sprite("Rock6", this, glm::vec2(270, 50), glm::vec2(335, 100), "textures/rock3.png"),
		new Sprite("Rock7", this, glm::vec2(350, 260), glm::vec2(110, 300), "textures/rock2.png"),
		new Sprite("Rock8", this, glm::vec2(350, 425), glm::vec2(40, 20), "textures/rock.png")

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

	Rocks[2]->setRotation(float(3.14));

	for (int i = 0; i < 8; i++)
	{
		Rocks[i]->setCollideDebug(true);
	}

	SceneObject *spawnObject = new SceneObject();
	spawnObject->setPosition(glm::vec2(rs2->getPosition().x + rs2->getSize().x / 2, rs2->getPosition().y - rs2->getSize().y / 2));
	std::cout << "\ntest: " << rs2->getPosX();
	std::cout << "\ntest2: " << spawnObject->getPosX();
	wave->setVisible(false);
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

	CollisionSensor *rocketRocksCollsionSensor = new CollisionSensor("rockgroup", rs2, rockVector);

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
	KeyboardSensor *ka = new KeyboardSensor("left", GLFW_KEY_A);
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
	MotionActuator *mUp = new MotionActuator("mup", rs2, .5, "forceForward");
	ObjectPoolActuator *rocketBullets = new ObjectPoolActuator("test", wave, 10, spawnObject, 10, rs2, "spriteSpawnRotateForce");
	SceneActuator *sceneAct1 = new SceneActuator("scene1", "next");

	//set up sound 
	SoundActuator *shootSound = new SoundActuator("sound/shoot.wav", "");
	SoundActuator *moveSound = new SoundActuator("sound/movement.wav", "");
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
	TimesActuator *t = new TimesActuator("health", &*this, 6, "reset");
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

	this->addSensor(ka);
	this->addSensor(kd);
	this->addSensor(kw);
	this->addSensor(ks);
	this->addSensor(kj);
	this->addSensor(kl);
	this->addSensor(ki);
	this->addSensor(kk);
	this->addSensor(kSpace);
	this->addSensor(rocketRocksCollsionSensor);

	this->addSensor(RocksWaveCol[0]);
	this->addSensor(RocksWaveCol[1]);
	this->addSensor(RocksWaveCol[2]);
	this->addSensor(RocksWaveCol[3]);
	this->addSensor(RocksWaveCol[4]);
	this->addSensor(RocksWaveCol[5]);
	this->addSensor(RocksWaveCol[6]);
	this->addSensor(RocksWaveCol[7]);

	//set camera witdth and height
	this->setCameraHeight(600);
	this->setCameraWidth(800);
}

Scene1::~Scene1()
{
}
