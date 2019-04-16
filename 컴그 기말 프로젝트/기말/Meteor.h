#pragma once
#include "Loadbitmap.h"

class Meteor
{
private:
	double Bigradius, Midradius, Smallradius;
	GLUquadricObj* meteor;
	int HP;
	GLuint textures[2];
	GLubyte* pBytes; 
	Loadbitmap Load;
	BITMAPINFO* info;
	bool exist, semi_exist;
	float Px, Pz, Semi_Px, Semi_Pz;
	float Pr, Semi_Pr;
	int frame, Semi_frame;
public:
	float x, y, z;
public:
	Meteor();
	~Meteor();
	void Render();
	int Reshape();
	void Particle();
	void Semi_Particle();
	int GetHP() { return HP; }
	int Collide(int damage);
	void Delete() { exist = false; }
	void Create();
	void Exist() { exist = true; }
	void Update();
	bool Get_Exist() { return exist; }
};

