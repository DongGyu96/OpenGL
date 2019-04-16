#pragma once

#define SOUNDMAX 5

class CSound
{
public:
	FMOD_SYSTEM *g_System;
	FMOD_SOUND *g_Sound[5];
	FMOD_CHANNEL *g_Channel[5];
public:
	CSound();
	~CSound();
	void init();
	void stop();
	void play(int num);
	void Release();
	void volume(int num, float vol);
};