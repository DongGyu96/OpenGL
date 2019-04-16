#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>

GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

GLuint textures[5]; // �ؽ�ó �̸�

struct Shape
{
	float x;
	float y;
	float z;
	float r;
	float r2;
};

Shape rota = { 0, 0, 0, 0, 0 };
Shape move = { 0, -40, 50, 1 };
Shape direct = { 1, 1, 1, 0 };
Shape scale[6];
Shape sphereP[6];
float zoom = 0;
int input = 1;
int jump = 0;

GLfloat SpotDirect[] = { 0.0, -1.0, 0.0 };
GLfloat SpotCutoff[] = { 30.0 };
GLfloat SpotExponent[] = { 10000.0 };
GLfloat DiffuseLight[] = { 1.0, 1.0, 1.0, 1.0f };
GLfloat lightPos[] = { 0.0, 20.0, 0.0, 1.0 };
GLfloat specref[] = { 0.0, 0.0, 0.0, 1.0 };

void main(int argc, char *argv[])
{   //�ʱ�ȭ �Լ���
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100);    // �������� ��ġ����  
	glutInitWindowSize(800, 600);    // �������� ũ�� ���� 
	glutCreateWindow("Example");    // ������ ���� (������ �̸�)  
	glutDisplayFunc(drawScene);    // ��� �Լ��� ���� 
	glutTimerFunc(100, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, 100);
	glRotatef(rota.r, rota.x, 0.0, 0.0);
	glRotatef(rota.r2, 0.0, rota.y, 0.0);
	glTranslatef(0.0f, 0.0f, -100);
	glPushMatrix();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDirect);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, SpotCutoff);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, SpotExponent);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHT0);

	glPushMatrix();
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	glPushMatrix();
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS); {
		glTexCoord3f(0, 1, 0);
		glVertex3f(-100, -50, 0);
		glTexCoord3f(0, 0, 0);
		glVertex3f(-100, -50, 200);
		glTexCoord3f(1, 0, 0);
		glVertex3f(-100, 50, 200);
		glTexCoord3f(1, 1, 0);
		glVertex3f(-100, 50, 0);
	}
	glEnd();

	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS); {
		glTexCoord3f(0, 1, 0);
		glVertex3f(100, -50, 200);
		glTexCoord3f(0, 0, 0);
		glVertex3f(100, -50, 0);
		glTexCoord3f(1, 0, 0);
		glVertex3f(100, 50, 0);
		glTexCoord3f(1, 1, 0);
		glVertex3f(100, 50, 200);
	}
	glEnd();
	glPopMatrix();


	for (int i = 0; i < 200; i++)
	{
		for (int j = -100; j < 100; j++)
		{
			if ((j >= -100 && j <= -50) || (j <= 25 && j >= -25) || (j <= 100 && j >= 50))
			{
				glPushMatrix();
				glColor3f(1, 1, 1);
				glBindTexture(GL_TEXTURE_2D, textures[0]);
				glBegin(GL_QUADS); {
					glTexCoord3f(0, 1, 0);
					glVertex3f(j + 1, -50.0f, i);
					glTexCoord3f(0, 0, 0);
					glVertex3f(j + 1, -50.0f, i + 1);
					glTexCoord3f(1, 0, 0);
					glVertex3f(j, -50.0f, i + 1);
					glTexCoord3f(1, 1, 0);
					glVertex3f(j, -50.0f, i);
				}
				glEnd();
				glPopMatrix();
			}
		}
	}
	glDisable(GL_CULL_FACE);
	glPopMatrix();
	glColor4f(0.0, 0.0, 1.0, 0.0);
	glTranslatef(move.x, move.y + 5, move.z);
	glRotatef(move.r2 * 2, 0.0, 0.0, 1.0);

	glutSolidCube(15);
	glColor4f(0.0, 1.0, 0.0, 0.0);

	glTranslatef(5.0, -10.0, 0.0);
	glutSolidSphere(3, 12, 12);
	glTranslatef(-10.0, 0.0, 0.0);
	glutSolidSphere(3, 12, 12);
	glPopMatrix();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0, 800.0f / 600.0f, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -100.0);

	gluLookAt
	(
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glGenTextures(5, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	{
		pBytes = LoadDIBitmap("brick.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	{
		pBytes = LoadDIBitmap("brick2.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	{
		pBytes = LoadDIBitmap("brick3.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	{
		pBytes = LoadDIBitmap("brick4.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	{
		pBytes = LoadDIBitmap("brick5.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
	glEnable(GL_TEXTURE_2D);
}

void TimerFunction(int value)
{
	if (move.z < -10)
	{
		direct.z = 1;
	}
	else if (move.z > 180)
	{
		direct.z = -1;
	}
	move.z += 3 * direct.z;

	lightPos[0] = move.x;
	lightPos[2] = move.z;

	if (jump == 1)
	{
		move.x += 3.5 * direct.x;
		move.r += 1;
		move.y += move.r;
		move.r2 += 10 * direct.x;

		if (move.r == 10)
		{
			jump = 2;
			move.r = 0;
		}
	}

	if (jump == 2)
	{
		move.y -= move.r;
		move.r += 1;
		move.x += 3.5 * direct.x;
		move.r2 += 10 * direct.x;

		if (move.r == 10 && move.x > -100 && move.x < 100)
		{
			jump = 0;
			move.r = 0;
			move.r2 = 0;
			move.y = -40;
		}
	}
	glutPostRedisplay();   // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����  
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'z')
	{
		zoom++;
	}
	else if (key == 'Z')
	{
		zoom--;
	}
	else if (key == 'i' || key == 'I')
	{
		rota.r = 0;
		rota.r2 = 0;
		rota.x = 0;
		rota.y = 0;
	}
	else if (key == 'x')
	{
		rota.r--;
		rota.x = 1;
	}
	else if (key == 'X')
	{
		rota.r++;
		rota.x = 1;
	}
	else if (key == 'y')
	{
		rota.r2--;
		rota.y = 1;
	}
	else if (key == 'Y')
	{
		rota.r2++;
		rota.y = 1;
	}
	else if (key == 'P')
	{
		lightPos[1] += 1;
	}
	else if (key == 'p')
	{
		lightPos[1] -= 1;
	}
	else if (key == 'a' || key == 'A')
	{
		if (jump == 0)
		{
			for (int i = 0; i < 3; ++i)
			{
				DiffuseLight[i] = rand() % 2 + 1;
			}
			jump = 1;
			direct.x = 1;
		}
	}
	else if (key == 'd' || key == 'D')
	{
		if (jump == 0)
		{
			for (int i = 0; i < 3; ++i)
			{
				DiffuseLight[i] = rand() % 2 + 1;
			}
			jump = 1;
			direct.x = -1;
		}
	}
	else if (key == '1')
	{
		if (input == 1)
			input = 0;
		else
			input = 1;
	}
	else if (key == 'q' || key == 'Q')
	{
		exit(0);
	}
	glutPostRedisplay();
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	//���̳ʸ� �б� ���� ������ ����.
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	//��Ʈ�� ���� ��带 �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	//������ BMP�������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	//BITMAPINFOHEADER ��ġ�� ����.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	//��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	//��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	//��Ʈ�� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth) *
		((*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);

	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� ��������.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� ��������.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}
