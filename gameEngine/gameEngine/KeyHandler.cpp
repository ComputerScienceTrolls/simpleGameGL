#include "KeyHandler.h"
#include <iostream>

KeyHandler* KeyHandler::instance = nullptr;

KeyHandler::KeyHandler()
{
	for (int i = 0; i < 1024; i++)
	{
		Keys[i] = GL_FALSE;
	}
}

KeyHandler * KeyHandler::getInstance()
{
	if (instance == nullptr)
	{
		instance = new KeyHandler();
	}

	return instance;
}

KeyHandler::~KeyHandler()
{
}
