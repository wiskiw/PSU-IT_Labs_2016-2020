#include <GL/glut.h>
#include <cmath>


GLfloat angle = 0;

void draw();

void changeSize(int w, int h);

void drawBorder();

void drawParallelepiped(double x, double y, double zRight, double zLeft, double red, double green, double blue);

void drawCylinder(int slices, int stacks, double x, double y, double zLeft, double zRight,
                  double red, double green, double blue, double opacity);

void drawCircle();

int main(int args, char **argv) {
    glutInit(&args, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Lab7");
    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(draw);
    glutReshapeFunc(changeSize);
    glutIdleFunc(draw);

    glutMainLoop();
    return 0;
}

void changeSize(int w, int h) {
    if (h == 0) {
        h = 1;
    }
    double ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
            0, 0, 10,
            0, 0, 0,
            0, 1, 0);
    glRotatef(angle, 0, 1, 0);

    //drawParallelepiped(0.52, 3, 0.0, 0.5, 1, 1, 0);
    //drawCylinder(360, 360, 1.7, 1.4, 0.52, -0.02, 1, 1, 0, 0.0);
    //drawCylinder(360, 360, 2.7, 2.4, 0.51, -0.01, 1, 1, 0, 1.0);
    drawCylinder(360, 360, 0.5, 0.8, 0.52, -0.02, 1, 1, 0, 0);
    drawCylinder(360, 360, 1, 1.2, 0.51, -0.01, 1, 1, 0, 1);
    //drawCylinder(360, 360, -1, -1.3, 0.51, -0.01, 1, 1, 0, 1);

    drawBorder();
//    drawCircle();

    glutSwapBuffers();

    angle += 1;

}

void drawCircle() {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1, 0, 0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glEnd();

}

void drawCylinder(int slices, int stacks,
                  double x, double y, double zLeft, double zRight,
                  double red, double green, double blue, double opacity) {

    //main part of cylinder
    glEnable(GL_NORMALIZE);
    glColor3d(red, green, blue);
    for (int j = 0; j < stacks; ++j) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= slices; ++i) {
            double rad = i * 2 * M_PI / slices;
            double angleX = sin(rad) * x;
            double angleY = cos(rad) * y;
            double angleZ = j * zLeft / stacks;
            glNormal3f(angleX, angleY, 0.0f);
            glVertex3f(angleX, angleY, angleZ);
            angleZ = (j + 1) * zLeft / stacks;
            glVertex3f(angleX, angleY, angleZ);
        }
        glEnd();
    }

    //top of cylinder
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4d(red, green, blue, opacity);

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, zRight);
    for (int i = 0; i <= slices; ++i) {
        double rad = i * 2 * M_PI / slices;
        glVertex3f(sin(rad) * x, cos(rad) * y, zRight);
    }
    glEnd();

    //bottom of cylinder
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, zLeft);
    for (int i = 0; i <= slices; ++i) {
        double rad = i * 2 * M_PI / slices;
        glVertex3f(sin(rad) * x, cos(rad) * y, zLeft);
    }
    glEnd();

}

void drawParallelepiped(double x, double y, double zRight, double zLeft, double red, double green, double blue) {

    glBegin(GL_QUADS);

    glColor3d(red, green, blue);
    glVertex3d(-x, y, zRight);     //a
    glVertex3d(x, y, zRight);      //b
    glVertex3d(x, -y, zRight);     //d
    glVertex3d(-x, -y, zRight);    //c

    glVertex3d(-x, -y, zRight);    //c
    glVertex3d(-x, -y, zLeft);    //g
    glVertex3d(-x, y, zLeft);     //e
    glVertex3d(-x, y, zRight);     //a

    glVertex3d(-x, y, zRight);     //a
    glVertex3d(-x, y, zLeft);     //e
    glVertex3d(x, y, zLeft);      //f
    glVertex3d(x, y, zRight);      //b

    glVertex3d(x, y, zRight);      //b
    glVertex3d(x, y, zLeft);      //f
    glVertex3d(x, -y, zLeft);     //h
    glVertex3d(x, -y, zRight);     //d

    glVertex3d(x, -y, zRight);     //d
    glVertex3d(-x, -y, zRight);    //c
    glVertex3d(-x, -y, zLeft);    //g
    glVertex3d(x, -y, zLeft);     //h

    glVertex3d(x, -y, zLeft);     //h
    glVertex3d(-x, -y, zLeft);    //g
    glVertex3d(-x, y, zLeft);     //e
    glVertex3d(x, y, zLeft);      //f

    glEnd();
    glFlush();

}

void drawBorder() {
    glColor3d(0, 0, 0);

    glBegin(GL_LINE_STRIP);

    glVertex3d(-0.53, -3, -0.03);   //c
    glVertex3d(-0.53, 3, -0.03);    //a
    glVertex3d(0.53, 3, -0.03);     //b
    glVertex3d(0.53, -3, -0.03);    //d
    glVertex3d(-0.53, -3, -0.03);   //c

    glVertex3d(-0.53, -3, 0.53);    //g
    glVertex3d(-0.53, 3, 0.53);     //e
    glVertex3d(-0.53, 3, -0.03);    //a

    glVertex3d(-0.53, 3, 0.53);     //e
    glVertex3d(0.53, 3, 0.53);      //f
    glVertex3d(0.53, 3, -0.03);     //b

    glVertex3d(0.53, 3, 0.53);      //f
    glVertex3d(0.53, -3, 0.53);     //h
    glVertex3d(0.53, -3, -0.03);    //d

    glVertex3d(-0.53, -3, -0.03);   //c
    glVertex3d(-0.53, -3, 0.53);    //g
    glVertex3d(0.53, -3, 0.53);     //h

    glVertex3d(-0.53, -3, 0.53);    //g
    glVertex3d(-0.53, 3, 0.53);     //e
    glVertex3d(0.53, 3, 0.53);      //f

    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex3d(cos(rad) * 2.7, sin(rad) * 2.4, -0.03);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex3d(cos(rad) * 2.7, sin(rad) * 2.4, 0.53);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex3d(cos(rad) * 1.7, sin(rad) * 1.4, -0.03);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex3d(cos(rad) * 1.7, sin(rad) * 1.4, 0.53);
    }
    glEnd();

}
