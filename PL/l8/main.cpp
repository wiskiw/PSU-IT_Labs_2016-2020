#include <GL/glut.h>
#include <cmath>
#include <cstdio>

float SCALE = 2.5;

float outCx = 1.4f * SCALE;
float outCy = 1.7f * SCALE;

float inCx = 0.7f * SCALE;
float inCy = 0.9f * SCALE;

float cz = 0.5f * SCALE;


GLuint textureID;
struct {
    int W;
    int H;
    unsigned char *Image;
} getTexture;

void draw();

int LoadTexture(char *FileName);

void changeSize(int w, int h);

int main(int args, char **argv) {
    glutInit(&args, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("L8");
    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(draw);
    if (LoadTexture((char *) "../texture2.bmp") != 1) {
        printf("Не удалось загрузить изображение\n");
    } else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, 500, 500);
    gluPerspective(45, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    //glutReshapeFunc(changeSize);
    */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, 500, 500);
    //gluPerspective(120, 1, 1, 1000);
    glOrtho(0, 10, 0, 10, -50, 50);
    glMatrixMode(GL_MODELVIEW);



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

void cylinder(int slices, int stacks, GLfloat x, GLfloat y, GLfloat depth,
              GLubyte red, GLubyte green, GLubyte blue, GLubyte opacity) {

    /*
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
*/
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

    return;
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

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -15);

    //cylinder(360, 1, inCx, inCy, cz + 0.01, 255, 255, 255, 0); //inner
    cylinder(360, 1, outCx, outCy, cz, 255, 255, 255, 255); //outer
    //borders(outCx, outCy, cz);
    //borders(inCx, inCy, cz + 0.01);

    glutSwapBuffers();
}

