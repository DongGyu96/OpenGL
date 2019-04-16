#include <gl/glut.h>
#include <iostream>
using namespace std;

typedef struct Rotate
{
	float fX;
	float fY;
	float fZ;
}Rotate;

typedef struct Rotate_Puls
{
	float fX;
	float fY;
	float fZ;
}Rotate_Plus;

typedef struct Trans
{
	float fX;
	float fY;
	float fZ;
}Trans;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunc(int value);
void Init();
void Rect();
void Sphere();
void Sphere_Trus();
void Keyboard(unsigned char key, int x, int y);

Rotate Cube_Rotate;
Rotate Sphere_Rotate;
Rotate Sphere_Trus_Rotate;
Rotate Trus_Rotate;

Rotate_Plus Cube_RotatePlus;
Rotate_Plus Sphere_RotatePlus;
Rotate_Plus Sphere_Trus_RotatePlus;
Rotate_Plus Trus_RotatePlus;

Trans Cube_Trans;
Trans Sphere_Trans;
Trans Sphere_Trus_Trans;
Trans Trus_Trans;

float fRotate_Y = 0.0f;
float fRotate_Plus_Y = 10.f;
float fAmbient_Light = 0.3f;
float fDiffuse_Light = 0.2f;
float fSpecre_f = 0.2f;
bool bLight = false;
int idistance = 0;
void main()
{
	//초기화 함수들
	Init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-25");
	glutDisplayFunc(drawScene);      //출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, TimerFunc, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glLoadIdentity();
	gluLookAt(0.0, 200.0, 500.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	GLfloat AmbientLight[] = { .30f, .30f, .30f, 1.f };
	GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat SpecularLight[] = { .0, .0, 1.0, 1.0 };
	glRotatef(fRotate_Y, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, idistance);
	glEnable(GL_LIGHTING);

	if (bLight == false)
		glEnable(GL_LIGHT0);
	else if (bLight == true)
		glDisable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	GLfloat lightPos[] = { 200, 75, 0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3d(0, 50, 0);
	glVertex3d(0, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3d(50, 0, 0);
	glVertex3d(0, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3d(0, 0, 50);
	glVertex3d(0, 0, 0);
	glEnd();

	glPushMatrix();
	{
		glTranslatef(-100.f, 50.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 150.f, 0.0f);
		glVertex3f(0.0f, -50.f, 0.0f);
		glEnd();
		Rect();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(100.f, 75.f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(-50.f, 0.0f, 0.0f);
		glVertex3f(150.f, 0.0f, 0.0f);
		glEnd();
		Sphere();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(50.f, -200.f, 0.0f);
		glRotatef(45.f, 0.0f, 1.0f, 0.0f);
		glRotatef(45.f, 1.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(-100.f, 0.0f, 0.0f);
		glVertex3f(250.f, 0.0f, 0.0f);
		glEnd();
		Sphere_Trus();
	}
	glPopMatrix();
	//glFlush();
	glutSwapBuffers();      //결과 출력
}

GLvoid Reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
}

void Init()
{
	Cube_Rotate.fX = 0.f;
	Cube_Rotate.fY = 0.f;
	Cube_Rotate.fZ = 0.0f;
	Cube_RotatePlus.fX = 10.f;
	Cube_RotatePlus.fY = 10.f;
	Cube_RotatePlus.fZ = 10.f;
	Cube_Trans.fX = -50.f;
	Cube_Trans.fY = 50.f;
	Cube_Trans.fZ = 0.0f;
	///////////////////////////////////
	Sphere_Rotate.fX = 0.0f;
	Sphere_Rotate.fY = 0.0f;
	Sphere_Rotate.fZ = 0.0f;
	Sphere_RotatePlus.fX = 10.f;
	Sphere_RotatePlus.fY = 10.f;
	Sphere_RotatePlus.fZ = 10.f;
	Sphere_Trans.fX = 50.f;
	Sphere_Trans.fY = 50.f;
	Sphere_Trans.fZ = 0.0f;
	//////////////////////////////////
	Sphere_Trus_Rotate.fX = 0.0f;
	Sphere_Trus_Rotate.fY = 0.0f;
	Sphere_Trus_Rotate.fZ = 0.0f;
	Sphere_Trus_RotatePlus.fX = 10.f;
	Sphere_Trus_RotatePlus.fY = 10.f;
	Sphere_Trus_RotatePlus.fZ = 10.f;
	Sphere_Trus_Trans.fX = 75.f;
	Sphere_Trus_Trans.fY = 0.f;
	Sphere_Trus_Trans.fZ = 0.0f;

	//////////

	Trus_Rotate.fX = 0.0f;
	Trus_Rotate.fY = 0.0f;
	Trus_Rotate.fZ = 0.0f;
	Trus_RotatePlus.fX = 10.f;
	Trus_RotatePlus.fY = 10.f;
	Trus_RotatePlus.fZ = 10.f;
	Trus_Trans.fX = 50.f;
	Trus_Trans.fY = 50.f;
	Trus_Trans.fZ = 50.f;
}

void TimerFunc(int value)
{
	Cube_Rotate.fY += Cube_RotatePlus.fY;
	Sphere_Rotate.fX += Sphere_RotatePlus.fX;
	Sphere_Trus_Rotate.fZ += Sphere_Trus_RotatePlus.fZ;

	glutPostRedisplay();
	glutTimerFunc(50, TimerFunc, 1);
}

void Rect()
{
	glColor3f(0.0, 1.0, 1.0);
	glRotatef(Cube_Rotate.fY, 0.0f, 1.0f, 0.0f);
	glTranslatef(Cube_Trans.fX, Cube_Trans.fY, Cube_Trans.fZ);
	glutSolidCube(50);
}

void Sphere()
{
	glColor3f(1.0, 0.0, 1.0);
	glRotatef(Sphere_Rotate.fX, 1.0f, 0.0f, 0.0f);
	glTranslatef(Sphere_Trans.fX, Sphere_Trans.fY, Sphere_Trans.fZ);
	glLineWidth(2);
	glutWireSphere(40, 20, 20);
}

void Sphere_Trus()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(Sphere_Trus_Rotate.fZ, 1.0f, 0.0f, 0.0f);
	glTranslatef(0, 0, 50);
	glLineWidth(2);
	glutWireSphere(20, 15, 15);

	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidTorus(10, 50, 30, 30);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
		idistance += 10;
	if (key == '-')
		idistance -= 10;
	 
	if (key == 'y')
	{
		fRotate_Y += fRotate_Plus_Y;
	}
	else if (key == 'Y')
	{
		fRotate_Y -= fRotate_Plus_Y;
	}
	else if (key == '1')
	{
		if (bLight == false)
			bLight = true;
		else if (bLight == true)
			bLight = false;
	}

}