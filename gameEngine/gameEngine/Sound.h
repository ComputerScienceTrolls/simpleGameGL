#ifndef SOUND_H
#define SOUND_H

#include "alut.h"
#include "al.h"
#include "alc.h"
#include <windows.h>
#include <string>

using std::string;

class Sound
{
public:

	Sound(string);
	~Sound();
	void play();
	void pause();
	void stop();
	void isLooping(ALboolean);
	void changePitch(ALfloat);
	void changeVolume(ALfloat);

private:
	string errorMessage = "Could Not Find Sound in Directory";

	// Buffers to hold sound data.
	ALuint Buffer;

	// Sources are points of emitting sound.
	ALuint Source;

	/*
	* These are 3D cartesian vector coordinates. A structure or class would be
	* a more flexible of handling these, but for the sake of simplicity we will
	* just leave it as is.
	*/

	// Position of the source sound.
	ALfloat SourcePos[3] = { 0.0, 0.0, 0.0 };

	// Velocity of the source sound.
	ALfloat SourceVel[3] = { 0.0, 0.0, 0.0 };

	// Position of the Listener.
	ALfloat ListenerPos[3] = { 0.0, 0.0, 0.0 };

	// Velocity of the Listener.
	ALfloat ListenerVel[3] = { 0.0, 0.0, 0.0 };

	// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
	// Also note that these should be units of '1'.
	ALfloat ListenerOri[6] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
};

#endif