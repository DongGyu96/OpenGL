#include "stdafx.h"
#include "Space.h"


Space::Space()
{
}


Space::~Space()
{
}

void Space::Render()
{
	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBegin(GL_QUADS); {// 앞
			glTexCoord3f(0, 1, 0);
			glVertex3f(-SIZE, SIZE, SIZE);
			glTexCoord3f(0, 0, 0);
			glVertex3f(-SIZE, -SIZE, SIZE);
			glTexCoord3f(1, 0, 0);
			glVertex3f(SIZE, -SIZE, SIZE);
			glTexCoord3f(1, 1, 0);
			glVertex3f(SIZE, SIZE, SIZE);
		}
		glEnd();

		glBegin(GL_QUADS); {//왼쪽
			glTexCoord3f(0, 1, 0);
			glVertex3f(SIZE, SIZE, SIZE);
			glTexCoord3f(0, 0, 0);
			glVertex3f(SIZE, -SIZE, SIZE);
			glTexCoord3f(1, 0, 0);
			glVertex3f(SIZE, -SIZE, -SIZE);
			glTexCoord3f(1, 1, 0);
			glVertex3f(SIZE, SIZE, -SIZE);
		}
		glEnd();

		glBegin(GL_QUADS); {//오른쪽
			glTexCoord3f(0, 1, 0);
			glVertex3f(-SIZE, SIZE, -SIZE);
			glTexCoord3f(0, 0, 0);
			glVertex3f(-SIZE, -SIZE, -SIZE);
			glTexCoord3f(1, 0, 0);
			glVertex3f(-SIZE, -SIZE, SIZE);
			glTexCoord3f(1, 1, 0);
			glVertex3f(-SIZE, SIZE, SIZE);

		}
		glEnd();

		glBegin(GL_QUADS); {//뒷쪽
			glTexCoord3f(1, 1, 0);
			glVertex3f(-SIZE, SIZE, -SIZE);
			glTexCoord3f(0, 1, 0);
			glVertex3f(SIZE, SIZE, -SIZE);
			glTexCoord3f(0, 0, 0);
			glVertex3f(SIZE, -SIZE, -SIZE);
			glTexCoord3f(1, 0, 0);
			glVertex3f(-SIZE, -SIZE, -SIZE);
		}
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glBegin(GL_QUADS); {//밑
			glTexCoord3f(1, 0, 0);
			glVertex3f(-SIZE, -SIZE, -SIZE);
			glTexCoord3f(0, 0, 0);
			glVertex3f(SIZE, -SIZE, -SIZE);
			glTexCoord3f(0, 1, 0);
			glVertex3f(SIZE, -SIZE, SIZE);
			glTexCoord3f(1, 1, 0);
			glVertex3f(-SIZE, -SIZE, SIZE);
		}
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glBegin(GL_QUADS); {//위
			glTexCoord3f(0, 1, 0);
			glVertex3f(-SIZE, SIZE, -SIZE);
			glTexCoord3f(0, 0, 0);
			glVertex3f(-SIZE, SIZE, SIZE);
			glTexCoord3f(1, 0, 0);
			glVertex3f(SIZE, SIZE, SIZE);
			glTexCoord3f(1, 1, 0);
			glVertex3f(SIZE, SIZE, -SIZE);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);

	}
	glPopMatrix();
}

void Space::init()
{
	sound.init(0, GameBgm,1, "gamebgm.wav");
}

void Space::update()
{
	sound.update();
}

void Space::release()
{
	sound.release(GameBgm);
}

int Space::Reshape()
{
	glGenTextures(MAX, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	{
		pBytes = Load.LoadDIBitmap("BK.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[1]);	//바닥
	{
		pBytes = Load.LoadDIBitmap("earth.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 279, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[2]);	//하늘
	{
		pBytes = Load.LoadDIBitmap("BK_top.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 286, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

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
