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
bool Track = false; // 경로를 따라그릴건지, 그냥 그릴건지
bool Shape = true; // 삼각형,사각형
bool Expand = true; // 신축
bool Reverse = false; // 끝점에 도착했을때 반대로 움직이게
bool Draw = false; // 마우스로 선 그리기
float Scaling = 1.0f; // 확대/축소
float angle = 0.0f; // CIRCLE이나 TORNADO일경우에 쓰는 각도값
float fx = 0.0f;
float fy = 0.0f;
float size = 0.07f; // 움직이는 도형의 크기
float Tornado_r = 0.0f; // 회오리 반지름
float Sin_x = -0.85f; // Sin곡선모양으로 움직일때 처음 시작점
float Sin_angle = 0.0f; // Sin_x에서의 각도
float Zigzag_x = -0.85f;
float Zigzag_y = 0.0f;
int Zigzag_type = 0;
int Mouse_count = 0; // 선을 몇개 그렷는지 카운트
float Mouse_move_x, Mouse_move_y; // CUSTOM 상태에서의 도형 원점으로 사용
float Mouse_x[5], Mouse_y[5]; // 5번 클릭, 4개의 선 생성
float Mouse_speed_x[4], Mouse_speed_y[4]; // 각 선들에서의 스피드값
int Mouse_type = 0; // 첫번째선 , 두번째선, 세번째선, 네번째선중 어느 선을 움직일건지
float Mouse_angle[4]; // 각 선들의 각도값

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
	glPushMatrix(); // X,Y축
		glBegin(GL_LINES);
		glVertex2f(-1.0, 0.0);
		glVertex2f(1.0, 0.0);
		glVertex2f(0.0, -1.0);
		glVertex2f(0.0, 1.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();//for(int y  =  {
		glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
		if (Type == CIRCLE) // 원모양
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 360; ++i)
			{
				glVertex2f(cosf(i * PI) * 0.7f, sinf(i*PI) * 0.7f);
			}
			glEnd();
		}
		else if (Type == SIN) // 사인곡선
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
		else if (Type == TORNADO) // 회오리
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
		else if (Type == ZIGZAG) // 지그재그
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
		else if (Type == CUSTOM) // 마우스로 선그리기
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < Mouse_count; ++i)
			{
				glVertex2f(Mouse_x[i], Mouse_y[i]);
			}
			glEnd();
		}
		
		glPushMatrix();
			if(Type == CIRCLE) // 원모양일때의 원점 좌표
				glTranslatef(cosf(angle  * PI) * 0.7f, sinf(angle * PI) * 0.7f, 0.0f);
			else if(Type == SIN) // 사인
				glTranslatef(Sin_x, sinf(angle * PI) * 0.3f, 0.0f);
			else if(Type == TORNADO) // 회오리
				glTranslatef(cosf(angle * PI) * Tornado_r, sinf(angle * PI) * Tornado_r, 0.0f);
			else if(Type == ZIGZAG) // 지그재그
				glTranslatef(Zigzag_x, Zigzag_y, 0.0f);
			else if(Type == CUSTOM) // 마우스로 선그리기
				if(!Draw) // 선그리기가 끝났을경우 도형을 시작점으로 위치시킨후 움직이게함
					glTranslatef(Mouse_move_x, Mouse_move_y, 0.0f);

			glScalef(Scaling, Scaling, 0.0f); // 확대/축소되게
			if (Shape) // 삼각/사각
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
							glRotatef(Mouse_angle[Mouse_type] + 90, 0.0f, 0.0f, 1.0f); // Mouse_type 번째 선의 각도만큼 회전 + 180도 해서 반대로 바라보게
						else
							glRotatef(Mouse_angle[Mouse_type] - 90, 0.0f, 0.0f, 1.0f); // Mouse_type 번째 선의 각도만큼 회전
						glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
						glBegin(GL_POLYGON);
						glVertex2f(0.f, size);
						glVertex2f(size, size * -1.f);
						glVertex2f(size * -1.f, size * -1.f);
						glEnd();
					}
					else if(Type == SIN)
					{
						if (Reverse) // Sin_angle 말고 angle로 쓰면 위쪽 굴곡에서 이상하게 움직임
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
			else // 사각형 출력
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
			Sin_x -= 0.0012f;																								 // atan2(y, x) = y/x일때의 tan(각도) 단 라디안값으로 리턴됨
			Sin_angle = atan2(sinf((angle + 1) * PI) * 0.3f - sinf((angle - 1) * PI) * 0.3f, 0.0024) / 3.141592f * 180.0f;	 // Sin_x에서의 각도값
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
		if (Reverse) // 중심으로 들어오는경우
		{
			angle--;
			if (angle < 0.f) angle = 0.0f, Reverse = false;
			Tornado_r -= 0.0008f; // 점점 감소
		}
		else // 밖으로 나가는 경우
		{
			angle++;
			if (angle > 1080.f) angle = 1080.0f, Reverse = true;
			Tornado_r += 0.0008f; // 점점증가
		}
	}
	else if (Type == ZIGZAG) // 각각의 꼭지점이 분기가 되어서 조건문으로 이동
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
		if (Reverse) // 반대로 움직임
		{
			if (Mouse_type == 0) // 두번째꼭지점 -> 첫번째꼭지점
			{
				Mouse_move_x -= Mouse_speed_x[0]; // 첫번째 선의 x너비를 100으로 나눈값
				Mouse_move_y -= Mouse_speed_y[0]; // 첫번째 선의 y너비를 100으로 나눈값
				if (Mouse_speed_x[0] > 0) // 이동하려는 꼭지점이 그 전 꼭지점보다 오른쪽에있는 경우
				{
					if (Mouse_move_x < Mouse_x[0])
					{
						Mouse_move_x = Mouse_x[0];
						Mouse_move_y = Mouse_y[0];
						Reverse = false;
					}
				}
				else // 이동하려는 꼭지점이 그 전 꼭지점보다 왼쪽에 있는 경우
				{
					if (Mouse_move_x > Mouse_x[0])
					{
						Mouse_move_x = Mouse_x[0];
						Mouse_move_y = Mouse_y[0];
						Reverse = false;
					}
				}
			}
			else if (Mouse_type == 1) // 세번째꼭지점 -> 두번째꼭지점
			{
				Mouse_move_x -= Mouse_speed_x[1]; // 두번째 선의 x너비를 100으로 나눈값
				Mouse_move_y -= Mouse_speed_y[1]; // 두번째 선의 y너비를 100으로 나눈값
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
			else if (Mouse_type == 2) // 네번째꼭지점 -> 세번째꼭지점
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
			if (Mouse_type == 3) // 다섯번째꼭지점 -> 네번째꼭지점
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
			if (Mouse_type == 0) // 첫번째꼭지점 -> 두번째꼭지점
			{
				Mouse_move_x += Mouse_speed_x[0]; // 첫번째 선의 x너비를 100으로 나눈값
				Mouse_move_y += Mouse_speed_y[0]; // 첫번째 선의 y너비를 100으로 나눈값
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
			else if (Mouse_type == 1) // 두번째꼭지점 -> 세번째꼭지점
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
			else if (Mouse_type == 2) // 세번째꼭지점 -> 네번째꼭지점
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
			else if (Mouse_type == 3) // 네번째꼭지점 -> 다섯번째꼭지점
			{
				Mouse_move_x += Mouse_speed_x[3];
				Mouse_move_y += Mouse_speed_y[3];
				if (Mouse_speed_x[3] > 0)
				{
					if (Mouse_move_x > Mouse_x[4])
					{
						Mouse_move_x = Mouse_x[4];
						Mouse_move_y = Mouse_y[4];
						Reverse = true; // 끝점 도착. 반대로 이동
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

	if (Expand) // 신축
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
	if (Draw) // 5번을 눌러서 마우스관련 변수 초기화 + Draw 키기
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{ // 마우스로 클릭할경우 -1~1값이 아닌 0~윈도우크기로 x,y에 들어감
			Mouse_x[Mouse_count] = ((float)x / 400) - 1.f; // 윈도우 너비 800의 절반인 400으로 나누면 0~2, 거기에 -1하면 -1~1값
			Mouse_y[Mouse_count] = ((800.0 - (float)y) / 400) - 1.f;
			Mouse_count++;
			if (Mouse_count >= 5) // 꼭지점 5개를 찍었을경우
			{
				Draw = false;
				Mouse_move_x = Mouse_x[0]; // 처음 시작해야하는 위치는 첫번째 꼭지점
				Mouse_move_y = Mouse_y[0];
				for (int i = 1; i < 5; ++i)
				{	// 도형이 움직이는 속도는 각각 선분의 x,y 너비를 100으로 나눈값
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