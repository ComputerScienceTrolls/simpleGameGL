#include "SoundActuator.h"



SoundActuator::SoundActuator(string dir)
{
	sound = new Sound(dir);
}


SoundActuator::~SoundActuator()
{
	delete sound;
}

void SoundActuator::run()
{
	sound->play();
}