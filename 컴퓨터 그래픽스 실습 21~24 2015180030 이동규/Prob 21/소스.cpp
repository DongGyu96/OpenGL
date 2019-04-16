#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
void MenuFunc(int button);

int MainWindow;
float Angle_Y = 45.f;
float Angle_Top = 0.f;
float Angle_Front = 0.f;
int Top_type = 0;
int Front_type = 0;
bool Shading = true;
bool Culling = false;
bool Depth = true;

void main()
{
	int SubMenu1, SubMenu2, SubMenu3, SubMenu4, SubMenu5; 
	int MainMenu;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	MainWindow = glutCreateWindow("Computer Graphics OpenGL");
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(KeyBoard);
	glutReshapeFunc(Reshape);

	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Flat", 1);
	glutAddMenuEntry("Smooth", 2);
	SubMenu2 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 3);
	glutAddMenuEntry("Off", 4);
	SubMenu3 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 5);
	glutAddMenuEntry("Off", 6);
	SubMenu4 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Open", 7);
	glutAddMenuEntry("Close", 8);
	SubMenu5 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Open", 9);
	glutAddMenuEntry("Close", 10);

	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Shading", SubMenu1);
	glutAddSubMenu("Depth", SubMenu2);
	glutAddSubMenu("Culling", SubMenu3);
	glutAddSubMenu("Top", SubMenu4);
	glutAddSubMenu("Front", SubMenu5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}


GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glTranslatef(0.f, -100.f, -500.f);
		glRotatef(30.f, 1.f, 0.f, 0.f);
		glRotatef(Angle_Y, 0.f, 1.f, 0.f);
		glFrontFace(GL_CCW);

		if(Shading)
			glShadeModel(GL_SMOOTH);
		else
			glShadeModel(GL_FLAT);

		if (Depth)
			glEnable(GL_DEPTH_TEST);

		if (Culling)
			glEnable(GL_CULL_FACE);

		glPushMatrix(); // À­¸é
			glTranslatef(0.f, 200.f, -200.f);
			glRotatef(Angle_Top * -1, 1.f, 0.f, 0.f);
			glBegin(GL_QUADS);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f(200.f, 0.f, 0.f);
				glColor3f(1.0f, 1.0f, 0.0f);
				glVertex3f(-200.f, 0.f, 00.f);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(-200.f, 0.f, 400.f);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(200.f, 0.f, 400.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // ¿ÞÂÊ¸é
			glTranslatef(-200.f, 0.f, 0.f);
			glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(0.f, 200.f, 200.f);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f(0.f, 200.f, -200.f);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(0.f, -200.f, -200.f);
				glColor3f(0.0f, 1.0f, 1.0f);
				glVertex3f(0.f, -200.f, 200.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // ¹Ø¸é
			glTranslatef(0.f, -200.f, 0.f);
			glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(200.f, 0.f, -200.f);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f(-200.f, 0.f, -200.f);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(-200.f, 0.f, 200.f);
				glColor3f(1.0f, 1.0f, 0.0f);
				glVertex3f(200.f, 0.f, 200.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // ¿À¸¥ÂÊ¸é
			glTranslatef(200.f, 0.f, 0.f);
			glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(0.f, 200.f, 200.f);
				glColor3f(1.0f, 1.0f, 0.0f);
				glVertex3f(0.f, -200.f, 200.f);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(0.f, -200.f, -200.f);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f(0.f, 200.f, -200.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // ¾Õ¸é
			glTranslatef(0.f, -200.f, 200.f);
			glRotatef(Angle_Front, 1.f, 0.f, 0.f);
			glBegin(GL_QUADS);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(200.f, 400.f, 0.f);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(-200.f, 400.f, 0.f);
				glColor3f(0.0f, 1.0f, 1.0f);
				glVertex3f(-200.f, 0.f, 0.f);
				glColor3f(1.0f, 0.0f, 1.0f);
				glVertex3f(200.f, 0.f, 0.f);
			glEnd();
		glPopMatrix();

		glPushMatrix(); // µÞ¸é
			glTranslatef(0.f, 0.f, -200.f);
			glBegin(GL_QUADS);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f(200.f, 200.f, 0.f);
				glColor3f(0.0f, 1.0f, 1.0f);
				glVertex3f(200.f, -200.f, 0.f);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(-200.f, -200.f, 0.f);
				glColor3f(1.0f, 1.0f, 0.0f);
				glVertex3f(-200.f, 200.f, 0.f);
			glEnd();
		glPopMatrix();

		if (Depth)
			glDisable(GL_DEPTH_TEST);

		if (Culling)
			glDisable(GL_CULL_FACE);

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
	if (Top_type == 1)
	{
		if (Angle_Top <= 85.f)
			Angle_Top += 5.f;
		else
			Top_type = 0;
	}
	else if (Top_type == 2)
	{
		if (Angle_Top >= 5.f)
			Angle_Top -= 5.f;
		else
			Top_type = 0;
	}

	if (Front_type == 1)
	{
		if (Angle_Front <= 85.f)
			Angle_Front += 5.f;
		else
			Front_type = 0;
	}
	else if (Front_type == 2)
	{
		if (Angle_Front >= 5.f)
			Angle_Front -= 5.f;
		else
			Front_type = 0;
	}
	//Angle_Y += 5.f;
	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') // Á¾·á
	{
		glutDestroyWindow(MainWindow);
		exit(0);
	}
	else if (key == 'd')
		Angle_Y += 5.f;
}

void MenuFunc(int button)
{
	switch (button) {
	case 1:
		Shading = true;
		break;
	case 2:
		Shading = false;
		break;
	case 3:
		Depth = true;
		break;
	case 4:
		Depth = false;
		break;
	case 5:
		Culling = true;
		break;
	case 6:
		Culling = false;
		break;
	case 7:
		Top_type = 1;
		break;
	case 8:
		Top_type = 2;
		break;
	case 9:
		Front_type = 1;
		break;
	case 10:
		Front_type = 2;
		break;
	}
}