#include "fmod.h"

signed char FMUSIC_FreeSong(FMUSIC_MODULE *mod)
{
	return FMOD_ERR_NONE;
}

signed char FMUSIC_GetPaused(FMUSIC_MODULE *mod)
{
	return 0;
}

signed char FMUSIC_IsFinished(FMUSIC_MODULE *mod)
{
	return 1;
}

signed char FMUSIC_IsPlaying(FMUSIC_MODULE *mod)
{
	return 0;
}

FMUSIC_MODULE *FMUSIC_LoadSong(const char *name)
{
	return nullptr;
}

FMUSIC_MODULE *FMUSIC_LoadSongEx(const char *name_or_data, int offset, int length, unsigned int mode, const int *samplelist, int samplelistnum)
{
	return nullptr;
}

signed char FMUSIC_PlaySong(FMUSIC_MODULE *mod)
{
	return FMOD_ERR_NONE;
}

signed char FMUSIC_SetMasterVolume(FMUSIC_MODULE *mod, int volume)
{
	return FMOD_ERR_NONE;
}

signed char FMUSIC_SetPaused(FMUSIC_MODULE *mod, signed char pause)
{
	return FMOD_ERR_NONE;
}

void FMUSIC_StopAllSongs()
{
}

signed char FMUSIC_StopSong(FMUSIC_MODULE *mod)
{
	return FMOD_ERR_NONE;
}
