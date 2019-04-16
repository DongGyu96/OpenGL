#include <gl/glut.h>
#include <math.h>
#include <Windows.h>
#include <stdio.h>
#define SIZE 0.8f
#define SMALL_SIZE 0.08f
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);

int MainWindow;
float Move_x[2] = { 0.0f, 0.0f };
float Move_y[2] = { 0.0f, 0.0f };
float angle = 0.0f;
int Move_type[2] = { 0,0 };
float turn = 0.f;
float X, Y, Z = 0.f;

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	MainWindow = glutCreateWindow("Computer Graphics OpenGL");
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(KeyBoard);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}


GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(-1.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();//for(int y  =  {
		if (X == 1.f || Y == 1.f || Z == 1.f)
		{
			glRotatef(turn, X, Y, Z);
			turn++;
			if (turn > 360) turn = 0.f;
		}
		glBegin(GL_LINE_STRIP);
			glVertex3f(0.0f, SIZE, 0.0f);
			glVertex3f(SIZE * -1.f, SIZE * -1.f, 0.0f);
			glVertex3f(SIZE, SIZE * -1.f,0.f);
			glVertex3f(0.0f, SIZE, 0.0f);
		glEnd();

		glBegin(GL_LINE_STRIP);
			glVertex3f(0.0f, SIZE, 0.0f);
			glVertex3f(0.0f, SIZE * -1.f, SIZE * -1.f);
			glVertex3f(0.0f, SIZE * -1.f, SIZE);
			glVertex3f(0.0f, SIZE, 0.0f);
		glEnd();

		glPushMatrix();
			glTranslatef(0.0f + Move_x[0], SIZE + Move_y[0], 0.0f);
			glBegin(GL_LINE_STRIP);
				glVertex3f(0.0f, SMALL_SIZE, 0.0f);
				glVertex3f(SMALL_SIZE * -1.f, SMALL_SIZE * -1.f, 0.0f);
				glVertex3f(SMALL_SIZE, SMALL_SIZE * -1.f, 0.f);
				glVertex3f(0.0f, SMALL_SIZE, 0.0f);
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, SIZE + Move_y[1], 0.0f + Move_x[1]);
			glBegin(GL_LINE_STRIP);
				glVertex3f(0.0f, SMALL_SIZE, 0.0f);
				glVertex3f(0.0f, SMALL_SIZE * -1.f, SMALL_SIZE * -1.f);
				glVertex3f(0.0f, SMALL_SIZE * -1.f, SMALL_SIZE);
				glVertex3f(0.0f, SMALL_SIZE, 0.0f);
			glEnd();
		glPopMatrix();
	glPopMatrix(); //for}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(60.0f, w / h, 1.0, 1000.0);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunction(int value)
{
	if (Move_type[0] == 0)
	{
		Move_x[0] += 0.0036f;
		Move_y[0] -= 0.0072f;
		if (Move_x[0] > SIZE)
		{
			Move_x[0] = SIZE;
			Move_y[0] = -2.f * SIZE;
			Move_type[0] = 1;
		}
	}
	else if (Move_type[0] == 1)
	{
		Move_x[0] -= 0.0036f;
		if (Move_x[0] < SIZE * -1.f)
		{
			Move_x[0] = SIZE * -1.f;
			Move_y[0] = -2.f * SIZE;
			Move_type[0] = 2;
		}
	}
	else if (Move_type[0] == 2)
	{
		Move_x[0] += 0.0036f;
		Move_y[0] += 0.0072f;
		if (Move_x[0] > 0.0f)
		{
			Move_x[0] = 0.0f;
			Move_y[0] = 0.0f;
			Move_type[0] = 0;
		}
	}

	if (Move_type[1] == 0)
	{
		Move_x[1] += 0.0036f;
		Move_y[1] -= 0.0072f;
		if (Move_x[1] > SIZE)
		{
			Move_x[1] = SIZE;
			Move_y[1] = -2.f * SIZE;
			Move_type[1] = 1;
		}
	}
	else if (Move_type[1] == 1)
	{
		Move_x[1] -= 0.0036f;
		if (Move_x[1] < SIZE * -1.f)
		{
			Move_x[1] = SIZE * -1.f;
			Move_y[1] = -2.f * SIZE;
			Move_type[1] = 2;
		}
	}
	else if (Move_type[1] == 2)
	{
		Move_x[1] += 0.0036f;
		Move_y[1] += 0.0072f;
		if (Move_x[1] > 0.0f)
		{
			Move_x[1] = 0.0f;
			Move_y[1] = 0.0f;
			Move_type[1] = 0;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'x' || key == 'X')
	{
		if (X != 1.f) X = 1.f;
		else X = 0.f;
		turn = 0.f;
	}
	else if (key == 'y' || key == 'Y')
	{
		if (Y != 1.f) Y = 1.f;
		else Y = 0.f;
		turn = 0.f;
	}
	else if (key == 'z' || key == 'Z')
	{
		if (Z != 1.f) Z = 1.f;
		else Z = 0.f;
		turn = 0.f;
	}
}
