#include <gl/glut.h>
#include <math.h>
#include <Windows.h>
#include <stdio.h>
#define R 0.11f
#define PI 3.141592/180.0
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);

int MainWindow;
int Start_Angle = 90;
float Scaling = 1.f;
float Start_X = 0.0f;
float turn = 0.f;
float X, Y, Z = 0.f;
float Move_X = 0.f;
bool Animation = false;

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	MainWindow = glutCreateWindow("Computer Graphics OpenGL");
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKeyBoard);
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


	float color = 0.0f;
	glPushMatrix();//for(int y  =  {
		glTranslatef(Move_X, -0.2f, 0.f);
		if (X == 1.f || Y == 1.f || Z == 1.f)
		{
			glRotatef(turn, X, Y, Z);
		}
		glScalef(Scaling, Scaling, Scaling);

		int angle = Start_Angle;
		glBegin(GL_LINE_STRIP);
		for (float fx = -0.5f; fx <= 0.5f; fx += 0.004f)
		{
			glColor4f(1.0f - color, 0.0f, color, 1.0f);
			glVertex2f(fx + (cosf(angle*PI) * R), sinf(angle*PI) * R);
			angle += 10;
			color += 0.005f;
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, 0.1f, 0.0f);
		if (X == 1.f || Y == 1.f || Z == 1.f)
		{
			glRotatef(turn, X, Y, Z);
		}
		glScalef(Scaling, Scaling, Scaling);
		angle = Start_Angle - 90;
		glBegin(GL_LINE_STRIP);
		for (float fx = -0.5f; fx <= 0.5f; fx += 0.004f)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glVertex2f(fx, sinf(angle*PI) * R);
			angle += 10;
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, 0.4f, 0.0f);
		if (X == 1.f || Y == 1.f || Z == 1.f)
		{
			glRotatef(turn, X, Y, Z);
		}
		glScalef(Scaling, Scaling, Scaling);
		angle = Start_Angle - 90;
		glBegin(GL_LINE_STRIP);
		for (float fx = -0.5f; fx <= 0.5f; fx += 0.004f)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glVertex2f(fx, cosf(angle*PI) * R);
			angle += 10;
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -0.45f, 0.0f);
		if (X == 1.f || Y == 1.f || Z == 1.f)
		{
			glRotatef(turn, X, Y, Z);
		}
		glScalef(Scaling, Scaling, Scaling);
		for (float i = -0.5f; i < 0.5f; i += 0.12f)
		{
			if (i + 0.05f + Start_X > 0.52f)
			{
				glRectf(i - 0.05f + Start_X, -0.4f, 0.52f, -0.5f);
				glRectf(-0.55f, -0.4f, 0.05f + Start_X - 0.02f, -0.05f);
			}
			else
				glRectf(i - 0.05f + Start_X, 0.05f, i + 0.05f + Start_X, -0.05f);
		}
	glPopMatrix();

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
	if (X == 1.f || Y == 1.f || Z == 1.f)
	{
		turn += 10.f;
		if (turn > 360) turn = 0.f;
	}
	if (Animation)
	{
		Start_Angle += 10;
		if (Start_Angle == 360) Start_Angle = 0;
		Start_X += 0.005f;
		if (Start_X > 0.12f) Start_X = 0.f;
	}
	else Start_Angle = 90;
	glutPostRedisplay();
	glutTimerFunc(40, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
	{
		glutDestroyWindow(MainWindow);
		exit(0);
	}
	else if (key == 'x' || key == 'X')
	{
		if(X != 1.f) X = 1.f;
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
	else if (key == 'a' || key == 'A')
	{
		if(Animation) Animation = false;
		else Animation = true;
	}
	else if (key == 's' || key == 'S')
	{
		Scaling += 0.1f;
		if (Scaling > 1.9f) Scaling = 0.5f;
	}
	else if (key == 'i' || key == 'I')
	{
		Start_Angle = 90;
		Scaling = 1.f;
		Start_X = 0.0f;
		turn = 0.f;
		X = Y = Z = 0.f;
		Move_X = 0.f;
		Animation = false;
	}
}

void SpecialKeyBoard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		Move_X -= 0.05f;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		Move_X += 0.05f;
	}
}


