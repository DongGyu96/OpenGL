#include "stdafx.h"
#include "Shop.h"

void Shop::Render_Shop(bool view)
{
	glEnable(GL_TEXTURE_2D);

	if (view)
	{
		glPushMatrix();
		glTranslatef(0.f, 9.f, -35.f);
		glRotatef(-10.f, 1.f, 0.f, 0.f);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBegin(GL_QUADS);
		{
			glTexCoord3f(1, 0, 0);
			glVertex3f(-200.f / 50.f, 0.f, 0.f);
			glTexCoord3f(0, 0, 0);
			glVertex3f(200.f / 50.f, 0.f, 0.f);
			glTexCoord3f(0, 1, 0);
			glVertex3f(200.f / 50.f, 300.f / 50.f, 0.f);
			glTexCoord3f(1, 1, 0);
			glVertex3f(-200.f / 50.f, 300.f / 50.f, 0.f);
		}
		glEnd();
		Render_Attack(50.0f);
		Render_Satellite(50.0f);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glTranslatef(0.f, 0.f, 50.f);
		glRotatef(-10.f, 1.f, 0.f, 0.f);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBegin(GL_QUADS);
		{
			glTexCoord3f(1, 0, 0);
			glVertex3f(-200.f, 0.f, 0.f);
			glTexCoord3f(0, 0, 0);
			glVertex3f(200.f, 0.f, 0.f);
			glTexCoord3f(0, 1, 0);
			glVertex3f(200.f, 300.f, 0.f);
			glTexCoord3f(1, 1, 0);
			glVertex3f(-200.f, 300.f, 0.f);
		}
		glEnd();
		Render_Attack(1.0f);
		Render_Satellite(1.0f);
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
}

int Shop::Reshape()
{
	glGenTextures(MAX, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	{
		pBytes = Load.LoadDIBitmap("SHOP.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	{
		pBytes = Load.LoadDIBitmap("attack.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	{
		pBytes = Load.LoadDIBitmap("satellite.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

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

void Shop::Render_Attack(float rate)
{
		glPushMatrix();
		glTranslatef(-90.f/rate, 150.f/ rate, 2.f / rate);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glBegin(GL_QUADS);
		{
			glTexCoord3f(1, 0, 0);
			glVertex3f(-80.f / rate, -80.f / rate, 0.f);
			glTexCoord3f(0, 0, 0);
			glVertex3f(80.f / rate, -80.f / rate, 0.f);
			glTexCoord3f(0, 1, 0);
			glVertex3f(80.f / rate, 80.f / rate, 0.f);
			glTexCoord3f(1, 1, 0);
			glVertex3f(-80.f / rate, 80.f / rate, 0.f);
		}
		glEnd();
		glPopMatrix();
}

void Shop::Render_Satellite(float rate)
{
	glPushMatrix();
	glTranslatef(90.f / rate, 150.f / rate, 2.f / rate);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	{
		glTexCoord3f(1, 0, 0);
		glVertex3f(-80.f / rate, -80.f / rate, 0.f);
		glTexCoord3f(0, 0, 0);
		glVertex3f(80.f / rate, -80.f / rate, 0.f);
		glTexCoord3f(0, 1, 0);
		glVertex3f(80.f / rate, 80.f / rate, 0.f);
		glTexCoord3f(1, 1, 0);
		glVertex3f(-80.f / rate, 80.f / rate, 0.f);
	}
	glEnd();
	glPopMatrix();
}
