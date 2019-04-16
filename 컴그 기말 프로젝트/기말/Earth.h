#pragma once
#include "Loadbitmap.h"

class Earth
{
private:
	GLuint textures[1];
	GLubyte* pBytes;
	Loadbitmap Load;
	BITMAPINFO* info;
public:
	Earth();
	~Earth();
	int Reshape();
};

