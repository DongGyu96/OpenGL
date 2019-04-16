#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 5
#define SPEED 5
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

typedef struct Ball {
	int movetype;
	float Move_x, Move_y, Move_z;
	float x, y, z;
}Ball;

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
void Motion(int x, int y);
void Set_Balls();

Ball balls[NUM];
int MainWindow;
float Angle_Y;
float Angle_Z;
int speed = 20;
int Z_type = 0;
float Color_R[6];
float Color_G[6];
float Color_B[6];

void main()
{
	for (int i = 0; i < 6; ++i)
	{
		Color_R[i] = 0.5f;
		Color_G[i] = 0.5f;
		Color_B[i] = 0.5f;
	}
	Color_R[0] = 1.f;

	Color_G[1] = 1.f;

	Color_B[2] = 1.f;

	Color_R[3] = 1.f;
	Color_G[3] = 1.f;

	Color_B[4] = 1.f;
	Color_R[4] = 1.f;

	Color_G[5] = 1.f;
	Color_B[5] = 1.f;

	srand((unsigned)time(NULL));
	Set_Balls();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	MainWindow = glutCreateWindow("Computer Graphics OpenGL");
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(KeyBoard);
	glutPassiveMotionFunc(Motion);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}


GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glTranslatef(0.f, -30.f, -500.f);
		glRotatef(Angle_Z, 0.f, 0.f, 1.f);
		glRotatef(Angle_Y, 0.f, 1.f, 0.f);
		glFrontFace(GL_CW);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		for (int i = 0; i < NUM; ++i)
		{
			glPushMatrix();
			glColor4f(0.f, 0.f, 0.f, 1.f);
			glTranslatef(balls[i].x, balls[i].y, balls[i].z);
			glutSolidSphere(10, 20, 20);
			glPopMatrix();
		}

		glPushMatrix(); // ¹Ø¸é
			glTranslatef(0.f, -300.f, 0.f);
			glColor4f(Color_R[0], Color_G[0], Color_B[0], 1.f);
			glBegin(GL_QUADS);
				glVertex3f(300.f, 0.f, -300.f);
				glVertex3f(300.f, 0.f, 300.f);
				glVertex3f(-300.f, 0.f, 300.f);
				glVertex3f(-300.f, 0.f, -300.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // µÞ¸é
			glTranslatef(0.f, 0.f, -300.f);
			glColor4f(Color_R[1], Color_G[1], Color_B[1], 1.f);
			glBegin(GL_QUADS);
				glVertex3f(300.f, 300.f, 0.f);
				glVertex3f(300.f, -300.f, 0.f);
				glVertex3f(-300.f, -300.f, 0.f);
				glVertex3f(-300.f, 300.f, 0.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // À­¸é
			glTranslatef(0.f, 300.f, 00.f);
			glColor4f(Color_R[2], Color_G[2], Color_B[2], 1.f);
			glBegin(GL_QUADS);
				glVertex3f(300.f, 0.f, -300.f);
				glVertex3f(-300.f, 0.f, -300.f);
				glVertex3f(-300.f, 0.f, 300.f);
				glVertex3f(300.f, 0.f, 300.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // ¿·¸é
			glTranslatef(-300.f, 0.f, 00.f);
			glColor4f(Color_R[3], Color_G[3], Color_B[3], 1.f);
			glBegin(GL_QUADS);
				glVertex3f(0.f, 300.f, -300.f);
				glVertex3f(0.f, -300.f, -300.f);
				glVertex3f(0.f, -300.f, 300.f);
				glVertex3f(0.f, 300.f, 300.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // ¿·¸é
			glTranslatef(300.f, 0.f, 00.f);
			glColor4f(Color_R[4], Color_G[4], Color_B[4], 1.f);
			glBegin(GL_QUADS);
				glVertex3f(0.f, 300.f, -300.f);
				glVertex3f(0.f, 300.f, 300.f);
				glVertex3f(0.f, -300.f, 300.f);
				glVertex3f(0.f, -300.f, -300.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // ¾Õ¸é
			glTranslatef(0.f, 0.f, 300.f);
			glColor4f(Color_R[5], Color_G[5], Color_B[5], 1.f);
			glBegin(GL_QUADS);
				glVertex3f(300.f, 300.f, 0.f);
				glVertex3f(-300.f, 300.f, 0.f);
				glVertex3f(-300.f, -300.f, 0.f);
				glVertex3f(300.f, -300.f, 0.f);
			glEnd();
		glPopMatrix();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

	glPopMatrix();

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1600.0);
	glTranslatef(0.0, 0.0, -400.0);

	//glOrtho(0.0, 800.0, 0.0, 800.0, 0.0, 800.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
}

void TimerFunction(int value)
{
	for (int i = 0; i < NUM; ++i)
	{
		balls[i].x += balls[i].Move_x;
		balls[i].y += balls[i].Move_y;
		balls[i].z += balls[i].Move_z;

		if (balls[i].x + balls[i].Move_x > 300.f)
		{
			balls[i].Move_x *= -1;
			Color_B[4] -= 0.1f;
			Color_R[4] -= 0.1f;
		}
		else if (balls[i].x + balls[i].Move_x < -300.f)
		{
			balls[i].Move_x *= -1;
			Color_R[3] -= 0.1f;
			Color_G[3] -= 0.1f;
			if (Color_R[3] < 0.f)
				Color_R[3] = Color_G[3] = 1.f;
		}

		if (balls[i].y + balls[i].Move_y > 300.f)
		{
			balls[i].Move_y *= -1;
			Color_B[2] -= 0.1f;
			if (Color_B[2] < 0.f)
				Color_B[2] = 1.f;
		}
		else if (balls[i].y + balls[i].Move_y < -300.f)
		{
			balls[i].Move_y *= -1;
			Color_R[0] -= 0.1f;
			if (Color_R[0] < 0.f)
				Color_R[0] = 1.f;
		}

		if (balls[i].z + balls[i].Move_z > 300.f)
		{
			balls[i].Move_z *= -1;
			Color_G[5] -= 0.1f;
			Color_B[5] -= 0.1f;
			if (Color_G[5] < 0.f)
				Color_G[5] = Color_B[5] = 1.f;
		}
		else if (balls[i].z + balls[i].Move_z < -300.f)
		{
			balls[i].Move_z *= -1;
			Color_G[1] -= 0.1f;
			if (Color_G[1] < 0.f)
				Color_G[1] = 1.f;
		}
	}

	if (Z_type == 1)
		Angle_Z -= 2.5f;
	else if (Z_type == 2)
		Angle_Z += 2.5f;
	glutPostRedisplay();
	glutTimerFunc(speed, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') // Á¾·á
	{
		glutDestroyWindow(MainWindow);
		exit(0);
	}
	else if (key == 'y' || key == 'Y')
	{
		Angle_Y += 5.f;
	}
	else if (key == 'z' || key == 'Z')
	{
		Angle_Z += 5.f;
	}
	else if (key == 'b' || key == 'B')
	{
		Set_Balls();
	}
	else if (key == 'i' || key == 'I')
	{
		Angle_Y = 0.f;
		Angle_Z = 0.f;
	}
}

void Set_Balls()
{
	for (int i = 0; i < NUM; ++i)
	{
		int type = 0;
		int count = 0;
		balls[i].movetype = rand() % 8 + 1;
		balls[i].x = rand() % 401 - 200;
		balls[i].y = rand() % 401 - 200;
		balls[i].z = rand() % 401 - 200;

		type = rand() % 3;
		count += type;
		if (type == 0)
			balls[i].Move_x = 0;
		else if (type == 1)
			balls[i].Move_x = -5;
		else if (type == 2)
			balls[i].Move_x = 5;

		type = rand() % 3;
		count += type;
		if (type == 0)
			balls[i].Move_y = 0;
		else if (type == 1)
			balls[i].Move_y = -5;
		else if (type == 2)
			balls[i].Move_y = 5;

		type = rand() % 3;
		count += type;
		if (type == 0)
			balls[i].Move_z = 0;
		else if (type == 1)
			balls[i].Move_z = -5;
		else if (type == 2)
			balls[i].Move_z = 5;

		if (count == 0)
		{
			balls[i].Move_z = 5;
			balls[i].Move_x = 5;
		}
	}
}

void Motion(int x, int y)
{
	if (x < 200)
	{
		Z_type = 2;
	}
	else if (x > 600)
	{
		Z_type = 1;
	}
	else
		Z_type = 0;
}