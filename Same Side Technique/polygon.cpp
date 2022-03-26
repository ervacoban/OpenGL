#include <gl/glut.h>

class Vector
{
public:
    long long int x, y, z;
    Vector() {}
    Vector(long long int  x, long long int  y, long long int  z = 0) // 2d vector z coordinate
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    friend Vector operator -(Vector v1, Vector v2) // vector subtraction overload
    {
        Vector sub(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
        return sub;
    }
};

const Vector p1(365, 185), p2(155, 245), p3(35, 205), p4(55, 35), p5(175, 25), p6(315, 55);
const long long int coordinates[6][2] = { {p1.x, p1.y}, {p2.x, p2.y}, {p3.x, p3.y}, {p4.x, p4.y}, {p5.x, p5.y}, {p6.x, p6.y} };
Vector mouse;
const GLsizei winWidth = 400, winHeight = 300;
const GLubyte text[2][7] = { {'i', 'n', 's', 'i', 'd', 'e', ' '}, {'o', 'u', 't', 's', 'i', 'd', 'e'}};

long long int dotProduct(Vector v1, Vector v2) // dot product
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector crossProduct(Vector v1, Vector v2) // cross product
{
    Vector a;
    a.x = v1.y * v2.z - v1.z * v2.y;
    a.y = v1.z * v2.x - v1.x * v2.z;
    a.z = v1.x * v2.y - v1.y * v2.x;
    return a;
}

bool sameSide(Vector v1, Vector v2, Vector v3)
{
    Vector cp1, cp2;
    cp1 = crossProduct(v2 - v3, mouse - v3);
    cp2 = crossProduct(v2 - v3, v1 - v3);
    if (dotProduct(cp1, cp2) >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isInsideTriangle(Vector v1, Vector v2, Vector v3)
{
    if (sameSide(v1, v2, v3) &&
        sameSide(v2, v1, v3) &&
        sameSide(v3, v1, v2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool triangeControl(int trianglePoint) // divide polygon to triangles
{
    Vector v1(coordinates[0][0], coordinates[0][1]),
        v2(coordinates[trianglePoint][0], coordinates[trianglePoint][1]),
        v3(coordinates[trianglePoint + 1][0], coordinates[trianglePoint + 1][1]);
    return isInsideTriangle(v1, v2, v3);
}

void printText()
{
    int i = 1;
    bool control = false;
    for (int k = 1; k < 5; k++)
    {
        control = triangeControl(k);
        if (control) {
            i = 0;
            break;
        }
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(10, i * 15 + 5);
    for (int k = 0; k < 7; k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i][k]);
    }
}

void mouseFunction(int button, int state, int x, int y)
{
    y = winHeight - y; 
    mouse.x = x;
    mouse.y = y;
    glColor3f(0.0f, 0.0f, 0.0f); // mouse point color
    glPointSize(3.0f); // mouse point size
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        glBegin(GL_POINTS);
        glVertex2i(mouse.x, mouse.y);
        glEnd();
        printText();
    }
}

void keyboardFunction(GLubyte key, GLint xMouse, GLint yMouse)
{
    switch (key)
    {
    case 27: // 27 = esc
        exit(0); // exit application
        break;
    }
}

void initFunction(void)
{
    glClearColor(0.0f, 0.5f, 0.5f, 0.0); // arka plan rengi
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLdouble(winWidth), 0.0, GLdouble(winHeight));
}

void displayFunction(void) {
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
    glVertex2i(p3.x, p3.y);
    glVertex2i(p4.x, p4.y);
    glVertex2i(p5.x, p5.y);
    glVertex2i(p6.x, p6.y);
    glEnd();
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Point in Polygon");
    glutDisplayFunc(displayFunction);
    glutKeyboardUpFunc(keyboardFunction);
    glutMouseFunc(mouseFunction);
    initFunction();
    glutMainLoop();
}