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
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	int width, height;
	int count = 0;
	int shape = rand() % 4;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	width = 800 / 3;
	height = 600 / 3;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (count % 2)
			{
				glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
				glRectf(width * j, height* i, width * j + width, height * i);

				glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
				if (shape == 0)
				{
					glBegin(GL_LINES);
						glVertex2i(20 + (width * j), 20 + (height * i));
						glVertex2i(200 + (width * j), 150 + (height * i));
					glEnd();
				}
				else if (shape == 1)
				{
					glBegin(GL_TRIANGLES);
						glVertex2i(20 + (width * j), 20 + (height * i));
						glVertex2i(100 + (width * j), 100 + (height * i));
						glVertex2i(180 + (width * j), 40 + (height * i));
					glEnd();
				}
				else if (shape == 2)
				{
					glBegin(GL_POLYGON);
						glVertex2i(20 + (width * j), 20 + (height * i));
						glVertex2i(200 + (width * j), 20 + (height * i));
						glVertex2i(200 + (width * j), 150 + (height * i));
						glVertex2i(20 + (width * j), 150 + (height * i));
					glEnd();
				}
				else if (shape == 3)
				{
					glBegin(GL_POLYGON);
						glVertex2i(80 + (width * j), 20 + (height * i));
						glVertex2i(180 + (width * j), 20 + (height * i));
						glVertex2i(220 + (width * j), 120 + (height * i));
						glVertex2i(110 + (width * j), 170 + (height * i));
						glVertex2i(20 + (width * j), 120 + (height * i));
					glEnd();
				}
			}
			else
			{
				glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
				glRectf(width * j, height* i, width * j + width, height * i + height);

				glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
				if (shape == 0)
				{
					glBegin(GL_LINES);
						glVertex2i(20 + (width * j), 20 + (height * i));
						glVertex2i(200 + (width * j), 150 + (height * i));
					glEnd();
				}
				else if (shape == 1)
				{
					glBegin(GL_TRIANGLES);
						glVertex2i(20 + (width * j), 20 + (height * i));
						glVertex2i(100 + (width * j), 100 + (height * i));
						glVertex2i(180 + (width * j), 40 + (height * i));
					glEnd();
				}
				else if (shape == 2)
				{
					glBegin(GL_POLYGON);
						glVertex2i(20 + (width * j), 20 + (height * i));
						glVertex2i(200 + (width * j), 20 + (height * i));
						glVertex2i(200 + (width * j), 150 + (height * i));
						glVertex2i(20 + (width * j), 150 + (height * i));
					glEnd();
				}
				else if (shape == 3)
				{
					glBegin(GL_POLYGON);
						glVertex2i(80 + (width * j), 20 + (height * i));
						glVertex2i(180 + (width * j), 20 + (height * i));
						glVertex2i(220 + (width * j), 120 + (height * i));
						glVertex2i(110 + (width * j), 170 + (height * i));
						glVertex2i(20 + (width * j), 120 + (height * i));
					glEnd();
				}
			}
			shape++;
			shape = shape % 4;
			count++;
		}
	}

	glFlush();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}