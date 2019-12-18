#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <cmath>


void draw();
void changeSize(int w, int h);

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Lab6");

    glutDisplayFunc(draw);
    //glutReshapeFunc(changeSize);

    glutMainLoop();

    return 0;
}

void draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1,1,0);
    glVertex2f(0.0, 0.0);
    for (int i = 0; i <= 51; i++) {
        double angle = (double)  i / 50 * M_PI * 2.0;
        glVertex2f(cosf(angle) * 1, sinf(angle) * 1);
    }
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glColor3d(0.67, 1, 0.18);
    glVertex3f(0.0, 1, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.54, 0.27, 0.07);
    glVertex2f(0.0, 0.0);
    for (int i = 0; i <= 51; i++) {
        double angle = (double)i / 50 * M_PI * 2.0;
        glVertex2f(cosf(angle) * 0.65, sinf(angle) * 0.65);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}

void changeSize(int w, int h) {

    if (h == 0) {
        h = 1;
    }
    float ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}