#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#define BASIC 100 // 도형 기본형태
#define SQUARE 1 // 정사각형
#define SCALING_SQUARE 101 // 신축 정사각형
#define TURN_SQUARE 102 // 회전 정사각형
#define SHEERING_SQUARE 103 // 밀림
#define REFLECTION_SHEERING_SQUARE 104 // 밀림 + 반사 사각형
#define TRIANGLE 2 // 삼각형
#define SCALING_TRIANGLE 201 // 신축 삼각형
#define TURN_TRIANGLE 202 // 회전 삼각형
#define SHEERING_TRIANGLE 203 // 밀림 삼각형
#define REFLECTION_TRIANGLE 204 // 반사 삼각형
#define PENTAGON 3 // 오각형
#define SCALING_PENTAGON 301 // 신축 오각형
#define TURN_PENTAGON 302 // 회전 오각형
#define SHERRING_PENTAGON 303 // 밀림 오각형
#define REFLECTION_PENTAGON 304 // 반사 오각형
#define HEXAGON 4 // 육각형
#define SCALING_HEXAGON 401 // 신축 육각형
#define TURN_HEXAGON 402 // 회전 육각형
#define SHEERING_HEXAGON 403 // 밀림 육각형
#define REFLECTION_HEXAGON 404 // 밀림 + 반사 육각형
#define BASE_RECTANGLE 0 // 만능 베이스 도형

#define SET_TIME 8000 // n초마다 스피드증가
#define SCORE_SPACE 150
#define ANGLE 90.f // 회전 각도
#define BLOCK_Y_SPACE 150 // 블록간의 간격
#define SHEERING_RATE 1.5f // 밀림비율
#define SCALING_RATE 1.5f // 신축비율
#define RECT_LEN 30.f // 도형 크기
#define PI 3.141592f/180.0f
#define BLOCK_NUMBER 10
#define PIXEL_SPEED 5
#define LINE_COUNT 5
#define LINE 150
#define WIDTH 500
#define HEIGHT 800
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

typedef int OutCode;
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
int SPEED = 30;
int Score = 0;
int Cnt = 0;
int MainWindow;
float Play_Time = 0;
int Time = 0;
float Max_y = 0;
bool Check_Line = false;
int Check_count = 0;

class GLRECT {
private:
	int line_count, type, shape;
	float fx, fy;
	bool state;
public:
	GLRECT(int count, int type, int shape) : line_count(count), type(type), shape(shape), fx(WIDTH / LINE_COUNT - WIDTH / LINE_COUNT / 2), fy(LINE - 50), state(true) {}
	GLRECT() : line_count(0), shape(rand() % 4 + 1), fy(HEIGHT + 100), fx(WIDTH / LINE_COUNT / 2), state(true) { type = shape * BASIC + rand() % 5; }
	void Down()
	{
		fy -= PIXEL_SPEED;
		if (fy < -50)
		{
			SetBlock();
		}
	}
	void Draw();
	void Remove() { state = false; SetBlock(); }
	void UpShape() { 
		shape++;
		if (shape == 5)
			shape = 1;
		type = shape * BASIC;
	}
	void DownShape() { 
		shape--; 
		if (shape == 0) 
			shape = 4;
		type = shape * BASIC;
	}
	void SetType(int n) { type = shape * BASIC + n; }
	void SetBlock()
	{ 
		line_count = rand() % LINE_COUNT;
		if (rand() % 10 == 0)
			shape = 0;
		else
			shape = rand() % 4 + 1;
		type = shape * BASIC + rand() % 5;
		fy = Max_y + BLOCK_Y_SPACE;
		Max_y = fy;
		fx = (WIDTH / LINE_COUNT * line_count) + (WIDTH / LINE_COUNT / 2);
		state = true;
	}
	void SetLine(int count) { 
		line_count = count;
		fx += WIDTH / LINE_COUNT * line_count;
	}
	void SetY(int y) { fy += y; }
	void Move_Left() {
		if (line_count > 0)
		{
			line_count--;
			fx -= WIDTH / LINE_COUNT;
		}
	}
	void Move_Right() {
		if (line_count < LINE_COUNT - 1)
		{
			line_count++;
			fx += WIDTH / LINE_COUNT;
		}
	}
	float GetY() { return fy; }
	float GetX() { return fx; }
	int GetShape() { return shape; }
	int GetType() { return type; }
	int GetLine() { return line_count; }
	bool GetState() { return state; }
};

GLRECT baserect(0, BASIC, SQUARE);
GLRECT blockrect[BLOCK_NUMBER];

void CollisionCheck();
void TimerFunction(int value);
void Keyboard(unsigned char, int, int);

void main()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < BLOCK_NUMBER; ++i)
	{
		blockrect[i].SetLine(rand() % LINE_COUNT);
		blockrect[i].SetY(i * BLOCK_Y_SPACE);
		if (Max_y < blockrect[i].GetY())
			Max_y = blockrect[i].GetY();
	}
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH + SCORE_SPACE, HEIGHT);
	MainWindow = glutCreateWindow("Computer Graphics OpenGL");
	glutTimerFunc(SPEED, TimerFunction, 1);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < LINE_COUNT; ++i)
	{
		if (i % 2)
			glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
		else
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glRectf(WIDTH/LINE_COUNT * i, 0, WIDTH/LINE_COUNT * (i + 1), HEIGHT);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glColor4f(0.5f, 0.5f, 1.0f, 0.6f);
	glRectf(0, 50 + (3 * Check_count), WIDTH, LINE - (3 * Check_count));

	glColor4f(0.3f, 0.3f, 0.3f, 0.4f);
	baserect.Draw();

	for (int i = 0; i < BLOCK_NUMBER; ++i)
	{
		glColor4f(0.8f, 0.3f, 0.3f, 1.0f);
		blockrect[i].Draw();
	}
	glDisable(GL_BLEND);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glRecti(WIDTH, 0, WIDTH + SCORE_SPACE, HEIGHT);
	for (int i = 0; i < 20; ++i)
	{
		if(Score > i)
			glColor4f(1.0f, 1.0f, 0.5f, 1.0f);
		else
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
		glRecti(WIDTH + 25, 50 + (i * 35), WIDTH + SCORE_SPACE - 25, 50 + ((i + 1) * 35));
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex2i(WIDTH + 25, 50 + ((i + 1) * 35));
		glVertex2i(WIDTH + SCORE_SPACE - 25, 50 + ((i + 1) * 35));
		glEnd();
	}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, WIDTH + SCORE_SPACE, 0.0, HEIGHT, -1.0, 1.0);
}

void TimerFunction(int value)
{
	CollisionCheck();

	Cnt = (Cnt + 1) % 2;

	if (Check_Line)
	{
		Check_count++;
		if (Check_count == 5)
		{
			Check_count = 0;
			Check_Line = false;
		}
	}
	for (int i = 0; i < BLOCK_NUMBER; ++i)
	{
		blockrect[i].Down();
	}
	Max_y -= PIXEL_SPEED;

	if (Score > 19)
	{
		glutDestroyWindow(MainWindow);
		printf("Congratulation!\nPlay Time : %fsec", Play_Time / 1000);
		getch();
		exit(0);
	}
	Play_Time += SPEED;
	Time += SPEED;
	if (Time > 5000)
	{
		if (SPEED > 10) SPEED -= 5;
		Time = 0;
		printf("%d초 경과\n", SET_TIME / 1000);
	}
	glutPostRedisplay();
	glutTimerFunc(SPEED, TimerFunction, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		baserect.Move_Left();
	}
	else if (key == 'd')
	{
		baserect.Move_Right();
	}
	else if (key == 32)
	{
		if (!Check_Line)
			Check_Line = true;
	}
	else if (key == '+')
	{
		if (SPEED > 10) SPEED -= 5;
	}
	else if (key == '-')
	{
		if (SPEED < 50) SPEED += 5;
	}
	else if (key == 'w')
	{
		baserect.DownShape();
	}
	else if (key == 'e')
	{
		baserect.UpShape();
	}
	else if (key >= 49 && key <= 54)
	{
		baserect.SetType(key - 49);
	}
}

void CollisionCheck() {
	if (Check_Line)
	{
		for (int i = 0; i < BLOCK_NUMBER; ++i)
		{
			if (blockrect[i].GetY() < LINE && blockrect[i].GetState())
			{
				if (blockrect[i].GetShape() == BASE_RECTANGLE)
				{
					if (baserect.GetY() == blockrect[i].GetY() && (baserect.GetLine() == blockrect[i].GetLine()))
					{
						blockrect[i].Remove();
						Score += 2;
						printf("Perfect Hit!	Score = %d\n", Score);
						break;
					}
					else if (baserect.GetY() >= blockrect[i].GetY() - RECT_LEN && baserect.GetY() <= blockrect[i].GetY() + RECT_LEN)
					{
						blockrect[i].Remove();
						Score += 1;
						printf("Hit!	Score = %d\n", Score);
						break;
					}
				}
				else if ((baserect.GetType() == blockrect[i].GetType()) && (baserect.GetLine() == blockrect[i].GetLine()))
				{
					if (baserect.GetY() == blockrect[i].GetY())
					{
						blockrect[i].Remove();
						Score += 2;
						printf("Perfect Hit!	Score = %d\n", Score);
						break;
					}
					else if (baserect.GetY() >= blockrect[i].GetY() - RECT_LEN && baserect.GetY() <= blockrect[i].GetY() + RECT_LEN)
					{
						blockrect[i].Remove();
						Score += 1;
						printf("Hit!	Score = %d\n", Score);
						break;
					}
				}
			}
		}
	}
}

void GLRECT::Draw()
{
	if (state)
	{
		if (shape == BASE_RECTANGLE)
		{
			if(Cnt)
				glColor4f(0.8f, 0.8f, 0.3f, 0.6f);
			else
				glColor4f(0.8f, 0.3f, 0.8f, 0.6f);
			glBegin(GL_POLYGON);
			glVertex2f(fx - RECT_LEN, fy + RECT_LEN);
			glVertex2f(fx + RECT_LEN, fy + RECT_LEN);
			glVertex2f(fx + RECT_LEN, fy - RECT_LEN);
			glVertex2f(fx - RECT_LEN, fy - RECT_LEN);
			glEnd();
		}
		else if (shape == SQUARE)
		{
			if (type == SQUARE * BASIC)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx - RECT_LEN, fy + RECT_LEN);
				glVertex2f(fx + RECT_LEN, fy + RECT_LEN);
				glVertex2f(fx + RECT_LEN, fy - RECT_LEN);
				glVertex2f(fx - RECT_LEN, fy - RECT_LEN);
				glEnd();
			}
			else if (type == SCALING_SQUARE)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx - (RECT_LEN * SCALING_RATE), fy + (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + (RECT_LEN * SCALING_RATE), fy + (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + (RECT_LEN * SCALING_RATE), fy - (RECT_LEN * SCALING_RATE));
				glVertex2f(fx - (RECT_LEN * SCALING_RATE), fy - (RECT_LEN * SCALING_RATE));
				glEnd();
			}
			else if (type == TURN_SQUARE)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf(0.f * PI) * RECT_LEN, fy + sinf(0.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(90.f * PI) * RECT_LEN, fy + sinf(90.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(180.f * PI) * RECT_LEN, fy + sinf(180.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(270.f * PI) * RECT_LEN, fy + sinf(270.f * PI) * RECT_LEN);
				glEnd();
			}
			else if (type == SHEERING_SQUARE)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx - RECT_LEN, fy + RECT_LEN);
				glVertex2f(fx + (RECT_LEN * SHEERING_RATE), fy + (RECT_LEN * SHEERING_RATE));
				glVertex2f(fx + RECT_LEN, fy - RECT_LEN);
				glVertex2f(fx - (RECT_LEN * SHEERING_RATE), fy - (RECT_LEN * SHEERING_RATE));
				glEnd();
			}
			else if (type == REFLECTION_SHEERING_SQUARE)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx - (RECT_LEN * SHEERING_RATE), fy + (RECT_LEN * SHEERING_RATE));
				glVertex2f(fx + RECT_LEN, fy + RECT_LEN);
				glVertex2f(fx + (RECT_LEN * SHEERING_RATE), fy - (RECT_LEN * SHEERING_RATE));
				glVertex2f(fx - RECT_LEN, fy - RECT_LEN);
				glEnd();
			}
		}
		if (shape == TRIANGLE)
		{
			if (type == TRIANGLE * BASIC)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + (cosf(90.f * PI) * RECT_LEN), fy + (sinf(90.f * PI) * RECT_LEN));
				glVertex2f(fx + (cosf(210.f * PI) * RECT_LEN), fy + (sinf(210.f * PI) * RECT_LEN));
				glVertex2f(fx + (cosf(330.f * PI) * RECT_LEN), fy + (sinf(330.f * PI) * RECT_LEN));
				glEnd();
			}
			else if (type == SCALING_TRIANGLE)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + (cosf(90.f * PI) * (RECT_LEN * SCALING_RATE)), fy + (sinf(90.f * PI) * (RECT_LEN * SCALING_RATE)));
				glVertex2f(fx + (cosf(210.f * PI) * (RECT_LEN * SCALING_RATE)), fy + (sinf(210.f * PI) * (RECT_LEN * SCALING_RATE)));
				glVertex2f(fx + (cosf(330.f * PI) * (RECT_LEN * SCALING_RATE)), fy + (sinf(330.f * PI) * (RECT_LEN * SCALING_RATE)));
				glEnd();
			}
			else if (type == TURN_TRIANGLE)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + (cosf((90.f + ANGLE) * PI) * RECT_LEN), fy + (sinf((90.f + ANGLE) * PI) * RECT_LEN));
				glVertex2f(fx + (cosf((210.f + ANGLE) * PI) * RECT_LEN), fy + (sinf((210.f + ANGLE) * PI) * RECT_LEN));
				glVertex2f(fx + (cosf((330.f + ANGLE) * PI) * RECT_LEN), fy + (sinf((330.f + ANGLE) * PI) * RECT_LEN));
				glEnd();
			}
			else if (type == SHEERING_TRIANGLE)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + (cosf(90.f * PI) * (RECT_LEN * SHEERING_RATE)), fy + (sinf(90.f * PI) * (RECT_LEN * SHEERING_RATE)));
				glVertex2f(fx + (cosf(210.f * PI) * RECT_LEN), fy + (sinf(210.f * PI) * RECT_LEN));
				glVertex2f(fx + (cosf(330.f * PI) * (RECT_LEN * SHEERING_RATE)), fy + (sinf(330.f * PI) * (RECT_LEN * SHEERING_RATE)));
				glEnd();
			}
			else if (type == REFLECTION_TRIANGLE)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + (cosf(30.f * PI) * RECT_LEN), fy + (sinf(30.f * PI) * RECT_LEN));
				glVertex2f(fx + (cosf(150.f * PI) * RECT_LEN), fy + (sinf(150.f * PI) * RECT_LEN));
				glVertex2f(fx + (cosf(270.f * PI) * RECT_LEN), fy + (sinf(270.f * PI) * RECT_LEN));
				glEnd();
			}
		}
		if (shape == PENTAGON)
		{
			if (type == PENTAGON * BASIC)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf(90.f * PI) * RECT_LEN, fy + sinf(90.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(162.f * PI) * RECT_LEN, fy + sinf(162.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(234.f * PI) * RECT_LEN, fy + sinf(234.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(306.f * PI) * RECT_LEN, fy + sinf(306.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(378.f * PI) * RECT_LEN, fy + sinf(378.f * PI) * RECT_LEN);
				glEnd();
			}
			else if (type == SCALING_PENTAGON)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf(90.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(90.f * PI) * (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + cosf(162.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(162.f * PI) * (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + cosf(234.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(234.f * PI) * (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + cosf(306.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(306.f * PI) * (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + cosf(378.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(378.f * PI) * (RECT_LEN * SCALING_RATE));
				glEnd();
			}
			else if (type == TURN_PENTAGON)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf((90.f + ANGLE) * PI) * RECT_LEN, fy + sinf((90.f + ANGLE) * PI) * RECT_LEN);
				glVertex2f(fx + cosf((162.f + ANGLE) * PI) * RECT_LEN, fy + sinf((162.f + ANGLE) * PI) * RECT_LEN);
				glVertex2f(fx + cosf((234.f + ANGLE) * PI) * RECT_LEN, fy + sinf((234.f + ANGLE) * PI) * RECT_LEN);
				glVertex2f(fx + cosf((306.f + ANGLE) * PI) * RECT_LEN, fy + sinf((306.f + ANGLE) * PI) * RECT_LEN);
				glVertex2f(fx + cosf((378.f + ANGLE)  * PI) * RECT_LEN, fy + sinf((378.f + ANGLE) * PI) * RECT_LEN);
				glEnd();
			}
			else if (type == SHERRING_PENTAGON)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf(90.f * PI) * RECT_LEN, fy + sinf(90.f * PI) * (RECT_LEN * SHEERING_RATE));
				glVertex2f(fx + cosf(162.f * PI) * (RECT_LEN * SHEERING_RATE), fy + sinf(162.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(234.f * PI) * RECT_LEN, fy + sinf(234.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(306.f * PI) * RECT_LEN, fy + sinf(306.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(378.f * PI) * (RECT_LEN * SHEERING_RATE), fy + sinf(378.f * PI) * RECT_LEN);
				glEnd();
			}
			else if (type == REFLECTION_PENTAGON)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf(270.f * PI) * RECT_LEN, fy + sinf(270.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(342.f * PI) * RECT_LEN, fy + sinf(342.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(54.f * PI) * RECT_LEN, fy + sinf(54.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(126.f * PI) * RECT_LEN, fy + sinf(126.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(198.f * PI) * RECT_LEN, fy + sinf(198.f * PI) * RECT_LEN);
				glEnd();
			}
		}
		if (shape == HEXAGON)
		{
			if (type == HEXAGON * BASIC)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf(0.f * PI) * RECT_LEN, fy + sinf(0.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(60.f * PI) * RECT_LEN, fy + sinf(60.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(120.f * PI) * RECT_LEN, fy + sinf(120.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(180.f * PI) * RECT_LEN, fy + sinf(180.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(240.f * PI) * RECT_LEN, fy + sinf(240.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(300.f * PI) * RECT_LEN, fy + sinf(300.f * PI) * RECT_LEN);
				glEnd();
			}
			else if (type == SCALING_HEXAGON)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf(0.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(0.f * PI) * (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + cosf(60.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(60.f * PI) * (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + cosf(120.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(120.f * PI) * (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + cosf(180.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(180.f * PI) * (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + cosf(240.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(240.f * PI) * (RECT_LEN * SCALING_RATE));
				glVertex2f(fx + cosf(300.f * PI) * (RECT_LEN * SCALING_RATE), fy + sinf(300.f * PI) * (RECT_LEN * SCALING_RATE));
				glEnd();
			}
			else if (type == TURN_HEXAGON)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf((0.f + ANGLE) * PI) * RECT_LEN, fy + sinf((0.f + ANGLE) * PI) * RECT_LEN);
				glVertex2f(fx + cosf((60.f + ANGLE) * PI) * RECT_LEN, fy + sinf((60.f + ANGLE) * PI) * RECT_LEN);
				glVertex2f(fx + cosf((120.f + ANGLE) * PI) * RECT_LEN, fy + sinf((120.f + ANGLE) * PI) * RECT_LEN);
				glVertex2f(fx + cosf((180.f + ANGLE) * PI) * RECT_LEN, fy + sinf((180.f + ANGLE) * PI) * RECT_LEN);
				glVertex2f(fx + cosf((240.f + ANGLE) * PI) * RECT_LEN, fy + sinf((240.f + ANGLE) * PI) * RECT_LEN);
				glVertex2f(fx + cosf((300.f + ANGLE) * PI) * RECT_LEN, fy + sinf((300.f + ANGLE) * PI) * RECT_LEN);
				glEnd();
			}
			else if (type == SHEERING_HEXAGON)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf(0.f * PI) * RECT_LEN, fy + sinf(0.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(60.f * PI) * (RECT_LEN * SHEERING_RATE), fy + sinf(60.f * PI) * (RECT_LEN * SHEERING_RATE));
				glVertex2f(fx + cosf(120.f * PI) * RECT_LEN, fy + sinf(120.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(180.f * PI) * RECT_LEN, fy + sinf(180.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(240.f * PI) * (RECT_LEN * SHEERING_RATE), fy + sinf(240.f * PI) * (RECT_LEN * SHEERING_RATE));
				glVertex2f(fx + cosf(300.f * PI) * RECT_LEN, fy + sinf(300.f * PI) * RECT_LEN);
				glEnd();
			}
			else if (type == REFLECTION_HEXAGON)
			{
				glBegin(GL_POLYGON);
				glVertex2f(fx + cosf(90.f * PI) * RECT_LEN, fy + sinf(90.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(150.f * PI) * (RECT_LEN * SHEERING_RATE), fy + sinf(150.f * PI) * (RECT_LEN * SHEERING_RATE));
				glVertex2f(fx + cosf(210.f * PI) * RECT_LEN, fy + sinf(210.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(270.f * PI) * RECT_LEN, fy + sinf(270.f * PI) * RECT_LEN);
				glVertex2f(fx + cosf(330.f * PI) * (RECT_LEN * SHEERING_RATE), fy + sinf(330.f * PI) * (RECT_LEN * SHEERING_RATE));
				glVertex2f(fx + cosf(30.f * PI) * RECT_LEN, fy + sinf(30.f * PI) * RECT_LEN);
				glEnd();
			}
		}
	}
}
