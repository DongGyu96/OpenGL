#pragma warning(disable : 4996)
#include <gl/glut.h>
#include <stdio.h>
#include <Windows.h>

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장핛 변수

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void MyMainMunu(int entryID);
void Menu();
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

float angle = 0;
bool UpQuad = true;

GLuint textures[5]; // 텍스처 이름

void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);


	glutCreateWindow("Practice19");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	Menu();
	glutTimerFunc(40, Timerfunction, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기


																			  // 텍스처를 객체에 맵핑
	glPushMatrix();
	{
		glRotatef(30, 1, 0, 0);
		glRotatef(45 + angle, 0, 1, 0);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBegin(GL_QUADS); {
			glTexCoord3f(0, 1, 0);
			glVertex3f(-50, 50, 50);
			glTexCoord3f(0, 0, 0);
			glVertex3f(-50, -50, 50);
			glTexCoord3f(1, 0, 0);
			glVertex3f(50, -50, 50);
			glTexCoord3f(1, 1, 0);
			glVertex3f(50, 50, 50);
		}
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glBegin(GL_QUADS); {//왼쪽
			glTexCoord3f(0, 1, 0);
			glVertex3f(50, 50, 50);
			glTexCoord3f(0, 0, 0);
			glVertex3f(50, -50, 50);
			glTexCoord3f(1, 0, 0);
			glVertex3f(50, -50, -50);
			glTexCoord3f(1, 1, 0);
			glVertex3f(50, 50, -50);
		}
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glBegin(GL_QUADS); {//오른쪽
			glTexCoord3f(0, 1, 0);
			glVertex3f(-50, 50, -50);
			glTexCoord3f(0, 0, 0);
			glVertex3f(-50, -50, -50);
			glTexCoord3f(1, 0, 0);
			glVertex3f(-50, -50, 50);
			glTexCoord3f(1, 1, 0);
			glVertex3f(-50, 50, 50);

		}
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glBegin(GL_QUADS); {//뒷쪽
			glTexCoord3f(1, 1, 0);
			glVertex3f(-50, 50, -50);
			glTexCoord3f(0, 1, 0);
			glVertex3f(50, 50, -50);
			glTexCoord3f(0, 0, 0);
			glVertex3f(50, -50, -50);
			glTexCoord3f(1, 0, 0);
			glVertex3f(-50, -50, -50);
		}
		glEnd();

		glBegin(GL_QUADS); {//밑
			glVertex3f(-50, -50, -50);
			glVertex3f(50, -50, -50);
			glVertex3f(50, -50, 50);
			glVertex3f(-50, -50, 50);
		}
		glEnd();


		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glBegin(GL_QUADS); {//위
			glTexCoord3f(0, 1, 0);
			glVertex3f(-50, 50, -50);
			glTexCoord3f(0, 0, 0);
			glVertex3f(-50, 50, 50);
			glTexCoord3f(1, 0, 0);
			glVertex3f(50, 50, 50);
			glTexCoord3f(1, 1, 0);
			glVertex3f(50, 50, -50);
		}
		glEnd();
	}
	glPopMatrix();
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	gluLookAt(0.0, 30, 300.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
	glGenTextures(5, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	{
		pBytes = LoadDIBitmap("front.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	{
		pBytes = LoadDIBitmap("left.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	{
		pBytes = LoadDIBitmap("right.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	{
		pBytes = LoadDIBitmap("back.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	{
		pBytes = LoadDIBitmap("up.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 홗성화
	glEnable(GL_TEXTURE_2D);
}

void Timerfunction(int value)
{
	angle += 0.5;
	glutPostRedisplay();
	glutTimerFunc(40, Timerfunction, 1);
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


void MyMainMunu(int entryID)
{
	if (entryID == 1)
	{
		glEnable(GL_DEPTH_TEST);
	}
	if (entryID == 2)
	{
		glDisable(GL_DEPTH_TEST);
	}
	if (entryID == 3)
	{
		glEnable(GL_CULL_FACE);
	}
	if (entryID == 4)
	{
		glDisable(GL_CULL_FACE);
	}
	if (entryID == 5)
	{
		glShadeModel(GL_FLAT);
	}
	if (entryID == 6)
	{
		glShadeModel(GL_SMOOTH);
	}
	if (entryID == 7)
	{
		UpQuad = true;
	}
	if (entryID == 8)
	{
		UpQuad = false;
	}
	if (entryID == 9)
	{
		glFrontFace(GL_CCW);
	}
	if (entryID == 10)
	{
		glFrontFace(GL_CW);
	}
}

void Menu()
{
	int SubMenu1, SubMenu2, SubMenu3, SubMenu4, SubMenu5;
	int MainMenu;
	SubMenu1 = glutCreateMenu(MyMainMunu);
	glutAddMenuEntry("ON", 1);
	glutAddMenuEntry("OFF", 2);

	SubMenu2 = glutCreateMenu(MyMainMunu);
	glutAddMenuEntry("ON", 3);
	glutAddMenuEntry("OFF", 4);

	SubMenu3 = glutCreateMenu(MyMainMunu);
	glutAddMenuEntry("flat", 5);
	glutAddMenuEntry("smooth", 6);

	SubMenu4 = glutCreateMenu(MyMainMunu);
	glutAddMenuEntry("ON", 7);
	glutAddMenuEntry("OFF", 8);

	SubMenu5 = glutCreateMenu(MyMainMunu);
	glutAddMenuEntry("ON", 9);
	glutAddMenuEntry("OFF", 10);

	MainMenu = glutCreateMenu(MyMainMunu);
	glutAddSubMenu("은면제거", SubMenu1);
	glutAddSubMenu("컬링", SubMenu2);
	glutAddSubMenu("쉐이딩", SubMenu3);
	glutAddSubMenu("윗면", SubMenu4);
	glutAddSubMenu("앞면", SubMenu5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

