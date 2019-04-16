#include <gl/glut.h>
#include <math.h>
#include <stdio.h>

#define POINT_MAX 32
#define WIDTH 800
#define HEIGHT 800

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("½Ç½À 25");
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}




GLfloat point[POINT_MAX][3];
int num;

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLineWidth(2.f);
	for (int i = 0; i <= num / 4; i++) 
	{
		if (i == num / 4) 
		{
			if (num % 4 != 1) 
			{
				glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, num % 4, &point[i * 4][0]);
				glEnable(GL_MAP1_VERTEX_3);
				glColor3f(1.f, 1.f, 1.f);
				glBegin(GL_LINE_STRIP);
				for (int p = 0; p <= 30; p++)
					glEvalCoord1f((GLfloat)p / 30);
				glEnd();
			}
		}
		else 
		{
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &point[i * 4][0]);
			glEnable(GL_MAP1_VERTEX_3);
			glColor3f(1, 0, 0);
			glBegin(GL_LINE_STRIP);
			for (int p = 0; p <= 30; p++)
				glEvalCoord1f((GLfloat)p / 30);
			glEnd();
		}
	}
	printf("%d\n", num);
	glPointSize(8.f);
	glBegin(GL_POINTS);
	for (int i = 0; i < num; i++)
	{
		if (i % 4)
			glColor3f(1, 1, 1);
		else
			glColor3f(0, 0, 1);
		glVertex3fv(&point[i][0]);
	}
	glEnd();

	glDisable(GL_MAP1_VERTEX_3);

	glPopMatrix();



	glMatrixMode(GL_PROJECTION);
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0., w, 0., h, -400, 400);
	glMatrixMode(GL_MODELVIEW);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		if (num == POINT_MAX)
			num = 0;
		if (num % 4 == 0 && num >= 4) {
			point[num][0] = point[num - 1][0];
			point[num][1] = point[num - 1][1];
			++num;
		}
		point[num][0] = x;
		point[num][1] = HEIGHT - y;
		++num;
	}
	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'r' || key == 'R')
	{
		num = 0;
	}
	glutPostRedisplay();
}