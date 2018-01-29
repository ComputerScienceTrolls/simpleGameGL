#include "SoundActuator.h"

SoundActuator::SoundActuator(std::string dir, std::string con)
{
	sound = new Sound(dir);
	if (con == "looping")
	{
		sound->isLooping(true);
		sound->play();
	}
}

SoundActuator::~SoundActuator()
{
	delete sound;
}

void SoundActuator::run()
{
	if (!sound->isPlaying())
	{
		sound->play();
	}

}