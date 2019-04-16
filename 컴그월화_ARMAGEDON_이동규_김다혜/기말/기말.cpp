#include "stdafx.h"
#include "Logo.h"
#include "Meteor.h"
#include "Spaceship.h"
#include "Meteor.h"
#include "Satellite.h"
#include "Space.h"
#include "Shop.h"
#include "Sound.h"


// 돈무한 치트 : money 변수를 그냥 변경시키면 끝
// 피회복 치트 : Player.Set_Life(3); 무조건 3이여야함
// 지구HP 치트 : Earth_Hp 변수를 그냥 변경시키면 끝
// Render_Defeat 함수가 패배시 알림창 띄우는 함수

#define FRONT 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define START_WINDOW_X 300
#define START_WINDOW_Y 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define DISPLAY_LOGO 10
#define DISPLAY_GAME 11
#define DISPLAY_SHOP 12
#define DEFEAT 13
#define FPS_VIEW true
#define TPS_VIEW false
#define WOL_VIEW false
#define METEOR_MAX 10
#define SATELLITE_MAX 5
#define ATTACK_UPGRADE_PRICE 200
#define SATELLITE_PRICE 500

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Render_GamePlay();

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
void Motion(int x, int y);
void Mouse(int button, int state, int x, int y);
void GamePlay_Init();
void Render_Defeat();
int MainWindow;
void String(float x, float y, float z, int rate);

float Move_Speed = 0.f;
int Camera_Move_LR = FRONT;
int Camera_Move_UD = FRONT;
int Game_State = DISPLAY_LOGO;
bool Camera_State = TPS_VIEW;
float Z = -150.f;
int width, height;
float Angle_Z;
int meteor_count = 0;
int play_time;
int score;
int money;
float m_x, m_y;
int satellite_count = 0;
int satellite_num = 0;
bool Collision;
int collision_frame;
int life;
int Earth_Hp;
bool Meteor_Boost;
int len;
char str[100];
char damage[30];

Logo logo;
Spaceship Player;
Meteor meteor[METEOR_MAX];
Satellite satellite[SATELLITE_MAX];
Space space;
Shop shop;

GLuint textures[1];
GLubyte* pBytes;
Loadbitmap Load;
BITMAPINFO* info;
CSound sound;

void main()
{
	srand((unsigned)time(NULL));
	SetCursorPos(START_WINDOW_X + WINDOW_WIDTH / 2, START_WINDOW_Y + WINDOW_HEIGHT / 2);
	/*ShowCursor(false);*/
	sound.init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(START_WINDOW_X, START_WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	MainWindow = glutCreateWindow("Armageddon");
	glutTimerFunc(30, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(KeyBoard);
	glutPassiveMotionFunc(Motion);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	//SetCursorPos(500, 500);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	if (Game_State == DISPLAY_LOGO)
	{
		logo.Render();
	}
	else if (Game_State == DEFEAT)
	{
		Render_Defeat();
	}
	else
	{
		Render_GamePlay();
	}

	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}


void GamePlay_Init()
{
	for (int i = 0; i < METEOR_MAX; ++i)
	{
		meteor[i].Reshape();
	}
	life = Player.Get_Life();
	Meteor_Boost = false;
	Collision = false;
	collision_frame = 0;
	meteor[0].Create();
	play_time = 0;
	meteor_count = 1;
	satellite_count = 0;
	score = 0;
	money = 0;
	Earth_Hp = 500;
}

void Render_GamePlay()
{
	glPushMatrix();
	if (Camera_State) // 1인칭
	{
		glTranslatef(0.f, 208.f, 426.f);
		if (Player.Boost_State() && Game_State == DISPLAY_GAME)
		{
			glTranslatef(0.f, (float)(rand() % 30 - 15) / 50.f, (float)(rand() % 30 - 15) / 50.f);
		}
	}
	else // 3인칭
	{
		if (Player.Boost_State() && Game_State == DISPLAY_GAME)
		{
			glTranslatef((float)(rand() % 8 - 4), (float)(rand() % 8 - 4), (float)(rand() % 8 - 4));
		}
	}
	if (Camera_State)
		glRotatef(-Angle_Z, 0.f, 0.f, 1.f);
	glRotatef(-Player.Get_Angle_X(), 1.f, 0.f, 0.f);
	glRotatef(-Player.Get_Angle_Y(), 0.f, 1.f, 0.f);
	glTranslatef(-Player.GetX(), -Player.GetY(), -Player.GetZ());

	space.Render();
	
	glPushMatrix();
	glTranslatef(Player.GetX(), Player.GetY(), Player.GetZ());
	glRotatef(Player.Get_Angle_Y(), 0.f, 1.f, 0.f);
	glRotatef(Player.Get_Angle_X(), 1.f, 0.f, 0.f);
	if (Camera_State)
	{
		glRotatef(Angle_Z, 0.f, 0.f, 1.f);
		if (collision_frame % 2 || !Collision)
		{
			if (Game_State == DISPLAY_SHOP)
			{
				shop.Render_Shop(Camera_State);
				Player.Render(true);
			}
			else
				Player.Render(false);
		}
		glPushMatrix();
		Player.Render_UI(Camera_State, Earth_Hp);
		String(-14, 3, -51, 18);
		glPopMatrix();
	}
	else
	{
		if (Game_State == DISPLAY_SHOP)
		{
			shop.Render_Shop(Camera_State);
		}
		glPushMatrix();
		Player.Render_UI(Camera_State, Earth_Hp);
		String(-250, -80, 0, 1);
		glPopMatrix();
		glRotatef(Angle_Z, 0.f, 0.f, 1.f);
		if (collision_frame % 2 || !Collision)
		{
			if (Game_State == DISPLAY_SHOP)
			{
				Player.Render(true);
			}
			else
				Player.Render(false);
		}
	}
	//Player.WireRender();
	glPopMatrix();

	for (int i = 0; i < satellite_count; ++i)
	{
		glPushMatrix();
		satellite[i].Render_Raser();
		glTranslatef(satellite[i].GetX(), satellite[i].GetY(), satellite[i].GetZ());
		satellite[i].Render();
		// 인공위성 범위
		//satellite[i].Render_Range();		
		glPopMatrix();
	}


	Player.Render_Bullet();

	/*glPushMatrix();
	glTranslatef(0.f, -5200.f, 0.f);
	glScalef(10.f, 0.1f, 10.f);
	glColor3f(0.2f, 0.2f, 1.f);
	glutSolidCube(5000);
	glPopMatrix();*/

	for (int i = 0; i < meteor_count; ++i)
	{
		meteor[i].Render();
	}
	glPopMatrix();
}

GLvoid Reshape(int w, int h)
{
	logo.Reshape();
	space.Reshape();
	shop.Reshape();
	Player.Reshape();
	glLoadIdentity();
	
	glGenTextures(MAX, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	{
		pBytes = Load.LoadDIBitmap("gameover.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 800.0, 0.0, -1.0, 1.0);

}

void TimerFunction(int value)
{
	if (Game_State == DISPLAY_LOGO)
	{
		logo.Timer();
	}
	else if (Game_State == DISPLAY_GAME)
	{
		if (Player.Move_State())
		{
			float tx = 0.f;
			float ty = 0.f;
			float tz = 0.f;
			if (Player.Boost_State())
			{
				tz = Player.GetZ() + sinf((Player.Get_Angle_Y() + 90.f) * PI) * -35.f;
				if (tz > -2500 && tz < 2500)
					Player.SetZ(tz);

				tx = Player.GetX() + cosf((Player.Get_Angle_Y() + 90.f) * PI) * 35.f;
				if (tx > -2500 && tx < 2500)
					Player.SetX(tx);

				ty = Player.GetY() + sinf(Player.Get_Angle_X() * PI) * 35.f;
				if (ty > -2500 && ty < 2500)
					Player.SetY(ty);

				Player.Use_Boost();
			}
			else
			{
				tz = Player.GetZ() + sinf((Player.Get_Angle_Y() + 90.f) * PI) * -15.f;
				if (tz > -2500 && tz < 2500)
					Player.SetZ(tz);

				tx = Player.GetX() + cosf((Player.Get_Angle_Y() + 90.f) * PI) * 15.f;
				if (tx > -2500 && tx < 2500)
					Player.SetX(tx);

				ty = Player.GetY() + sinf(Player.Get_Angle_X() * PI) * 15.f;
				if (ty > -2500 && ty < 2500)
					Player.SetY(ty);
			}
		}

		Player.Turn_Y(m_x);

		Player.Turn_X(m_y);

		Player.Update();

		for (int j = 0; j < satellite_count; ++j)
		{
			satellite[j].Delete_Raser();
			for (int i = 0; i < meteor_count; ++i)
			{
				satellite[j].Set_Raser(meteor[i], i);
			}
			if (satellite[j].Get_An() != -1)
			{
				int check = 0;
				check += meteor[satellite[j].Get_An()].Collide(1);
				if (check != 0) // 운석이 파괴될 경우
				{
					sound.volume(3, 1.0);
					sound.play(3);
					satellite[j].Delete_Raser();
					money += check;
					score += 100;
					//printf("Money =	%d, Score =	%d\n", money, score);
				}
			}
		}

		for (int i = 0; i < meteor_count; ++i)
		{
			if (Player.Collide(meteor[i]))
			{
				int check = 0;
				check += meteor[i].Collide(Player.Get_Damage());
				if (check != 0) // 운석이 파괴될 경우
				{
					sound.volume(3, 1.0);
					sound.play(3);
					money += check;
					score += 100;
					//printf("Money =	%d, Score =	%d\n", money, score);
				}
			}
			if (Player.Ship_Collide(meteor[i]))
			{
				if (!Collision)
				{
					Player.Hit_Life();
					life--;
					if (life == 0)
						Game_State = DEFEAT;
					Collision = true;
				}
			}
			if (Meteor_Boost)
			{
				meteor[i].Update();
				meteor[i].Update();
				meteor[i].Update();
			}
				meteor[i].Update();
			if (meteor[i].y - meteor[i].GetHP() < -3500)
			{
				Earth_Hp -= meteor[i].GetHP() / 2;
				meteor[i].Collide(meteor[i].GetHP());
				if (Earth_Hp <= 0)
				{
					Earth_Hp = 0;
					Game_State = DEFEAT;
				}
			}
		}
		if (Collision)
		{
			collision_frame += 1;
			if (collision_frame == 150)
			{
				collision_frame = 0;
				Collision = false;
			}
		}
		play_time += 30;
		if (play_time > 20000)
		{
			if (meteor_count < METEOR_MAX)
			{
				meteor[meteor_count].Create();
				meteor_count++;
				//printf("20초 경과 %d번째 운석 생성\n", meteor_count);
			}
			play_time -= 20000;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') // 종료
	{
		sound.Release();

		glutDestroyWindow(MainWindow);
		exit(0);
	}
	
	if (Game_State == DISPLAY_LOGO)
	{
		if (key == 13)
		{
			sound.stop();
			sound.play(1);
			glViewport(0, 0, width, height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			gluPerspective(60.0f, width / height, 1.0, 10000.0);

			gluLookAt(0.0, 220.0, 400.0, 0.0, 0.0, -800.0, 0.0, 1.0, 0.0);
			//glOrtho(0.0, 800.0, 0.0, 800.0, 0.0, 800.0);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			Game_State = DISPLAY_GAME;
			ShowCursor(false);
			GamePlay_Init();
		}
	}

	if (key == 'w' || key == 'W')
	{
		if (Game_State == DISPLAY_GAME)
		{
			if (!Player.Move_State())
				Player.Start_Move();
			else
			{
				Player.End_Move();
				Player.Boost_Off();
			}
		}
	}
	else if (key == 'p' || key == 'P')
	{
		if (Game_State == DISPLAY_GAME)
		{
			Game_State = DISPLAY_SHOP;
			ShowCursor(true);
		}
		else if (Game_State == DISPLAY_SHOP)
		{
			Game_State = DISPLAY_GAME;
			ShowCursor(false);
		}
	}
	else if (key == 'd' || key == 'D')
	{
		Angle_Z -= 5.f;
	}
	else if (key == 'a' || key == 'A')
	{
		Angle_Z += 5.f;
	}
	else if (key == 'c' || key == 'C')
	{
		if (Camera_State)
			Camera_State = TPS_VIEW;
		else
			Camera_State = FPS_VIEW;
	}
	else if (key == ' ')
	{
		if (Player.Move_State())
		{
			if (Player.Boost_State())
				Player.Boost_Off();
			else
			{
				sound.play(2);
				Player.Boost_On();
			}
		}
	}
	else if (key == '-')
	{
		if (Earth_Hp > 0)
			Earth_Hp -= 10;
	}
	else if (key == '+')
	{
		if (Earth_Hp < 500)
			Earth_Hp += 10;
	}
	else if (key == 'm' || key == 'M')
	{
		if (Meteor_Boost)
			Meteor_Boost = false;
		else
			Meteor_Boost = true;
	}
	else if (key == '1')
	{
		money += 100000;
		printf("money = %d\n", money);
	}
	else if (key == '2')
	{
		Player.Set_Life(3);
	}
	else if (key == '3')
	{
		Earth_Hp = 500;
	}
	else if (key == '4')
	{
		Game_State = DEFEAT;
	}
}
void Motion(int x, int y)
{
	if (Game_State == DISPLAY_GAME)
	{
		m_x = 0.f;
		m_y = 0.f;
		if (x - WINDOW_WIDTH / 2 < -100)
		{
			m_x = (float)(x - WINDOW_WIDTH / 2) / -180.f;
		}
		else if (x - WINDOW_WIDTH / 2 > 100)
		{
			m_x = (float)(x - WINDOW_WIDTH / 2) / -180.f;
		}

		if (y - WINDOW_HEIGHT / 2 > 100)
		{
			m_y = (float)(y - WINDOW_WIDTH / 2) / -180.f;
		}
		else if (y - WINDOW_HEIGHT / 2 < -100)
		{
			m_y = (float)(y - WINDOW_WIDTH / 2) / -180.f;
		}

		RECT rt = { START_WINDOW_X, START_WINDOW_Y, START_WINDOW_X + WINDOW_WIDTH, START_WINDOW_Y + WINDOW_HEIGHT };
		ClipCursor(&rt);
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//if (Game_State == DISPLAY_LOGO)
		//{
		//	logo.Relese();
		//	space.init();
		//	glViewport(0, 0, width, height);
		//	glMatrixMode(GL_PROJECTION);
		//	glLoadIdentity();

		//	gluPerspective(60.0f, width / height, 1.0, 10000.0);

		//	gluLookAt(0.0, 220.0, 400.0, 0.0, 0.0, -800.0, 0.0, 1.0, 0.0);
		//	//glOrtho(0.0, 800.0, 0.0, 800.0, 0.0, 800.0);

		//	glMatrixMode(GL_MODELVIEW);
		//	glLoadIdentity();
		//	Game_State = DISPLAY_GAME;
		//	ShowCursor(false);
		//	GamePlay_Init();
		//}
		if (Game_State == DISPLAY_GAME)
		{ // 총알 발사
			sound.play(4);
			Player.Create_Bullet();
		}
		else if (Game_State == DISPLAY_SHOP)
		{
			if (Camera_State == FPS_VIEW)
			{
				if (x - 400 > -252 && x - 400 < -15 && y - 400 > -240 && y - 400 < -8)
				{
					if (money < ATTACK_UPGRADE_PRICE)
						printf("공격력 업그레이드는 %d원 입니다. ( 잔액 : %d원 )\n", ATTACK_UPGRADE_PRICE, money);
					else if (money > ATTACK_UPGRADE_PRICE)
					{
						if (Player.Upgrade(5))
						{
							money -= ATTACK_UPGRADE_PRICE;
							printf("업그레이드 완료 ( 잔액 : %d원 )\n", money);
						}
						else
							printf("더이상 업그레이드 불가능\n");
					}
				}
				else if (x - 400 > 14 && x - 400 < 252 && y - 400 > -240 && y - 400 < -8)
				{
					if (money < SATELLITE_PRICE)
						printf("인공위성은 %d원 입니다. ( 잔액 : %d원 )\n", ATTACK_UPGRADE_PRICE, money);
					else if (money > SATELLITE_PRICE)
					{
						if (satellite_count < SATELLITE_MAX)
						{
							money -= SATELLITE_PRICE;
							printf("구매 완료 ( 잔액 : %d원 )\n", money);
							satellite[satellite_count].Create(Player.GetX(), Player.GetY(), Player.GetZ());
							satellite_count++;
						}
						else
						{
							printf("더이상 구매 불가능\n");
						}
					}
				}
				else if (x - 400 > 229 && x - 400 < 293 && y - 400 > 73 && y - 400 < 92)
				{
					Game_State = DISPLAY_GAME;
					ShowCursor(false);
				}
			}
			else
			{
				if (x - 400 > -309 && x - 400 < -21 && y - 400 > -140 && y - 400 < 150)
				{
					if (money < ATTACK_UPGRADE_PRICE)
						printf("공격력 업그레이드는 %d원 입니다. ( 잔액 : %d원 )\n", ATTACK_UPGRADE_PRICE, money);
					else if (money > ATTACK_UPGRADE_PRICE)
					{
						if (Player.Upgrade(5))
						{
							money -= ATTACK_UPGRADE_PRICE;
							printf("업그레이드 완료 ( 잔액 : %d원 )\n", money);
						}
						else
							printf("더이상 업그레이드 불가능\n");
					}
				}
				else if (x - 400 > 19 && x - 400 < 306 && y - 400 > -140 && y - 400 < 150)
				{
					if (money < SATELLITE_PRICE)
						printf("인공위성은 %d원 입니다. ( 잔액 : %d원 )\n", ATTACK_UPGRADE_PRICE, money);
					else if (money > SATELLITE_PRICE)
					{
						if (satellite_count < SATELLITE_MAX)
						{
							money -= SATELLITE_PRICE;
							printf("구매 완료 ( 잔액 : %d원 )\n", money);
							satellite[satellite_count].Create(Player.GetX(), Player.GetY(), Player.GetZ());
							satellite_count++;
						}
						else
						{
							printf("더이상 구매 불가능\n");
						}
					}
				}
				else if (x - 400 > 280 && x - 400 < 360 && y - 400 > 245 && y - 400 < 270)
				{
					Game_State = DISPLAY_GAME;
					ShowCursor(false);
				}
			}
		}
	}
}

void Render_Defeat()
{
	Camera_State = TPS_VIEW;
	glPushMatrix();
	glColor3f(1.f, 1.f, 1.f);
	glRotatef(-10.0f, 1, 0, 0);
	glTranslated(0, -50, 0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glTexCoord3f(1, 0, 0);
	glVertex3f(-200.f, 0.f, 0.f);
	glTexCoord3f(0, 0, 0);
	glVertex3f(200.f, 0.f, 0.f);
	glTexCoord3f(0, 1, 0);
	glVertex3f(200.f, 400.f, 0.f);
	glTexCoord3f(1, 1, 0);
	glVertex3f(-200.f, 400.f, 0.f);
	glEnd();
	glPopMatrix();
}

void String(float x, float y, float z, int rate)
{
	glColor3f(1.f, 1.f, 1.f);
	//glTranslatef(-250/rate, -80/rate, 0);
	glTranslatef(x, y, z);
	glRasterPos2f(0, 0);
	sprintf(str, "Money:%d Score:%d", money, score);
	len = (int)strlen(str);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	glColor3f(1.f, 0.f, 0.f);
	glRasterPos2f(440/rate, 0);
	sprintf(damage, "Damage:%d",Player.Get_Damage());
	len = (int)strlen(damage);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, damage[i]);
	glColor3f(0.f, 1.f, 0.f);
}