#include <GL/glut.h>
#include <cmath>
#include <cstdio>


int xAngle, yAngle;
// угол поворота камеры
double angle = 0.0;
//Ключи статуса камеры. Переменные инициализируются нулевыми значениями
//когда клавиши не нажаты
double deltaAngle = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

bool xRotate = false, yRotate = false, zRotate = false;


GLuint textureID;
struct {
    int W;
    int H;
    unsigned char *Image;
} getTexture;

GLfloat xrot;
GLfloat yrot;
GLfloat zrot;

void draw();
int LoadTexture(char *FileName);
void changeSize(int w, int h);
void drawBorder();
void drawParallelepiped(double x, double y, double zLeft, double zRight, double red, double green, double blue);
void drawCylinder(int slices, int stacks, double x, double y, double zRight, double zLeft,
                  double red, double green, double blue, double opacity);
void mouseButton(int button, int state, int x, int y);
void mouseMove(int x, int y);
void processSpecialKeys(int key, int xx, int yy);
void processNormalKeys(unsigned char key, int x, int y);

int main(int args, char **argv) {
    glutInit(&args, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Lab7");
    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(draw);
    if (LoadTexture((char *) "../texture.bmp") != 1) {
        printf("Не удалось загрузить изображение\n");
    }
    glutReshapeFunc(changeSize);
    glutIdleFunc(draw);

    glutKeyboardFunc(processNormalKeys);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

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

int LoadTexture(char *FileName) {
    FILE *F;
//     Открываем файл
    if ((F = fopen(FileName, "rb")) == nullptr)
        return 0;
//    Перемещаемся в bmp-файле на нужную позицию, и считываем ширину и длинну
    fseek(F, 18, SEEK_SET);
    fread(&(getTexture.W), 2, 1, F);
    fseek(F, 2, SEEK_CUR);
    fread(&(getTexture.H), 2, 1, F);

    printf("%d x %d\n", getTexture.W, getTexture.H);

//     Выделяем память под изображение. Если память не выделилась, закрываем файл и выходим с ошибкой
    if ((getTexture.Image = (unsigned char *) malloc(sizeof(unsigned char) * 3 * getTexture.W * getTexture.H)) ==
        nullptr) {
        fclose(F);
        return 0;
    }
//     Считываем изображение в память по 3 бита, то бишь RGB для каждого пикселя
    fseek(F, 30, SEEK_CUR);
    fread(getTexture.Image, 3, getTexture.W * getTexture.H, F);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, getTexture.W, getTexture.H, GL_RGB, GL_UNSIGNED_BYTE, getTexture.Image);
    free(getTexture.Image);
    fclose(F);

    return 1;
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
            0, 0, 10,
            0, 0, 0,
            0, 1, 0);
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);

//    glRotatef(angle, xRotate, yRotate, zRotate);

    drawParallelepiped(0.52, 3, 0.0, 0.5, 1, 1, 1);
    drawCylinder(360, 360, 1.7, 1.4, 0.52, -0.02, 1, 1, 1, 0.0);
    drawCylinder(360, 360, 2.7, 2.4, 0.51, -0.01, 1, 1, 1, 1.0);

    glutSwapBuffers();

//    xrot += 0.3f;
//    yrot += 0.2f;
//    zrot += 0.4f;
}


void cylinder(int slices, int stacks, GLfloat x, GLfloat y, GLfloat depth,
              GLubyte red, GLubyte green, GLubyte blue, GLubyte opacity) {

    //main part of cylinder
    glEnable(GL_NORMALIZE);
    glColor3ub(red, green, blue);
    for (int j = 0; j < stacks; ++j) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= slices; ++i) {
            double rad = i * 2 * M_PI / slices;
            double angleX = sin(rad) * x;
            double angleY = cos(rad) * y;
            double angleZ = j / stacks - depth / 2;
            glNormal3f(angleX, angleY, 0.0f);
            glTexCoord2d(angleX, angleY);
            glVertex3f(angleX, angleY, angleZ);
            angleZ = (j + 1) * depth / 2 / stacks;
            glTexCoord2d(angleX, angleY);
            glVertex3f(angleX, angleY, angleZ);
        }
        glEnd();
    }
    //top of cylinder
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4ub(red, green, blue, opacity);

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2d(0, 0);
    glVertex3f(0.0f, 0.0f, 0);
    for (int i = 0; i <= 50; ++i) {
        double rad = i * 2 * M_PI / 50;
        glTexCoord2d(sin(rad) * 100, cos(rad) * 100);
        glVertex3f(sin(rad) * 100, cos(rad) * 100, 0);
    }
    glEnd();

    //bottom of cylinder
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2d(0, 0);
    glVertex3f(0.0f, 0.0f, -depth / 2);
    for (int i = 0; i <= slices; ++i) {
        double rad = i * 2 * M_PI / slices;
        glTexCoord2d(sin(rad) * x, cos(rad) * y);
        glVertex3f(sin(rad) * x, cos(rad) * y, -depth / 2);
    }
    glEnd();

}



void cylinder111(int slices, int stacks, GLfloat x, GLfloat y, GLfloat depth,
              GLubyte red, GLubyte green, GLubyte blue, GLubyte opacity) {

    //main part of cylinder
    glEnable(GL_NORMALIZE);
    glColor3ub(red, green, blue);
    for (int j = 0; j < stacks; ++j) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= slices; ++i) {
            double rad = i * 2 * M_PI / slices;
            double angleX = sin(rad) * x;
            double angleY = cos(rad) * y;
            double angleZ = j / stacks - depth / 2;
            glNormal3f(angleX, angleY, 0.0f);
            glTexCoord2d(angleX, angleY);
            glVertex3f(angleX, angleY, angleZ);
            angleZ = (j + 1) * depth / 2 / stacks;
            glTexCoord2d(angleX, angleY);
            glVertex3f(angleX, angleY, angleZ);
        }
        glEnd();
    }
    //top of cylinder
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4ub(red, green, blue, opacity);

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2d(0, 0);
    glVertex3f(0.0f, 0.0f, 0);
    for (int i = 0; i <= 50; ++i) {
        double rad = i * 2 * M_PI / 50;
        glTexCoord2d(sin(rad) * 100, cos(rad) * 100);
        glVertex3f(sin(rad) * 100, cos(rad) * 100, 0);
    }
    glEnd();

    //bottom of cylinder
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2d(0, 0);
    glVertex3f(0.0f, 0.0f, -depth / 2);
    for (int i = 0; i <= slices; ++i) {
        double rad = i * 2 * M_PI / slices;
        glTexCoord2d(sin(rad) * x, cos(rad) * y);
        glVertex3f(sin(rad) * x, cos(rad) * y, -depth / 2);
    }
    glEnd();

}

void borders(float x, float y, GLfloat depth) {
    glColor3d(0, 0, 0);

    // + Z
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex3d(cos(rad) * x, sin(rad) * y, depth / 2);
    }
    glEnd();

    // -Z
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex3d(cos(rad) * x, sin(rad) * y, -depth / 2);
    }
    glEnd();

}

void draw111() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -15);

    //cylinder(360, 1, inCx, inCy, cz + 0.01, 255, 255, 255, 0); //inner
    //cylinder(360, 1, outCx, outCy, cz, 255, 255, 255, 255); //outer
    //borders(outCx, outCy, cz);
    //borders(inCx, inCy, cz + 0.01);

    glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y){
    switch(key){
        case 32: {
            int mod = glutGetModifiers();
            if (mod != GLUT_ACTIVE_CTRL) {
                xRotate = false;
                yRotate = false;
                zRotate = false;
            } else {
                xRotate = true;
                yRotate = true;
                zRotate = true;
            }
            break;
        }
        case 1:
            exit(1);
        default:break;
    }
}

void mouseButton(int button, int state, int x, int y) {

    // только при начале движения, если нажата левая кнопка
    if (button == GLUT_LEFT_BUTTON) {

        // когда кнопка отпущена
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
            yOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
            yOrigin = y;
        }
    }
}

void mouseMove(int x, int y) {

    // если левая кнопка опущена
    if (xOrigin >= 0 || yOrigin >= 0) {
        xrot = (y - yOrigin) * 0.5;
        yrot = (x - xOrigin) * 0.5f;
    }
}

void drawCylinder(int slices, int stacks,
                  double x, double y, double zRight, double zLeft,
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
            double angleZ = j * zRight / stacks;
            glNormal3f(angleX, angleY, 0.0f);
            glTexCoord2d(angleX, angleY);
            glVertex3f(angleX, angleY, angleZ);
            angleZ = (j + 1) * zRight / stacks;
            glTexCoord2d(angleX, angleY);
            glVertex3f(angleX, angleY, angleZ);
        }
        glEnd();
    }
    glDisable(GL_NORMALIZE);

    //top of cylinder
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4d(red, green, blue, opacity);

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, zLeft);
    for (int i = 0; i <= slices; ++i) {
        double rad = i * 2 * M_PI / slices;
        glTexCoord2d(sin(rad) * x, cos(rad) * y);
        glVertex3f(sin(rad) * x, cos(rad) * y, zLeft);
    }
    glEnd();

    //bottom of cylinder
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, zRight);
    for (int i = 0; i <= slices; ++i) {
        double rad = i * 2 * M_PI / slices;
        glTexCoord2d(sin(rad) * x, cos(rad) * y);
        glVertex3f(sin(rad) * x, cos(rad) * y, zRight);
    }
    glEnd();
    glDisable(GL_BLEND);

}

void drawParallelepiped(double x, double y, double zLeft, double zRight, double red, double green, double blue) {

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glColor3d(red, green, blue);

    glTexCoord2d(-x, y);
    glVertex3d(-x, y, zLeft);     //a
    glTexCoord2d(x, y);
    glVertex3d(x, y, zLeft);      //b
    glTexCoord2d(x, -y);
    glVertex3d(x, -y, zLeft);     //d
    glTexCoord2d(-x, -y);
    glVertex3d(-x, -y, zLeft);    //c

    glTexCoord2d(-x, -y);
    glVertex3d(-x, -y, zLeft);    //c
    glTexCoord2d(-x, -y);
    glVertex3d(-x, -y, zRight);    //g
    glTexCoord2d(-x, y);
    glVertex3d(-x, y, zRight);     //e
    glTexCoord2d(-x, y);
    glVertex3d(-x, y, zLeft);     //a

    glTexCoord2d(-x, y);
    glVertex3d(-x, y, zLeft);     //a
    glTexCoord2d(-x, y);
    glVertex3d(-x, y, zRight);     //e
    glTexCoord2d(x, y);
    glVertex3d(x, y, zRight);      //f
    glTexCoord2d(x, y);
    glVertex3d(x, y, zLeft);      //b

    glTexCoord2d(x, y);
    glVertex3d(x, y, zLeft);      //b
    glTexCoord2d(x, y);
    glVertex3d(x, y, zRight);      //f
    glTexCoord2d(x, -y);
    glVertex3d(x, -y, zRight);     //h
    glTexCoord2d(x, -y);
    glVertex3d(x, -y, zLeft);     //d

    glTexCoord2d(x, -y);
    glVertex3d(x, -y, zLeft);     //d
    glTexCoord2d(-x, -y);
    glVertex3d(-x, -y, zLeft);    //c
    glTexCoord2d(-x, -y);
    glVertex3d(-x, -y, zRight);    //g
    glTexCoord2d(x, -y);
    glVertex3d(x, -y, zRight);     //h

    glTexCoord2d(x, -y);
    glVertex3d(x, -y, zRight);     //h
    glTexCoord2d(-x, -y);
    glVertex3d(-x, -y, zRight);    //g
    glTexCoord2d(-x, y);
    glVertex3d(-x, y, zRight);     //e
    glTexCoord2d(x, y);
    glVertex3d(x, y, zRight);      //f

    glEnd();
    glFlush();

}

void drawBorder() {
    //glColor3d(0, 0, 0);

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
