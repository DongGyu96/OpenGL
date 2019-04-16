#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#define SPEED 5
#define PI 3.141592
#define DEG2RAD PI/180
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Rect {
	int x, y;
	int direction;
	int r, count;
	BOOL stat, expand;
};

Rect glrect[20];
int count = 0;

void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);

void main()
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Computer Graphics OpenGL");
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(0.8f, 0.5f, 0.5f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2i(100, 500);
	glVertex2i(700, 500);
	glVertex2i(700, 100);
	glVertex2i(100, 100);
	glVertex2i(100, 500);
	glEnd();

	for (int i = 0; i < 20; ++i)
	{
		glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
		if (glrect[i].stat)
		{
			glBegin(GL_POINTS);
			for (int n = 0; n < 360; n+=10)
			{
				int X = cos(n * DEG2RAD) * glrect[i].r;
				int Y = sin(n * DEG2RAD) * glrect[i].r;
				glVertex2i(glrect[i].x + X, glrect[i].y + Y);
			}
			glEnd();
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
		if ((x > 100 && x < 700) && (y>100 && y < 500))
		{
			glrect[count].x = x;
			glrect[count].y = 600 - y;
			glrect[count].r = 10;
			glrect[count].count = 0;
			glrect[count].direction = rand() % 8;
			glrect[count].stat = true;
			glrect[count].expand = true;
			count++;
			count = count % 20;
			glutPostRedisplay();
		}
	}
}

void TimerFunction(int value)
{
	for (int i = 0; i < 20; ++i)
	{
		if (glrect[i].stat)
		{
			if (glrect[i].expand)
			{
				glrect[i].r++;
				glrect[i].count++;
				if (glrect[i].count == 5)
				{
					glrect[i].expand = false;
				}
			}
			else
			{
				glrect[i].r--;
				glrect[i].count--;
				if (glrect[i].count == 0)
				{
					glrect[i].expand = true;
				}
			}

			if (glrect[i].direction == 0) // 위
			{
				glrect[i].y += SPEED;
				if (glrect[i].y + SPEED > 500)
				{
					glrect[i].stat = false;
				}
			}
			else if (glrect[i].direction == 1) // 오른쪽 위
			{
				glrect[i].x += SPEED;
				glrect[i].y += SPEED;
				if (glrect[i].x + SPEED > 700)
				{
					glrect[i].stat = false;
				}
				if (glrect[i].y + SPEED > 500)
				{
					glrect[i].stat = false;
				}
			}
			else if (glrect[i].direction == 2) // 오른쪽
			{
				glrect[i].x += SPEED;
				if (glrect[i].x + SPEED > 700)
				{
					glrect[i].stat = false;
				}
			}
			else if (glrect[i].direction == 3) // 오른쪽 아래
			{
				glrect[i].x += SPEED;
				glrect[i].y -= SPEED;
				if (glrect[i].x + SPEED > 700)
				{
					glrect[i].stat = false;
				}
				if (glrect[i].y - SPEED < 100)
				{
					glrect[i].stat = false;
				}
			}
			else if (glrect[i].direction == 4) // 아래
			{
				glrect[i].y -= SPEED;
				if (glrect[i].y - SPEED < 100)
				{
					glrect[i].stat = false;
				}
			}
			else if (glrect[i].direction == 5) // 왼쪽 아래
			{
				glrect[i].x -= SPEED;
				glrect[i].y -= SPEED;
				if (glrect[i].x - SPEED < 100)
				{
					glrect[i].stat = false;
				}
				if (glrect[i].y - SPEED < 100)
				{
					glrect[i].stat = false;
				}
			}
			else if (glrect[i].direction == 6) // 왼쪽
			{
				glrect[i].x -= SPEED;
				if (glrect[i].x - SPEED < 100)
				{
					glrect[i].stat = false;
				}
			}
			else if (glrect[i].direction == 7) // 왼쪽 위
			{
				glrect[i].x -= SPEED;
				glrect[i].y += SPEED;
				if (glrect[i].x - SPEED < 100)
				{
					glrect[i].stat = false;
				}
				if (glrect[i].y + SPEED > 500)
				{
					glrect[i].stat = false;
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(80, TimerFunction, 1);
}