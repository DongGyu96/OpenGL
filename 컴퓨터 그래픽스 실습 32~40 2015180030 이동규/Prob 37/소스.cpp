#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

GLuint textures[5]; // 텍스처 이름

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
{   //초기화 함수들
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정  
	glutInitWindowSize(800, 600);    // 윈도우의 크기 지정 
	glutCreateWindow("Example");    // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(drawScene);    // 출력 함수의 지정 
	glutTimerFunc(100, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수 
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
	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
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
	glutPostRedisplay();   // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정  
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

	//바이너리 읽기 모드로 파일을 연다.
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	//비트맵 파일 헤드를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	//파일이 BMP파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	//BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	//비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	//비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	//비트맵 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth) *
		((*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 핛당핚다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장핚다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}
