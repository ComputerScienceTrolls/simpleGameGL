#ifndef SOUNDACTUATOR_H
#define SOUNDACTUATOR_H

#include "AbstractActuator.h"
#include "../Sound.h"


class SoundActuator : public AbstractActuator
{
public:
	SoundActuator(std::string, std::string con = "");
	~SoundActuator();
	void run();

private:
	Sound* sound;
};

#endif