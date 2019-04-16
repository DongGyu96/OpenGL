#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
bool AABB_Collision_Check(float, float);

int MainWindow;
float Sphere_X, Sphere_Z;
float X_angle, Y_angle, Z_angle;
float Move_X = 80.f;
float Bottom_Angle;
float Middle_X_Angle;
float Middle_Y_Angle;
float Top_X_Angle;
float Top_Z_Angle;
float Wheel_Angle;
bool Move = true;

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

	glPushMatrix(); // 크레인
		glTranslatef(Move_X, -280.f, -300.f);
		glRotatef(Bottom_Angle, 0.f, 1.f, 0.f);

		glPushMatrix(); // 바퀴
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

			glPushMatrix();
			glTranslatef(20.f, 0.f, 20.f);
			glRotatef(Wheel_Angle, 0.f, 0.f, 1.f);
			glutWireSphere(10.f, 10, 10);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-20.f, 0.f, 20.f);
			glRotatef(Wheel_Angle, 0.f, 0.f, 1.f);
			glutWireSphere(10.f, 10, 10);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-20.f, 0.f, -20.f);
			glRotatef(Wheel_Angle, 0.f, 0.f, 1.f);
			glutWireSphere(10.f, 10, 10);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(20.f, 0.f, -20.f);
			glRotatef(Wheel_Angle, 0.f, 0.f, 1.f);
			glutWireSphere(10.f, 10, 10);
			glPopMatrix();
		glPopMatrix();

		glTranslatef(0.f, 40.f, -0.f);
		glScalef(1.f, 1.f, 1.f);
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

	glPushMatrix(); // 구
		glTranslatef(Sphere_X, -260.0f, -300.0f + Sphere_Z);
		glRotatef(X_angle, 1.f, 0.f, 0.f);
		glRotatef(Y_angle, 0.f, 1.f, 0.f);
		glRotatef(Z_angle, 0.f, 0.f, 1.f);
		glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
		glutWireSphere(40.0f, 20, 20);
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
	if (!AABB_Collision_Check(0.f, 0.f))
	{
		if (Move)
		{
			Move_X += 5.f;
			if (Move_X > 250.f)
			{
				Move_X = 250.f;
				Move = false;
			}
		}
		else
		{
			Move_X -= 5.f;
			if (Move_X < -250.f)
			{
				Move_X = -250.f;
				Move = true;
			}
		}
	}
	Wheel_Angle += 5.f;
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
	else if (key == 'y' || key == 'Y')
	{
		Y_angle += 5.f;
	}
	else if (key == 's' || key == 'S')
	{
		X_angle -= 5.f;
		if (!AABB_Collision_Check(0.f, 5.f))
		if (Sphere_Z + 5.f <= 300.f)
		{
			Sphere_Z += 5.f;
		}
	}
	else if (key == 'd' || key == 'D')
	{
		Z_angle -= 5.f;
		if (!AABB_Collision_Check(5.f, 0.f))
		{
			if (Sphere_X + 5.f <= 300.f)
			{
				Sphere_X += 5.f;
			}
		}
	}
	else if (key == 'w' || key == 'W')
	{
		X_angle += 5.f;
		if (!AABB_Collision_Check(0.f, -5.f))
		{
			if (Sphere_Z - 5.f >= -300.f)
			{
				Sphere_Z -= 5.f;
			}
		}
	}
	else if (key == 'a' || key == 'A')
	{
		Z_angle += 5.f;
		if (!AABB_Collision_Check(-5.f, 0.f))
		{
			if (Sphere_X - 5.f >= -300.f)
			{
				Sphere_X -= 5.f;
			}
		}
	}
	else if (key == 'i' || key == 'I') // 초기화
	{
		glLoadIdentity();
		gluLookAt(0.0f, 0.0, 100.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
		Z_angle = X_angle = Z_angle = 0.f;
		Sphere_X = Sphere_Z = 0.f;
	}
	else if (key == '-')
	{
		gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	}
	else if (key == '+')
	{
		gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	}
	else if (key == 49)
	{
		Bottom_Angle += 5.f;
	}
	else if (key == 50)
	{
		if (Middle_X_Angle + 5.f < 40)
			Middle_X_Angle += 5.f;
	}
	else if (key == 51)
	{
		if (Middle_X_Angle - 5.f > -40)
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
		if (Top_Z_Angle + 5.f < 40)
			Top_Z_Angle += 5.f;
	}
	else if (key == 57)
	{
		if (Top_Z_Angle - 5.f > -40)
			Top_Z_Angle -= 5.f;
	}
	else if (key == 'm' || key == 'M')
	{
		gluLookAt(10.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	}
}

bool AABB_Collision_Check(float x, float z)
{
	if (Sphere_X + 40.f + x < Move_X - 30.f || Sphere_X - 40.f + x > Move_X + 30.f) return false;
	if (Sphere_Z + 40.f + z < -30.f || Sphere_Z - 40.f + z > 30.f) return false;
	return true;
}