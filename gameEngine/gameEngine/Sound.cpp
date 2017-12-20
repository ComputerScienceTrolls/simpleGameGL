#include "Sound.h"



Sound::Sound(string dir)
{
	
	//create the buffer
	Buffer = alutCreateBufferFromFile(dir.c_str());
	
	// Bind the buffer with the source.
	alGenSources(1, &Source);

	alSourcei(Source, AL_BUFFER, Buffer);

	//pop up message box if there is something wrong
	if (alGetError() != AL_NO_ERROR)
		MessageBox(NULL, errorMessage.c_str(), "Error Message", MB_OK);

	//Set default values for sound file
	alSourcei(Source, AL_BUFFER, Buffer);
	alSourcef(Source, AL_PITCH, 1.0);
	alSourcef(Source, AL_GAIN, 1.0);
	alSourcefv(Source, AL_POSITION, SourcePos);
	alSourcefv(Source, AL_VELOCITY, SourceVel);
	alSourcei(Source, AL_LOOPING, AL_FALSE);

	//set up the listeners
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}


Sound::~Sound()
{
	alDeleteBuffers(1, &Buffer);
	alDeleteSources(1, &Source);
}

void Sound::play()
{
	alSourcePlay(Source);
}


void Sound::pause()
{
	alSourcePause(Source);
}

void Sound::stop()
{
	alSourceStop(Source);
}

//change the pitch of the sound. Range: 0.5 - 2.0
void Sound::changePitch(ALfloat pitch)
{
	alSourcef(Source, AL_PITCH, pitch);
}

//change the volume of the sound. Range: 0.0 - 1.0 
void Sound::changeVolume(ALfloat volume)
{
	alSourcef(Source, AL_GAIN, volume);
}


void Sound::isLooping(ALboolean isLooping)
{
	alSourcei(Source, AL_LOOPING, isLooping);
}
