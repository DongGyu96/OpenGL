#include "stdafx.h"
#include "Sound.h"


CSound::CSound()
{
}


CSound::~CSound()
{
}

void CSound::init()
{
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 10, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(g_System, "bgm.wav", FMOD_LOOP_NORMAL, 0, &g_Sound[0]);
	FMOD_System_CreateSound(g_System, "gamebgm.wav", FMOD_LOOP_NORMAL, 0, &g_Sound[1]);
	FMOD_System_CreateSound(g_System, "Boost.wav", FMOD_DEFAULT, 0, &g_Sound[2]);
	FMOD_System_CreateSound(g_System, "meteor.wav", FMOD_DEFAULT, 0, &g_Sound[3]);
	FMOD_System_CreateSound(g_System, "Gun.wav", FMOD_DEFAULT, 0, &g_Sound[4]);
	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]);
}

void CSound::stop()
{
	FMOD_BOOL IsPlaying;

	FMOD_Channel_IsPlaying(g_Channel[0], &IsPlaying);
	FMOD_Sound_Release(g_Sound[0]);
}

void CSound::play(int num)
{
	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[num], 0, &g_Channel[num]);
}

void CSound::Release()
{
	FMOD_Sound_Release(g_Sound[1]);
	FMOD_Sound_Release(g_Sound[2]);
	FMOD_Sound_Release(g_Sound[3]);
	FMOD_Sound_Release(g_Sound[4]);
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

void CSound::volume(int num, float vol)
{
	FMOD_Channel_SetVolume(g_Channel[num], vol);
}
