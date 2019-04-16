#pragma once
#include "Sound.h"
#include "Loadbitmap.h"
#define MAX 3
#define SIZE 3500

class Space
{
private:
	CSound sound;
	GLuint textures[MAX];
	GLubyte* pBytes;
	Loadbitmap Load;
	BITMAPINFO* info;
public:
	Space();
	~Space();
	void Render();
	void init();
	void update();
	void release();
	int Reshape();
};

