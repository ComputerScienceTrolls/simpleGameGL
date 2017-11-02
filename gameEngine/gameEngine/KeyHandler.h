#include <GLFW/glfw3.h>
#include <memory>

class KeyHandler
{
public:
	static KeyHandler* getInstance();
	GLboolean Keys[1024];
	~KeyHandler();

private:
	KeyHandler();
	static std::auto_ptr<KeyHandler> instance;
};

