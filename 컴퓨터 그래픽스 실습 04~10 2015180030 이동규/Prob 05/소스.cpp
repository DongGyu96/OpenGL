#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#define PI 3.141592
#define DEG2RAD PI/180
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Rect {
	int x, y;
	int direction;
	BOOL shape, Color, stat;
};

BOOL shape = false;
int SPEED = 10;
Rect glrect[20];
int count = 0;

void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void MenuFunc(int button);

void main()
{
	int MainMenu;

	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Computer Graphics OpenGL");
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutTimerFunc(200, TimerFunction, 2);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

	MainMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Ellipse", 1);
	glutAddMenuEntry("Rectangle", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 20; ++i)
	{
		if (glrect[i].Color)
			glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
		else
			glColor4f(0.8f, 0.5f, 0.5f, 1.0f);

		if (glrect[i].stat)
		{
			if (shape) // 원
			{
				glBegin(GL_POLYGON);
				for (int n = 0; n < 360; ++n)
				{
					int X = cos(n * DEG2RAD) * 20;
					int Y = sin(n * DEG2RAD) * 20;
					glVertex2i(glrect[i].x + X, glrect[i].y + Y);
				}
				glEnd();
			}
			else
			{
				if (glrect[i].shape)
				{
					glBegin(GL_POLYGON);
					glVertex2i(glrect[i].x - 20, glrect[i].y - 10);
					glVertex2i(glrect[i].x - 20, glrect[i].y + 10);
					glVertex2i(glrect[i].x + 20, glrect[i].y + 10);
					glVertex2i(glrect[i].x + 20, glrect[i].y - 10);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glVertex2i(glrect[i].x - 10, glrect[i].y - 20);
					glVertex2i(glrect[i].x - 10, glrect[i].y + 20);
					glVertex2i(glrect[i].x + 10, glrect[i].y + 20);
					glVertex2i(glrect[i].x + 10, glrect[i].y - 20);
					glEnd();
				}
			}
		}
	}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glrect[count].x = x;
		glrect[count].y = 600 - y;
		glrect[count].direction = rand() % 4;
		glrect[count].shape = true;
		glrect[count].Color = true;
		glrect[count].stat = true;
		count++;
		count = count % 20;
		glutPostRedisplay();
	}
}

void TimerFunction(int value)
{
	if (value == 1)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (glrect[i].Color)
				glrect[i].Color = false;
			else
				glrect[i].Color = true;



			if (glrect[i].direction == 0) // 오른쪽 위
			{
				glrect[i].x += SPEED;
				glrect[i].y += SPEED;
				if (glrect[i].y >= 600)
					glrect[i].direction = 1;
				if (glrect[i].x >= 800)
					glrect[i].direction = 2;
			}
			else if (glrect[i].direction == 1) // 오른쪽 아래
			{
				glrect[i].x += SPEED;
				glrect[i].y -= SPEED;
				if (glrect[i].y <= 0)
					glrect[i].direction = 0;
				if (glrect[i].x >= 800)
					glrect[i].direction = 3;
			}
			else if (glrect[i].direction == 2) // 왼쪽 위
			{
				glrect[i].x -= SPEED;
				glrect[i].y += SPEED;
				if (glrect[i].y >= 600)
					glrect[i].direction = 1;
				if (glrect[i].x <= 0)
					glrect[i].direction = 0;
			}
			else if (glrect[i].direction == 3) // 왼쪽 아래
			{
				glrect[i].x -= SPEED;
				glrect[i].y -= SPEED;
				if (glrect[i].y <= 0)
					glrect[i].direction = 2;
				if (glrect[i].x <= 0)
					glrect[i].direction = 1;
			}


		}
		glutPostRedisplay();
		glutTimerFunc(100, TimerFunction, 1);
	}
	else if (value == 2)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (glrect[i].shape)
				glrect[i].shape = false;
			else
				glrect[i].shape = true;
		}
		glutPostRedisplay();
		glutTimerFunc(200, TimerFunction, 2);
	}
}

void MenuFunc(int button)
{
	if (button == 1)
	{
		shape = true;
	}
	else if (button == 2)
	{
		shape = false;
	}
	glutPostRedisplay();
}