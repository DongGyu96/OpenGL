#pragma once
#include "Meteor.h"
#define RANGE 800
#define PI 3.141592f / 180.f

class Satellite {
private:
	float fx, fy, fz;
	float Ax, Ay, Az;
	int An;
	double min;
	bool exist;
public:
	Satellite() {}
	~Satellite() {}
	void SetX(float x) { fx = x; }
	void SetY(float y) { fy = y; }
	void SetZ(float z) { fz = z; }
	float GetX() { return fx; }
	float GetY() { return fy; }
	float GetZ() { return fz; }
	void Render();
	void Render_Range();
	double Check_Range(float x2, float y2, float z2);
	void Set_Raser(Meteor meteor, int n);
	void Render_Raser();
	void Create(float x, float y, float z);
	void Delete() { exist = false; }
	bool Exist() { return exist; }
	void Delete_Raser();
	int Get_An() { return An; }
	//void Update();
};
