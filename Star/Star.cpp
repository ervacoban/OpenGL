#include <tchar.h>
#include <glut.h>

const int p1[] = { 35, 35 }, p2[] = { 100, 135 }, p3[] = { 165, 35 }, p4[] = { 25, 100 }, p5[] = { 175, 100 };

void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2iv(p1);
	glVertex2iv(p2);
	glVertex2iv(p3);
	glVertex2iv(p4);
	glVertex2iv(p5);
	glEnd();
	glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.5, 0.5, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 150);
}

int main(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Star");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
	return 0;
}