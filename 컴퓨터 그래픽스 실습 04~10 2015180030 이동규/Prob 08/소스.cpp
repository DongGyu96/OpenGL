#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#define SPEED 5
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

typedef struct Rect {
	int x, y, distX, distY, count;
	BOOL stat;
}Rect;

Rect goalrect;
Rect glrect[10];
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
	for (int i = 0; i < 10; ++i)
	{
		glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
		if (glrect[i].stat)
		{
			glBegin(GL_POLYGON);
			glVertex2i(glrect[i].x - 10, glrect[i].y - 10);
			glVertex2i(glrect[i].x - 10, glrect[i].y + 10);
			glVertex2i(glrect[i].x + 10, glrect[i].y + 10);
			glVertex2i(glrect[i].x + 10, glrect[i].y - 10);
			glEnd();
		}
	}
	glColor4f(0.8f, 0.5f, 0.8f, 1.0f);
	if (goalrect.stat)
	{
		glBegin(GL_POLYGON);
		glVertex2i(goalrect.x - 10, goalrect.y - 10);
		glVertex2i(goalrect.x + 10, goalrect.y - 10);
		glVertex2i(goalrect.x, goalrect.y + 10);
		glEnd();
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
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glrect[count].x = x;
		glrect[count].y = 600 - y;
		glrect[count].stat = true;
		glrect[count].count = 0;
		count++;
		count = count % 10;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		goalrect.x = x;
		goalrect.y = 600 - y;
		goalrect.stat = true;
		for (int i = 0; i < 10; ++i)
		{
			glrect[i].count = 0;
			glrect[i].distX = goalrect.x - glrect[i].x;
			glrect[i].distX = glrect[i].distX / 20;
			glrect[i].distY = goalrect.y - glrect[i].y;
			glrect[i].distY = glrect[i].distY / 20;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		goalrect.stat = false;
	}
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (goalrect.stat)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (glrect[i].stat)
			{
				if (glrect[i].count < 20)
				{
					glrect[i].x += glrect[i].distX;
					glrect[i].y += glrect[i].distY;
					glrect[i].count++;
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}