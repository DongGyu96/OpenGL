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
	// num = 0 : �������
	// num = 1 : ȿ����
	// channel : ä�ι�ȣ
	// soundnum : ���ǹ�ȣ
	// name : �����̸�
	void release(int soundnum);
	void update();
};

