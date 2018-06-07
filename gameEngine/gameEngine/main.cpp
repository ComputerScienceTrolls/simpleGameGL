#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "SceneDirector.h"
#include "Sprite.h"
#include "Scene1.h"

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Scene scene2 ("level2", 800, 600);
Scene scene3("levels3", 800, 600);


int main(int argc, char *argv[])
{	
	Scene1 *mainScene = new Scene1("main", 800, 600);
	//initiate main scene
	mainScene->Init();

	//add scenes to the scene director
	SceneDirector::getInstance()->addScene(mainScene);
	SceneDirector::getInstance()->addScene(&scene3);

	//set camera witdth and height
	mainScene->setCameraHeight(600);
	mainScene->setCameraWidth(800);

	//start game 
	SceneDirector::getInstance()->Start();

	return 0;
}