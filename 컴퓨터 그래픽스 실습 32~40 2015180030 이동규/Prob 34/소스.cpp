#include <gl/glut.h> 
#include <math.h>
#include <iostream>
#include <time.h>
using namespace std;

#define PI 3.14
#define Move 2
#define RANGE 50
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

GLfloat AmbientLight[] = { 1,1,1, 1.f };
GLfloat DiffuseLight[] = { 1,0,0, 1 };
GLfloat SpecularLight[] = { 1,1,1, 1.0 };
GLfloat lightPos[] = { -150, 80, 450 , 1.0f };
GLfloat specref[] = { 1,1,1,1 };
bool bJump = false;
bool bDown = false;
int iCount = 0;

int light = 70;
int Add_ZPos = 0;
int Paricle_value;
GLfloat ctrlpoints[3][3][3] = { { { -20, 0.0, 400.0 },{ -20, 0.0, 400.0 },{ 100, 0.0, 400.0 } },
{ { -20, 0.0, 0.0 },{ -20, 0.0, 0.0 },{ 100, 0.0, 0.0 } },
{ { -20, 0.0, -900.0 },{ -20, 0.0, -900.0 },{ 100, 0.0, -900.0 } } };

GLfloat ctrlpoints1[3][3][3] = { { { -180, 0.0, 400.0 },{ -180, 0.0, 400.0 },{ -60, 0.0, 400.0 } },
{ { -180, 0.0, 0.0 },{ -180, 0.0, 0.0 },{ -60, 0.0, 0.0 } },
{ { -180, 0.0, -900.0 },{ -180, 0.0, -900.0 },{ -60, 0.0, -900.0 } } };

GLfloat ctrlpoints2[3][3][3] = { { { 150, 0.0, 400.0 },{ 150, 0.0, 400.0 },{ 270, 0.0, 400.0 } },
{ { 150, 0.0, 0.0 },{ 150, 0.0, 0.0 },{ 270, 0.0, 0.0 } },
{ { 150, 0.0, -900.0 },{ 150, 0.0, -900.0 },{ 270, 0.0, -900.0 } } };

bool bMakeCar = true;
void Light()
{
	glPushMatrix();
	glLightf(GL_LIGHT0, GL_SPOT_DIRECTION, (0, -1, 0));
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 4);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glPopMatrix();
}

void Check_Collision()
{
	if (Add_Xpos<50 && Add_Xpos > -10 && Add_Ypos <= 0 && Add_ZPos == -150)
	{
		Paricle_value = 1;
		bMakeCar = false;
	}
	if (Add_Xpos>-10 && Add_Xpos < -90 && Add_Ypos <= 0 && Add_ZPos == -355)
	{
		Paricle_value = 0;
		bMakeCar = false;
	}
	if (Add_Xpos<250 && Add_Xpos > 100 && Add_Ypos <= 0 && Add_ZPos == -555)
	{
		Paricle_value = 2;
		bMakeCar = false;
	}

}

void DrawScene()
{
	glLoadIdentity();
	gluPerspective(60.0f, 8 / 6, 1.0, -300);
	glTranslatef(0, -150, -600);

	Check_Collision();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glutSolidCube(20);
	glPointSize(10);

	glRotatef(yRotate, 0, 1, 0);
	glRotatef(xRotate, 1, 0, 0);
	glTranslatef(0, 0, Distance_Z);

	Light();

	glBegin(GL_POLYGON);
	glVertex3f(150, 50, -350);
	glVertex3f(270 , 50, -350);
	glVertex3f(270, -50, -350);
	glVertex3f(150, -50, -350);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-60, 50, -150);
	glVertex3f(-180, 50, -150);
	glVertex3f(-180, -50, -150);
	glVertex3f(-60, -50, -150);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(90, 50, 50);
	glVertex3f(-20, 50, 50);
	glVertex3f(-20, -50, 50);
	glVertex3f(90, -50, 50);
	glEnd();


	glPushMatrix();
	{

		glColor3f(0.3, 0.3, 0.4);
		// 곡면 제어점 설정
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결
		glEvalMesh2(GL_FILL, 0, 10, 0, 10);
		glPointSize(2.0); glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				glVertex3fv(ctrlpoints[i][j]);
		glEnd();
		//////
		glColor3f(0.3, 0.3, 0.4);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints1[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		glEvalMesh2(GL_FILL, 0, 10, 0, 10);
		glPointSize(2.0); glColor3f(0.0, 0.0, 1.0);
		glEvalMesh2(GL_FILL, 0, 10, 0, 10);
		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				glVertex3fv(ctrlpoints1[i][j]);

		glEnd();

		//////
		glColor3f(0.3, 0.3, 0.4);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints2[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		glEvalMesh2(GL_FILL, 0, 10, 0, 10);
		glPointSize(2.0); glColor3f(0.0, 0.0, 1.0);
		glEvalMesh2(GL_FILL, 0, 10, 0, 10);
		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				glVertex3fv(ctrlpoints2[i][j]);

		glEnd();
	}
	glPopMatrix();


	//////차를 만들어보자.
	if (bMakeCar)
	{
		glPushMatrix();
		{
			//몸ㅁ통
			glPushMatrix();
			{
				glPushMatrix();
				glTranslatef(10 + Add_Xpos, 35 + Add_Ypos, 220 + Add_ZPos);
				//glRotatef(zRotate, 0, 1, 0);
				glColor3f(1, 1, 0);
				glutSolidCube(30);



				/*glPushMatrix();
				glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
				glColor3f(1, 1, 1);
				glutSolidCube(10);
				glPopMatrix();*/
				glPopMatrix();

			}
			glPopMatrix();

			//바퀴들
			glPushMatrix();
			{
				glPushMatrix();
				{
					glColor3f(1, 0, 0);
					if (!bDown) {
						glTranslatef(0 + Add_Xpos, 10 + Add_Ypos, 210 + Add_ZPos);
						//glRotatef(tire_rotate, 1, 0, 0);
						//glutWireSphere(10, 10, 10);
						glutSolidSphere(10, 10, 10);
					}
				}
				glPopMatrix();

				glPushMatrix();
				{
					glColor3f(1, 0, 0);
					if (!bDown) {
						glTranslatef(20 + Add_Xpos, 10 + Add_Ypos, 210 + Add_ZPos);
						//glRotatef(tire_rotate, 1, 0, 0);
						glutSolidSphere(10, 10, 10);
					}
				}
				glPopMatrix();


				glPushMatrix();
				{
					glColor3f(1, 0, 0);
					if (!bDown)
					{

						glTranslatef(0 + Add_Xpos, Add_Ypos + 10, 230 + Add_ZPos);
						//glRotatef(tire_rotate, 1, 0, 0);
						glutSolidSphere(10, 10, 10);
					}
				}
				glPopMatrix();


				glPushMatrix();
				{
					glColor3f(1, 0, 0);
					if (!bDown)
					{
						glTranslatef(20 + Add_Xpos, 10 + Add_Ypos, 230 + Add_ZPos);
						//glRotatef(tire_rotate, 1, 0, 0);
						glutSolidSphere(10, 10, 10);
					}
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (!bMakeCar)
	{

		glPushMatrix();
		{
			glColor3f(1, 1, 0);
			for (int i = 0; i < RANGE; ++i)
			{
				glPushMatrix();
				{
					glTranslatef(tPos[Paricle_value][i].x, tPos[Paricle_value][i].y, tPos[Paricle_value][i].z);
					glutSolidCube(10);
				}
				glPopMatrix();
			}

		}
		glPopMatrix();
	}
	//   glDisable(GL_DEPTH_TEST);
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
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);
}

//enum eShape { Spere, Cube, Cone, Teapot };

void SpecialKey(int key, int x, int y)
{
	if (Add_Ypos >= 0)
	{
		if (key == GLUT_KEY_LEFT)
		{
			Add_Xpos -= 10;
			lightPos[0] -= 10;
		}
		if (key == GLUT_KEY_RIGHT)
		{
			Add_Xpos += 10;
			lightPos[0] += 10;
		}
	}
	cout << Add_ZPos << endl;
	glutPostRedisplay();
}
/*
lightPos[] = { -25, 30,25,1.0f };
lightPos2[] = { 25,30,25, 1.0f };
lightPos3[] = { -25,30,-25,1.0f };
lightPos4[] = { 25,30,-25, 1.0f };

*/
void Timer(int value)
{
	if (bMakeCar)
	{
		Add_ZPos -= 5;
		lightPos[2] -=5;
	}
	if (!bMakeCar)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int i = 0; i < RANGE; ++i)
			{
				tPos[j][i].y -= rand() % 6 + 4;
			}
		}
	}


	tire_rotate -= 10;

	if (bJump)
	{
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
			}
		}

	}

	if ((Add_Xpos > -80 && Add_Xpos < -69) || Add_Xpos < 80 && Add_Xpos>69)
		Add_Ypos -= 10;


	glutTimerFunc(100, Timer, ivalue);
	glutPostRedisplay();
}

void Initi()
{
	for (int i = 0; i < RANGE; ++i)
	{
		tPos[0][i].x = -(rand() % 30) - 100;
		tPos[0][i].y = (rand() % 30) + 5;
		tPos[0][i].z = -130 + i*(0.5);
	}

	for (int i = 0; i < RANGE; ++i)
	{
		tPos[1][i].x = (rand() % 50) + 20;
		tPos[1][i].y = (rand() % 30) + 5;
		tPos[1][i].z = 60 + i*(0.5);
	}

	for (int i = 0; i < RANGE; ++i)
	{
	tPos[2][i].x = (rand() % 45) + 185;
	tPos[2][i].y = (rand() % 30) + 5;
	tPos[2][i].z = -350 + i*(0.5);
	}
	
	bMakeCar = true;
	lightPos[2] = 450;
	Add_ZPos = 0;
	Add_Xpos = 0;

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
		Initi();
		Add_Xpos = 0;
		Add_Ypos = 0;
		AmbientLight[1] = 0.4f;
		bDown = false;
		zRotate = 0;
		bJump = false;
	}

	if (key == ' ')
		bJump = true;

	if (key == 'a' || key == 'A')
		light += 5;
	if (key == 's' || key == 'S')
		light -= 5;

	cout << light << endl;
	glutPostRedisplay();
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