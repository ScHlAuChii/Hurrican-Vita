#include "fmod.h"

void FSOUND_Close()
{
}

int FSOUND_GetError()
{
	return FMOD_ERR_NONE;
}

int FSOUND_GetMaxChannels()
{
	return 256;
}

int FSOUND_GetVolume(int channel)
{
	return 0;
}

signed char FSOUND_Init(int mixrate, int maxsoftwarechannels, unsigned int flags)
{
	return 1;
}

signed char FSOUND_IsPlaying(int channel)
{
	return 0;
}

int FSOUND_PlaySound(int channel, FSOUND_SAMPLE *sptr)
{
	return channel;
}

void FSOUND_Sample_Free(FSOUND_SAMPLE *sptr)
{
}

FSOUND_SAMPLE *FSOUND_Sample_Load(int index, const char *name_or_data, unsigned int mode, int offset, int length)
{
	return nullptr;
}

signed char FSOUND_SetDriver(int driver)
{
	return 1;
}

signed char FSOUND_SetFrequency(int channel, int freq)
{
	return 1;
}

signed char FSOUND_SetMixer(int mixer)
{
	return 1;
}

signed char FSOUND_SetOutput(int outputtype)
{
	return 1;
}

signed char FSOUND_SetPan(int channel, int pan)
{
	return 1;
}

signed char FSOUND_SetVolume(int channel, int vol)
{
	return 1;
}

signed char FSOUND_StopSound(int channel)
{
	return 1;
}
