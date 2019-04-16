

#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);

int MainWindow;
float Move_X;
float Bottom_Angle;
float Middle_X_Angle;
float Middle_Y_Angle;
float Top_X_Angle;
float Top_Z_Angle;
bool Turn = false;

void main()
{
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

	if (Turn) // 카메라 회전
		gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	//glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
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
		glTranslatef(Move_X, -240.f, -300.f);
		glRotatef(Bottom_Angle, 0.f, 1.f, 0.f);
		glScalef(1.f, 1.f, 1.5f);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glutSolidCube(60);

		glPushMatrix();
			glTranslatef(0.0f, 45.f, 0.f);
			glRotatef(Middle_X_Angle, 1.f, 0.f, 0.f);
			glRotatef(Middle_Y_Angle, 0.f, 1.f, 0.f);
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			glutSolidCube(30);

			glPushMatrix();
				glTranslatef(0.0f, 30.f, 0.f);
				glRotatef(Top_X_Angle, 1.f, 0.f, 0.f);
				glRotatef(Top_Z_Angle, 0.f, 0.f, 1.f);
				glScalef(1.f, 3.f, 1.f);
				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				glutSolidCube(10);
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
		if (Turn) Turn = false;
		else Turn = true;
	}
	else if (key == 'a' || key == 'A')
	{
		if(Move_X - 5.f > -250)
			Move_X -= 5.f;
	}
	else if (key == 'd' || key == 'D')
	{
		if(Move_X + 5.f < 250)
			Move_X += 5.f;
	}
	else if (key == 'i' || key == 'I') // 초기화
	{
		glLoadIdentity();
		gluLookAt(0.0f, 0.0, 100.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
		Turn = false;
	}
	else if (key == 49)
	{
		Bottom_Angle += 5.f;
	}
	else if (key == 50)
	{
		if(Middle_X_Angle + 5.f < 40)
			Middle_X_Angle += 5.f;
	}
	else if (key == 51)
	{
		if(Middle_X_Angle - 5.f > -40)
			Middle_X_Angle -= 5.f;
	}
	else if (key == 52)
	{
		Middle_Y_Angle += 5.f;
	}
	else if (key == 53)
	{
		Middle_Y_Angle -= 5.f;
	}
	else if (key == 54)
	{
		if (Top_X_Angle + 5.f < 40)
			Top_X_Angle += 5.f;
	}
	else if (key == 55)
	{
		if (Top_X_Angle - 5.f > -40)
			Top_X_Angle -= 5.f;
	}
	else if (key == 56)
	{
		if(Top_Z_Angle + 5.f < 40)
			Top_Z_Angle += 5.f;
	}
	else if (key == 57)
	{
		if (Top_Z_Angle - 5.f > -40)
			Top_Z_Angle -= 5.f;
	}
}

