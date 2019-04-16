#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Rect {
	int x, y;
	int direction;
	BOOL stat, Start;
};
Rect Clonrect[10];
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
	glutTimerFunc(1000, TimerFunction, 1);
	glutTimerFunc(40, TimerFunction, 2);
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
		for (int i = 0; i < 10; ++i)
		{
			Clonrect[i].x = glrect[i].x;
			Clonrect[i].y = glrect[i].y;
			glrect[i].Start = true;
			glrect[i].direction = 1;
		}
		glutPostRedisplay();
	}
}

void TimerFunction(int value)
{
	if (value == 1)
	{
		glrect[count].x = rand() % 65 * 10;
		glrect[count].y = 600 - (rand() % 45 * 10);
		glrect[count].stat = true;
		glrect[count].Start = false;
		count++;
		if(count != 10)
			glutTimerFunc(1000, TimerFunction, 1);
		glutPostRedisplay();
	}


	if (value == 2)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (glrect[i].Start)
			{
				if (glrect[i].direction == 1)
				{
					if (glrect[i].x + 10 == Clonrect[i].x)
						glrect[i].Start = false;
					else if (glrect[i].x + 10 >= 800)
						glrect[i].direction = 2;
					else
						glrect[i].x += 10;
				}
				else if (glrect[i].direction == 2)
				{
					if (glrect[i].y - 10 <= 0)
						glrect[i].direction = 3;
					else
						glrect[i].y -= 10;
				}
				else if (glrect[i].direction == 3)
				{
					if (glrect[i].x - 10 <= 0)
						glrect[i].direction = 4;
					else
						glrect[i].x -= 10;
				}
				else if (glrect[i].direction == 4)
				{
					if (glrect[i].y + 10 == Clonrect[i].y)
						glrect[i].direction = 1;
					else
						glrect[i].y += 10;
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(40, TimerFunction, 2);
	}
}