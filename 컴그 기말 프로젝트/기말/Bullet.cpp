#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	exist = false;
}


Bullet::~Bullet()
{
}

void Bullet::SetX(float x)
{
	fx = x;
}

void Bullet::SetY(float y)
{
	fy = y;
}

void Bullet::SetZ(float z)
{
	fz = z;
}

void Bullet::Set_Angle_X(float X_angle)
{
	Angle_X = X_angle;
}

void Bullet::Set_Angle_Y(float Y_angle)
{
	Angle_Y = Y_angle;
}

void Bullet::Set_Dist(float r)
{
	dist = r;
}

void Bullet::Create()
{
	exist = true;
}

float Bullet::Get_Angle_X()
{
	return Angle_X;
}

float Bullet::Get_Angle_Y()
{
	return Angle_Y;
}

float Bullet::GetX()
{
	return fx;
}

float Bullet::GetY()
{
	return fy;
}

float Bullet::GetZ()
{
	return fz;
}

bool Bullet::Exist()
{
	return exist;
}
