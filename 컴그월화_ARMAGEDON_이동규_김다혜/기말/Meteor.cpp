#include "stdafx.h"
#include "Meteor.h"


Meteor::Meteor()
{
	Bigradius = 500, Midradius = 250, Smallradius = 50;
	HP = 500;
	x = 0;
	y = 600;
	z = -800;
	exist = true;
}

Meteor::~Meteor()
{
}

int Meteor::Collide(int damage)
{
	if (exist)
	{
		HP -= damage;
		if (HP < 50)
		{
			HP = 0;
			exist = false;
			Pr = 5.f;
			Px = 0.f;
			Pz = 0.f;
			frame = 0;

			Semi_frame = 0;
			Semi_Pr = 5.f;
			Semi_Px = 0.f;
			Semi_Pz = 0.f;
			semi_exist = true;
			return rand() % 51 + 50;
		}
		Semi_frame = 0;
		Semi_Pr = 5.f;
		Semi_Px = 0.f;
		Semi_Pz = 0.f;
		semi_exist = true;
	}

	return 0;
}

void Meteor::Render()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	if (exist)
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glRotatef(90, 0, 1, 0);
		glutSolidSphere(HP, 100, 100);

		
		glPopMatrix();
	}
	else
	{
		Particle();
	}

	if (semi_exist)
	{
		Semi_Particle();
	}
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	if (y - HP < -1500)
	{
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(x, y - (float)HP / 2.f, z);
		glRotatef(90.f, 1.f, 0.f, 0.f);
		glColor4f(1.f, 0.8f, 0.3f, 0.8f);
		glutSolidCone(HP, HP / 1.25, 20, 20);

		glTranslatef(0.f, 0.f, HP / 4.f);
		glColor4f(1.f, 0.3f, 0.3f, 0.8f);
		glutSolidCone(HP / 1.25, HP / 2, 20, 20);

		glColor4f(1.f, 0.f, 0.f, 0.8f);
		glutSolidCone(HP / 1.5, HP / 1.75, 20, 20);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
} 

int Meteor::Reshape()
{
	glGenTextures(2, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	{
		pBytes = Load.LoadDIBitmap("meteor.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	{
		pBytes = Load.LoadDIBitmap("meteor2.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);

	return true;
}

void Meteor::Particle()
{
	for (int j = 0; j < 12; ++j)
	{
		for (int i = 0; i < 36; ++i)
		{
			glPushMatrix();
			Px = cosf((float)(i * 10) * PI) * Pr;
			Pz = sinf((float)(i * 10) * PI) * Pr;
			glTranslatef(x, y, z);
			glRotatef((float)j * 30.f, 0.f, 0.f, 1.f);
			glTranslatef(Px, 0.f, Pz);
			glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
			glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
			glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
			glColor3f(1.0, 1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			glutSolidCube(10);
			glPopMatrix();
		}
	}
}

void Meteor::Semi_Particle()
{
	for (int j = 0; j < 8; ++j)
	{
		for (int i = 0; i < 36; ++i)
		{
			glPushMatrix();
			Semi_Px = cosf((float)(i * 10) * PI) * (HP + Semi_Pr);
			Semi_Pz = sinf((float)(i * 10) * PI) * (HP + Semi_Pr);
			glTranslatef(x, y, z);
			glRotatef((float)j * 45.f, 1.f, 0.f, 0.f);
			glTranslatef(Semi_Px, 0.f, Semi_Pz);
			glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
			glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
			glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
			glColor3f(1.0, 1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			glutSolidCube(8);
			glPopMatrix();
		}
	}
}

void Meteor::Update()
{
	if (exist)
	{
		y -= 3.f;
	}
	else
	{
		frame += 1;
		Pr += 15.f;
		if (frame == 30)
			Create();
	}

	if (semi_exist)
	{
		Semi_frame += 1;
		if(HP > 0)
			Semi_Pr += (float)(HP / 40);
		else
			Semi_Pr += 15.f;
		if (Semi_frame == 30)
		{
			semi_exist = false;
			Semi_frame = 0;
			Semi_Pr = 5.f;
		}
	}
}

void Meteor::Create()
{
	exist = true;
	x = (float)(rand() % 5001 - 2500);
	y = (float)(rand() % 1001 + 2000);
	z = (float)(rand() % 5001 - 2500);
	HP = rand() % 201 + 300;
	frame = 0;
}