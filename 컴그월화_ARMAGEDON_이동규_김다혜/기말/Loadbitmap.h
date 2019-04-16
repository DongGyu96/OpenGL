#pragma once
class Loadbitmap
{
private:
	GLubyte* TexBits;
public:
	Loadbitmap();
	~Loadbitmap();
	GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info);
	void setUp(const char* filename, BITMAPINFO* texture, GLsizei w, GLsizei h);
};

