#pragma warning(disable : 4996)
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define SNOW_NUM	20

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장핛 변수

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void Mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
//------------------------------------------------------
void Piramid();
void satellite();
void Make_Light();
void Light();
void Init_snow();

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

GLuint textures[3]; // 텍스처 이름

struct Point {
	float x;
	float y;
	float z;
};

Point t[SNOW_NUM];
int earth_angle = 0;
int moon_angle = 0;
int camera_x = 0, camera_y = 300, camera_z = 800;
bool first_light = false, second_light = false, third_light = false, four_light = false;
int angle = 0;
int angle_cnt = 0;
bool goZ = true;
int aa = -1;

void main(int argc, char *argv[])
{
	Init_snow();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("practice23");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(40, Timerfunction, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	Light();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
	glColor3f(1, 1, 0);

	glRotatef(angle, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	{
		glTexCoord3f(0, 1, 0);
		glVertex3f(300, -100, -300);
		glTexCoord3f(0, 0, 0);
		glVertex3f(-300, -100, -300);
		glTexCoord3f(1, 0, 0);
		glVertex3f(-300, -100, 300);
		glTexCoord3f(1, 1, 0);
		glVertex3f(300, -100, 300);
	}
	glEnd();
	for (int i = 0; i < SNOW_NUM; i++) {
		glPushMatrix();
		{
			glColor3f(1, 1, 1);
			glTranslatef(t[i].x, t[i].y, t[i].z);
			glutSolidCube(10);
		}
		glPopMatrix();
	}
	Piramid();
	satellite();
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
	glGenTextures(3, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	{
		pBytes = LoadDIBitmap("33floor.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	{
		pBytes = LoadDIBitmap("33piramid.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	{
		pBytes = LoadDIBitmap("33sphere.bmp", &info);
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
	if (goZ == true)
		camera_z -= 5;
	if (camera_z == 500 && angle_cnt < 4) {
		goZ = false;
		angle += 5;
		if (angle % 360 == 0)
			angle_cnt++;
	}
	if (angle_cnt == 4 && goZ == false)
		camera_z += 5;
	if (camera_z == 800) {
		goZ = true;
		angle_cnt = 0;
	}
	for (int i = 0; i < SNOW_NUM; i++)
	{
		t[i].y -= 5;
		if (t[i].y < -100)
			t[i].y = 150;
	}
	earth_angle += 5;
	moon_angle += 5;
	glutPostRedisplay();
	glutTimerFunc(40, Timerfunction, 1);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		if (first_light == false) {
			first_light = true;
			printf("first_light = true \n");
			return;
		}
		if (first_light == true) {
			first_light = false;
			printf("first_light = false \n");
			return;
		}
	}
	if (key == '2')
	{
		if (second_light == false) {
			second_light = true;
			printf("second_light = true \n");
			return;
		}
		if (second_light == true) {
			second_light = false;
			printf("second_light = false \n");
			return;
		}
	}
	if (key == '3')
	{
		if (third_light == false) {
			third_light = true;
			printf("third_light = true \n");
			return;
		}
		if (third_light == true) {
			third_light = false;
			printf("third_light = false \n");
			return;
		}
	}
	if (key == '4')
	{
		if (four_light == false) {
			four_light = true;
			printf("four_light = true \n");
			return;
		}
		if (four_light == true) {
			four_light = false;
			printf("four_light = false \n");
			return;
		}
	}

}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT && state == GLUT_DOWN)
	{
	}

}

void Piramid()
{
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);//앞
	{
		glTexCoord2f(0.5, 1.0);
		glVertex3f(100, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(75, -100, 25);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(125, -100, 25);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);//오른쪽
	{
		glTexCoord2f(0.5, 1.0);
		glVertex3f(100, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(125, -100, 25);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(125, -100, -25);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);//왼쪽
	{
		glTexCoord2f(0.5, 1.0);
		glVertex3f(100, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(75, -100, -25);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(75, -100, 25);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);//뒤
	{
		glTexCoord2f(0.5, 1.0);
		glVertex3f(100, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(125, -100, -25);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(75, -100, -25);
	}
	glEnd();
	//-------------------------------------------
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2f(0.5, 1.0);
		glVertex3f(-100, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-125, -100, 25);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-75, -100, 25);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2f(0.5, 1.0);
		glVertex3f(-100, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-75, -100, 25);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-75, -100, -25);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2f(0.5, 1.0);
		glVertex3f(-100, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-125, -100, -25);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-125, -100, 25);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2f(0.5, 1.0);
		glVertex3f(-100, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-75, -100, -25);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-125, -100, -25);
	}
	glEnd();
}

void satellite()
{
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glPushMatrix();
	{
		glTranslatef(100, 0, 0);
		glRotatef(earth_angle, 0, 1, 0);
		glTranslatef(100, 0, 0);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glColor3f(1, 1, 1);
		glutSolidSphere(50, 20, 20);
		glPushMatrix();
		{
			glRotatef(moon_angle, 0, 1, 0);
			glTranslatef(50, 0, 0);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glBindTexture(GL_TEXTURE_2D, textures[2]);
			glColor3f(1, 1, 1);
			glutSolidSphere(25, 20, 20);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-100, 0, 0);
		glRotatef(-earth_angle, 0, 1, 0);
		glTranslatef(100, 0, 0);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glColor3f(1, 1, 1);
		glutSolidSphere(50, 20, 20);
		glPushMatrix();
		{
			glRotatef(-moon_angle, 0, 1, 0);
			glTranslatef(50, 0, 0);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glBindTexture(GL_TEXTURE_2D, textures[2]);
			glColor3f(1, 1, 1);
			glutSolidSphere(25, 20, 20);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void Init_snow()
{
	srand(1000);
	for (int i = 0; i < SNOW_NUM; i++)
	{
		if (rand() % 2 == 0)
			aa *= -1;
		t[i].x = (rand() % 300) * aa;
		t[i].y = (rand() % 150) * aa;
		t[i].z = (rand() % 300) * aa;
	}
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
void Light()
{
	GLfloat AmbientLight[] = { 0.1, 0.1, 0.1, 1.0f };
	GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat DiffuseLight0[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat lightPos0[] = { 300, -100, -300, 1.0 };

	GLfloat DiffuseLight1[] = { 0.5, 1.0, 0.5, 1.0 };
	GLfloat lightPos1[] = { -300, -100, -300, 1.0 };

	GLfloat DiffuseLight2[] = { 0.5, 0.5, 1.0, 1.0 };
	GLfloat lightPos2[] = { -300, -100, 300, 1.0 };

	GLfloat DiffuseLight3[] = { 1.0, 1.0, 0.5, 1.0 };
	GLfloat lightPos3[] = { 300, -100, 300, 1.0 };

	GLfloat specref[] = { 0.0f, 1.0f, 1.0f, 1.0f };

	glEnable(GL_LIGHTING);

	if (first_light == true)
		glEnable(GL_LIGHT0);
	if (first_light == false)
		glDisable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	if (second_light == true)
		glEnable(GL_LIGHT1);
	if (second_light == false)
		glDisable(GL_LIGHT1);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	if (third_light == true)
		glEnable(GL_LIGHT2);
	if (third_light == false)
		glDisable(GL_LIGHT2);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

	if (four_light == true)
		glEnable(GL_LIGHT3);
	if (four_light == false)
		glDisable(GL_LIGHT3);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
}