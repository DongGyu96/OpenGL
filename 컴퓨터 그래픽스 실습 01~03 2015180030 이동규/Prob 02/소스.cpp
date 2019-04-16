#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main()
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	int num = rand() % 6 + 3;
	int width;
	width = 800 / num;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num; ++j)
		{
			if (i%2)
			{
				if (j % 2)
				{
					glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
					glRectf(width * j, width * i, width * j + width, width * i + width);
				}
				else
				{
					glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
					glRectf(width * j, width * i, width * j + width, width * i + width);
				}
			}
			else
			{
				if (j % 2)
				{
					glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
					glRectf(width * j, width * i, width * j + width, width * i + width);
				}
				else
				{
					glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
					glRectf(width * j, width * i, width * j + width, width * i + width);
				}
			}
		}
	}

	glFlush();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 800.0, -1.0, 1.0);
}