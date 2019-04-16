#include <gl/glut.h>
#include <Windows.h>
#include <math.h>
#define PI 3.141592
#define DEG2RAD PI/180
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Rect {
	int x, y;
	int r;
	BOOL stat;
};

Rect glrect[20];
int count = 0;

void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);

void main()
{
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
	for (int i = 0; i < 20; ++i)
	{
		if (glrect[i].stat)
		{
			glBegin(GL_POINTS);
			for (int n = 0; n < 360; n = n + 10)
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
		glrect[count].x = x;
		glrect[count].y = 600 - y;
		glrect[count].stat = true;
		glrect[count].r = 0;
		count++;
		count = count % 20;
		glutPostRedisplay();
	}
}

void TimerFunction(int value)
{
	for (int i = 0; i < 20; ++i)
	{
		if (glrect[i].stat)
		{
			glrect[i].r += 5;
			if (glrect[i].r >= 600)
			{
				glrect[i].stat = false;
				glrect[i].r = 0;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}