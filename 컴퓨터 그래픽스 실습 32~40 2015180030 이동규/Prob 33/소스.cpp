#include <gl/glut.h> 
#include <math.h>
#include <iostream>
#include <time.h>
using namespace std;

#define PI 3.14
#define Move 2
#define RANGE 90
bool bButton[4];

typedef struct position
{
	int x;
	int y;
	int z;
}Pos;
Pos tPos[3][RANGE];

//void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
GLvoid DrawLine()
{
	glColor3f(1, 1, 1);

}
//앞왼 앞오 뒤오 뒤왼 






int xUp = 0;
int zUp = 0;

int ivalue = 1;
int yRotate = 0;
int xRotate = 0;
int tire_rotate = 0;

bool Left_Jump = false;
bool Mid_State = false;
bool RIght_Jump = false;
int zRotate = 0;
int Add_Xpos = 0;
int Add_Ypos = 0;
int Distance_Z = 0;

GLfloat AmbientLight[] = { .40f, .40f, .40f, 1.f };
GLfloat DiffuseLight[] = { .4f, .4f, .4f, 1.0f };
GLfloat SpecularLight[] = { 0,0,1, 1.0 };
GLfloat lightPos[] = { 0, 30, 0  , 1.0f };

bool bJump = false;
bool bDown = false;
int iCount = 0;

void Light()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glMaterialf(GL_FRONT, GL_AMBIENT, 64);
	//glMaterialf(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 1);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

}

void DrawScene()
{
	glLoadIdentity();
	gluPerspective(60.0f, 8 / 6, 1.0, -300);
	glPushMatrix();
	Light();
	glPopMatrix();
	glTranslatef(0, 0, -400);



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawLine();




	//glutSolidCube(20);
	glPointSize(10);
	glRotatef(20, 1, 0, 0);
	glRotatef(yRotate, 0, 1, 0);
	glRotatef(xRotate, 1, 0, 0);
	glTranslatef(0, 0, Distance_Z);

	glPushMatrix();
	{

		glBegin(GL_POLYGON);
		{
			glVertex3f(-90, 0, 500);
			glVertex3f(-200, 0, 500);
			glVertex3f(-200, 0, -1000);
			glVertex3f(-90, 0, -1000);
		}
		glEnd();

		glBegin(GL_POLYGON);
		{
			glVertex3f(60, 0, 500);
			glVertex3f(-40, 0, 500);
			glVertex3f(-40, 0, -1000);
			glVertex3f(60, 0, -1000);
		}
		glEnd();

		glBegin(GL_POLYGON);
		{
			glVertex3f(220, 0, 500);
			glVertex3f(100, 0, 500);
			glVertex3f(100, 0, -1000);
			glVertex3f(220, 0, -1000);
		}
		glEnd();


	}
	glEnd();


	//////차
	glPushMatrix();
	{

		//몸통
		glPushMatrix();
		{
			Light();

			glColor3f(1, 1, 0);
			glTranslatef(10 + Add_Xpos, 35 + Add_Ypos, 220);
			glRotatef(zRotate, 0, 0, 1);
			glutSolidCube(30);
		}
		glPopMatrix();
		//바퀴
		glPushMatrix();
		{

			glPushMatrix();
			{
				Light();
				glColor3f(1, 0, 0);
				if (!bDown) {
					glTranslatef(0 + Add_Xpos, 10 + Add_Ypos, 210);
					glRotatef(tire_rotate, 1, 0, 0);
					//glutWireSphere(10, 10, 10);
					glutSolidSphere(10, 10, 10);
				}
			}
			glPopMatrix();

			glPushMatrix();
			{
				glColor3f(1, 0, 0);
				Light();
				if (!bDown) {
					glTranslatef(20 + Add_Xpos, 10 + Add_Ypos, 210);
					glRotatef(tire_rotate, 1, 0, 0);
					glutSolidSphere(10, 10, 10);
				}
			}
			glPopMatrix();


			glPushMatrix();
			{
				glColor3f(1, 0, 0);
				Light();
				if (!bDown)
				{

					glTranslatef(0 + Add_Xpos, Add_Ypos + 10, 230);
					glRotatef(tire_rotate, 1, 0, 0);
					glutSolidSphere(10, 10, 10);
				}
			}
			glPopMatrix();


			glPushMatrix();
			{
				glColor3f(1, 0, 0);
				Light();
				if (!bDown)
				{
					glTranslatef(20 + Add_Xpos, 10 + Add_Ypos, 230);
					glRotatef(tire_rotate, 1, 0, 0);
					glutSolidSphere(10, 10, 10);
				}
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();



	glDisable(GL_DEPTH_TEST);
	glFlush(); // 화면에 출력하기
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, w, h);
	glLoadIdentity();
	gluPerspective(60.0f, w / h, 1.0, -300);
	glTranslatef(0, 0, -400);
	//gluLookAt(0, 0, -300, 0, 0,0, 0, 0, 0);
	//gluLookAt(0.0, 10.0, 500.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0

	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);
}

//enum eShape { Spere, Cube, Cone, Teapot };

void SpecialKey(int key, int x, int y)
{
	if (Add_Ypos >= 0)
	{

		if (key == GLUT_KEY_LEFT)
		{
			Add_Xpos -= 10;
		}

		if (key == GLUT_KEY_RIGHT)
		{
			Add_Xpos += 10;
		}
	}
	cout << Add_Xpos << endl;
	glutPostRedisplay();
}

void Timer(int value)
{

	tire_rotate -= 10;
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < RANGE; ++i)
		{
			tPos[j][i].z += 5;
			if (tPos[j][i].z > 500)
				tPos[j][i].z = -1000;
		}
	}

	if (bJump)
	{
		AmbientLight[1] = 1.0f;
		if (Add_Ypos < 100 && iCount != 10)
		{
			zRotate += 10;
			Add_Ypos += 10;
			iCount++;
		}
		else if (iCount == 10)
		{
			zRotate += 10;
			Add_Ypos -= 10;
			if (Add_Ypos == 10)
			{
				bJump = false;
				iCount = 0;
				Add_Ypos = 0;
				zRotate = 0;
				AmbientLight[1] = .4f;
			}
		}

	}

	if ((Add_Xpos > -80 && Add_Xpos < -69) || Add_Xpos<80 && Add_Xpos>69)
		Add_Ypos -= 10;


	glutTimerFunc(100, Timer, ivalue);
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{

	if (key == 'y')
		yRotate += 10;
	if (key == 'Y')
		yRotate -= 10;
	if (key == 'x')
		xRotate += 10;
	if (key == 'X')
		xRotate -= 10;
	if (key == '+')
		Distance_Z += 10;
	if (key == '-')
		Distance_Z -= 10;
	if (key == 'i')
	{
		Add_Xpos = 0;
		Add_Ypos = 0;
		AmbientLight[1] = 0.4f;
		bDown = false;
		bJump = false;
		zRotate = 0;
	}

	if (key == ' ')
		bJump = true;


	glutPostRedisplay();
}

void Initi()
{
	for (int i = 0; i < RANGE; ++i)
	{
		tPos[0][i].x = -(rand() % 90) - 95;
		tPos[0][i].y = 0;
		tPos[0][i].z = -(rand() % 1055) + rand() % 500;
	}

	for (int i = 0; i < RANGE; ++i)
	{
		tPos[1][i].x = (rand() % 85) - 30;
		tPos[1][i].y = 0;
		tPos[1][i].z = -(rand() % 1055) + rand() % 500;
	}

	for (int i = 0; i < RANGE; ++i)
	{
		tPos[2][i].x = (rand() % 110) + 105;
		tPos[2][i].y = 0;
		tPos[2][i].z = -(rand() % 1055) + rand() % 500;
	}




}

void main(int argc, char *argv[])
{
	//초기화 함수들 
	srand(time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	Initi();
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example2");
	glutSpecialFunc(SpecialKey);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, Timer, ivalue);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}