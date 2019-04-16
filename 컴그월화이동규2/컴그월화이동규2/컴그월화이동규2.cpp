#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define DRAW_RAIL 0 // 중앙 선로 그리기
#define LEFT 1 // 왼쪽 선로 그리기
#define RIGHT 2 // 오른쪽 선로 그리기
#define TREE_NUM 80 // 나무 숫자
#define POINT_MAX 33 // 제어점의 개수
#define SET_ROAD 0 // 선로 설정 모드
#define VIEW_FIELD 1 // 3인칭 화면 뷰 모드
#define VIEW_COASTER 2 // 1인칭 코스터 뷰 모드
#define CHASE_COASTER 3 // 3인칭 코스터 뷰 모드
#define ROAD_WIDTH 6 // 선로 너비
#define WEATHER_NUM 800 // 날씨요소 개체 수
#define COASTER_NUM 4 // 코스터 수
#define X 0
#define Y 1
#define Z 2
#define WEATHER_SPEED 3 // 4번째 배열
#define ANGLE 3 // 4번쨰 배열
#define NONE 100 // 날씨 상태
#define SNOW 101 // 눈
#define RAIN 102 // 비
#define BULLET_NUM 100 // 총알 최대 발사개수
#define BULLET_SPEED 15 // 총알 스피드
#define FIELD_WIDTH 1000 // 바닥 너비
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

typedef struct Point3D {
	float x, y, z;
}Point3D;

typedef struct Coaster {
	int count; // 현재 어느 곡선 선로를 지나는가
	float X_angle;
	float Y_angle;
	float x, y, z;
	float move_rail; // 곡선 선로 내부를 지나는 Detail값
}Coaster;

typedef struct Tunnel {
	bool exist; // 터널이 생성됫는지 안됫는지
	float X_angle;
	float Y_angle;
	float x, y, z;
}Tunnel;

typedef struct Bullet {
	float x, y, z;
	float X_angle;
	float Y_angle;
	float move;
	bool exist;
}Bullet;

class Tree {
private:
	float fx, fz;
public:
	Tree() : fx(rand()% (FIELD_WIDTH * 2) - FIELD_WIDTH), fz(rand()% (FIELD_WIDTH * 2) - FIELD_WIDTH) {}
	void Render_Tree();
	void SetX(float x) { fx = x; }
	void SetZ(float z) { fz = z; }
	float GetX() { return fx; }
	float GetZ() { return fz; }
};

Point3D GetBezier(float fDetail, int n, int type, int count);
void TimerFunction(int value);
void KeyBoard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Render_Road();
void Render_Coaster();
void Set_Coaster();
void Render_Tunnel();
void Render_Bullet(int);

Bullet bullet[BULLET_NUM];
int bullet_count = 0;
GLfloat point[POINT_MAX][3];
Coaster coaster[COASTER_NUM];
Tunnel tunnel;
int MainWindow;
int num = 0;
int Camera_State = SET_ROAD;
int Weather_Type = NONE;
float Rotate_Angle_X;
float Rotate_Angle_Y;
float Rotate_Move_Z;
float height;
float weather[WEATHER_NUM][4];
Tree tree[TREE_NUM];
bool Straight_Mode = false;

void main()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < WEATHER_NUM; ++i)
	{
		weather[i][X] = rand() % (FIELD_WIDTH * 2) - FIELD_WIDTH;
		weather[i][Y] = rand() % 201 + 600;
		weather[i][Z] = rand() % (FIELD_WIDTH * 2) - FIELD_WIDTH;
		weather[i][WEATHER_SPEED] = (float)(rand() % 6 + 2);
	}
	tunnel.exist = false;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	if (Camera_State == SET_ROAD)
	{
		glTranslatef(0.f, 0.f, 500.f);
		glRotatef(90.f, 1.f, 0.f, 0.f);
	}
	else if(Camera_State == VIEW_FIELD)
	{
		glTranslatef(0.f, -400.f, Rotate_Move_Z);
		glRotatef(Rotate_Angle_X, 1.f, 0.f, 0.f);
		glRotatef(Rotate_Angle_Y, 0.f, 1.f, 0.f);
	}
	else if (Camera_State == VIEW_COASTER)
	{
		glTranslatef(0.f, -23.f, 1200.f);
		//printf("X = %f , Y = %f\n", &coaster[0].X_angle, &coaster[0].Y_angle);
		if (coaster[0].X_angle < 90.f && coaster[0].X_angle > 0.f)
		{
			glRotatef(-coaster[0].X_angle, -1.f, 0.f, 0.f);
		}
		else
		{
			glRotatef(-coaster[0].X_angle, 1.f, 0.f, 0.f);
		}
		glRotatef(coaster[0].Y_angle + 90.f, 0.f, 1.f, 0.f);
		glTranslatef(-coaster[0].x, -coaster[0].y, -coaster[0].z);
	}
	else if (Camera_State == CHASE_COASTER)
	{
		glTranslatef(0.f, -400.f, 0.f);
		gluLookAt((double)coaster[0].x, (double)coaster[0].y, (double)coaster[0].z, (double)coaster[1].x, (double)coaster[1].y, (double)coaster[1].z, 0.0, 1.0, 0.0);
	}

	glPushMatrix(); // 밑면
	glColor4f(0.4f, 1.0f, 0.3f, 1.f);
	glBegin(GL_QUADS);
	glVertex3f(FIELD_WIDTH, 0.f, -FIELD_WIDTH);
	glVertex3f(FIELD_WIDTH, 0.f, FIELD_WIDTH);
	glVertex3f(-FIELD_WIDTH, 0.f, FIELD_WIDTH);
	glVertex3f(-FIELD_WIDTH, 0.f, -FIELD_WIDTH);
	glEnd();
	glPopMatrix();

	if (Weather_Type != NONE)
	{
		for (int i = 0; i < WEATHER_NUM; ++i)
		{
			glPushMatrix();
			glTranslatef(weather[i][X], weather[i][Y], weather[i][Z]);
			if (Weather_Type == SNOW)
			{
				glColor3f(1.f, 1.f, 1.f);
				glutSolidSphere(3, 20, 20);
			}
			else if (Weather_Type == RAIN)
			{
				glColor3f(0.f, 0.f, 1.f);
				glScalef(1.f, 8.f, 1.f);
				glutSolidCube(1);
			}
			glPopMatrix();
		}
	}

	if (num > 2)
	{
		Render_Coaster();
	}

	if (tunnel.exist)
		Render_Tunnel();

	for (int i = 0; i < BULLET_NUM; ++i)
	{
		Render_Bullet(i);
	}

	for (int i = 0; i < TREE_NUM; ++i)
	{
		tree[i].Render_Tree();
	}

	Render_Road();
	glDisable(GL_DEPTH_TEST);
	glPopMatrix();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 5000.0);
	//glTranslatef(0.0, 0.0, 0.0);

	//glOrtho(0.0, 800.0, 0.0, 800.0, 0.0, 800.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void TimerFunction(int value)
{
	if (Weather_Type != NONE)
	{
		for (int i = 0; i < WEATHER_NUM; ++i)
		{
			weather[i][Y] -= weather[i][WEATHER_SPEED];
			if (weather[i][Y] < 0.f)
				weather[i][Y] = (float)(rand() % 201 + 600);
		}
	}

	if (Camera_State != SET_ROAD)
	{
		for (int i = 0; i < COASTER_NUM; ++i)
		{
			float tmp_x1 = point[coaster[i].count - 2][X] * ((1 - (coaster[i].move_rail - 0.03f)) * (1 - (coaster[i].move_rail - 0.03f))) + point[coaster[i].count - 1][X] * ((2 * (coaster[i].move_rail - 0.03f)) * (1 - (coaster[i].move_rail - 0.03f))) + point[coaster[i].count][X] * ((coaster[i].move_rail - 0.03f) * (coaster[i].move_rail - 0.03f));
			float tmp_x2 = point[coaster[i].count - 2][X] * ((1 - (coaster[i].move_rail + 0.03f)) * (1 - (coaster[i].move_rail + 0.03f))) + point[coaster[i].count - 1][X] * ((2 * (coaster[i].move_rail + 0.03f)) * (1 - (coaster[i].move_rail + 0.03f))) + point[coaster[i].count][X] * ((coaster[i].move_rail + 0.03f) * (coaster[i].move_rail + 0.03f));

			float tmp_y1 = point[coaster[i].count - 2][Y] * ((1 - (coaster[i].move_rail - 0.03f)) * (1 - (coaster[i].move_rail - 0.03f))) + point[coaster[i].count - 1][Y] * ((2 * (coaster[i].move_rail - 0.03f)) * (1 - (coaster[i].move_rail - 0.03f))) + point[coaster[i].count][Y] * ((coaster[i].move_rail - 0.03f) * (coaster[i].move_rail - 0.03f));
			float tmp_y2 = point[coaster[i].count - 2][Y] * ((1 - (coaster[i].move_rail + 0.03f)) * (1 - (coaster[i].move_rail + 0.03f))) + point[coaster[i].count - 1][Y] * ((2 * (coaster[i].move_rail + 0.03f)) * (1 - (coaster[i].move_rail + 0.03f))) + point[coaster[i].count][Y] * ((coaster[i].move_rail + 0.03f) * (coaster[i].move_rail + 0.03f));

			float tmp_z1 = point[coaster[i].count - 2][Z] * ((1 - (coaster[i].move_rail - 0.03f)) * (1 - (coaster[i].move_rail - 0.03f))) + point[coaster[i].count - 1][Z] * ((2 * (coaster[i].move_rail - 0.03f)) * (1 - (coaster[i].move_rail - 0.03f))) + point[coaster[i].count][Z] * ((coaster[i].move_rail - 0.03f) * (coaster[i].move_rail - 0.03f));
			float tmp_z2 = point[coaster[i].count - 2][Z] * ((1 - (coaster[i].move_rail + 0.03f)) * (1 - (coaster[i].move_rail + 0.03f))) + point[coaster[i].count - 1][Z] * ((2 * (coaster[i].move_rail + 0.03f)) * (1 - (coaster[i].move_rail + 0.03f))) + point[coaster[i].count][Z] * ((coaster[i].move_rail + 0.03f) * (coaster[i].move_rail + 0.03f));


			coaster[i].Y_angle = atan2f((tmp_z2 - tmp_z1), (tmp_x2 - tmp_x1)) / 3.141592f * 180.0f;
			if (point[coaster[i].count][Y] == 0.f && point[coaster[i].count - 1][Y] == 0.f && point[coaster[i].count - 2][Y] == 0.f)
				coaster[i].X_angle = 0.f;
			else
				coaster[i].X_angle = atan2f((tmp_y2 - tmp_y1), (tmp_x2 - tmp_x1)) / 3.141592f * 180.0f;

			coaster[i].x = point[coaster[i].count - 2][X] * ((1 - coaster[i].move_rail) * (1 - coaster[i].move_rail)) + point[coaster[i].count - 1][X] * ((2 * coaster[i].move_rail) * (1 - coaster[i].move_rail)) + point[coaster[i].count][X] * (coaster[i].move_rail * coaster[i].move_rail);
			coaster[i].y = point[coaster[i].count - 2][Y] * ((1 - coaster[i].move_rail) * (1 - coaster[i].move_rail)) + point[coaster[i].count - 1][Y] * ((2 * coaster[i].move_rail) * (1 - coaster[i].move_rail)) + point[coaster[i].count][Y] * (coaster[i].move_rail * coaster[i].move_rail);
			coaster[i].z = point[coaster[i].count - 2][Z] * ((1 - coaster[i].move_rail) * (1 - coaster[i].move_rail)) + point[coaster[i].count - 1][Z] * ((2 * coaster[i].move_rail) * (1 - coaster[i].move_rail)) + point[coaster[i].count][Z] * (coaster[i].move_rail * coaster[i].move_rail);
			coaster[i].move_rail += 0.01f;
			if (coaster[i].move_rail > 1.f)
			{
				coaster[i].move_rail -= 1.f;
				coaster[i].count += 2;
				if (coaster[i].count > POINT_MAX)
					coaster[i].count = 2;
			}
		}

		for (int i = 0; i < BULLET_NUM; ++i)
		{
			if(bullet[i].exist)
				bullet[i].move += BULLET_SPEED;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') // 종료
	{
		glutDestroyWindow(MainWindow);
		exit(0);
	}
	else if (key == 'a' || key == 'A')
	{
		Rotate_Angle_Y += 5.f;
	}
	else if (key == 'd' || key == 'D')
	{
		Rotate_Angle_Y -= 5.f;
	}
	else if (key == 'w' || key == 'W')
	{
		Rotate_Angle_X += 5.f;
	}
	else if (key == 's' || key == 'S')
	{
		Rotate_Angle_X -= 5.f;
	}
	else if (key == 'c' || key == 'C')
	{
		if (Camera_State != SET_ROAD)
		{
			Camera_State++;
			Camera_State = Camera_State % 3 + 1;
		}
	}
	else if (key == '+')
	{
		if (Camera_State == SET_ROAD)
		{
			height += 10.f;
			printf("Height = %f\n", height);
		}
		else
			Rotate_Move_Z += 5.f;
	}
	else if (key == '-')
	{
		if (Camera_State == SET_ROAD)
		{
			if (height > 0.f)
			{
				height -= 10.f;
				printf("Height = %f\n", height);
			}
		}
		else
			Rotate_Move_Z -= 5.f;
	}
	else if (key == 'm' || key == 'M')
	{
		if (Straight_Mode)
		{
			Straight_Mode = false;
			printf("직선 생성 OFF\n");
		}
		else
		{
			Straight_Mode = true;
			printf("직선 생성 ON\n");
		}
	}
	else if (key == ' ')
	{
		if (Camera_State != SET_ROAD)
		{
			bullet[bullet_count].x = coaster[0].x;
			bullet[bullet_count].y = coaster[0].y;
			bullet[bullet_count].z = coaster[0].z;
			bullet[bullet_count].X_angle = coaster[0].X_angle;
			bullet[bullet_count].Y_angle = coaster[0].Y_angle;
			bullet[bullet_count].exist = true;
			bullet[bullet_count].move = 0.f;
			bullet_count++;
			if (bullet_count == BULLET_NUM)
				bullet_count = 0;
		}
	}
	else if (key == 49)
	{
		Weather_Type = NONE;
	}
	else if (key == 50)
	{
		Weather_Type = SNOW;
	}
	else if (key == 51)
	{
		Weather_Type = RAIN;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Camera_State == SET_ROAD)
	{
		for (int i = 0; i < TREE_NUM; ++i)
		{
			if (x - 400 > tree[i].GetX() - 15 && x - 400 < tree[i].GetX() + 15 && y - 400 > tree[i].GetZ() - 15 && y - 400 < tree[i].GetZ() + 15)
			{
				return;
			}
		}
		if (Straight_Mode && num % 2 == 0 && num > 2)
		{
			point[num][X] = x - 400;
			point[num][Z] = y - 400;
			point[num][Y] = height;

			point[num - 1][X] = (point[num][X] + point[num - 2][X]) / 2;
			point[num - 1][Z] = (point[num][Z] + point[num - 2][Z]) / 2;
			point[num - 1][Y] = (point[num][Y] + point[num - 2][Y]) / 2;

			tunnel.exist = true;
			tunnel.x = point[num - 1][X];
			tunnel.y = point[num - 1][Y];
			tunnel.z = point[num - 1][Z];
			tunnel.Y_angle = atan2f((point[num][Z] - point[num - 2][Z]), (point[num][X] - point[num - 2][X])) / 3.141592f * 180.0f;
			tunnel.X_angle = atan2f((point[num][Y] - point[num - 2][Y]), (point[num][X] - point[num - 2][X])) / 3.141592f * 180.0f;
		}
		else
		{
			point[num][X] = x - 400;
			point[num][Z] = y - 400;
			point[num][Y] = height;
		}

		if (num == 2)
		{
			point[num - 1][X] = (point[num][X] + point[num - 2][X]) / 2;
			point[num - 1][Y] = (point[num][Y] + point[num - 2][Y]) / 2;
			point[num - 1][Z] = (point[num][Z] + point[num - 2][Z]) / 2;
			Set_Coaster();
		}

		++num;

		if (num == POINT_MAX)
		{
			Camera_State = VIEW_FIELD;
		}
	}
	glutPostRedisplay();
}

void Render_Road()
{
	glPushMatrix(); // 선로
	glTranslatef(0.f, 10.f, 0.f);
	//glTranslatef(-400.f, 10.f, -400.f);
	for (int i = 0; i < num; i++)
	{
		if (i == 2) // 스테이션
		{
			if (Camera_State == VIEW_COASTER)
				glLineWidth(20.f);
			else
				glLineWidth(5.f);
			glColor3f(0.2f, 0.2f, 0.2f);
			glBegin(GL_LINE_STRIP);
			for (float p = 0.f; p <= 1.03f; p += (1.0f / 30.f))
			{
				Point3D tmp = GetBezier(p, i, LEFT, 0);
				if(Camera_State == SET_ROAD) // 직각 투영
					glVertex3f(tmp.x, 0.f, tmp.z);
				else
					glVertex3f(tmp.x, tmp.y, tmp.z);
			}
			glEnd();

			glBegin(GL_LINE_STRIP);
			for (float p = 0.f; p <= 1.03f; p += (1.0f / 30.f))
			{
				Point3D tmp = GetBezier(p, i, RIGHT, 0);
				if (Camera_State == SET_ROAD) // 직각 투영
					glVertex3f(tmp.x, 0.f, tmp.z);
				else
					glVertex3f(tmp.x, tmp.y, tmp.z);
			}
			glEnd();

			glColor3f(0.3f, 0.3f, 0.3f);
			int cnt = 0;
			glLineWidth(3.f);
			for (float p = 0.f; p <= 1.03f; p += (1.0f / 30.f))
			{
				Point3D tmp = GetBezier(p, i, DRAW_RAIL, cnt);
				cnt++;
			}
		}
		else if (i % 2 == 0 && i > 2)
		{
			glColor3f(0.3f, 0.8f, 0.8f);
			if (Camera_State == VIEW_COASTER)
				glLineWidth(20.f);
			else
				glLineWidth(5.f);
			glBegin(GL_LINE_STRIP);
			for (float p = 0.f; p <= 1.03f; p += (1.0f / 30.f))
			{
				Point3D tmp = GetBezier(p, i, LEFT, 0); // 왼쪽선로
				if (Camera_State == SET_ROAD)
					glVertex3f(tmp.x, 0.f, tmp.z);
				else
					glVertex3f(tmp.x, tmp.y, tmp.z);
			}
			glEnd();

			glBegin(GL_LINE_STRIP);
			for (float p = 0.f; p <= 1.03f; p += (1.0f / 30.f))
			{
				Point3D tmp = GetBezier(p, i, RIGHT, 0); // 오른쪽선로
				if (Camera_State == SET_ROAD)
					glVertex3f(tmp.x, 0.f, tmp.z);
				else
					glVertex3f(tmp.x, tmp.y, tmp.z);
			}
			glEnd();

			glColor3f(0.5f, 0.5f, 0.5f);
			int cnt = 0;
			if (Camera_State == VIEW_COASTER)
				glLineWidth(10.f);
			else
				glLineWidth(3.f);
			for (float p = 0.f; p <= 1.03f; p += (1.0f / 30.f))
			{
				Point3D tmp = GetBezier(p, i, DRAW_RAIL, cnt); // 중앙선로
				cnt++;
			}
		}
	}

	//printf("%d\n", num);
	for (int i = 0; i < num; i++)
	{
		if (i % 2 == 0 || i == POINT_MAX - 1)
			glColor3f(0.f, 0.f, 1.f);
		else
			glColor3f(1.f, 1.f, 1.f);
		if (Camera_State == SET_ROAD)
		{
			glPushMatrix();
			glTranslatef(point[i][X], 0.f, point[i][Z]);
			glScalef(1.f, 0.1f, 1.f);
			glutSolidSphere(5, 10, 10);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslatef(point[i][X], point[i][Y], point[i][Z]);
			glScalef(1.f, 0.1f, 1.f);
			glutSolidSphere(5, 10, 10);
			glPopMatrix();
		}
	}

	if (Camera_State != SET_ROAD)
	{
		glBegin(GL_LINES);
		for (int i = 0; i < num; i++)
		{
			if (i % 2 == 0 || i == POINT_MAX - 1)
			{
				glColor3f(0.5f, 0.5f, 0.5f);
				glVertex3f(point[i][X], 0, point[i][Z]);
				glVertex3f(point[i][X], point[i][Y], point[i][Z]);
			}
		}
		glEnd();
	}

	glPopMatrix();
}

Point3D GetBezier(float fDetail, int n, int type, int count)
{
	Point3D result;
	float angle = atan2f((point[n][Z] - point[n - 2][Z]), (point[n][X] - point[n - 2][X])) / 3.141592f * 180.0f;

	if ((angle > -45 && angle < 45) || (angle > 135 || angle < -135))
	{
		if (type == LEFT)
		{
			result.x = point[n - 2][X] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][X] * ((2 * fDetail) * (1 - fDetail)) + point[n][X] * (fDetail * fDetail);
			result.y = point[n - 2][Y] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Y] * ((2 * fDetail) * (1 - fDetail)) + point[n][Y] * (fDetail * fDetail);
			result.z = (point[n - 2][Z] - ROAD_WIDTH) * ((1 - fDetail) * (1 - fDetail)) + (point[n - 1][Z] - ROAD_WIDTH) * ((2 * fDetail) * (1 - fDetail)) + (point[n][Z] - ROAD_WIDTH) * (fDetail * fDetail);
		}
		else if (type == RIGHT)
		{
			result.x = point[n - 2][X] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][X] * ((2 * fDetail) * (1 - fDetail)) + point[n][X] * (fDetail * fDetail);
			result.y = point[n - 2][Y] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Y] * ((2 * fDetail) * (1 - fDetail)) + point[n][Y] * (fDetail * fDetail);
			result.z = (point[n - 2][Z] + ROAD_WIDTH) * ((1 - fDetail) * (1 - fDetail)) + (point[n - 1][Z] + ROAD_WIDTH) * ((2 * fDetail) * (1 - fDetail)) + (point[n][Z] + ROAD_WIDTH) * (fDetail * fDetail);
		}
		else if (type == DRAW_RAIL)
		{
			if (count % 2 == 0)
			{
				result.x = point[n - 2][X] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][X] * ((2 * fDetail) * (1 - fDetail)) + point[n][X] * (fDetail * fDetail);
				result.y = point[n - 2][Y] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Y] * ((2 * fDetail) * (1 - fDetail)) + point[n][Y] * (fDetail * fDetail);
				result.z = point[n - 2][Z] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Z] * ((2 * fDetail) * (1 - fDetail)) + point[n][Z] * (fDetail * fDetail);
				if (Camera_State == SET_ROAD)
				{
					glBegin(GL_LINES);
					glVertex3f(result.x, 0, result.z - 5);
					glVertex3f(result.x, 0, result.z + 5);
					glEnd();
				}
				else
				{
					glBegin(GL_LINES);
					glVertex3f(result.x, result.y, result.z - 5);
					glVertex3f(result.x, result.y, result.z + 5);
					glEnd();
				}
			}
		}
	}
	else
	{
		if (type == LEFT)
		{
			result.x = (point[n - 2][X] - ROAD_WIDTH) * ((1 - fDetail) * (1 - fDetail)) + (point[n - 1][X] - ROAD_WIDTH) * ((2 * fDetail) * (1 - fDetail)) + (point[n][X] - ROAD_WIDTH) * (fDetail * fDetail);
			result.y = point[n - 2][Y] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Y] * ((2 * fDetail) * (1 - fDetail)) + point[n][Y] * (fDetail * fDetail);
			result.z = point[n - 2][Z] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Z] * ((2 * fDetail) * (1 - fDetail)) + point[n][Z] * (fDetail * fDetail);
		}
		else if (type == RIGHT)
		{
			result.x = (point[n - 2][X] + ROAD_WIDTH) * ((1 - fDetail) * (1 - fDetail)) + (point[n - 1][X] + ROAD_WIDTH) * ((2 * fDetail) * (1 - fDetail)) + (point[n][X] + ROAD_WIDTH) * (fDetail * fDetail);
			result.y = point[n - 2][Y] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Y] * ((2 * fDetail) * (1 - fDetail)) + point[n][Y] * (fDetail * fDetail);
			result.z = point[n - 2][Z] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Z] * ((2 * fDetail) * (1 - fDetail)) + point[n][Z] * (fDetail * fDetail);
		}
		else if (type == DRAW_RAIL)
		{
			if (count % 2 == 0)
			{
				result.x = point[n - 2][X] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][X] * ((2 * fDetail) * (1 - fDetail)) + point[n][X] * (fDetail * fDetail);
				result.y = point[n - 2][Y] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Y] * ((2 * fDetail) * (1 - fDetail)) + point[n][Y] * (fDetail * fDetail);
				result.z = point[n - 2][Z] * ((1 - fDetail) * (1 - fDetail)) + point[n - 1][Z] * ((2 * fDetail) * (1 - fDetail)) + point[n][Z] * (fDetail * fDetail);
				if (Camera_State == SET_ROAD)
				{
					glBegin(GL_LINES);
					glVertex3f(result.x - 5, 0, result.z);
					glVertex3f(result.x + 5, 0, result.z);
					glEnd();
				}
				else
				{
					glBegin(GL_LINES);
					glVertex3f(result.x - 5, result.y, result.z);
					glVertex3f(result.x + 5, result.y, result.z);
					glEnd();
				}
			}
		}
	}
	
	if (type != DRAW_RAIL)
		return result;
	else
	{
		Point3D none;
		none.x = 0.f;
		none.y = 0.f;
		none.z = 0.f;
		return none;
	}
}

void Tree::Render_Tree()
{
	glPushMatrix();
		glTranslatef(fx, 0.f, fz);

		glPushMatrix(); // 나무몸통
			glColor3f(0.8f, 0.3f, 0.2f);
			glTranslatef(0.f, 10.f, 0.f);
			glScalef(1.f, 4.f, 1.f);
			glutSolidCube(10);
		glPopMatrix();

		glPushMatrix(); // 맨 위쪽 잎
			glColor3f(0.f, 1.f, 0.f);
			glTranslatef(0.f, 45.f, 0.f);
			glRotatef(-90.f, 1.f, 0.f, 0.f);
			glutSolidCone(15, 30, 8, 8);
		glPopMatrix();

		glPushMatrix(); // 중간 잎
			glColor3f(0.2f, 1.f, 0.2f);
			glTranslatef(0.f, 30.f, 0.f);
			glRotatef(-90.f, 1.f, 0.f, 0.f);
			glutSolidCone(20, 40, 8, 8);
		glPopMatrix();

		glPushMatrix(); // 아랫 잎
			glColor3f(0.f, 0.6f, 0.f);
			glTranslatef(0.f, 20.f, 0.f);
			glRotatef(-90.f, 1.f, 0.f, 0.f);
			glutSolidCone(20, 40, 8, 8);
		glPopMatrix();

	glPopMatrix();
}

void Set_Coaster()
{
	for (int i = 0; i < COASTER_NUM; ++i)
	{
		float fDetail = (float)1 / COASTER_NUM * (COASTER_NUM - i) - 0.2;
		coaster[i].Y_angle = atan2f((point[2][Z] - point[0][Z]), (point[2][X] - point[0][X])) / 3.141592f * 180.0f;
		coaster[i].x = point[0][X] * ((1 - fDetail) * (1 - fDetail)) + point[1][X] * ((2 * fDetail) * (1 - fDetail)) + point[2][X] * (fDetail * fDetail);
		coaster[i].y = point[0][Y] * ((1 - fDetail) * (1 - fDetail)) + point[1][Y] * ((2 * fDetail) * (1 - fDetail)) + point[2][Y] * (fDetail * fDetail);
		coaster[i].z = point[0][Z] * ((1 - fDetail) * (1 - fDetail)) + point[1][Z] * ((2 * fDetail) * (1 - fDetail)) + point[2][Z] * (fDetail * fDetail);
		coaster[i].count = 2;
		coaster[i].move_rail = fDetail;
	}
}

void Render_Coaster()
{
	for (int i = 0; i < COASTER_NUM; ++i)
	{
		glPushMatrix();
		glTranslatef(0.f, 15.f, 0.f);
		glTranslatef(coaster[i].x, coaster[i].y, coaster[i].z);
		glRotatef(coaster[i].X_angle, 1.f, 0.f, 0.f);
		glRotatef(-coaster[i].Y_angle, 0.f, 1.f, 0.f);
		printf("X = %f , Y = %f\n", &coaster[0].X_angle, &coaster[0].Y_angle);
		glScalef(1.6f, 1.f, 1.f);
		glColor3f(1.f, 0.f, 0.f);
		glutSolidCube(10);
		glColor3f(0.f, 0.f, 0.f);
		glLineWidth(3.f);
		glutWireCube(10);
		glPopMatrix();
	}
}

void Render_Tunnel()
{
	if (Camera_State == SET_ROAD)
	{
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.5f);
		glTranslatef(tunnel.x, 0.f, tunnel.z);
		glRotatef(-tunnel.Y_angle + 90.f, 0.f, 1.f, 0.f);
		glScalef(1.f, 1.f, 3.f);
		glutSolidTorus(10, 40, 20, 20);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.5f);
		glTranslatef(tunnel.x, tunnel.y, tunnel.z);
		glRotatef(-tunnel.Y_angle + 90.f, 0.f, 1.f, 0.f);
		glRotatef(tunnel.X_angle, 1.f, 0.f, 0.f);
		glScalef(1.f, 1.f, 5.f);
		glutSolidTorus(10, 40, 20, 20);
		glPopMatrix();
	}
}

void Render_Bullet(int n)
{
	if (bullet[n].exist)
	{
		glPushMatrix();
		glTranslatef(bullet[n].x, bullet[n].y + 15, bullet[n].z);
		glRotatef(bullet[n].X_angle, 1.f, 0.f, 0.f);
		glRotatef(-bullet[n].Y_angle + 90.f, 0.f, 1.f, 0.f);
		glTranslatef(0.f, 0.f, bullet[n].move);

		glColor3f(1.f, 0.f, 0.f);
		glutSolidSphere(4, 10, 10);
		glPopMatrix();
	}
}