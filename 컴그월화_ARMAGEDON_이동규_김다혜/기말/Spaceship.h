// Armagedon_Spaceship.h
#pragma once
#include "Meteor.h"
#include "Loadbitmap.h"

#define BULLET_NUM 100
#define BULLET_SPEED 50.f
#define PI 3.141592f / 180.f
#define TRACE_NUM 5


class Bullet {
private:
	float fx, fy, fz, dist;
	float Angle_X, Angle_Y;
	bool exist;
public:
	Bullet() : exist(false) {}
	~Bullet() {}
	void SetX(float x) { fx = x; }
	void SetY(float y) { fy = y; }
	void SetZ(float z) { fz = z; }
	void Set_Angle_X(float X_angle) { Angle_X = X_angle; }
	void Set_Angle_Y(float Y_angle) { Angle_Y = Y_angle; }
	void Set_Dist(float r) { dist = r; }
	void Create() { exist = true; }
	float Get_Angle_X() { return Angle_X; }
	float Get_Angle_Y() { return Angle_Y; }
	float GetX() { return fx; }
	float GetY() { return fy; }
	float GetZ() { return fz; }
	bool Exist() { return exist; }
	bool Collide(Meteor meteor, float x, float y, float z);
	void Render();
	void Update();
	void Delete() { exist = false; }
};

class Spaceship {
private:
	float fx, fy, fz;
	float Angle_X, Angle_Y;
	Bullet bullet[BULLET_NUM];
	int bullet_count;
	int boost;
	bool Boost_Mode;
	bool Move;
	int life;
	GLuint textures[4];
	GLubyte* pBytes;
	Loadbitmap Load;
	BITMAPINFO* info;
	int damage;
public:
	Spaceship();
	~Spaceship() {}
	void SetX(float x) { fx = x; }
	void SetY(float y) { fy = y; }
	void SetZ(float z) { fz = z; }
	void Set_Angle_X(float X_angle) { Angle_X = X_angle; }
	void Set_Angle_Y(float Y_angle) { Angle_Y = Y_angle; }
	void Turn_X(float angle);
	void Turn_Y(float angle);
	float Get_Angle_X() { return Angle_X; }
	float Get_Angle_Y() { return Angle_Y; }
	float GetX() { return fx; }
	float GetY() { return fy; }
	float GetZ() { return fz; }
	void Render(bool shop);
	void WireRender();
	void Render_Bullet();
	void Render_UI(bool view, int Earth);
	void Update();
	void Create_Bullet();
	void Start_Move() { Move = true; }
	void End_Move() { Move = false; }
	bool Move_State() { return Move; }
	void Boost_On() { Boost_Mode = true; }
	void Boost_Off() { Boost_Mode = false; }
	bool Boost_State() { return Boost_Mode; }
	void Use_Boost();
	bool Collide(Meteor meteor);
	bool Ship_Collide(Meteor meteor);
	int Get_Damage() { return damage; }
	int Get_Life() { return life; }
	void Hit_Life() { if (life > 0) life--; }
	void Set_Life(int n) { life = n; }
	bool Upgrade(int num);
	int Reshape();
};