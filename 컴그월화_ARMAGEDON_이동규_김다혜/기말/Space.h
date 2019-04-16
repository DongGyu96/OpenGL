#pragma once
#include "Loadbitmap.h"
#define MAX 3
#define SIZE 3500

class Space
{
private:
	GLuint textures[MAX];
	GLubyte* pBytes;
	Loadbitmap Load;
	BITMAPINFO* info;
public:
	Space();
	~Space();
	void Render();
	int Reshape();
};

