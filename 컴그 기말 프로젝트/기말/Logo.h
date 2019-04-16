#pragma once
#include "Loadbitmap.h"
#include "Sound.h"

#define LOGO 9
class CSound;
class Logo
{
private:
	int frame;
	int time;
	GLuint textures[LOGO];
	GLubyte* pBytes;
	Loadbitmap Load;
	GLUquadricObj* logo;
	BITMAPINFO* info;
	CSound sound;
public:
	Logo();
	~Logo();
	void init();
	void Render();
	int Reshape();
	void Timer();
	void Relese();
};

