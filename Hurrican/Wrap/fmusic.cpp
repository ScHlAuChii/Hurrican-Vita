#include "fmod.h"

#include <assert.h>

struct FMUSIC_MODULE
{
};

signed char FMUSIC_FreeSong(FMUSIC_MODULE *mod)
{
	assert(mod != nullptr);
	
	delete mod;
	
	return 1;
}

signed char FMUSIC_GetPaused(FMUSIC_MODULE *mod)
{
	assert(mod != nullptr);
	
	return 0;
}

signed char FMUSIC_IsFinished(FMUSIC_MODULE *mod)
{
	assert(mod != nullptr);
	
	return 1;
}

signed char FMUSIC_IsPlaying(FMUSIC_MODULE *mod)
{
	assert(mod != nullptr);
	
	return 0;
}

FMUSIC_MODULE *FMUSIC_LoadSong(const char *name)
{
	return new FMUSIC_MODULE;
}

FMUSIC_MODULE *FMUSIC_LoadSongEx(const char *name_or_data, int offset, int length, unsigned int mode, const int *samplelist, int samplelistnum)
{
	return nullptr;
}

signed char FMUSIC_PlaySong(FMUSIC_MODULE *mod)
{
	assert(mod != nullptr);
	
	return 1;
}

signed char FMUSIC_SetMasterVolume(FMUSIC_MODULE *mod, int volume)
{
	assert(mod != nullptr);
	
	return 1;
}

signed char FMUSIC_SetPaused(FMUSIC_MODULE *mod, signed char pause)
{
	assert(mod != nullptr);
	
	return 1;
}

void FMUSIC_StopAllSongs()
{
}

signed char FMUSIC_StopSong(FMUSIC_MODULE *mod)
{
	assert(mod != nullptr);
	
	return 1;
}
