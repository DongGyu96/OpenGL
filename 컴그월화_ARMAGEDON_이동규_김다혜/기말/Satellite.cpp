#include "stdafx.h"
#include "Satellite.h"

void Satellite::Render()
{
	glPushMatrix();

	glPushMatrix();
	glColor3f(0.7f, 0.7f, 0.7f);
	glScalef(1.2f, 1.f, 1.5f);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glScalef(1.f, 2.f, 1.f);
	glutSolidCube(25);

	glPushMatrix();
	glColor3f(0.6f, 0.6f, 0.6f);
	glTranslatef(0.f, -22.f, 0.f);
	glScalef(1.f, 1.5f, 1.f);
	glutSolidCube(15);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50.f, 0.f, 0.f);
	glRotatef(330.f, 1.f, 0.f, 0.f);
	glScalef(3.f, 2.f, 0.3f);
	glColor3f(0.2f, 0.2f, 1.f);
	glutSolidCube(20);

	glColor3f(0.f, 0.f, 0.f);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, -5.f);
	glScalef(12.f, 0.5f, 0.5f);
	glColor3f(0.6f, 0.6f, 0.6f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(50.f, 0.f, 0.f);
	glRotatef(330.f, 1.f, 0.f, 0.f);
	glScalef(3.f, 2.f, 0.3f);
	glColor3f(0.2f, 0.2f, 1.f);
	glutSolidCube(20);

	glColor3f(0.f, 0.f, 0.f);
	glutWireCube(20);
	glPopMatrix();

	glPopMatrix();
}

void Satellite::Render_Range()
{
	glPushMatrix();
	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; ++i)
	{
		glVertex3f(cosf(i * PI) * RANGE, 0.f, sinf(i * PI) * RANGE);
	}
	glEnd();

	glRotatef(90.f, 1.f, 0.f, 0.f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; ++i)
	{
		glVertex3f(cosf(i * PI) * RANGE, 0.f, sinf(i * PI) * RANGE);
	}
	glEnd();

	glPopMatrix();
}

double Satellite::Check_Range(float x2, float y2, float z2)
{
	return sqrt((x2 - fx)*(x2 - fx) + (y2 - fy)*(y2 - fy) + (z2 - fz) * (z2 - fz));
}

void Satellite::Set_Raser(Meteor meteor, int n)
{
	if (meteor.Get_Exist())
	{
		if (Check_Range(meteor.x, meteor.y, meteor.z) < min && Check_Range(meteor.x, meteor.y, meteor.z) < RANGE)
		{
			min = Check_Range(meteor.x, meteor.y, meteor.z);
			Ax = meteor.x;
			Ay = meteor.y;
			Az = meteor.z;
			An = n;
		}
	}
}

void Satellite::Render_Raser()
{
	if (Ax != 0.f || Ay != 0.f || Az != 0.f)
	{
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glLineWidth(3.f);
		glColor4f(1.f, 1.f, 0.f, 0.5f);
		glBegin(GL_LINES);
		glVertex3f(fx, fy, fz);
		glVertex3f(Ax, Ay, Az);
		glEnd();
		glDisable(GL_BLEND);
		glLineWidth(1.f);
		glPopMatrix();
	}
}

void Satellite::Create(float x, float y, float z)
{
	fx = x;
	fy = y;
	fz = z;
	exist = true;
	min = RANGE;
}

void Satellite::Delete_Raser()
{
	min = RANGE;
	Ax = 0.f;
	Ay = 0.f;
	Az = 0.f;
	An = -1;
}