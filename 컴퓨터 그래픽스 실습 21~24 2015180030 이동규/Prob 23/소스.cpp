#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#define PI 3.141592f/180.f
#define NUM 8
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

typedef struct Torus {
	float y;
	float angle;
}Torus;

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);

int MainWindow;
Torus torus[NUM];
int torus_count = 0;
int torus_num = 1;
int floor_count = -1;
float floor_y[NUM / 2];
float floor_angle;
float Angle_Y;
bool Torus_Create = true;
bool Floor_Create = false;
bool Depth = true;

void main()
{
	for (int i = 0; i < NUM; ++i)
	{
		torus[i].y = 800.f;
	}
	for (int i = 0; i < NUM / 2; ++i)
	{
		floor_y[i] = 1000.f;
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

	glPushMatrix();
		glTranslatef(0.f, 0.f, -700.f);
		glRotatef(Angle_Y, 0.f, 1.f, 0.f);

		if(Depth)
			glEnable(GL_DEPTH_TEST);

		glPushMatrix(); // ¹Ø¸é
			glTranslatef(0.f, -400.f, 0.f);
			glColor3f(0.5f, 0.7f, 0.7f);
			glBegin(GL_QUADS);
				glVertex3f(400.f, 0.f, -400.f);
				glVertex3f(-400.f, 0.f, -400.f);
				glVertex3f(-400.f, 0.f, 400.f);
				glVertex3f(400.f, 0.f, 400.f);
			glEnd();

			glColor3f(1.0f, 1.0f, 1.0f);
			//glLineWidth(5);
			glBegin(GL_LINES);
				glVertex3f(0.f, 0.f, 0.f);
				glVertex3f(0.f, 800.f, 0.f);
			glEnd();
		glPopMatrix();


		glPushMatrix();
		glColor4f(1.f, 0.f, 0.f, 1.f);
		for (int i = 0; i < torus_count; ++i)
		{
			glPushMatrix();
			glTranslatef(0.f, torus[i].y - 400, 0.f);
			glRotatef(90.f, 1.f, 0.f, 0.f);
			glutWireTorus(40, 160, 30, 30);
			glPopMatrix();
		}

		if (Torus_Create)
		{
			glPushMatrix();
			glTranslatef(cosf(torus[torus_count].angle * PI) * 110.f, torus[torus_count].y - 400, sinf(torus[torus_count].angle * PI) * 110.f);
			glRotatef(90.f, 1.f, 0.f, 0.f);
			glutWireTorus(40, 160, 30, 30);
			glPopMatrix();
		}
		glPopMatrix();

		if (floor_count > 0)
		{
			for (int i = 0; i < floor_count; ++i)
			{
				glPushMatrix();
				glColor4f(1.f, 1.f, 1.f, 1.f);
				glTranslatef(0.f, floor_y[i] - 400.f, 0.f);
				glBegin(GL_QUADS);
				glVertex3f(200.f, 0.f, -200.f);
				glVertex3f(200.f, 0.f, 200.f);
				glVertex3f(-200.f, 0.f, 200.f);
				glVertex3f(-200.f, 0.f, -200.f);
				glEnd();
				glPopMatrix();
			}
		}

		if (Floor_Create)
		{
			glPushMatrix();
			glColor4f(1.f, 1.f, 1.f, 1.f);
			glTranslatef(0.f, floor_y[floor_count] - 400.f, 0.f);
			glRotatef(floor_angle, 0.f, 1.f, 0.f);
			glBegin(GL_QUADS);
			glVertex3f(200.f, 0.f, -200.f);
			glVertex3f(200.f, 0.f, 200.f);
			glVertex3f(-200.f, 0.f, 200.f);
			glVertex3f(-200.f, 0.f, -200.f);
			glEnd();
			glPopMatrix();
		}

		if(Depth)
			glDisable(GL_DEPTH_TEST);

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
	gluLookAt(0.0f, 0.0, 0.0, 0.0, -10.0, -100.0, 0.0, 1.0, 0.0);
}

void TimerFunction(int value)
{
	if (Torus_Create)
	{
		torus[torus_count].y -= 5.f;
		torus[torus_count].angle += 5.f;
		if (torus[torus_count].y - 45.f < -400.f || torus[torus_count].y - 45.f < torus[torus_count - 1].y + 45.f)
		{
			torus_count++;
			if (torus_count % 2 == 0)
			{
				if(floor_count == -1)
					floor_count++;
				Floor_Create = true;
				Torus_Create = false;
			}
			if (torus_count == NUM)
			{
				Torus_Create = false;
			}
		}
	}

	if (Floor_Create)
	{
		floor_angle += 5.f;
		floor_y[floor_count] -= 5.f;
		if (floor_y[floor_count] - 5.f < torus[torus_count - 1].y + 45.f)
		{
			Floor_Create = false;
			if(torus_count != NUM)
				Torus_Create = true;
			floor_angle = 0.f;
			floor_count++;
			if (floor_count == NUM / 2)
				Floor_Create = false;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(20, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') // Á¾·á
	{
		glutDestroyWindow(MainWindow);
		exit(0);
	}
	else if (key == 'y')
	{
		Angle_Y += 5.f;
	}
	else if (key == 'Y')
	{
		Angle_Y -= 5.f;
	}
	else if (key == 'd' || key == 'D')
	{
		if (Depth)
			Depth = false;
		else 
			Depth = true;
	}
}