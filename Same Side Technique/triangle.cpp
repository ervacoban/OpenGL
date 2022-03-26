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

const Vector p1(35, 35), p2(200, 265), p3(365, 35);
Vector mouse;
const GLsizei winWidth = 400, winHeight = 300;
const GLubyte text[2][7] = { {'i', 'n', 's', 'i', 'd', 'e', ' '}, {'o', 'u', 't', 's', 'i', 'd', 'e'} };

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

bool isInsideTriangle()
{
    if (sameSide(p1, p2, p3) &&
        sameSide(p2, p1, p3) &&
        sameSide(p3, p1, p2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void printText() 
{
    int i = 0;
    if (isInsideTriangle())
    {
        i = 0;
    }
    else
    {
        i = 1;
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
    glFlush();
}

void initFunction(void)
{
    glClearColor(0.0f, 0.5f, 0.5f, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLdouble(winWidth), 0.0, GLdouble(winHeight));
}

void displayFunction(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
    glVertex2i(p3.x, p3.y);
    glEnd();
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Point in Triangle");
    glutDisplayFunc(displayFunction);
    glutMouseFunc(mouseFunction);
    initFunction();
    glutMainLoop();
}