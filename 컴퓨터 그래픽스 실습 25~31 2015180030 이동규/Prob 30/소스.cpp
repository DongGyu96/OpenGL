#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.141592f / 180.0f
#define SNOW_NUM 400
#define X 0
#define Y 1
#define Z 2
#define SPEED 3
#define START_MOVE_Z 0
#define TURN_BY_Y 1
#define END_MOVE_Z 2
#define NONE -1
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);

int MainWindow;
float Angle_Y;
float Sphere_Angle, Small_Sphere_Angle;
float Move_Z;
int Animation = START_MOVE_Z;
bool Right_Front_Light = true;
bool Right_Back_Light = true;
bool Left_Front_Light = true;
bool Left_Back_Light = true;
float Snow[SNOW_NUM][4];

GLfloat right_front_AmbienLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat right_front_DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat right_front_SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat right_front_lightPos[] = { 300.0f, -300.0f, 0.0f, 1.0f };
GLfloat left_front_DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat left_front_SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat left_front_lightPos[] = { -300.0f, -300.0f, 0.0f, 1.0f };
GLfloat left_front_AmbienLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };

GLfloat right_back_AmbienLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat right_back_DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat right_back_SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat right_back_lightPos[] = { 300.0f, -300.0f, -600.0f, 1.0f };
GLfloat left_back_DiffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat left_back_SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat left_back_lightPos[] = { -300.0f, -300.0f, -600.0f, 1.0f };
GLfloat left_back_AmbienLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };

void main()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < SNOW_NUM; ++i)
	{
		Snow[i][X] = (float)(rand() % 601 - 300);
		Snow[i][Y] = (float)(rand() % 401 - 100);
		Snow[i][Z] = (float)(rand() % 601 - 300);
		Snow[i][SPEED] = (float)(rand() % 4 + 2);
	}
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0.f, 0.f, Move_Z - 100);
	glTranslatef(0.f, 0.f, -300.f);
	glRotatef(Angle_Y, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, 300.f);

	if (Right_Front_Light)
	{
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, right_front_AmbienLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, right_front_DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, right_front_SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, right_front_lightPos);
		glEnable(GL_LIGHT0);
	}
	else
		glDisable(GL_LIGHT0);

	if (Left_Front_Light)
	{
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT1, GL_AMBIENT, left_front_AmbienLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, left_front_DiffuseLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, left_front_SpecularLight);
		glLightfv(GL_LIGHT1, GL_POSITION, left_front_lightPos);
		glEnable(GL_LIGHT1);
	}
	else
		glDisable(GL_LIGHT1);

	if (Right_Back_Light)
	{
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT2, GL_AMBIENT, right_back_AmbienLight);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, right_back_DiffuseLight);
		glLightfv(GL_LIGHT2, GL_SPECULAR, right_back_SpecularLight);
		glLightfv(GL_LIGHT2, GL_POSITION, right_back_lightPos);
		glEnable(GL_LIGHT2);
	}
	else
		glDisable(GL_LIGHT2);

	if (Left_Back_Light)
	{
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT3, GL_AMBIENT, left_back_AmbienLight);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, left_back_DiffuseLight);
		glLightfv(GL_LIGHT3, GL_SPECULAR, left_back_SpecularLight);
		glLightfv(GL_LIGHT3, GL_POSITION, left_back_lightPos);
		glEnable(GL_LIGHT3);
	}
	else
		glDisable(GL_LIGHT3);

	glPushMatrix();
	glTranslatef(right_front_lightPos[X], right_front_lightPos[Y], right_front_lightPos[Z]);
	glutWireSphere(10, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(left_front_lightPos[X], left_front_lightPos[Y], left_front_lightPos[Z]);
	glutWireSphere(10, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(right_back_lightPos[X], right_back_lightPos[Y], right_back_lightPos[Z]);
	glutWireSphere(10, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(left_back_lightPos[X], left_back_lightPos[Y], left_back_lightPos[Z]);
	glutWireSphere(10, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, -300.f);
	for (int i = 0; i < SNOW_NUM; ++i)
	{
		glPushMatrix();
		glTranslatef(Snow[i][X], Snow[i][Y], Snow[i][Z]);
		glutSolidSphere(3, 10, 10);
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON); // ¹Ù´Ú
	glVertex3f(-300.0f, -300.0f, 0.0f);
	glVertex3f(-300.0f, -300.0f, -600.0f);
	glVertex3f(300.0f, -300.0f, -600.0f);
	glVertex3f(300.0f, -300.0f, 0.0f);
	glEnd();

	glPopMatrix();

	glPushMatrix(); // ----------------------------------------
	glTranslatef(-200.f, -220.0f, -300.0f);

	glPushMatrix();
	glTranslatef(0.f, -80.f, 0.f);

	glColor3f(1.f, 0.5f, 0.0f);
	glPushMatrix();
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glRotatef(-45.f, 0.f, 0.f, 1.f);
	glutSolidCone(80, 150, 4, 4);
	glPopMatrix();
	/*glBegin(GL_POLYGON);
	glVertex3f(-50.f, 0.f, -50.f);
	glVertex3f(50.f, 0.f, -50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(50.f, 0.f, -50.f);
	glVertex3f(50.f, 0.f, 50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-50.f, 0.f, 50.f);
	glVertex3f(50.f, 0.f, 50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-50.f, 0.f, -50.f);
	glVertex3f(-50.f, 0.f, 50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glEnd();*/

	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(cosf(Sphere_Angle * PI) * 80.f, 150.f, sinf(Sphere_Angle * PI) * 80.f);
	glutSolidSphere(20, 20, 20);

	glPushMatrix();
	glColor3f(1.f, 0.5f, 0.5f);
	glTranslatef(cosf(Small_Sphere_Angle * PI) * 40.f, 0.f, sinf(Small_Sphere_Angle * PI) * 40.f);
	glutSolidSphere(10, 20, 20);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix(); // -----------------------------------------

	glPushMatrix(); // ----------------------------------------
	glTranslatef(200.f, -220.0f, -300.0f);

	glPushMatrix();
	glTranslatef(0.f, -80.f, 0.f);

	glColor3f(1.f, 0.5f, 0.0f);
	glPushMatrix();
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glRotatef(-45.f, 0.f, 0.f, 1.f);
	glutSolidCone(80, 150, 4, 4);
	glPopMatrix();
	/*glBegin(GL_POLYGON);
	glVertex3f(-50.f, 0.f, -50.f);
	glVertex3f(50.f, 0.f, -50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(50.f, 0.f, -50.f);
	glVertex3f(50.f, 0.f, 50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-50.f, 0.f, 50.f);
	glVertex3f(50.f, 0.f, 50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-50.f, 0.f, -50.f);
	glVertex3f(-50.f, 0.f, 50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glEnd();*/

	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(cosf(Sphere_Angle * PI) * 80.f, 150.f, sinf(Sphere_Angle * PI) * 80.f);
	glutSolidSphere(20, 20, 20);

	glPushMatrix();
	glColor3f(1.f, 0.5f, 0.5f);
	glTranslatef(cosf(Small_Sphere_Angle * PI) * 40.f, 0.f, sinf(Small_Sphere_Angle * PI) * 40.f);
	glutSolidSphere(10, 20, 20);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix(); // -----------------------------------------


	glPopMatrix();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, w / h, 1.0, 5000.0);
	glTranslatef(0.0, 0.0, -500.0);
	gluLookAt(0.0f, 0.0, 100.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunction(int value)
{
	Sphere_Angle += 5.f;
	Small_Sphere_Angle += 10.f;

	for (int i = 0; i < SNOW_NUM; ++i)
	{
		Snow[i][Y] -= Snow[i][SPEED];
		if(Snow[i][Y] < -300.f)
			Snow[i][Y] = (float)(rand() % 101 + 200);
	}

	if (Animation == START_MOVE_Z)
	{
		Move_Z += 3.f;
		if (Move_Z >= 100.f)
		{
			Move_Z = 100.f;
			Animation = TURN_BY_Y;
		}
	}
	else if (Animation == TURN_BY_Y)
	{
		Angle_Y += 5.f;
		if (Angle_Y > 1440.f)
		{
			Angle_Y = 0.f;
			Animation = END_MOVE_Z;
		}
	}
	else if (Animation == END_MOVE_Z)
	{
		Move_Z -= 3.f;
		if (Move_Z < 0.f)
		{
			Move_Z = 0.f;
			Animation = NONE;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') // Á¾·á
	{
		glutDestroyWindow(MainWindow);
		exit(0);
	}
	else if (key == 49)
	{
		if (Right_Front_Light)
			Right_Front_Light = false;
		else
			Right_Front_Light = true;
	}
	else if (key == 50)
	{
		if (Left_Front_Light)
			Left_Front_Light = false;
		else
			Left_Front_Light = true;
	}
	else if (key == 51)
	{
		if (Right_Back_Light)
			Right_Back_Light = false;
		else
			Right_Back_Light = true;
	}
	else if (key == 52)
	{
		if (Left_Back_Light)
			Left_Back_Light = false;
		else	 
			Left_Back_Light = true;
	}
}