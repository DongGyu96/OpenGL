#pragma warning(disable : 4996)
#include <gl/glut.h>
#include <stdio.h>
#include <Windows.h>

GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void MyMainMunu(int entryID);
void Menu();
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

float angle = 0;
bool UpQuad = true;

GLuint textures[5]; // �ؽ�ó �̸�

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�


																			  // �ؽ�ó�� ��ü�� ����
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
		glBegin(GL_QUADS); {//����
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
		glBegin(GL_QUADS); {//������
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
		glBegin(GL_QUADS); {//����
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

		glBegin(GL_QUADS); {//��
			glVertex3f(-50, -50, -50);
			glVertex3f(50, -50, -50);
			glVertex3f(50, -50, 50);
			glVertex3f(-50, -50, 50);
		}
		glEnd();


		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glBegin(GL_QUADS); {//��
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
	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� �R��ȭ
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
	glutAddSubMenu("��������", SubMenu1);
	glutAddSubMenu("�ø�", SubMenu2);
	glutAddSubMenu("���̵�", SubMenu3);
	glutAddSubMenu("����", SubMenu4);
	glutAddSubMenu("�ո�", SubMenu5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

