#pragma once

#define SOUNDMAX 10
class CSound
{
public:
	System* g_system;
	Sound* g_Sound[SOUNDMAX];
	Channel* g_channel[SOUNDMAX];
public:
	CSound();
	~CSound();
	void init(int num, int soundnum,int channel, char* name);
	// num = 0 : 배경음악
	// num = 1 : 효과음
	// channel : 채널번호
	// soundnum : 음악번호
	// name : 파일이름
	void release(int soundnum);
	void update();
};

