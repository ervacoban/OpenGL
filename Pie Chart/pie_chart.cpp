#include <glut.h>
#include <math.h>

const GLfloat percentage[13] = { 10.4, 7.2, 6.5, 5.0, 4.5, 4.0, 3.9, 3.9, 3.3, 3.3, 3.2, 3.0, 2.7 };
const GLfloat countries = 13;
const GLfloat colors[13][3] = { {0.31f, 0.5f, 0.74f}, {0.75f, 0.31f, 0.3f}, {0.6f, 0.73f, 0.35f},
{0.5f, 0.39f, 0.64f}, {0.29f, 0.67f, 0.78f}, {0.97f, 0.58f, 0.27f}, {0.17f, 0.3f, 0.46f}, {0.47f, 0.17f, 0.16f},
{0.37f, 0.46f, 0.18f}, {0.29f, 0.22f, 0.38f}, {0.15f, 0.41f, 0.49f}, {0.71f, 0.33f, 0.02f}, {0.44f, 0.59f, 0.79f} };
const GLubyte country[] = {
'T', 'U', 'R', 'I', 'R', 'L', 'I', 'R', 'N', 'G', 'B', 'R', 'R', 'U', 'S', 'M', 'A', 'R',
'N', 'Z', 'L', 'C', 'H', 'L',
'E', 'G', 'Y', 'P', 'O', 'L', 'J', 'P', 'N', 'S', 'A', 'U', 'Z', 'A', 'F' };
GLsizei winWidth = 400, winHeight = 300;

void drawCircle(GLint currentCountry, GLfloat x, GLfloat y, GLfloat radius, GLfloat startingAngle, GLfloat endingAngle) {
	const GLfloat pi = 22 / 7;
	GLfloat angle = startingAngle * (pi / 180);
	GLfloat angle_increment = endingAngle * (pi / (180 * countries));
	glColor3f(colors[currentCountry][0], colors[currentCountry][1], colors[currentCountry][2]);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= countries; i++) {
		glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
		angle += angle_increment;
	}
	glEnd();
}

void countryNames(GLint currentCountry, GLfloat x, GLfloat y, GLfloat radius, GLfloat startingAngle,	GLfloat endingAngle) {
	const GLfloat pi = 22 / 7;
	GLfloat angle = (startingAngle + (endingAngle / 2)) * (pi / 180);
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(x + (radius * cos(angle)) / 1.5, y + (radius * sin(angle)) / 1.5);
	for (int k = 3 * currentCountry; k < 3 * currentCountry + 3; k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, country[k]);

}
void plotPieChart() {
	const GLfloat centerX = 200;
	const GLfloat centerY = 150;
	GLfloat startingAngle = 0;
	GLfloat endAngle;
	GLfloat angleIncrement;
	const GLfloat radius = 100;
	GLint totalBan = 0;
	for (int i = 0; i < countries; i++)
		totalBan += percentage[i];
	for (int i = 0; i < countries; i++) {
		endAngle = percentage[i] / totalBan * 360.0f;
		drawCircle(i, centerX, centerY, radius, startingAngle, endAngle);
		startingAngle += endAngle;
	}

	startingAngle = 0;
	for (int i = 0; i < countries; i++) {
		endAngle = percentage[i] / totalBan * 360.0f;
		countryNames(i, centerX, centerY, radius, startingAngle, endAngle);
		startingAngle += endAngle;
	}
}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	plotPieChart();
	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
	glClear(GL_COLOR_BUFFER_BIT);
	winWidth = newWidth;
	winHeight = newHeight;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Pie Chart");
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}