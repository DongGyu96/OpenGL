#include <gl/glut.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glRectf(-1.0f, 1.0f, -0.8f, 0.8f);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glRectf(0.8f, 0.8f, 1.0f, 1.0f);

	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glRectf(-0.1f, -0.1f, 0.1f, 0.1f);

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glRectf(-1.0f, -1.0f, -0.8f, -0.8f);

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glRectf(1.0f, -1.0f, 0.8f, -0.8f);

	glFlush();
}
GLvoid Reshape(int w, int h) 
{ 
	glViewport(0, 0, w, h);
}