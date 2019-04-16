#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SPHERE 0
#define CUBE 1
#define CONE 2
#define TEAPOT 3
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);

int random = rand() % 3;
int MainWindow;
int Shape_Type = SPHERE;
bool Y_Turn = false;
bool X_Turn = false;
bool Z_Turn = false;
bool LEFT = false;
bool RIGHT = false;
bool Y_Turn_l = false;
bool X_Turn_l = false;
bool Z_Turn_l = false;
float turn = 0.0f;
float turn_l = 0.0f;

void main()
{
	srand((unsigned)time(NULL));
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

	glPushMatrix();
	if (Y_Turn_l)
		glRotatef(turn_l, 0.0f, 1.0f, 0.0f);
	else if (X_Turn_l)
		glRotatef(turn_l, 1.0f, 0.0f, 0.0f);
	else if (Z_Turn_l)
		glRotatef(turn_l, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON); // 바닥
	glVertex3f(-300.0f, -300.0f, 0.0f);
	glVertex3f(-300.0f, -300.0f, -600.0f);
	glVertex3f(300.0f, -300.0f, -600.0f);
	glVertex3f(300.0f, -300.0f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix(); // Y축
	glTranslatef(0.0f, 11.0f, -100.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glScalef(1.0f, 8.0f, 1.0f);
	glutSolidCube(3);
	glPopMatrix();
	glPushMatrix(); // Z축
	glTranslatef(0.0f, 0.0f, -111.0f);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glScalef(1.0f, 1.0f, 8.0f);
	glutSolidCube(3);
	glPopMatrix();
	glPushMatrix(); // X축
	glTranslatef(11.0f, 0.0f, -100.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glScalef(8.0f, 1.0f, 1.0f);
	glutSolidCube(3);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0f, -260.0f, -300.0f);
	glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(-150.0f, 0.0f, 0.0f);
	if (Y_Turn)
		glRotatef(turn, 0.0f, 1.0f, 0.0f);
	else if (X_Turn)
		glRotatef(turn, 1.0f, 0.0f, 0.0f);
	else if (Z_Turn)
		glRotatef(turn, 0.0f, 0.0f, 1.0f);
	if (LEFT)
	{
		if (random == 0)
			glRotatef(turn, 1.0f, 0.0f, 0.0f);
		else if (random == 1)
			glRotatef(turn, 0.0f, 1.0f, 0.0f);
		else if (random == 2)
			glRotatef(turn, 0.0f, 0.0f, 1.0f);
	}
	if (Shape_Type == SPHERE)
	{
		glutSolidSphere(40.0, 15, 15);
	}
	else if (Shape_Type == CUBE)
	{
		glutSolidCube(80.0);
	}
	else if (Shape_Type == CONE)
	{
		glTranslatef(0.0f, -40.0f, 0.0f);
		glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(30.0, 60.0f, 15, 15);
	}
	else if (Shape_Type == TEAPOT)
	{
		glutSolidTeapot(50.0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(150.0f, 0.0f, 0.0f);
	if (Y_Turn)
		glRotatef(turn, 0.0f, 1.0f, 0.0f);
	else if (X_Turn)
		glRotatef(turn, 1.0f, 0.0f, 0.0f);
	else if (Z_Turn)
		glRotatef(turn, 0.0f, 0.0f, 1.0f);
	if (RIGHT)
	{
		if(random == 0)
			glRotatef(turn, 1.0f, 0.0f, 0.0f);
		else if(random == 1)
			glRotatef(turn, 0.0f, 1.0f, 0.0f);
		else if(random == 2)
			glRotatef(turn, 0.0f, 0.0f, 1.0f);
	}
	if (Shape_Type == SPHERE)
	{
		glutWireSphere(40.0, 15, 15);
	}
	else if (Shape_Type == CUBE)
	{
		glutWireCube(80.0);
	}
	else if (Shape_Type == CONE)
	{
		glTranslatef(0.0f, -40.0f, 0.0f);
		glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
		glutWireCone(30.0, 60.0f, 15, 15);
	}
	else if (Shape_Type == TEAPOT)
	{
		glutWireTeapot(50.0);
	}
	glPopMatrix();
	glPopMatrix();
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
	gluLookAt(0.0f, 0.0, 100.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
}

void TimerFunction(int value)
{
	turn += 10.0f;
	turn_l += 10.0f;
	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') // 종료
	{
		glutDestroyWindow(MainWindow);
		exit(0);
	}
	else if (key == 'y' || key == 'Y') // 카메라 회전
	{
		if (Y_Turn) Y_Turn = false;
		else Y_Turn = true;
		X_Turn = Z_Turn = LEFT = RIGHT = false;
	}
	else if (key == 'x' || key == 'X') // 카메라 회전
	{
		if (X_Turn) X_Turn = false;
		else X_Turn = true;
		Y_Turn = Z_Turn = LEFT = RIGHT = false;
	}
	else if (key == 'z' || key == 'Z') // 카메라 회전
	{
		if (Z_Turn) Z_Turn = false;
		else Z_Turn = true;
		X_Turn = Y_Turn = LEFT = RIGHT = false;
	}
	else if (key == 'i' || key == 'I') // 초기화
	{
		glLoadIdentity();
		gluLookAt(0.0f, 0.0, 100.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
	}
	else if (key == 49)
	{
		Shape_Type = SPHERE;
	}
	else if (key == 50)
	{
		Shape_Type = CUBE;
	}
	else if (key == 51)
	{
		Shape_Type = CONE;
	}
	else if (key == 52)
	{
		Shape_Type = TEAPOT;
	}
	else if (key == 'j' || key == 'J') // 카메라 회전
	{
		if (Y_Turn_l) Y_Turn_l = false;
		else Y_Turn_l = true;
		X_Turn_l = Z_Turn_l = false;
	}
	else if (key == 'h' || key == 'H') // 카메라 회전
	{
		if (X_Turn_l) X_Turn_l = false;
		else X_Turn_l = true;
		Y_Turn_l = Z_Turn_l = false;
	}
	else if (key == 'g' || key == 'G') // 카메라 회전
	{
		if (Z_Turn_l) Z_Turn_l = false;
		else Z_Turn_l = true;
		X_Turn_l = Y_Turn_l = false;
	}
	else if (key == 'l' || key == 'L')
	{
		random = rand() % 3;
		X_Turn = Y_Turn = Z_Turn = RIGHT = false;
		if (LEFT) LEFT = false;
		else LEFT = true;
	}
	else if (key == 'r' || key == 'R')
	{
		random = rand() % 3;
		X_Turn = Y_Turn = Z_Turn = LEFT = false;
		if (RIGHT) RIGHT = false;
		else RIGHT = true;
	}
}
