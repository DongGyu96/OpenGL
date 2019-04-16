#include <gl/glut.h>
#include <Windows.h>
#include <math.h>
#define PI 3.141592
#define DEG2RAD PI/180
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Rect {
	int x, y;
	int angle, R_angle;
	BOOL stat, reverse;
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
			for (int n = 0; n < glrect[i].angle; n = n + 10)
			{
				int X = cos(n * DEG2RAD) * (n / 10);
				int Y = sin(n * DEG2RAD) * (n / 10);
				glVertex2i(glrect[i].x + X, glrect[i].y + Y);
			}
			if (glrect[i].reverse)
			{
				for (int n = 540; n >= glrect[i].R_angle; n = n - 10)
				{
					int X = cos(n * DEG2RAD) * ((n + 180) / 10);
					int Y = sin(n * DEG2RAD) * ((n + 180) / 10);
					glVertex2i((glrect[i].x + 144) + X, glrect[i].y + Y);
				}
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
		glrect[count].angle = 0;
		glrect[count].R_angle = 0;
		glrect[count].reverse = false;
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
			if (!glrect[i].reverse)
			{
				glrect[i].angle += 10;
				if (glrect[i].angle == 720)
				{
					glrect[i].R_angle = 540;
					glrect[i].reverse = true;
				}
			}
			else
			{
				glrect[i].R_angle -= 10;
				if (glrect[i].R_angle == -180)
				{
					glrect[i].stat = 0;
					glrect[i].angle = 0;
					glrect[i].R_angle = 0;
					glrect[i].reverse = false;
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}