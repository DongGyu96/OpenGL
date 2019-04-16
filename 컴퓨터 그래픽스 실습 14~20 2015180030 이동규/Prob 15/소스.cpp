#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#define BIG_R 300.0f
#define SMALL_R 120.0f
#define PI 3.141592 / 180
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
void Draw_Orbit();
void MenuFunc(int button);

int MainWindow;
float Big_Sphere_Angle[3];
float Small_Sphere_Angle[3];
float turn = 0.f;
float move_x = 0.f;
float move_y = 0.f;
bool Left_X = false;
bool shape = false;
bool Right_X = false;
bool Up_Y = false;
bool Down_Y = false;
bool Z_turn = false;

void main()
{
	int MainMenu;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	MainWindow = glutCreateWindow("Computer Graphics OpenGL");
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(KeyBoard);
	glutReshapeFunc(Reshape);

	MainMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Solid", 1);
	glutAddMenuEntry("Wire", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}


GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glRotatef(turn, 0.0f, 0.0f, 1.0f);
		gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
		glTranslatef(move_x, move_y, 0.0f);

		glPushMatrix();
			Draw_Orbit();
		glPopMatrix();

		glPushMatrix(); // ¼öÆò ±Ëµµ
			glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
			glTranslatef(cosf(Big_Sphere_Angle[0] * PI) * BIG_R, 0.0f, sinf(Big_Sphere_Angle[0] * PI) * BIG_R);
			if(shape)
				glutSolidSphere(15.0, 15, 15);
			else
				glutWireSphere(15.0, 15, 15);

			glPushMatrix();
				glBegin(GL_POINTS);
				for (int angle = 0; angle < 360; ++angle)
				{
					glVertex3f(cosf(angle * PI) * SMALL_R, 0.0f, sinf(angle * PI) * SMALL_R);
				}
				glEnd();

				glPushMatrix();
				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				glTranslatef(cosf(Small_Sphere_Angle[0] * PI) * SMALL_R, 0.0f, sinf(Small_Sphere_Angle[0] * PI) * SMALL_R);
				if(shape)
					glutSolidSphere(8.0, 15, 15);
				else
					glutWireSphere(8.0, 15, 15);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); // / ±Ëµµ
			glColor4f(0.5f, 1.f, 0.5f, 1.0f);
			glRotatef(45.f, 0.f, 0.f, 1.f);
			glTranslatef(cosf(Big_Sphere_Angle[1] * PI) * BIG_R, 0.0f, sinf(Big_Sphere_Angle[1] * PI) * BIG_R);
			if (shape)
				glutSolidSphere(15.0, 15, 15);
			else
				glutWireSphere(15.0, 15, 15);
			glRotatef(-45.f, 0.f, 0.f, 1.f);

			glPushMatrix();
				glBegin(GL_POINTS);
				for (int angle = 0; angle < 360; ++angle)
				{
					glVertex3f(cosf(angle * PI) * SMALL_R, 0.0f, sinf(angle * PI) * SMALL_R);
				}
				glEnd();

				glPushMatrix();
				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				glTranslatef(cosf(Small_Sphere_Angle[1] * PI) * SMALL_R, 0.0f, sinf(Small_Sphere_Angle[1] * PI) * SMALL_R);
				if (shape)
					glutSolidSphere(8.0, 15, 15);
				else
					glutWireSphere(8.0, 15, 15);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); // \ ±Ëµµ
			glColor4f(1.f, 0.5f, 0.5f, 1.0f);
			glRotatef(135.f, 0.f, 0.f, 1.f);
			glTranslatef(cosf(Big_Sphere_Angle[2] * PI) * BIG_R, 0.0f, sinf(Big_Sphere_Angle[2] * PI) * BIG_R);
			if (shape)
				glutSolidSphere(15.0, 15, 15);
			else
				glutWireSphere(15.0, 15, 15);
			glRotatef(-135.f, 0.f, 0.f, 1.f);

			glPushMatrix();
				glBegin(GL_POINTS);
				for (int angle = 0; angle < 360; ++angle)
				{
					glVertex3f(cosf(angle * PI) * SMALL_R, 0.0f, sinf(angle * PI) * SMALL_R);
				}
				glEnd();

				glPushMatrix();
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				glTranslatef(cosf(Small_Sphere_Angle[2] * PI) * SMALL_R, 0.0f, sinf(Small_Sphere_Angle[2] * PI) * SMALL_R);
				if (shape)
					glutSolidSphere(8.0, 15, 15);
				else
					glutWireSphere(8.0, 15, 15);
				glPopMatrix();
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
	glTranslatef(0.0, 0.0, -500.0);

	//glOrtho(0.0, 800.0, 0.0, 800.0, 0.0, 800.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0, 100.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
}

void TimerFunction(int value)
{
	if (Z_turn)
		turn += 5.f;
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0)
		{
			Big_Sphere_Angle[i] += 2;
			Small_Sphere_Angle[i] += 3;
		}
		else if (i == 1)
		{
			Big_Sphere_Angle[i] += 3;
			Small_Sphere_Angle[i] += 1;
		}
		else
		{
			Big_Sphere_Angle[i] += 1;
			Small_Sphere_Angle[i] += 2;
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
	else if (key == 'y' || key == 'Y')
	{
		move_y += 5.f;
	}
	else if (key == 'u' || key == 'U')
	{
		move_y -= 5.f;
	}
	else if (key == 'x' || key == 'X')
	{
		move_x -= 5.f;
	}
	else if (key == 'c' || key == 'C')
	{
		move_x += 5.f;
	}
	else if (key == 'z' || key == 'Z')
	{
		if (Z_turn) Z_turn = false;
		else Z_turn = true;
	}
	else if (key == '-')
	{
		gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	}
	else if (key == '+')
	{
		gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	}
	else if (key == 'i' || key == 'I') // ÃÊ±âÈ­
	{
		glLoadIdentity();
		gluLookAt(0.0, 0.0, 100.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
		Z_turn = false;
		turn = 0.0f;
		move_x = move_y;
	}
	glutPostRedisplay();
}

void Draw_Orbit()
{
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if(shape)
		glutSolidSphere(30.0, 20, 20);
	else
		glutWireSphere(30.0, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int angle = 0; angle < 360; ++angle)
	{
		glVertex3f(cosf(angle * PI) * BIG_R, 0.0f, sinf(angle * PI) * BIG_R);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRotatef(45.f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int angle = 0; angle < 360; ++angle)
	{
		glVertex3f(cosf(angle * PI) * BIG_R, 0.0f, sinf(angle * PI) * BIG_R);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRotatef(135.f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int angle = 0; angle < 360; ++angle)
	{
		glVertex3f(cosf(angle * PI) * BIG_R, 0.0f, sinf(angle * PI) * BIG_R);
	}
	glEnd();
	glPopMatrix();
}

void MenuFunc(int button)
{
	if (button == 1)
	{
		shape = true;
	}
	else if (button == 2)
	{
		shape = false;
	}
	glutPostRedisplay();
}