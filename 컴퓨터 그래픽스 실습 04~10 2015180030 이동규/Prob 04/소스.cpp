#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

typedef struct Rect {
	int x, y;
	BOOL direction, Color, stat;
}Rect;

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
	glutTimerFunc(200, TimerFunction, 2);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 10; ++i)
	{
		if(glrect[i].Color)
			glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
		else
			glColor4f(0.8f, 0.5f, 0.5f, 1.0f);

		if (glrect[i].stat)
		{
			if (glrect[i].direction)
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

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glrect[count].x = x;
		glrect[count].y = 600 - y;
		glrect[count].direction = true;
		glrect[count].Color = true;
		glrect[count].stat = true;
		count++;
		count = count % 10;
		glutPostRedisplay();
	}
}

void TimerFunction(int value)
{
	if (value == 1)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (glrect[i].Color)
				glrect[i].Color = false;
			else
				glrect[i].Color = true;
		}
		glutPostRedisplay();
		glutTimerFunc(100, TimerFunction, 1);
	}
	else if (value == 2)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (glrect[i].direction)
				glrect[i].direction = false;
			else
				glrect[i].direction = true;
		}
		glutPostRedisplay();
		glutTimerFunc(200, TimerFunction, 2);
	}
}