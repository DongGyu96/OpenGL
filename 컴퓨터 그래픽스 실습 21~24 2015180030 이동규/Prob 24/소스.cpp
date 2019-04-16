#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define UP_FRONT_LEFT 1
#define UP_FRONT_RIGHT 2
#define UP_BACK_LEFT 3
#define UP_BACK_RIGHT 4
#define DOWN_FRONT_LEFT 5
#define DOWN_FRONT_RIGHT 6
#define DOWN_BACK_LEFT 7
#define DOWN_BACK_RIGHT 8
#define NUM 5
#define SPEED 5
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

typedef struct Ball {
	int movetype;
	float Move_x, Move_y, Move_z;
	float x, y, z;
}Ball;

typedef struct Cube {
	float x, y, z;
	int size;
}Cube;

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
void Motion(int x, int y);
void Set_Balls();

Ball balls[NUM];
Cube cubes[3];
float cube_speed = 5;
int MainWindow;
float Angle_Y;
float Angle_Z;
int speed = 20;
int Z_type = 0;
int Angle = 0;
bool Depth = true;

void main()
{
	srand((unsigned)time(NULL));
	Set_Balls();

	cubes[0].x = 0.f;
	cubes[0].y = -200.f;
	cubes[0].z = -200.f;
	cubes[0].size = 200;
	cubes[1].x = 0.f;
	cubes[1].y = -225.f;
	cubes[1].z = -25.f;
	cubes[1].size = 150;
	cubes[2].x = 0.f;
	cubes[2].y = -250.f;
	cubes[2].z = 100.f;
	cubes[2].size = 100;

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

	if(Depth)
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
	glColor4f(1.0f, 1.0f, 0.2f, 1.f);
	glBegin(GL_QUADS);
	glVertex3f(300.f, 0.f, -300.f);
	glVertex3f(300.f, 0.f, 300.f);
	glVertex3f(-300.f, 0.f, 300.f);
	glVertex3f(-300.f, 0.f, -300.f);
	glEnd();
	glPopMatrix();

	glPushMatrix(); // µÞ¸é
	glTranslatef(0.f, 0.f, -300.f);
	glColor4f(1.0f, 0.2f, 0.2f, 1.f);
	glBegin(GL_QUADS);
	glVertex3f(300.f, 300.f, 0.f);
	glVertex3f(300.f, -300.f, 0.f);
	glVertex3f(-300.f, -300.f, 0.f);
	glVertex3f(-300.f, 300.f, 0.f);
	glEnd();
	glPopMatrix();

	glPushMatrix(); // À­¸é
	glTranslatef(0.f, 300.f, 00.f);
	glColor4f(0.2f, 1.0f, 1.0f, 1.f);
	glBegin(GL_QUADS);
	glVertex3f(300.f, 0.f, -300.f);
	glVertex3f(-300.f, 0.f, -300.f);
	glVertex3f(-300.f, 0.f, 300.f);
	glVertex3f(300.f, 0.f, 300.f);
	glEnd();
	glPopMatrix();

	glPushMatrix(); // ¿·¸é
	glTranslatef(-300.f, 0.f, 00.f);
	glColor4f(0.5f, 0.5f, 1.0f, 1.f);
	glBegin(GL_QUADS);
	glVertex3f(0.f, 300.f, -300.f);
	glVertex3f(0.f, -300.f, -300.f);
	glVertex3f(0.f, -300.f, 300.f);
	glVertex3f(0.f, 300.f, 300.f);
	glEnd();
	glPopMatrix();

	glPushMatrix(); // ¿·¸é
	glTranslatef(300.f, 0.f, 00.f);
	glColor4f(0.5f, 1.0f, 0.5f, 1.f);
	glBegin(GL_QUADS);
	glVertex3f(0.f, 300.f, -300.f);
	glVertex3f(0.f, 300.f, 300.f);
	glVertex3f(0.f, -300.f, 300.f);
	glVertex3f(0.f, -300.f, -300.f);
	glEnd();
	glPopMatrix();

	glPushMatrix(); // ¾Õ¸é
	glTranslatef(0.f, 0.f, 300.f);
	glColor4f(0.8f, 0.8f, 0.8f, 1.f);
	glBegin(GL_QUADS);
	glVertex3f(300.f, 300.f, 0.f);
	glVertex3f(-300.f, 300.f, 0.f);
	glVertex3f(-300.f, -300.f, 0.f);
	glVertex3f(300.f, -300.f, 0.f);
	glEnd();
	glPopMatrix();

	glDisable(GL_CULL_FACE);

	for (int i = 0; i < 3; ++i)
	{
		glPushMatrix();
		glColor4f(0.6f, 0.3f, 0.3f, 1.f);
		glTranslatef(cubes[i].x, cubes[i].y, cubes[i].z);
		glutSolidCube(cubes[i].size);
		glColor4f(0.f, 0.f, 0.f, 1.f);
		glutWireCube(cubes[i].size + 1);
		glPopMatrix();
	}
	printf("%d\n", Angle);





	if (Depth)
		glDisable(GL_DEPTH_TEST);

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
	Angle = (int)Angle_Z;
	for (int i = 0; i < NUM; ++i)
	{
		balls[i].x += balls[i].Move_x;
		balls[i].y += balls[i].Move_y;
		balls[i].z += balls[i].Move_z;

		if (balls[i].x + balls[i].Move_x > 300.f)
			balls[i].Move_x *= -1;
		else if (balls[i].x + balls[i].Move_x < -300.f)
			balls[i].Move_x *= -1;

		if (balls[i].y + balls[i].Move_y > 300.f)
			balls[i].Move_y *= -1;
		else if (balls[i].y + balls[i].Move_y < -300.f)
			balls[i].Move_y *= -1;

		if (balls[i].z + balls[i].Move_z > 300.f)
			balls[i].Move_z *= -1;
		else if (balls[i].z + balls[i].Move_z < -300.f)
			balls[i].Move_z *= -1;
	}

	cube_speed = (Angle % 90) / 5;
	if (Angle_Z > 0.f && Angle_Z < 90.f)
	{
		for (int i = 0; i < 3; ++i)
		{
			if(cubes[i].x - (cubes[i].size / 2) - cube_speed > -300.f)
				cubes[i].x -= cube_speed;

			if (cubes[i].y - (cubes[i].size / 2) - 10.f > -300.f)
				cubes[i].y -= 10.f;
		}
	}
	if (Angle_Z > 90.f && Angle_Z < 180.f)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (cubes[i].y + (cubes[i].size / 2) + cube_speed < 300.f)
				cubes[i].y += cube_speed;

			if (cubes[i].x - (cubes[i].size / 2) - 10.f > -300.f)
				cubes[i].x -= 10.f;
		}
	}
	if (Angle_Z > 180.f && Angle_Z < 270.f)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (cubes[i].x + (cubes[i].size / 2) + cube_speed < 300.f)
				cubes[i].x += cube_speed;

			if (cubes[i].y + (cubes[i].size / 2) + 10.f < 300.f)
				cubes[i].y += 10.f;
		}
	}
	if (Angle_Z > 270.f && Angle_Z < 360.f)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (cubes[i].y - (cubes[i].size / 2) - cube_speed > -300.f)
				cubes[i].y -= cube_speed;

			if (cubes[i].x + (cubes[i].size / 2) + 10.f < 300.f)
				cubes[i].x += 10.f;
		}
	}

	if (Z_type == 1)
		Angle_Z -= 2.5f;
	else if (Z_type == 2)
		Angle_Z += 2.5f;

	if (Angle_Z > 360.f)
		Angle_Z -= 360.f;
	else if (Angle_Z < 0.f)
		Angle_Z += 360.f;
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
	else if (key == 'x' || key == 'X')
	{
		Angle_Z += 10.f;
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
	else if (key == 'd' || key == 'D')
	{
		if (Depth)
			Depth = false;
		else
			Depth = true;
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
	/*if (x < 200)
	{
		Z_type = 2;
	}
	else if (x > 600)
	{
		Z_type = 1;
	}
	else
		Z_type = 0;*/
}