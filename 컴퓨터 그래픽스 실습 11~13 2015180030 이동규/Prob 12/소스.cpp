#include <gl/glut.h>
#include <math.h>
#include <Windows.h>
#include <stdio.h>
#define CIRCLE 0
#define SIN 1
#define TORNADO 2
#define ZIGZAG 3
#define CUSTOM 4
#define PI 3.141592/180.0
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);

int MainWindow;
int Type = CIRCLE;
bool Track = false; // ��θ� ����׸�����, �׳� �׸�����
bool Shape = true; // �ﰢ��,�簢��
bool Expand = true; // ����
bool Reverse = false; // ������ ���������� �ݴ�� �����̰�
bool Draw = false; // ���콺�� �� �׸���
float Scaling = 1.0f; // Ȯ��/���
float angle = 0.0f; // CIRCLE�̳� TORNADO�ϰ�쿡 ���� ������
float fx = 0.0f;
float fy = 0.0f;
float size = 0.07f; // �����̴� ������ ũ��
float Tornado_r = 0.0f; // ȸ���� ������
float Sin_x = -0.85f; // Sin�������� �����϶� ó�� ������
float Sin_angle = 0.0f; // Sin_x������ ����
float Zigzag_x = -0.85f;
float Zigzag_y = 0.0f;
int Zigzag_type = 0;
int Mouse_count = 0; // ���� � �׷Ǵ��� ī��Ʈ
float Mouse_move_x, Mouse_move_y; // CUSTOM ���¿����� ���� �������� ���
float Mouse_x[5], Mouse_y[5]; // 5�� Ŭ��, 4���� �� ����
float Mouse_speed_x[4], Mouse_speed_y[4]; // �� ���鿡���� ���ǵ尪
int Mouse_type = 0; // ù��°�� , �ι�°��, ����°��, �׹�°���� ��� ���� �����ϰ���
float Mouse_angle[4]; // �� ������ ������

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	MainWindow = glutCreateWindow("Computer Graphics OpenGL");
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}


GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix(); // X,Y��
		glBegin(GL_LINES);
		glVertex2f(-1.0, 0.0);
		glVertex2f(1.0, 0.0);
		glVertex2f(0.0, -1.0);
		glVertex2f(0.0, 1.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();//for(int y  =  {
		glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
		if (Type == CIRCLE) // �����
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 360; ++i)
			{
				glVertex2f(cosf(i * PI) * 0.7f, sinf(i*PI) * 0.7f);
			}
			glEnd();
		}
		else if (Type == SIN) // ���ΰ
		{
			glBegin(GL_LINE_STRIP);
			float x = -0.85f;
			for (int i = 0; i < 1441; ++i)
			{
				glVertex2f(x, sinf(i*PI) * 0.3f);
				x += 0.0012f;
			}
			glEnd();
		}
		else if (Type == TORNADO) // ȸ����
		{
			glBegin(GL_LINE_STRIP);
			float r = 0.f;
			for (int i = 0; i < 1080; ++i)
			{
				glVertex2f(cosf(i * PI) * r, sinf(i*PI) * r);
				r += 0.0008f;
			}
			glEnd();
		}
		else if (Type == ZIGZAG) // �������
		{
			glBegin(GL_LINE_STRIP);
			float y = 0.0f;
			for (float x = -0.85f; x < -0.5f; x += 0.003f)
			{
				glVertex2f(x, y);
				y += 0.003f;
			}
			y = 0.35f;
			for (float x = -0.5f; x < 0.0f; x += 0.003f)
			{
				glVertex2f(x, y);
				y -= 0.003f;
			}
			y = -0.15f;
			for (float x = 0.0f; x < 0.5f; x += 0.003f)
			{
				glVertex2f(x, y);
				y += 0.003f;
			}
			y = 0.35f;
			for (float x = 0.5f; x < 0.85f; x += 0.003f)
			{
				glVertex2f(x, y);
				y -= 0.003f;
			}
			glEnd();
		}
		else if (Type == CUSTOM) // ���콺�� ���׸���
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < Mouse_count; ++i)
			{
				glVertex2f(Mouse_x[i], Mouse_y[i]);
			}
			glEnd();
		}
		
		glPushMatrix();
			if(Type == CIRCLE) // ������϶��� ���� ��ǥ
				glTranslatef(cosf(angle  * PI) * 0.7f, sinf(angle * PI) * 0.7f, 0.0f);
			else if(Type == SIN) // ����
				glTranslatef(Sin_x, sinf(angle * PI) * 0.3f, 0.0f);
			else if(Type == TORNADO) // ȸ����
				glTranslatef(cosf(angle * PI) * Tornado_r, sinf(angle * PI) * Tornado_r, 0.0f);
			else if(Type == ZIGZAG) // �������
				glTranslatef(Zigzag_x, Zigzag_y, 0.0f);
			else if(Type == CUSTOM) // ���콺�� ���׸���
				if(!Draw) // ���׸��Ⱑ ��������� ������ ���������� ��ġ��Ų�� �����̰���
					glTranslatef(Mouse_move_x, Mouse_move_y, 0.0f);

			glScalef(Scaling, Scaling, 0.0f); // Ȯ��/��ҵǰ�
			if (Shape) // �ﰢ/�簢
			{
				if (Track)
				{
					if (Type == ZIGZAG)
					{
						if (Reverse)
						{
							if (Zigzag_type == 0 || Zigzag_type == 2)
								glRotatef(135.f, 0.0f, 0.0f, 1.0f);
							else if (Zigzag_type == 1 || Zigzag_type == 3)
								glRotatef(45.f, 0.0f, 0.0f, 1.0f);
						}
						else
						{
							if (Zigzag_type == 0 || Zigzag_type == 2)
								glRotatef(315.f, 0.0f, 0.0f, 1.0f);
							else if (Zigzag_type == 1 || Zigzag_type == 3)
								glRotatef(225.f, 0.0f, 0.0f, 1.0f);
						}
						glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
						glBegin(GL_POLYGON);
						glVertex2f(0.f, size);
						glVertex2f(size, size * -1.f);
						glVertex2f(size * -1.f, size * -1.f);
						glEnd();
					}
					else if (Type == CUSTOM)
					{
						if (Reverse)
							glRotatef(Mouse_angle[Mouse_type] + 90, 0.0f, 0.0f, 1.0f); // Mouse_type ��° ���� ������ŭ ȸ�� + 180�� �ؼ� �ݴ�� �ٶ󺸰�
						else
							glRotatef(Mouse_angle[Mouse_type] - 90, 0.0f, 0.0f, 1.0f); // Mouse_type ��° ���� ������ŭ ȸ��
						glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
						glBegin(GL_POLYGON);
						glVertex2f(0.f, size);
						glVertex2f(size, size * -1.f);
						glVertex2f(size * -1.f, size * -1.f);
						glEnd();
					}
					else if(Type == SIN)
					{
						if (Reverse) // Sin_angle ���� angle�� ���� ���� ����� �̻��ϰ� ������
							glRotatef(Sin_angle + 90, 0.0f, 0.0f, 1.0f); // glRotatef(angle + 180, 0.0f, 0.0f, 1.0f);
						else
							glRotatef(Sin_angle - 90, 0.0f, 0.0f, 1.0f); // glRotatef(angle, 0.0f, 0.0f, 1.0f);
						glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
						glBegin(GL_POLYGON);
						glVertex2f(0.f, size);
						glVertex2f(size, size * -1.f);
						glVertex2f(size * -1.f, size * -1.f);
						glEnd();
					}
					else
					{
						if (Reverse)
							glRotatef(angle + 180, 0.0f, 0.0f, 1.0f);
						else
							glRotatef(angle, 0.0f, 0.0f, 1.0f);
						glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
						glBegin(GL_POLYGON);
						glVertex2f(0.f, size);
						glVertex2f(size, size * -1.f);
						glVertex2f(size * -1.f, size * -1.f);
						glEnd();
					}
				}
				else
				{
					glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
					glBegin(GL_POLYGON);
					glVertex2f(0.f, size);
					glVertex2f(size, size * -1.f);
					glVertex2f(size * -1.f, size * -1.f);
					glEnd();
				}
			}
			else // �簢�� ���
			{
				if (Track)
				{
					if (Type == ZIGZAG)
					{
						if (Reverse)
						{
							if (Zigzag_type == 0 || Zigzag_type == 2)
								glRotatef(135.f, 0.0f, 0.0f, 1.0f);
							else if (Zigzag_type == 1 || Zigzag_type == 3)
								glRotatef(45.f, 0.0f, 0.0f, 1.0f);
						}
						else
						{
							if (Zigzag_type == 0 || Zigzag_type == 2)
								glRotatef(315.f, 0.0f, 0.0f, 1.0f);
							else if (Zigzag_type == 1 || Zigzag_type == 3)
								glRotatef(225.f, 0.0f, 0.0f, 1.0f);
						}
						glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
						glBegin(GL_POLYGON);
						glVertex2f(size * -1.f, size);
						glVertex2f(size, size);
						glVertex2f(size, size * -1.f);
						glVertex2f(size * -1.f, size * -1.f);
						glEnd();
					}
					else if (Type == CUSTOM)
					{
						if (Reverse)
							glRotatef(Mouse_angle[Mouse_type] + 90, 0.0f, 0.0f, 1.0f);
						else
							glRotatef(Mouse_angle[Mouse_type] - 90, 0.0f, 0.0f, 1.0f);
						glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
						glBegin(GL_POLYGON);
						glVertex2f(size * -1.f, size);
						glVertex2f(size, size);
						glVertex2f(size, size * -1.f);
						glVertex2f(size * -1.f, size * -1.f);
						glEnd();
					}
					else if(Type == SIN)
					{
						if(Reverse)
							glRotatef(Sin_angle + 90, 0.0f, 0.0f, 1.0f); // glRotatef(angle + 180, 0.0f, 0.0f, 1.0f);
						else
							glRotatef(Sin_angle - 90, 0.0f, 0.0f, 1.0f); // glRotatef(angle, 0.0f, 0.0f, 1.0f);
						glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
						glBegin(GL_POLYGON);
						glVertex2f(size * -1.f, size);
						glVertex2f(size, size);
						glVertex2f(size, size * -1.f);
						glVertex2f(size * -1.f, size * -1.f);
						glEnd();
					}
					else
					{
						if (Reverse)
							glRotatef(angle + 180, 0.0f, 0.0f, 1.0f);
						else
							glRotatef(angle, 0.0f, 0.0f, 1.0f);
						glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
						glBegin(GL_POLYGON);
						glVertex2f(size * -1.f, size);
						glVertex2f(size, size);
						glVertex2f(size, size * -1.f);
						glVertex2f(size * -1.f, size * -1.f);
						glEnd();
					}
				}
				else
				{
					glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
					glBegin(GL_POLYGON);
					glVertex2f(size * -1.f, size);
					glVertex2f(size, size);
					glVertex2f(size, size * -1.f);
					glVertex2f(size * -1.f, size * -1.f);
					glEnd();
				}
			}
		glPopMatrix();
	glPopMatrix(); //for}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(60.0f, w / h, 1.0, 1000.0);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunction(int value)
{
	if (Type == CIRCLE)
	{
		angle++;
		if (angle > 360.0f) angle = 0.0f;
	}
	else if (Type == SIN)
	{
		if (Reverse)
		{
			angle--;
			Sin_x -= 0.0012f;																								 // atan2(y, x) = y/x�϶��� tan(����) �� ���Ȱ����� ���ϵ�
			Sin_angle = atan2(sinf((angle + 1) * PI) * 0.3f - sinf((angle - 1) * PI) * 0.3f, 0.0024) / 3.141592f * 180.0f;	 // Sin_x������ ������
			if (angle < 0.0f) angle = 0.0f, Reverse = false;																 // (Sin_x + 0.0012) - (Sin_x - 0.0012) = 0.0024
		}
		else
		{
			angle++;
			Sin_x += 0.0012f;
			Sin_angle = atan2(sinf((angle + 1) * PI) * 0.3f - sinf((angle - 1) * PI) * 0.3f, 0.0024) / 3.141592f * 180.0f;
			if (angle > 1440.0f) angle = 1440.0f, Reverse = true;
		}
	}
	else if (Type == TORNADO)
	{
		if (Reverse) // �߽����� �����°��
		{
			angle--;
			if (angle < 0.f) angle = 0.0f, Reverse = false;
			Tornado_r -= 0.0008f; // ���� ����
		}
		else // ������ ������ ���
		{
			angle++;
			if (angle > 1080.f) angle = 1080.0f, Reverse = true;
			Tornado_r += 0.0008f; // ��������
		}
	}
	else if (Type == ZIGZAG) // ������ �������� �бⰡ �Ǿ ���ǹ����� �̵�
	{
		if (Reverse)
		{
			Zigzag_x -= 0.003f;
			if (Zigzag_type == 0)
			{
				Zigzag_y -= 0.003f;
				if (Zigzag_x < -0.85f)
					Zigzag_x = -0.85f, Reverse = false;
			}
			else if (Zigzag_type == 1)
			{
				Zigzag_y += 0.003f;
				if (Zigzag_x < -0.5f)
					Zigzag_x = -0.5f, Zigzag_type = 0;
			}
			else if (Zigzag_type == 2)
			{
				Zigzag_y -= 0.003f;
				if (Zigzag_x < 0.0f)
					Zigzag_x = 0.0f, Zigzag_type = 1;
			}
			else if (Zigzag_type == 3)
			{
				Zigzag_y += 0.003f;
				if (Zigzag_x < 0.5f)
					Zigzag_x = 0.5f, Zigzag_type = 2;
			}
		}
		else
		{
			Zigzag_x += 0.003f;
			if (Zigzag_type == 0)
			{
				Zigzag_y += 0.003f;
				if (Zigzag_x > -0.5f)
					Zigzag_x = -0.5f, Zigzag_type = 1;
			}
			else if (Zigzag_type == 1)
			{
				Zigzag_y -= 0.003f;
				if (Zigzag_x > 0.0f)
					Zigzag_x = 0.0f, Zigzag_type = 2;
			}
			else if (Zigzag_type == 2)
			{
				Zigzag_y += 0.003f;
				if (Zigzag_x > 0.5f)
					Zigzag_x = 0.5f, Zigzag_type = 3;
			}
			else if (Zigzag_type == 3)
			{
				Zigzag_y -= 0.003f;
				if (Zigzag_x > 0.85f)
					Zigzag_x = 0.85f, Reverse = true;
			}
		}
	}
	else if (Type == CUSTOM && !Draw)
	{
		if (Reverse) // �ݴ�� ������
		{
			if (Mouse_type == 0) // �ι�°������ -> ù��°������
			{
				Mouse_move_x -= Mouse_speed_x[0]; // ù��° ���� x�ʺ� 100���� ������
				Mouse_move_y -= Mouse_speed_y[0]; // ù��° ���� y�ʺ� 100���� ������
				if (Mouse_speed_x[0] > 0) // �̵��Ϸ��� �������� �� �� ���������� �����ʿ��ִ� ���
				{
					if (Mouse_move_x < Mouse_x[0])
					{
						Mouse_move_x = Mouse_x[0];
						Mouse_move_y = Mouse_y[0];
						Reverse = false;
					}
				}
				else // �̵��Ϸ��� �������� �� �� ���������� ���ʿ� �ִ� ���
				{
					if (Mouse_move_x > Mouse_x[0])
					{
						Mouse_move_x = Mouse_x[0];
						Mouse_move_y = Mouse_y[0];
						Reverse = false;
					}
				}
			}
			else if (Mouse_type == 1) // ����°������ -> �ι�°������
			{
				Mouse_move_x -= Mouse_speed_x[1]; // �ι�° ���� x�ʺ� 100���� ������
				Mouse_move_y -= Mouse_speed_y[1]; // �ι�° ���� y�ʺ� 100���� ������
				if (Mouse_speed_x[1] > 0)
				{
					if (Mouse_move_x < Mouse_x[1])
					{
						Mouse_move_x = Mouse_x[1];
						Mouse_move_y = Mouse_y[1];
						Mouse_type = 0;
					}
				}
				else
				{
					if (Mouse_move_x > Mouse_x[1])
					{
						Mouse_move_x = Mouse_x[1];
						Mouse_move_y = Mouse_y[1];
						Mouse_type = 0;
					}
				}
			}
			else if (Mouse_type == 2) // �׹�°������ -> ����°������
			{
				Mouse_move_x -= Mouse_speed_x[2];
				Mouse_move_y -= Mouse_speed_y[2];
				if (Mouse_speed_x[2] > 0)
				{
					if (Mouse_move_x < Mouse_x[2])
					{
						Mouse_move_x = Mouse_x[2];
						Mouse_move_y = Mouse_y[2];
						Mouse_type = 1;
					}
				}
				else
				{
					if (Mouse_move_x > Mouse_x[2])
					{
						Mouse_move_x = Mouse_x[2];
						Mouse_move_y = Mouse_y[2];
						Mouse_type = 1;
					}
				}
			}
			if (Mouse_type == 3) // �ټ���°������ -> �׹�°������
			{
				Mouse_move_x -= Mouse_speed_x[3];
				Mouse_move_y -= Mouse_speed_y[3];
				if (Mouse_speed_x[3] > 0)
				{
					if (Mouse_move_x < Mouse_x[3])
					{
						Mouse_move_x = Mouse_x[3];
						Mouse_move_y = Mouse_y[3];
						Mouse_type = 2;
					}
				}
				else
				{
					if (Mouse_move_x > Mouse_x[3])
					{
						Mouse_move_x = Mouse_x[3];
						Mouse_move_y = Mouse_y[3];
						Mouse_type = 2;
					}
				}
			}
		}
		// ---------------------------------------
		else
		{
			if (Mouse_type == 0) // ù��°������ -> �ι�°������
			{
				Mouse_move_x += Mouse_speed_x[0]; // ù��° ���� x�ʺ� 100���� ������
				Mouse_move_y += Mouse_speed_y[0]; // ù��° ���� y�ʺ� 100���� ������
				if (Mouse_speed_x[0] > 0)
				{
					if (Mouse_move_x > Mouse_x[1])
					{
						Mouse_move_x = Mouse_x[1];
						Mouse_move_y = Mouse_y[1];
						Mouse_type = 1;
					}
				}
				else
				{
					if (Mouse_move_x < Mouse_x[1])
					{
						Mouse_move_x = Mouse_x[1];
						Mouse_move_y = Mouse_y[1];
						Mouse_type = 1;
					}
				}
			}
			else if (Mouse_type == 1) // �ι�°������ -> ����°������
			{
				Mouse_move_x += Mouse_speed_x[1];
				Mouse_move_y += Mouse_speed_y[1];
				if (Mouse_speed_x[1] > 0)
				{
					if (Mouse_move_x > Mouse_x[2])
					{
						Mouse_move_x = Mouse_x[2];
						Mouse_move_y = Mouse_y[2];
						Mouse_type = 2;
					}
				}
				else
				{
					if (Mouse_move_x < Mouse_x[2])
					{
						Mouse_move_x = Mouse_x[2];
						Mouse_move_y = Mouse_y[2];
						Mouse_type = 2;
					}
				}
			}
			else if (Mouse_type == 2) // ����°������ -> �׹�°������
			{
				Mouse_move_x += Mouse_speed_x[2];
				Mouse_move_y += Mouse_speed_y[2];
				if (Mouse_speed_x[2] > 0)
				{
					if (Mouse_move_x > Mouse_x[3])
					{
						Mouse_move_x = Mouse_x[3];
						Mouse_move_y = Mouse_y[3];
						Mouse_type = 3;
					}
				}
				else
				{
					if (Mouse_move_x < Mouse_x[3])
					{
						Mouse_move_x = Mouse_x[3];
						Mouse_move_y = Mouse_y[3];
						Mouse_type = 3;
					}
				}
			}
			else if (Mouse_type == 3) // �׹�°������ -> �ټ���°������
			{
				Mouse_move_x += Mouse_speed_x[3];
				Mouse_move_y += Mouse_speed_y[3];
				if (Mouse_speed_x[3] > 0)
				{
					if (Mouse_move_x > Mouse_x[4])
					{
						Mouse_move_x = Mouse_x[4];
						Mouse_move_y = Mouse_y[4];
						Reverse = true; // ���� ����. �ݴ�� �̵�
					}
				}
				else
				{
					if (Mouse_move_x < Mouse_x[4])
					{
						Mouse_move_x = Mouse_x[4];
						Mouse_move_y = Mouse_y[4];
						Reverse = true;
					}
				}
			}
		}
	}

	if (Expand) // ����
	{
		Scaling += 0.01f;
		if (Scaling > 1.2f) Expand = false;
	}
	else
	{
		Scaling -= 0.01f;
		if (Scaling < 0.7f) Expand = true;
	}

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
	{
		glutDestroyWindow(MainWindow);
		exit(0);
	}
	else if (key == 'w' || key == 'W')
	{
		if (Track) Track = false;
		else Track = true;
	}
	else if (key == 'e' || key == 'E')
	{
		if (Shape) Shape = false;
		else Shape = true;
	}
	else if (key == 49)
	{
		Type = CIRCLE;
		angle = 0.0f;
		Reverse = false;
	}
	else if (key == 50)
	{
		Type = SIN;
		Sin_x = -0.85f;
		angle = 0.0f;
		Sin_angle = 0.0f;
		Reverse = false;
	}
	else if (key == 51)
	{
		Type = TORNADO;
		angle = 0.0f;
		Reverse = false;
		Tornado_r = 0.0f;
	}
	else if (key == 52)
	{
		Type = ZIGZAG;
		Zigzag_x = -0.85f;
		Zigzag_y = 0.0f;
		Zigzag_type = 0;
		Reverse = false;
	}
	else if (key == 53)
	{
		Type = CUSTOM;
		Mouse_count = 0;
		Reverse = false;
		Draw = true;
		Mouse_type = 0;
		Mouse_move_x = 0.0f;
		Mouse_move_y = 0.0f;
		for (int i = 0; i < 5; ++i)
		{
			Mouse_x[i] = 0.0f;
			Mouse_y[i] = 0.0f;
		}
		for (int i = 0; i < 4; ++i)
		{
			Mouse_speed_x[i] = 0.0f;
			Mouse_speed_y[i] = 0.0f;
			Mouse_angle[i] = 0.0f;
		}
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (Draw) // 5���� ������ ���콺���� ���� �ʱ�ȭ + Draw Ű��
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{ // ���콺�� Ŭ���Ұ�� -1~1���� �ƴ� 0~������ũ��� x,y�� ��
			Mouse_x[Mouse_count] = ((float)x / 400) - 1.f; // ������ �ʺ� 800�� ������ 400���� ������ 0~2, �ű⿡ -1�ϸ� -1~1��
			Mouse_y[Mouse_count] = ((800.0 - (float)y) / 400) - 1.f;
			Mouse_count++;
			if (Mouse_count >= 5) // ������ 5���� ��������
			{
				Draw = false;
				Mouse_move_x = Mouse_x[0]; // ó�� �����ؾ��ϴ� ��ġ�� ù��° ������
				Mouse_move_y = Mouse_y[0];
				for (int i = 1; i < 5; ++i)
				{	// ������ �����̴� �ӵ��� ���� ������ x,y �ʺ� 100���� ������
					Mouse_speed_x[i - 1] = Mouse_x[i] - Mouse_x[i - 1];
					Mouse_speed_y[i - 1] = Mouse_y[i] - Mouse_y[i - 1];

					Mouse_speed_x[i - 1] /= 100;
					Mouse_speed_y[i - 1] /= 100;

					Mouse_angle[i - 1] = atan2(Mouse_y[i] - Mouse_y[i - 1] , Mouse_x[i] - Mouse_x[i - 1]) * 180.0f / 3.141592f; // arctan
				}
			}
		}
	}
}