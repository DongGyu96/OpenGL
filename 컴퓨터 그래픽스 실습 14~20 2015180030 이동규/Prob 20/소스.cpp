#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define CUBE 100
#define SPHERE 101
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
bool Collision_Check(int shape, int move_type);
bool AABB_Check(float fx1, float fz1, float fsize1, int move_type, float fx2, float fz2, float fsize2);

int MainWindow;
float Building_Move_Y;
bool Building_Move_Y_Type = false;
float Building_Scaling = 1.f;
bool Building_Scaling_Type = false;
float Building_Angle;
bool Door_Type = false;
float Door_Angle;

float Sphere_X = -150.f, Sphere_Z;
float X_angle, Y_angle, Z_angle;
float Move_X = 150.f, Move_Z;
float Bottom_Angle;
float Middle_X_Angle;
float Middle_Y_Angle;
float Top_X_Angle;
float Top_Z_Angle;
float Wheel_Angle;

int Cube_Move;
int Sphere_Move;

void main()
{
	srand((unsigned)time(NULL));
	Cube_Move = rand() % 4;
	Sphere_Move = rand() % 4;
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

	glPushMatrix(); // 크레인
	glTranslatef(Move_X, -280.f, -300.f + Move_Z);
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
		Door_Angle += 3;
		if (Door_Angle > 0)
			Door_Type = false;
	}
	else
	{
		Door_Angle -= 3;
		if (Door_Angle < -90)
			Door_Type = true;
	}

	if (Cube_Move == UP)
	{
		if (Move_Z - 5.f < -260.f)
		{
			Cube_Move = rand() % 4;
		}
		else if (Collision_Check(CUBE, UP))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, UP, -260.f, -260.f, 30.f))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, UP, 260.f, -260.f, 30.f))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, UP, 0.f, 0.f, 25.f))
		{
			Cube_Move = rand() % 4;
		}
		else
			Move_Z -= 5.f;
	}
	else if (Cube_Move == RIGHT)
	{
		if (Move_X + 5.f > 280.f)
		{
			Cube_Move = rand() % 4;
		}
		else if (Collision_Check(CUBE, RIGHT))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, RIGHT, 260.f, -260.f, 30.f))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, RIGHT, 260.f, 260.f, 60.f))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, RIGHT, 0.f, 0.f, 25.f))
		{
			Cube_Move = rand() % 4;
		}
		else
			Move_X += 5.f;
	}
	else if (Cube_Move == DOWN)
	{
		if (Move_Z + 5.f > 260.f)
		{
			Cube_Move = rand() % 4;
		}
		else if (Collision_Check(CUBE, DOWN))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, DOWN, -260.f, 260.f, 30.f))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, DOWN, 260.f, 260.f, 60.f))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, DOWN, 0.f, 0.f, 25.f))
		{
			Cube_Move = rand() % 4;
		}
		else
			Move_Z += 5.f;
	}
	else if (Cube_Move == LEFT)
	{
		if (Move_X - 5.f < -280.f)
		{
			Cube_Move = rand() % 4;
		}
		else if (Collision_Check(CUBE, LEFT))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, LEFT, -260.f, -260.f, 30.f))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, LEFT, -260.f, 260.f, 30.f))
		{
			Cube_Move = rand() % 4;
		}
		else if (AABB_Check(Move_X, Move_Z, 30.f, LEFT, 0.f, 0.f, 25.f))
		{
			Cube_Move = rand() % 4;
		}
		else
			Move_X -= 5.f;
	}

	if (Sphere_Move == UP)
	{
		X_angle += 5.f;
		if (Sphere_Z - 5.f < -280.f)
		{
			Sphere_Move = rand() % 4;
		}
		else if (Collision_Check(SPHERE, UP))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, UP, -260.f, -260.f, 30.f))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, UP, 260.f, -260.f, 30.f))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, UP, 0.f, 0.f, 25.f))
		{
			Sphere_Move = rand() % 4;
		}
		else
			Sphere_Z -= 5.f;
	}
	else if (Sphere_Move == RIGHT)
	{
		Z_angle -= 5.f;
		if (Sphere_X + 5.f > 280.f)
		{
			Sphere_Move = rand() % 4;
		}
		else if (Collision_Check(SPHERE, RIGHT))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, RIGHT, 260.f, -260.f, 30.f))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, RIGHT, 260.f, 260.f, 60.f))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, RIGHT, 0.f, 0.f, 25.f))
		{
			Sphere_Move = rand() % 4;
		}
		else
			Sphere_X += 5.f;
	}
	else if (Sphere_Move == DOWN)
	{
		X_angle -= 5.f;
		if (Sphere_Z + 5.f > 280.f)
		{
			Sphere_Move = rand() % 4;
		}
		else if (Collision_Check(SPHERE, DOWN))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, DOWN, -260.f, 260.f, 30.f))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, DOWN, 260.f, 260.f, 60.f))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, DOWN, 0.f, 0.f, 25.f))
		{
			Sphere_Move = rand() % 4;
		}
		else
			Sphere_Z += 5.f;
	}
	else if (Sphere_Move == LEFT)
	{
		Z_angle += 5.f;
		if (Sphere_X - 5.f < -280.f)
		{
			Sphere_Move = rand() % 4;
		}
		else if (Collision_Check(SPHERE, LEFT))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, LEFT, -260.f, -260.f, 30.f))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, LEFT, -260.f, 260.f, 30.f))
		{
			Sphere_Move = rand() % 4;
		}
		else if (AABB_Check(Sphere_X, Sphere_Z, 40.f, LEFT, 0.f, 0.f, 25.f))
		{
			Sphere_Move = rand() % 4;
		}
		else
			Sphere_X -= 5.f;
	}
	Building_Angle += 5.f;
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
	else if (key == 'w' || key == 'W')
	{
		Sphere_Move = UP;
	}
	else if (key == 'd' || key == 'D')
	{
		Sphere_Move = RIGHT;
	}
	else if (key == 's' || key == 'S')
	{
		Sphere_Move = DOWN;
	}
	else if (key == 'a' || key == 'A')
	{
		Sphere_Move = LEFT;
	}
}

bool Collision_Check(int shape, int move_type)
{
	if (shape == CUBE)
	{
		if (move_type == UP)
		{
			if (Sphere_X + 40.f < Move_X - 30.f || Sphere_X - 40.f > Move_X + 30.f) return false;
			if (Sphere_Z + 40.f < Move_Z - 30.f - 5.f || Sphere_Z - 40.f > Move_Z + 30.f - 5.f) return false;
		}
		else if (move_type == RIGHT)
		{
			if (Sphere_X + 40.f < Move_X - 30.f + 5.f || Sphere_X - 40.f > Move_X + 30.f + 5.f) return false;
			if (Sphere_Z + 40.f < Move_Z - 30.f || Sphere_Z - 40.f > Move_Z + 30.f) return false;
		}
		else if (move_type == DOWN)
		{
			if (Sphere_X + 40.f < Move_X - 30.f || Sphere_X - 40.f > Move_X + 30.f) return false;
			if (Sphere_Z + 40.f < Move_Z - 30.f + 5.f || Sphere_Z - 40.f > Move_Z + 30.f + 5.f) return false;
		}
		else if (move_type == LEFT)
		{
			if (Sphere_X + 40.f < Move_X - 30.f - 5.f || Sphere_X - 40.f > Move_X + 30.f - 5.f) return false;
			if (Sphere_Z + 40.f < Move_Z - 30.f || Sphere_Z - 40.f > Move_Z + 30.f) return false;
		}
	}
	else if (shape == SPHERE)
	{
		if (move_type == UP)
		{
			if (Sphere_X + 40.f < Move_X - 30.f || Sphere_X - 40.f > Move_X + 30.f) return false;
			if (Sphere_Z + 40.f - 5.f < Move_Z - 30.f || Sphere_Z - 40.f - 5.f > Move_Z + 30.f) return false;
		}
		else if (move_type == RIGHT)
		{
			if (Sphere_X + 40.f + 5.f < Move_X - 30.f || Sphere_X - 40.f + 5.f > Move_X + 30.f) return false;
			if (Sphere_Z + 40.f < Move_Z - 30.f || Sphere_Z - 40.f > Move_Z + 30.f) return false;
		}
		else if (move_type == DOWN)
		{
			if (Sphere_X + 40.f < Move_X - 30.f || Sphere_X - 40.f > Move_X + 30.f) return false;
			if (Sphere_Z + 40.f + 5.f < Move_Z - 30.f || Sphere_Z - 40.f + 5.f > Move_Z + 30.f) return false;
		}
		else if (move_type == LEFT)
		{
			if (Sphere_X + 40.f - 5.f < Move_X - 30.f || Sphere_X - 40.f - 5.f > Move_X + 30.f) return false;
			if (Sphere_Z + 40.f < Move_Z - 30.f || Sphere_Z - 40.f > Move_Z + 30.f) return false;
		}
	}

	return true;
}

bool AABB_Check(float fx1, float fz1, float fsize1, int move_type, float fx2, float fz2, float fsize2)
{
	if (move_type == UP)
	{
		if (fx1 + fsize1 < fx2 - fsize2 || fx1 - fsize1 > fx2 + fsize2) return false;
		if (fz1 + fsize1 - 5.f < fz2 - fsize2 || fz1 - fsize1 - 5.f > fz2 + fsize2) return false;
	}
	else if (move_type == RIGHT)
	{
		if (fx1 + fsize1 + 5.f < fx2 - fsize2 || fx1 - fsize1 + 5.f > fx2 + fsize2) return false;
		if (fz1 + fsize1 < fz2 - fsize2 || fz1 - fsize1 > fz2 + fsize2) return false;
	}
	else if (move_type == DOWN)
	{
		if (fx1 + fsize1 < fx2 - fsize2 || fx1 - fsize1 > fx2 + fsize2) return false;
		if (fz1 + fsize1 + 5.f < fz2 - fsize2 || fz1 - fsize1 + 5.f > fz2 + fsize2) return false;
	}
	else if (move_type == LEFT)
	{
		if (fx1 + fsize1 - 5.f < fx2 - fsize2 || fx1 - fsize1 - 5.f > fx2 + fsize2) return false;
		if (fz1 + fsize1 < fz2 - fsize2 || fz1 - fsize1 > fz2 + fsize2) return false;
	}
	return true;
}