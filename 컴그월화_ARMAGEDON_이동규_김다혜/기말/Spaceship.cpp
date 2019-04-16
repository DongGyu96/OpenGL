// Armagedon_Spaceship.cpp
#include "stdafx.h"
#include "Spaceship.h"

// Spaceship
Spaceship::Spaceship()
{
	bullet_count = 0;
	Boost_Mode = false;
	boost = 200;
	damage = 20;
	Move = false;
	life = 3;
}

bool Spaceship::Upgrade(int num)
{
	if (damage < 50)
	{
		damage += num;
		return true;
	}
	return false;
}

int Spaceship::Reshape()
{
	glGenTextures(4, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	{
		pBytes = Load.LoadDIBitmap("지구100%.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[1]);	
	{
		pBytes = Load.LoadDIBitmap("지구50%.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[2]);	
	{
		pBytes = Load.LoadDIBitmap("지구10%.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[3]);	
	{
		pBytes = Load.LoadDIBitmap("heart.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

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

void Spaceship::Turn_X(float angle)
{
	if (Angle_X + angle < 45.f && Angle_X + angle > -45.f)
		Angle_X += angle;
}
void Spaceship::Turn_Y(float angle)
{
	Angle_Y += angle;
	if (Angle_Y > 360.f)
		Angle_Y -= 360.f;
	else if (Angle_Y < 0.f)
		Angle_Y += 360.f;
}

void Spaceship::Render(bool shop)
{
	glPushMatrix();

	glTranslatef(0.f, 0.f, -10.f);

	glPushMatrix(); // 몸통기둥
	glTranslatef(0.f, 0.f, 20.f);
	glScalef(0.8f, 0.8f, 2.f);

	for (float angle = 0.f; angle < 360.f; angle += 0.25f)
	{
		glColor3f(0.6f, 0.6f, 0.6f);
		glRotatef(angle, 0.f, 0.f, 1.f);
		glutSolidCube(26);
	}
	glPopMatrix();

	glPushMatrix(); // 앞부분
	glColor3f(0.7f, 0.7f, 0.7f);
	glTranslatef(0.f, 0.f, -5.f);
	glRotatef(180.f, 0.f, 1.f, 0.f);
	glScalef(1.f, 1.f, 0.85f);
	glutSolidCone(15, 40, 10, 4);

	glColor3f(1.f, 1.f, 1.f); // 조종석
	glTranslatef(0.f, 7.f, 10.f);
	glScalef(1.f, 1.f, 2.f);
	glutSolidSphere(5, 20, 20);
	glPopMatrix();

	glPushMatrix(); // 왼쪽날개
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(0.f, 0.f, 20.f);
	glRotatef(-80.f, 0.f, 1.f, 0.f);
	glRotatef(-10.f, 1.f, 0.f, 0.f);
	glScalef(1.1f, 0.5f, 1.1f);
	glutSolidCone(25, 60, 10, 4);

	glColor3f(0.2f, 0.2f, 0.2f);
	glTranslatef(-5.f, -10.f, 30.f);
	glScalef(1.f, 0.6f, 1.f);
	glutSolidCube(20);
	glPopMatrix();

	glPushMatrix(); // 오른쪽날개
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(0.f, 0.f, 20.f);
	glRotatef(80.f, 0.f, 1.f, 0.f);
	glRotatef(-10.f, 1.f, 0.f, 0.f);
	glScalef(1.1f, 0.5f, 1.1f);
	glutSolidCone(25, 60, 10, 4);

	glColor3f(0.2f, 0.2f, 0.2f);
	glTranslatef(5.f, -10.f, 30.f);
	glScalef(1.f, 0.6f, 1.f);
	glutSolidCube(20);
	glPopMatrix();

	glPushMatrix(); // 몸통 밑
	glColor3f(0.2f, 0.2f, 0.2f);
	glTranslatef(0.f, -5.f, 15.f);
	glScalef(0.8f, 0.8f, 2.f);
	glutSolidCube(26);
	glPopMatrix();

	glPushMatrix(); // 왼쪽 앞부분 블록
	glColor3f(0.4f, 0.4f, 0.4f);
	glTranslatef(-10.f, 0.f, -12.f);
	glRotatef(-25.f, 0.f, 1.f, 0.f);
	glScalef(1.f, 1.f, 4.f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix(); // 오른쪽 앞부분 블록
	glColor3f(0.4f, 0.4f, 0.4f);
	glTranslatef(10.f, 0.f, -12.f);
	glRotatef(25.f, 0.f, 1.f, 0.f);
	glScalef(1.f, 1.f, 4.f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix(); // 앞부분 마무리부분
	glColor3f(0.4f, 0.4f, 0.4f);
	glTranslatef(0.f, 0.f, -18.f);
	glScalef(1.f, 1.f, 3.f);
	glutSolidSphere(7, 20, 20);
	glPopMatrix();

	glPushMatrix(); // 꼬리 날개
	glColor3f(0.6f, 0.6f, 0.6f);
	glTranslatef(0.f, 10.f, 35.f);
	glRotatef(270.f, 1.f, 0.f, 0.f);
	glRotatef(40.f, 1.f, 0.f, 0.f);
	glScalef(0.6f, 1.f, 1.f);
	glutSolidCone(10, 25, 10, 4);
	glPopMatrix();

	glPushMatrix(); // 꼬리 날개 블록
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(0.f, 10.f, 25.f);
	glRotatef(-10.f, 1.f, 0.f, 0.f);
	glScalef(1.f, 1.2f, 2.f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix(); // 배기구
	glColor3f(0.4f, 0.4f, 0.4f);
	glTranslatef(0.f, 0.f, 45.f);
	glutSolidTorus(4, 12, 10, 10);
	glPopMatrix();

	glPushMatrix(); // 불꽃
	glTranslatef(0.f, 0.f, 45.f);
	glColor3f(1.f, 0.3f, 0.0f);
	glutSolidSphere(8, 20, 20);
	glTranslatef(0.f, 0.f, 10.f);
	glRotatef(180.f, 1.f, 0.f, 0.f);
	glColor3f(1.f, 0.5f, 0.2f);
	glutSolidCone(13, 25, 10, 4);
	glPopMatrix();

	if (!shop)
	{
		if (Move)
		{
			if (!Boost_Mode)
			{
				glPushMatrix();
				glTranslatef(0.f, 0.f, 50.f);
				glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
				glColor3f(0.8f, 0.0f, 0.0f);
				glutSolidCube(15);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.f, 0.f, 60.f);
				glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
				glColor3f(1.f, 0.3f, 0.0f);
				glutSolidCube(14);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.f, 0.f, 70.f);
				glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
				glColor3f(1.f, 0.6f, 0.0f);
				glutSolidCube(13);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.f, 0.f, 80.f);
				glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
				glColor3f(1.f, 0.9f, 0.0f);
				glutSolidCube(11);
				glPopMatrix();
			}
			else
			{

				glPushMatrix();
				glTranslatef(0.f, 0.f, 50.f);
				glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
				glColor3f(0.8f, 0.0f, 0.0f);
				glutSolidCube(20);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.f, 0.f, 60.f);
				glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
				glColor3f(1.f, 0.3f, 0.0f);
				glutSolidCube(21);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.f, 0.f, 70.f);
				glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
				glColor3f(1.f, 0.6f, 0.0f);
				glutSolidCube(23);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.f, 0.f, 80.f);
				glRotatef((float)(rand() % 360), 1.f, 0.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 1.f, 0.f);
				glRotatef((float)(rand() % 360), 0.f, 0.f, 1.f);
				glColor3f(1.f, 0.9f, 0.0f);
				glutSolidCube(25);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
}

void Spaceship::WireRender()
{
	glPushMatrix();

	glTranslatef(0.f, 0.f, -10.f);
	glPushMatrix(); // 몸통기둥
	glTranslatef(0.f, 0.f, 20.f);
	glScalef(0.8f, 0.8f, 2.f);
	int count = 0;
	for (float angle = 0.f; angle < 360.f; angle += 0.25f)
	{
		glRotatef(angle, 0.f, 0.f, 1.f);
		if (count % 300 == 0)
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(26);
		}
		count++;
	}
	glPopMatrix();

	glPushMatrix(); // 앞부분
	glTranslatef(0.f, 0.f, -5.f);
	glRotatef(180.f, 0.f, 1.f, 0.f);
	glScalef(1.f, 1.f, 0.85f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCone(15, 40, 10, 4);

	glColor3f(0.f, 0.f, 0.f); // 조종석
	glTranslatef(0.f, 7.f, 10.f);
	glScalef(1.f, 1.f, 2.f);
	glutWireSphere(5, 10, 10);
	glPopMatrix();

	glPushMatrix(); // 왼쪽날개
	glTranslatef(0.f, 0.f, 20.f);
	glRotatef(-80.f, 0.f, 1.f, 0.f);
	glRotatef(-10.f, 1.f, 0.f, 0.f);
	glScalef(1.1f, 0.5f, 1.1f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCone(25, 60, 10, 4);

	glTranslatef(-5.f, -10.f, 30.f);
	glScalef(1.f, 0.6f, 1.f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix(); // 오른쪽날개
	glTranslatef(0.f, 0.f, 20.f);
	glRotatef(80.f, 0.f, 1.f, 0.f);
	glRotatef(-10.f, 1.f, 0.f, 0.f);
	glScalef(1.1f, 0.5f, 1.1f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCone(25, 60, 10, 4);

	glTranslatef(5.f, -10.f, 30.f);
	glScalef(1.f, 0.6f, 1.f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix(); // 몸통 밑
	glTranslatef(0.f, -5.f, 15.f);
	glScalef(0.8f, 0.8f, 2.f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(26);
	glPopMatrix();

	glPushMatrix(); // 왼쪽 앞부분 블록
	glTranslatef(-10.f, 0.f, -12.f);
	glRotatef(-25.f, 0.f, 1.f, 0.f);
	glScalef(1.f, 1.f, 4.f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(10);
	glPopMatrix();

	glPushMatrix(); // 오른쪽 앞부분 블록
	glTranslatef(10.f, 0.f, -12.f);
	glRotatef(25.f, 0.f, 1.f, 0.f);
	glScalef(1.f, 1.f, 4.f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(10);
	glPopMatrix();

	glPushMatrix(); // 앞부분 마무리부분
	glTranslatef(0.f, 0.f, -18.f);
	glScalef(1.f, 1.f, 3.f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(7, 20, 20);
	glPopMatrix();

	glPushMatrix(); // 꼬리 날개
	glTranslatef(0.f, 10.f, 35.f);
	glRotatef(270.f, 1.f, 0.f, 0.f);
	glRotatef(40.f, 1.f, 0.f, 0.f);
	glScalef(0.6f, 1.f, 1.f);
	glColor3f(0.f, 0.f, 0.f);
	glutWireCone(10, 25, 10, 4);
	glPopMatrix();

	glPushMatrix(); // 꼬리 날개 블록
	glTranslatef(0.f, 10.f, 25.f);
	glRotatef(-10.f, 1.f, 0.f, 0.f);
	glScalef(1.f, 1.2f, 2.f);
	glColor3f(0.f, 0.f, 0.f);
	glutWireCube(10);
	glPopMatrix();

	glPushMatrix(); // 배기구
	glTranslatef(0.f, 0.f, 45.f);
	glColor3f(0.f, 0.f, 0.f);
	glutWireTorus(4, 12, 10, 10);
	glPopMatrix();

	glPopMatrix();
}

void Spaceship::Render_Bullet()
{
	for (int i = 0; i < BULLET_NUM; ++i)
	{
		if (bullet[i].Exist())
		{
			glPushMatrix();
			glTranslatef(fx, fy, fz);
			bullet[i].Render();
			glPopMatrix();
		}
	}
}

void Spaceship::Update()
{
	for (int i = 0; i < BULLET_NUM; ++i)
	{
		if (bullet[i].Exist())
		{
			bullet[i].Update();
		}
	}
	if (!Boost_Mode)
	{
		if (boost + 3 < 200)
			boost += 3;
		else if (boost > 200)
			boost = 200;
	}
}

void Spaceship::Use_Boost()
{
	if (boost > 0)
		boost -= 3;
	else if (boost < 3)
		Boost_Mode = false;
}
void Spaceship::Create_Bullet()
{
	bullet[bullet_count].SetX(fx);
	bullet[bullet_count].SetY(fy);
	bullet[bullet_count].SetZ(fz);
	bullet[bullet_count].Set_Angle_X(Angle_X);
	bullet[bullet_count].Set_Angle_Y(Angle_Y);
	bullet[bullet_count].Set_Dist(BULLET_SPEED);
	bullet[bullet_count].Create();
	bullet_count++;
	if (bullet_count == BULLET_NUM)
		bullet_count = 0;
}

bool Spaceship::Collide(Meteor meteor)
{
	for (int i = 0; i < BULLET_NUM; ++i)
	{
		if (bullet[i].Exist())
		{
			if (bullet[i].Collide(meteor, fx, fy, fz))
			{
				bullet[i].Delete();
				return true;
			}
		}
	}
	return false;
}

bool Spaceship::Ship_Collide(Meteor meteor)
{
	if (meteor.Get_Exist())
	{
		if (fx > meteor.x - meteor.GetHP() && fx < meteor.x + meteor.GetHP())
		{
			if (fy > meteor.y - meteor.GetHP() && fy < meteor.y + meteor.GetHP())
			{
				if (fz > meteor.z - meteor.GetHP() && fz < meteor.z + meteor.GetHP())
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Spaceship::Render_UI(bool view, int Earth)
{
	if (view)
	{
		/*glColor3f(0.5f, 0.5f, 0.5f);
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(-400.f / 50.f, 400.f / 50.f, 0.f);
		glVertex3f(400.f / 50.f, 400.f / 50.f, 0.f);
		glVertex3f(400.f / 50.f, 300.f / 50.f, 0.f);
		glVertex3f(-400.f / 50.f, 300.f / 50.f, 0.f);
		glEnd();
		glPopMatrix();*/

		glColor3f(1.f, 0.5f, 0.f);
		glPushMatrix();
		
		glBegin(GL_QUADS);
		glVertex3f((-200.f + (float)(200 - boost)) / 50.f, (-100.f / 50.f) + 5.f, -51.f);
		glVertex3f((200.f - (float)(200 - boost)) / 50.f, (-100.f / 50.f) + 5.f, -51.f);
		glVertex3f((200.f - (float)(200 - boost)) / 50.f, (-130.f / 50.f) + 5.f, -51.f);
		glVertex3f((-200.f + (float)(200 - boost)) / 50.f, (-130.f / 50.f) + 5.f, -51.f);
		glEnd();
		glPopMatrix();

		for (int i = 0; i < life; ++i)
		{
			glColor3f(1.f, 0.f, 0.f);
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[3]);
			glBegin(GL_QUADS);
			glTexCoord3f(0, 1, 0);
			glVertex3f((-212.f + (float)(i * 50)) / 50.f, 14.5f, -36.f);
			glTexCoord3f(0, 0, 0);
			glVertex3f((-212.f + (float)(i * 50)) / 50.f, 15.3f, -36.f);
			glTexCoord3f(1, 0, 0);
			glVertex3f((-250.f + (float)(i * 50)) / 50.f, 15.3f, -36.f);
			glTexCoord3f(1, 1 ,0);
			glVertex3f((-250.f + (float)(i * 50)) / 50.f, 14.5f, -36.f);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}

		glColor3f(0.5f, 1.f, 0.5f); // 지구 HP
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(180.f / 50.f, 15.3f, -36.f);
		glVertex3f((180.f - (float)(Earth / 2)) / 50.f, 15.3f, -36.f);
		glVertex3f((180.f - (float)(Earth / 2)) / 50.f, 15.f, -36.f);
		glVertex3f(180.f / 50.f, 15.f, -36.f);
		glEnd();
		glPopMatrix();

		glColor3f(0.5f, 0.5f, 0.5f); // 이모티콘
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		if (Earth > 350)
			glBindTexture(GL_TEXTURE_2D, textures[0]);
		else if (Earth <= 350 && Earth > 100)
			glBindTexture(GL_TEXTURE_2D, textures[1]);
		else if (Earth <= 100)
			glBindTexture(GL_TEXTURE_2D, textures[2]);
		glBegin(GL_QUADS);
		glTexCoord3f(0, 1, 0);
		glVertex3f(5.f, 14.3f, -36.f);
		glTexCoord3f(0, 0, 0);
		glVertex3f(5.f, 15.3f, -36.f);
		glTexCoord3f(1, 0, 0);
		glVertex3f(4.f, 15.3f, -36.f);
		glTexCoord3f(1, 1, 0);
		glVertex3f(4.f, 14.3f, -36.f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	else
	{
		/*glColor3f(0.5f, 0.5f, 0.5f);
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(-400.f, 400.f, 0.f);
		glVertex3f(400.f, 400.f, 0.f);
		glVertex3f(400.f, 300.f, 0.f);
		glVertex3f(-400.f, 300.f, 0.f);
		glEnd();
		glPopMatrix();*/

		for (int i = 0; i < life; ++i)
		{
			glColor3f(1.f, 0.f, 0.f);
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[3]);
			glBegin(GL_QUADS);
			glTexCoord3f(0, 1, 0);
			glVertex3f(-170.f + (float)(i * 40), 320.f, 1.f);
			glTexCoord3f(0, 0, 0);
			glVertex3f(-170.f + (float)(i * 40), 350.f, 1.f);
			glTexCoord3f(1, 0, 0);
			glVertex3f(-200.f + (float)(i * 40), 350.f, 1.f);
			glTexCoord3f(1, 1, 0);
			glVertex3f(-200.f + (float)(i * 40), 320.f, 1.f);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}

		glColor3f(0.5f, 1.f, 0.5f); // 지구 HP
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(150.f, 350.f, 1.f);
		glVertex3f(150.f - (float)(Earth / 2.5), 350.f, 1.f);
		glVertex3f(150.f - (float)(Earth / 2.5), 340.f, 1.f);
		glVertex3f(150.f, 340.f, 1.f);
		glEnd();
		glPopMatrix();

		glColor3f(0.5f, 0.5f, 0.5f); // 이모티콘
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		if (Earth > 350)
			glBindTexture(GL_TEXTURE_2D, textures[0]);
		else if (Earth <= 350 && Earth > 100)
			glBindTexture(GL_TEXTURE_2D, textures[1]);
		else if (Earth <= 100)
			glBindTexture(GL_TEXTURE_2D, textures[2]); 
		glBegin(GL_QUADS);
		glTexCoord3f(0, 1, 0);
		glVertex3f(200.f, 320.f, 1.f);
		glTexCoord3f(0, 0, 0);
		glVertex3f(200.f, 350.f, 1.f);
		glTexCoord3f(1, 0, 0);
		glVertex3f(170.f, 350.f, 1.f);
		glTexCoord3f(1, 1, 0);
		glVertex3f(170.f, 320.f, 1.f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();


		glColor3f(1.f, 0.5f, 0.f);
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(-200.f + (float)(200 - boost), -100.f, 0.f);
		glVertex3f(200.f - (float)(200 - boost), -100.f, 0.f);
		glVertex3f(200.f - (float)(200 - boost), -130.f, 0.f);
		glVertex3f(-200.f + (float)(200 - boost), -130.f, 0.f);
		glEnd();
		glPopMatrix();
	}
}

// Bullet
void Bullet::Render()
{
	glPushMatrix();
	glTranslatef(fx, fy - 25.f, fz);
	glColor3f(1.f, 0.5f, 0.f);
	glutSolidSphere(3, 10, 10);
	glPopMatrix();
}
void Bullet::Update()
{
	if (exist)
	{
		dist += BULLET_SPEED;
		fx = cosf((Angle_Y + 90.f)* PI) * dist;
		fz = sinf((Angle_Y + 90.f) * PI) * -dist;
		fy = sinf(Angle_X * PI) * dist;

		if (fx > 5000 || fy > 5000 || fz > 5000)
			exist = false;
		else if (fx < -5000 || fy < -5000 || fz < -5000)
			exist = false;
	}
}

bool Bullet::Collide(Meteor meteor, float x, float y, float z)
{
	if (x + fx > meteor.x - meteor.GetHP() && x + fx < meteor.x + meteor.GetHP())
	{
		if (y + fy - 25.f > meteor.y - meteor.GetHP() && y + fy - 25.f < meteor.y + meteor.GetHP())
		{
			if (z + fz > meteor.z - meteor.GetHP() && z + fz < meteor.z + meteor.GetHP())
			{
				return true;
			}
		}
	}
	return false;
}