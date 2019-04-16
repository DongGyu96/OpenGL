#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#define PI 3.141592f / 180.0f
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
float Angle_Y;
float Sphere_Angle, Small_Sphere_Angle;
bool Left_Light, Right_Light;
GLfloat right_AmbienLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat right_DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat right_SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat right_lightPos[] = { 600.0f, 300.0f, -300.0f, 1.0f };
GLfloat left_AmbienLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat left_DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat left_SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat left_lightPos[] = { -600.0f, 300.0f, -300.0f, 1.0f };

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

	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0.f, 0.f, -300.f);
	glRotatef(Angle_Y, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, 300.f);

	if (Right_Light)
	{
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, right_AmbienLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, right_DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, right_SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, right_lightPos);
		glEnable(GL_LIGHT0);
	}
	else
		glDisable(GL_LIGHT0);

	if (Left_Light)
	{
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT1, GL_AMBIENT, left_AmbienLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, left_DiffuseLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, left_SpecularLight);
		glLightfv(GL_LIGHT1, GL_POSITION, left_lightPos);
		glEnable(GL_LIGHT1);
	}
	else
		glDisable(GL_LIGHT1);

	glPushMatrix();
	glTranslatef(right_lightPos[0], right_lightPos[1], right_lightPos[2]);
	glutWireSphere(10, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(left_lightPos[0], left_lightPos[1], left_lightPos[2]);
	glutWireSphere(10, 10, 10);
	glPopMatrix();

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

	glPushMatrix(); // ----------------------------------------
	glTranslatef(0.f, -220.0f, -300.0f);

	glPushMatrix(); // 중앙 문
	glTranslatef(0.f, -80.f, 0.f);

	glColor3f(1.f, 0.5f, 0.0f);
	glPushMatrix();
	glRotatef(-90.f, 1.f, 0.f, 0.f);
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
		Angle_Y += 5.f;
	}
	else if (key == 'a')
	{
		for (int i = 0; i < 3; ++i)
		{
			right_AmbienLight[i] += 0.1f;
			left_AmbienLight[i] += 0.1f;
		}
	}
	else if (key == 'A')
	{
		for (int i = 0; i < 3; ++i)
		{
			right_AmbienLight[i] -= 0.1f;
			left_AmbienLight[i] -= 0.1f;
		}
	}
	else if (key == 'd')
	{
		for (int i = 0; i < 3; ++i)
		{
			right_DiffuseLight[i] += 0.1f;
			left_DiffuseLight[i] += 0.1f;
		}
	}
	else if (key == 'D')
	{
		for (int i = 0; i < 3; ++i)
		{
			right_DiffuseLight[i] -= 0.1f;
			left_DiffuseLight[i] -= 0.1f;
		}
	}
	else if (key == 's')
	{
		for (int i = 0; i < 3; ++i)
		{
			right_SpecularLight[i] += 0.1f;
			left_SpecularLight[i] += 0.1f;
		}
	}
	else if (key == 'S')
	{
		for (int i = 0; i < 3; ++i)
		{
			right_SpecularLight[i] -= 0.1f;
			left_SpecularLight[i] -= 0.1f;
		}
	}
	else if (key == 49)
	{
		if (Left_Light)
			Left_Light = false;
		else
			Left_Light = true;
	}
	else if (key == 50)
	{
		if (Right_Light)
			Right_Light = false;
		else
			Right_Light = true;
	}
}