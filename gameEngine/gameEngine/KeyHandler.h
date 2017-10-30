#include <GLFW/glfw3.h>

class KeyHandler
{
public:
	static KeyHandler* getInstance();
	GLboolean Keys[1024];
	~KeyHandler();

private:
	KeyHandler();
	static KeyHandler* instance;
};

