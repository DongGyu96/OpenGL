#pragma once
#include "Loadbitmap.h"

#define LOGO 12
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
public:
	Logo();
	~Logo();
	void Render();
	int Reshape();
	void Timer();
};

