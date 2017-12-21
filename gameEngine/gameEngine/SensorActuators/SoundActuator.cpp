#include "SoundActuator.h"

SoundActuator::SoundActuator(std::string dir)
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