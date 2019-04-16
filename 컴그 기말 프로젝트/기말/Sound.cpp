#include "stdafx.h"
#include "Sound.h"


CSound::CSound()
{
}


CSound::~CSound()
{
}

void CSound::init(int num, int soundnum,int channel, char* name)
{
	System_Create(&g_system);
	g_system->init(SOUNDMAX, FMOD_INIT_NORMAL, 0);
	//배경음악
	if (num == 0)
	{
		g_system->createSound(name, FMOD_LOOP_NORMAL, NULL, &g_Sound[soundnum]);// 경로에서 파일 불러오는 것
		g_system->playSound(FMOD_CHANNEL_FREE, g_Sound[soundnum], false, &g_channel[channel]);
	}
	//효과음
	else if (num == 1)
	{
		g_system->createSound(name, FMOD_HARDWARE | FMOD_LOOP_OFF, NULL, &g_Sound[soundnum]);
		g_system->playSound(FMOD_CHANNEL_FREE, g_Sound[soundnum], false, &g_channel[channel]);
	}
}

void CSound::release(int soundnum)
{
	g_Sound[soundnum]->release();
	g_system->release();
	g_system->close();
}

void CSound::update()
{
	g_system->update();
}
