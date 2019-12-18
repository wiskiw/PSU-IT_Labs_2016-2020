#include <GL/gl.h>
#include <GL/freeglut.h>

#include <cmath>

const int WINDOW_LENGTH = 400;
const int WINDOW_HEIGTH = 400;
const float SCALE = 1.4;

void redraw();

void ellips(float x, float y, float z, float rX, float rY, float angle,
            GLubyte rgbGreen, GLubyte rgbRed, GLubyte rgbBlue);

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_LENGTH, WINDOW_HEIGTH);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("L6");
    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, WINDOW_LENGTH, WINDOW_HEIGTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15, 15, -15, 15);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glutDisplayFunc(redraw);

    glutMainLoop();

    return 0;
}

void redraw() {
    // очистка буфера цвета и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glScalef(SCALE, SCALE, 1);

    glBegin(GL_TRIANGLES);
    glColor3ub(255, 255, 0);
    glVertex3f(2, 3.5, 0);
    glVertex3f(0.0f, 6.5, 0);
    glVertex3f(-2, 3.5, 0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0);
    glVertex3f(2, 3.5, 0.001);
    glVertex3f(0.0f, 6.5, 0.001);
    glVertex3f(-2, 3.5, 0.001);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(0, 255, 0);
    glVertex3f(-3.5, -1.5, 0.00);
    glVertex3f(3.5, -1.5, 0.00);
    glVertex3f(3.5, -3.5, 0.00);
    glVertex3f(-3.5, -3.5, 0.00);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0);
    glVertex3f(-3.5, -1.5, 0.01);
    glVertex3f(3.5, -1.5, 0.01);
    glVertex3f(3.5, -3.5, 0.01);
    glVertex3f(-3.5, -3.5, 0.01);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(0, 255,0);
    glVertex3f(2, 3.5, 0.02);
    glVertex3f(-2, 3.5, 0.02);
    glVertex3f(-2, -3.5, 0.02);
    glVertex3f(2, -3.5, 0.02);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0);
    glVertex3f(2, 3.5, 0.03);
    glVertex3f(-2, 3.5,0.03);
    glVertex3f(-2, -3.5, 0.03);
    glVertex3f(2, -3.5, 0.03);
    glEnd();

    ellips(2.7, -4.9, 0, 0.7, 1.1, 30, 255, 0, 0);
    ellips(-2.7, -4.9, -0.1, 0.7, 1.1, -30, 255, 0, 0);
    ellips(0, -4.9, -0.1, 0.7, 1.1, 0, 255, 0, 0);

    // эллюмы
    ellips(0, 1.7, 0.8, 1, 1, 0, 255, 255, 0);
    ellips(0, -1.4, 0.8, 1, 1, 0, 255, 255, 0);

    glutSwapBuffers();
}

void ellips(float x, float y, float z, float rX, float rY, float angle,
            GLubyte rgbGreen, GLubyte rgbRed, GLubyte rgbBlue) {
    glPushMatrix();
    const double degRad = 3.14159 / 180.0;

    glNormal3f(x, y, z);
    glTranslatef(x, y, z);
    glRotatef(angle, false, false, true);

    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * degRad;
        glColor3ub(rgbGreen, rgbRed, rgbBlue);
        glVertex3f(cos(rad) * rX, sin(rad) * rY, 0);
    }
    glEnd();


    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float rad = i * degRad;
        glColor3ub(0, 0, 0);
        glVertex3f(cos(rad) * rX, sin(rad) * rY, 0.001);
    }
    glEnd();
    glPopMatrix();
}
