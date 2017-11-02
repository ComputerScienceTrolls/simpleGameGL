#include "KeyHandler.h"
#include <iostream>

std::auto_ptr<KeyHandler> KeyHandler::instance;

KeyHandler::KeyHandler()
{
	for (int i = 0; i < 1024; i++)
	{
		Keys[i] = GL_FALSE;
	}
}

KeyHandler* KeyHandler::getInstance()
{
	if (instance.get() == nullptr)
	{
		instance.reset(new KeyHandler());
	}

	return instance.get();
}

KeyHandler::~KeyHandler()
{
}
