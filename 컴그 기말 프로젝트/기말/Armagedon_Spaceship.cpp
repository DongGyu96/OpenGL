#include "stdafx.h"
#include "Armagedon_Spaceship.h"

void Spaceship::Render()
{
	glPushMatrix();

	glTranslatef(0.f, 0.f, -10.f);

		glPushMatrix(); // ������
			glTranslatef(0.f, 0.f, 20.f);
			glScalef(0.8f, 0.8f, 2.f);

			for (float angle = 0.f; angle < 360.f; angle += 0.25f)
			{
				glColor3f(0.6f, 0.6f, 0.6f);
				glRotatef(angle, 0.f, 0.f, 1.f);
				glutSolidCube(26);
			}
		glPopMatrix();

		glPushMatrix(); // �պκ�
			glColor3f(0.7f, 0.7f, 0.7f);
			glTranslatef(0.f, 0.f, -5.f);
			glRotatef(180.f, 0.f, 1.f, 0.f);
			glScalef(1.f, 1.f, 0.85f);
			glutSolidCone(15, 40, 10, 4);

			glColor3f(1.f, 1.f, 1.f); // ������
			glTranslatef(0.f, 7.f, 10.f);
			glScalef(1.f, 1.f, 2.f);
			glutSolidSphere(5, 20, 20);
		glPopMatrix();

		glPushMatrix(); // ���ʳ���
			glColor3f(0.5f, 0.5f, 0.5f);
			glTranslatef(0.f, 0.f, 20.f);
			glRotatef(-80.f, 0.f, 1.f, 0.f);
			glRotatef(-10.f, 1.f, 0.f, 0.f);
			glScalef(1.1f, 0.5f, 1.1f);
			glutSolidCone(25, 60, 10, 4);

			glColor3f(0.2f, 0.2f, 0.2f);
			glTranslatef(-5.f, -10.f, 30.f);
			glScalef(1.f, 0.6f, 1.f);
			glutSolidCube(20);
		glPopMatrix();

		glPushMatrix(); // �����ʳ���
			glColor3f(0.5f, 0.5f, 0.5f);
			glTranslatef(0.f, 0.f, 20.f);
			glRotatef(80.f, 0.f, 1.f, 0.f);
			glRotatef(-10.f, 1.f, 0.f, 0.f);
			glScalef(1.1f, 0.5f, 1.1f);
			glutSolidCone(25, 60, 10, 4);

			glColor3f(0.2f, 0.2f, 0.2f);
			glTranslatef(5.f, -10.f, 30.f);
			glScalef(1.f, 0.6f, 1.f);
			glutSolidCube(20);
		glPopMatrix();

		glPushMatrix(); // ���� ��
			glColor3f(0.2f, 0.2f, 0.2f);
			glTranslatef(0.f, -5.f, 15.f);
			glScalef(0.8f, 0.8f, 2.f);
			glutSolidCube(26);
		glPopMatrix();

		glPushMatrix(); // ���� �պκ� ���
			glColor3f(0.4f, 0.4f, 0.4f);
			glTranslatef(-10.f, 0.f, -12.f);
			glRotatef(-25.f, 0.f, 1.f, 0.f);
			glScalef(1.f, 1.f, 4.f);
			glutSolidCube(10);
		glPopMatrix();

		glPushMatrix(); // ������ �պκ� ���
			glColor3f(0.4f, 0.4f, 0.4f);
			glTranslatef(10.f, 0.f, -12.f);
			glRotatef(25.f, 0.f, 1.f, 0.f);
			glScalef(1.f, 1.f, 4.f);
			glutSolidCube(10);
		glPopMatrix();

		glPushMatrix(); // �պκ� �������κ�
			glColor3f(0.4f, 0.4f, 0.4f);
			glTranslatef(0.f, 0.f, -18.f);
			glScalef(1.f, 1.f, 3.f);
			glutSolidSphere(7, 20, 20);
		glPopMatrix();

		glPushMatrix(); // ���� ����
			glColor3f(0.6f, 0.6f, 0.6f);
			glTranslatef(0.f, 10.f, 35.f);
			glRotatef(270.f, 1.f, 0.f, 0.f);
			glRotatef(40.f, 1.f, 0.f, 0.f);
			glScalef(0.6f, 1.f, 1.f);
			glutSolidCone(10, 25, 10, 4);
		glPopMatrix();

		glPushMatrix(); // ���� ���� ���
			glColor3f(0.5f, 0.5f, 0.5f);
			glTranslatef(0.f, 10.f, 25.f);
			glRotatef(-10.f, 1.f, 0.f, 0.f);
			glScalef(1.f, 1.2f, 2.f);
			glutSolidCube(10);
		glPopMatrix();

		glPushMatrix(); // ��ⱸ
			glColor3f(0.4f, 0.4f, 0.4f);
			glTranslatef(0.f, 0.f, 45.f);
			glutSolidTorus(4, 12, 10, 10);
		glPopMatrix();

		glPushMatrix(); // �Ҳ�
			glTranslatef(0.f, 0.f, 45.f);
			glColor3f(1.f, 0.3f, 0.0f);
			glutSolidSphere(8, 20, 20);
			glTranslatef(0.f, 0.f, 10.f);
			glRotatef(180.f, 1.f, 0.f, 0.f);
			glColor3f(1.f, 0.5f, 0.2f);
			glutSolidCone(13, 25, 10, 4);
		glPopMatrix();
	glPopMatrix();
}

void Spaceship::WireRender()
{
	glPushMatrix();

		glTranslatef(0.f, 0.f, -10.f);
		glPushMatrix(); // ������
			glTranslatef(0.f, 0.f, 20.f);
			glScalef(0.8f, 0.8f, 2.f);
			int count = 0;
			for (float angle = 0.f; angle < 360.f; angle += 0.25f)
			{
				glRotatef(angle, 0.f, 0.f, 1.f);
				if (count % 300 == 0)
				{
					glColor3f(0.0f, 0.0f, 0.0f);
					glutWireCube(26);
				}
				count++;
			}
		glPopMatrix();

		glPushMatrix(); // �պκ�
			glTranslatef(0.f, 0.f, -5.f);
			glRotatef(180.f, 0.f, 1.f, 0.f);
			glScalef(1.f, 1.f, 0.85f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCone(15, 40, 10, 4);

			glColor3f(0.f, 0.f, 0.f); // ������
			glTranslatef(0.f, 7.f, 10.f);
			glScalef(1.f, 1.f, 2.f);
			glutWireSphere(5, 10, 10);
		glPopMatrix();

		glPushMatrix(); // ���ʳ���
			glTranslatef(0.f, 0.f, 20.f);
			glRotatef(-80.f, 0.f, 1.f, 0.f);
			glRotatef(-10.f, 1.f, 0.f, 0.f);
			glScalef(1.1f, 0.5f, 1.1f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCone(25, 60, 10, 4);

			glTranslatef(-5.f, -10.f, 30.f);
			glScalef(1.f, 0.6f, 1.f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(20);
		glPopMatrix();

		glPushMatrix(); // �����ʳ���
			glTranslatef(0.f, 0.f, 20.f);
			glRotatef(80.f, 0.f, 1.f, 0.f);
			glRotatef(-10.f, 1.f, 0.f, 0.f);
			glScalef(1.1f, 0.5f, 1.1f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCone(25, 60, 10, 4);

			glTranslatef(5.f, -10.f, 30.f);
			glScalef(1.f, 0.6f, 1.f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(20);
		glPopMatrix();

		glPushMatrix(); // ���� ��
			glTranslatef(0.f, -5.f, 15.f);
			glScalef(0.8f, 0.8f, 2.f);

			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(26);
		glPopMatrix();

		glPushMatrix(); // ���� �պκ� ���
			glTranslatef(-10.f, 0.f, -12.f);
			glRotatef(-25.f, 0.f, 1.f, 0.f);
			glScalef(1.f, 1.f, 4.f);

			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(10);
		glPopMatrix();

		glPushMatrix(); // ������ �պκ� ���
			glTranslatef(10.f, 0.f, -12.f);
			glRotatef(25.f, 0.f, 1.f, 0.f);
			glScalef(1.f, 1.f, 4.f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireCube(10);
		glPopMatrix();

		glPushMatrix(); // �պκ� �������κ�
			glTranslatef(0.f, 0.f, -18.f);
			glScalef(1.f, 1.f, 3.f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glutWireSphere(7, 20, 20);
		glPopMatrix();

		glPushMatrix(); // ���� ����
			glTranslatef(0.f, 10.f, 35.f);
			glRotatef(270.f, 1.f, 0.f, 0.f);
			glRotatef(40.f, 1.f, 0.f, 0.f);
			glScalef(0.6f, 1.f, 1.f);
			glColor3f(0.f, 0.f, 0.f);
			glutWireCone(10, 25, 10, 4);
		glPopMatrix();

		glPushMatrix(); // ���� ���� ���
			glTranslatef(0.f, 10.f, 25.f);
			glRotatef(-10.f, 1.f, 0.f, 0.f);
			glScalef(1.f, 1.2f, 2.f);
			glColor3f(0.f, 0.f, 0.f);
			glutWireCube(10);
		glPopMatrix();

		glPushMatrix(); // ��ⱸ
			glTranslatef(0.f, 0.f, 45.f);
			glColor3f(0.f, 0.f, 0.f);
			glutWireTorus(4, 12, 10, 10);
		glPopMatrix();

	glPopMatrix();
}