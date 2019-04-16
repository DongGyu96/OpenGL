#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);

int MainWindow;
float Building_Move_Y;
bool Building_Move_Y_Type = false;
float Building_Scaling = 1.f;
bool Building_Scaling_Type = false;
float Building_Angle;
bool Door_Type = false;
float Door_Angle;

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

	glPushMatrix(); // ----------------------------------------
		glTranslatef(0.f, -220.0f, -300.0f);
		glPushMatrix(); // 중앙 문
			glRotatef(Building_Angle, 0.f, 1.f, 0.f);
			glPushMatrix();
				glPushMatrix();
					glTranslatef(-30.f, -40.0f, 0.0f);
					glScalef(1.f, 3.f, 1.f);

					glPushMatrix();
						glTranslatef(10.f, 0.0f, 5.0f);
						glRotatef(Door_Angle, 0.f, 1.f, 0.f);
						glColor4f(0.5f, 0.0f, 0.0f, 1.0f);
						glScalef(2.f, 1.f, 0.25f);
						glutSolidCube(20);
					glPopMatrix();

					glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
					glutSolidCube(20);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(30.f, -40.0f, 0.0f);
					glScalef(1.f, 3.f, 1.f);

					glPushMatrix();
						glTranslatef(-10.f, 0.0f, 5.0f);
						glRotatef(180 - Door_Angle, 0.f, 1.f, 0.f);
						glColor4f(0.5f, 0.0f, 0.0f, 1.0f);
						glScalef(2.f, 1.f, 0.25f);
						glutSolidCube(20);
					glPopMatrix();

					glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
					glutSolidCube(20);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				glTranslatef(0.f, 0.0f, 0.0f);
				glScalef(4.f, 1.f, 1.f);
				glutSolidCube(20);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); // 왼쪽 끝 나무
			glColor4f(0.0f, 0.5f, 0.0f, 1.0f);
			glTranslatef(-260.f, 0.0f, -260.0f);
			glScalef(1.f, 4.f, 1.f);
			glutSolidCube(40);

			glPushMatrix();
				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				glTranslatef(0.f, 20.0f, 0.0f);
				glRotatef(Building_Angle, 0.f, 1.f, 0.f);
				glScalef(5.f, 0.25f, 1.f);
				glutSolidCube(40);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); // 오른쪽 끝 나무
			glColor4f(0.0f, 0.5f, 0.0f, 1.0f);
			glTranslatef(260.f, 0.0f, -260.0f);

			glPushMatrix();
				glScalef(1.f, 4.f, 1.f);
				glutSolidCube(40);
			glPopMatrix();

			glPushMatrix();
				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				glTranslatef(0.f, 70.0f, 0.0f);
				glScalef(0.5f + Building_Scaling, 0.5f + Building_Scaling, 0.5f + Building_Scaling);
				glutWireSphere(50, 20, 20);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); // 왼쪽 앞 건물
			glColor4f(0.5f, 0.0f, 0.0f, 1.0f);
			glTranslatef(-260.f, 0.0f, 260.0f);
			glScalef(1.f, 4.f, 1.f);
			glutSolidCube(40);

			glPushMatrix();
				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				glTranslatef(0.f, 20.0f + Building_Move_Y, 0.0f);
				glScalef(1.f, 0.25f, 1.f);
				glRotatef(90.f, 1.f, 0.f, 0.f);
				glutWireTorus(20, 60, 20, 20);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); // 오른쪽 앞 원뿔
			glColor4f(0.5f, 0.f, 0.f, 1.f);
			glTranslatef(240.f, 0.f, 240.f);

			glPushMatrix();
				glTranslatef(0.f, -80.f, 0.f);
				glRotatef(270.f, 1.f, 0.f, 0.f);
				glScalef(1.f - Building_Scaling, 1.f - Building_Scaling, 1.f - Building_Scaling);
				glutWireCone(60, 120, 20, 20);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.f, 40.f, 0.f);
				glRotatef(90.f, 1.f, 0.f, 0.f);
				glScalef(Building_Scaling, Building_Scaling, Building_Scaling);
				glutWireCone(60, 120, 20, 20);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix(); // -----------------------------------------

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
	if (Building_Move_Y_Type)
	{
		Building_Move_Y += 1.f;
		if (Building_Move_Y > 0)
			Building_Move_Y_Type = false;
	}
	else
	{
		Building_Move_Y -= 1.f;
		if (Building_Move_Y < -25)
			Building_Move_Y_Type = true;
	}

	if (Building_Scaling_Type)
	{
		Building_Scaling += 0.05f;
		if (Building_Scaling > 1.0f)
			Building_Scaling_Type = false;
	}
	else
	{
		Building_Scaling -= 0.05f;
		if (Building_Scaling < 0.0f)
			Building_Scaling_Type = true;
	}

	if (Door_Type)
	{
		Door_Angle+=3;
		if (Door_Angle > 0)
			Door_Type = false;
	}
	else
	{
		Door_Angle-=3;
		if (Door_Angle < -90)
			Door_Type = true;
	}
	Building_Angle += 5.f;
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
	else if (key == 'i' || key == 'I') // 초기화
	{
		glLoadIdentity();
		gluLookAt(0.0f, 0.0, 100.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
	}
	else if (key == '-')
	{
		gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	}
	else if (key == '+')
	{
		gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	}
	else if (key == 'y' || key == 'Y')
	{
		gluLookAt(10.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	}
}

