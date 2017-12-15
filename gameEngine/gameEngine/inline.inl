inline
void SceneDirector::Update(float delta)
{
	currentScene->Update(delta);

	//check sensors 
	for (int i = 0; i < sensors.size(); i++)
	{
		sensors.at(i)->sense();
	}

	/*
	// Measure speed
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0)
	{ // If last prinf() was more than 1 sec ago
	  // printf and reset timer
		printf("%f ms/frame\n", 1000.0 / double(nbFrames));
		nbFrames = 0;
		lastTime += 1.0;
	}
	*/
}