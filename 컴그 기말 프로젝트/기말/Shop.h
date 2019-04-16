#pragma once
#include "Loadbitmap.h"
#define MAX 10

class Shop {
private:
	GLuint textures[MAX];
	GLubyte* pBytes;
	Loadbitmap Load;
	BITMAPINFO* info;
	bool attack;
	bool statellite;
public:
	Shop() {}
	~Shop() {}
	void Render_Shop(bool view);
	int Reshape();
	void Render_Attack(float rate);
	void Render_Satellite(float rate);
};