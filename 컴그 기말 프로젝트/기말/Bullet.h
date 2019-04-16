#pragma once

#define BULLET_NUM 100
#define BULLET_SPEED 25.f

class Bullet
{
private:
	float fx, fy, fz, dist;
	float Angle_X, Angle_Y;
	bool exist;
public:
	Bullet();
	~Bullet();
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void Set_Angle_X(float X_angle);
	void Set_Angle_Y(float Y_angle);
	void Set_Dist(float r);
	void Create();
	float Get_Angle_X();
	float Get_Angle_Y();
	float GetX();
	float GetY();
	float GetZ();
	bool Exist();
	void Render();
	void Update();
};