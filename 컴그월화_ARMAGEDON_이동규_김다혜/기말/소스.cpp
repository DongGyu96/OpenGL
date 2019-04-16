#include "stdafx.h"

#define PI 3.141592 / 180
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);


void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
void Motion(int x, int y);

int MainWindow;
float Move_Speed = 0.f;
float Move_Z = 0.f;
float Angle_Y;
float Angle_Z;
float Z = -150.f;
GLdouble Camera_X, Camera_Z;
GLdouble Front_Angle_X, Front_Angle_Z;
Spaceship Player;

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
	glutPassiveMotionFunc(Motion);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}


GLvoid drawScene(GLvoid)
{
	//SetCursorPos(500, 500);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
		glRotatef(Angle_Y, 0.f, 1.f, 0.f);
		gluLookAt(Camera_X, 260.0, Move_Z + Camera_Z, Front_Angle_X, 160.0, Move_Z + Front_Angle_Z, 0.0, 1.0, 0.0);

		/*glPushMatrix();
		glTranslatef(Camera_X, 260.0, Camera_Z);
		glColor3f(1.f, 1.f, 0.f);
		glutWireSphere(20, 10, 10);
		glPopMatrix();*/

		glPushMatrix();
		glTranslatef(Front_Angle_X, 160.0, Move_Z + Front_Angle_Z);
		glColor3f(1.f, 0.f, 0.f);
		glutWireSphere(10, 20, 20);
		glPopMatrix();

		glRotatef(-Angle_Y, 0.f, 1.f, 0.f);

		glPushMatrix();
			glColor3f(1.f, 1.f, 1.f);
			glutWireCube(100);
			glutWireCube(5000);
		glPopMatrix();

		glPushMatrix();
			glRotatef(Angle_Y * 2, 0.f, 1.f, 0.f);
			glTranslatef(0.f, 0.f, Move_Z);
			printf("Move_Z : %f	Angle_Z : %f\n", Move_Z, Angle_Y);
			Player.Render();
			//Player.WireRender();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.f, -5200.f, 0.f);
			glScalef(10.f, 0.1f, 10.f);
			glColor3f(0.2f, 0.2f, 1.f);
			glutSolidCube(5000);
		glPopMatrix();

	glPopMatrix();


	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 10000.0);

	//glOrtho(0.0, 800.0, 0.0, 800.0, 0.0, 800.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunction(int value)
{
	Camera_X = cos((Angle_Y - 90) * PI) * 500;
	Camera_Z = sin((Angle_Y - 90) * PI) * -500;
	Front_Angle_X = cos((Angle_Y + 90) * PI) * 200;
	Front_Angle_Z = sin((Angle_Y + 90) * PI) * -200;
	Move_Z -= Move_Speed;
	//SetCursorPos(500, 500);
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
	else if (key == 'a')
	{
		Angle_Y -= 5;
	}
	else if (key == 'd')
	{
		Angle_Y += 5;
	}
	else if (key == 'w')
	{
		if(Move_Speed < 20.f)
			Move_Speed += 0.1f;
	}
	else if (key == 's')
	{
		if (Move_Speed > 0.f)
			Move_Speed -= 1.f;
	}
	else if (key == 'e')
	{
		Angle_Z -= 5.f;
	}
	else if (key == 'r')
	{
		Angle_Z += 5.f;
	}
}

void Motion(int x, int y)
{
	Angle_Y = (x - 400) / -13;
}