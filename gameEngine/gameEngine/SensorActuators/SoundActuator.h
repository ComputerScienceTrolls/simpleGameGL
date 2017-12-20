#ifndef SOUNDACTUATOR_H
#define SOUNDACTUATOR_H

#include "AbstractActuator.h"
#include "../Sound.h"

using std::string;


class SoundActuator : public AbstractActuator
{
public:
	SoundActuator(string);
	~SoundActuator();
	void run();

private:
	Sound* sound;
};

#endif