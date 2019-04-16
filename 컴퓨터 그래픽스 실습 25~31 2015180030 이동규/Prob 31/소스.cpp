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
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);

int MainWindow;
float Angle_Y, Light_Angle, Angle_X;
float Sphere_Angle, Small_Sphere_Angle;
float Move_Z;
bool Light = true, Vector = false;
float Snow[SNOW_NUM][4];

GLfloat AmbienLight[] = { 1.0f, 1.0f, 1.5f, 1.0f };
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos[] = { 0.0f, 100.0f, 0.0f, 1.0f };

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

	if (Vector)
	{
		glEnable(GL_NORMALIZE);
	}
	else
		glDisable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0.f, 0.f, -300.f);
	glRotatef(Angle_X, 1.f, 0.f, 0.f);
	glRotatef(Angle_Y, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, 300.f);

	if (Light)
	{
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbienLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glEnable(GL_LIGHT0);
	}
	else
		glDisable(GL_LIGHT0);

	glPushMatrix();
	glTranslatef(0.f, 0.f, -300.f);
	glTranslatef(lightPos[X], lightPos[Y], lightPos[Z]);
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

	glPushMatrix(); // ¹Ù´Ú
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(0.f, -300.f, -300.f);
	glScalef(120.f, 1.f, 120.f);
	glutSolidCube(5);
	glEnd();

	glPopMatrix();

	glPushMatrix(); // ----------------------------------------
	glTranslatef(-200.f, -220.0f, -300.0f);

	glPushMatrix();
	glTranslatef(0.f, -80.f, 0.f);

	glColor3f(1.f, 0.5f, 0.0f);
	glBegin(GL_TRIANGLES);
	glNormal3f(-50.f, 150.f, 0.f);
	glVertex3f(-50.f, 0.f, -50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glVertex3f(50.f, 0.f, -50.f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(50.f, 150.f, 0.f);
	glVertex3f(50.f, 0.f, -50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glVertex3f(50.f, 0.f, 50.f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(-50.f, 150.f, 0.f);
	glVertex3f(-50.f, 0.f, 50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glVertex3f(50.f, 0.f, 50.f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(50.f, 150.f, 0.f);
	glVertex3f(-50.f, 0.f, -50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glVertex3f(-50.f, 0.f, 50.f);
	glEnd();

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

	glBegin(GL_TRIANGLES);
	glNormal3f(-50.f, 150.f, 0.f);
	glVertex3f(-50.f, 0.f, -50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glVertex3f(50.f, 0.f, -50.f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(50.f, 150.f, 0.f);
	glVertex3f(50.f, 0.f, -50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glVertex3f(50.f, 0.f, 50.f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(-50.f, 150.f, 0.f);
	glVertex3f(-50.f, 0.f, 50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glVertex3f(50.f, 0.f, 50.f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(50.f, 150.f, 0.f);
	glVertex3f(-50.f, 0.f, -50.f);
	glVertex3f(0.f, 150.f, 0.f);
	glVertex3f(-50.f, 0.f, 50.f);
	glEnd();

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

	lightPos[X] = cosf(Light_Angle * PI) * 500.f;
	lightPos[Z] = sinf(Light_Angle * PI) * 500.f;

	Light_Angle += 3.f;

	for (int i = 0; i < SNOW_NUM; ++i)
	{
		Snow[i][Y] -= Snow[i][SPEED];
		if (Snow[i][Y] < -300.f)
			Snow[i][Y] = (float)(rand() % 101 + 200);
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
	else if (key == 'r')
	{
		if (Light)
			Light = false;
		else
			Light = true;
	}
	else if (key == 'e')
	{
		if (Vector)
			Vector = false;
		else
			Vector = true;
	}
	else if (key == 'a')
	{
		Angle_Y += 5.f;
	}
	else if (key == 'd')
	{
		Angle_Y -= 5.f;
	}
	else if (key == 'w')
	{
		Angle_X -= 5.f;
	}
	else if (key == 's')
	{
		Angle_X += 5.f;
	}
}