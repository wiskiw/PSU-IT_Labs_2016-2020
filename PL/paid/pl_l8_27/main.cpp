#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <cstdio>
#include <iostream>

float outCx = 3.5f; // внешний радиус арки
float inCx = 2.0f; // внутренний
float cz = 1.25f; // глубина

// положение мыши при клике
int xOrigin = 0;
int yOrigin = 0;

GLuint textureID; // текстурка

// углы поворота мышью
GLfloat xrot;
GLfloat yrot;
GLfloat zrot;

// рисует 3д дугу и границы
void arc3d(int slices, int stacks,
           GLfloat inRx,
           GLfloat inRy,
           GLfloat outRx,
           GLfloat outRy,
           GLfloat depth,
           GLubyte red, GLubyte green, GLubyte blue) {

    glColor3ub(red, green, blue);

    //outer cylinder border (внешняя часть)
    for (int j = 0; j < stacks; ++j) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= slices; ++i) {
            double rad = i / 2 * M_PI / slices;
            double angleX = sin(rad) * outRx;
            double angleY = cos(rad) * outRy;
            double angleZ = j / stacks - depth / 2;
            glNormal3f(angleX, angleY, 0.0f);
            glTexCoord2d(angleX, angleY);
            glVertex3f(angleX, angleY, angleZ);
            angleZ = (j + 1) * depth / 2 / stacks;
            glVertex3f(angleX, angleY, angleZ);
        }
        glEnd();
    }

    //inner cylinder border (внутренняя часть)
    for (int j = 0; j < stacks; ++j) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= slices; ++i) {
            double rad = i / 2 * M_PI / slices;
            double angleX = sin(rad) * inRx;
            double angleY = cos(rad) * inRy;
            double angleZ = j / stacks - depth / 2;
            glNormal3f(angleX, angleY, 0.0f);
            glTexCoord2d(angleX, angleY);
            glVertex3f(angleX, angleY, angleZ);
            angleZ = (j + 1) * depth / 2 / stacks;
            glVertex3f(angleX, angleY, angleZ);
        }
        glEnd();
    }


    //top of cylinder (передняя сторона)
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= slices; ++i) {
        double rad = i / 2 * M_PI / slices;
        glTexCoord2d(sin(rad) * outRx, cos(rad) * outRy);
        glVertex3f(sin(rad) * outRx, cos(rad) * outRy, depth / 2);
        glTexCoord2d(sin(rad) * inRx, cos(rad) * inRy);
        glVertex3f(sin(rad) * inRx, cos(rad) * inRy, depth / 2);

    }
    glEnd();

    //top of cylinder (задняя сторона)
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= slices; ++i) {
        double rad = i / 2 * M_PI / slices;
        glTexCoord2d(sin(rad) * outRx, cos(rad) * outRy);
        glVertex3f(sin(rad) * outRx, cos(rad) * outRy, -depth / 2);
        glTexCoord2d(sin(rad) * inRx, cos(rad) * inRy);
        glVertex3f(sin(rad) * inRx, cos(rad) * inRy, -depth / 2);

    }
    glEnd();


    // ----------- границы -----------------

    glColor3ub(1, 1, 1);

    //передняя сторона - границы(внешний радиус)
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= slices; ++i) {
        double rad = i / 2 * M_PI / slices;
        glVertex3f(sin(rad) * outRx, cos(rad) * outRy, depth / 2);
    }
    glEnd();

    //передняя сторона - границы(внутренний радиус)
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= slices; ++i) {
        double rad = i / 2 * M_PI / slices;
        glVertex3f(sin(rad) * inRx, cos(rad) * inRy, depth / 2);
    }
    glEnd();

     //задняя сторона - границы(внешний радиус)
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= slices; ++i) {
        double rad = i / 2 * M_PI / slices;
        glVertex3f(sin(rad) * outRx, cos(rad) * outRy, -depth / 2);
    }
    glEnd();

    //передняя сторона - границы(внутренний радиус)
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= slices; ++i) {
        double rad = i / 2 * M_PI / slices;
        glVertex3f(sin(rad) * inRx, cos(rad) * inRy, -depth / 2);
    }
    glEnd();
}

// рисует параллелепипед
void rect(GLfloat lbX,
        GLfloat lbY,
        GLfloat rtX,
        GLfloat rtY,
        GLfloat depth,
        GLubyte red, GLubyte green, GLubyte blue){

    glColor3ub(red, green, blue);

    // front/перед
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbX);
    glVertex3f(lbX, lbY, depth / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(lbX, rtY, depth / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, rtY, depth / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(rtX, lbY, depth / 2);
    glEnd();


    // rear/ зад
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbX);
    glVertex3f(lbX, lbY, -depth / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(lbX, rtY, -depth / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, rtY, -depth / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(rtX, lbY, -depth / 2);
    glEnd();

    //right
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbX);
    glVertex3f(rtX, rtY, depth / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(rtX, lbY, depth / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, lbY, -depth / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(rtX, rtY, -depth / 2);
    glEnd();

    // left
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbX);
    glVertex3f(lbX, lbY, depth / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(lbX, rtY, depth / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(lbX, rtY, -depth / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(lbX, lbY, -depth / 2);
    glEnd();

    //top/верх
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbX);
    glVertex3f(lbX, rtY, depth / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(rtX, rtY, depth / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, rtY, -depth / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(lbX, rtY, -depth / 2);
    glEnd();


    //bottom/низ
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbX);
    glVertex3f(lbX, lbY, depth / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(lbX, lbY, -depth / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, lbY, -depth / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(rtX, lbY, depth / 2);
    glEnd();


    /* -- границы гробика -- */

    glColor3ub(1, 1, 1);

    // front/перед
    glBegin(GL_LINE_LOOP);
    glVertex3f(lbX, lbY, depth / 2);
    glVertex3f(lbX, rtY, depth / 2);
    glVertex3f(rtX, rtY, depth / 2);
    glVertex3f(rtX, lbY, depth / 2);
    glEnd();

    // rear/ зад
    glBegin(GL_LINE_LOOP);
    glVertex3f(lbX, lbY, -depth / 2);
    glVertex3f(lbX, rtY, -depth / 2);
    glVertex3f(rtX, rtY, -depth / 2);
    glVertex3f(rtX, lbY, -depth / 2);
    glEnd();

    // right
    glBegin(GL_LINE_LOOP);
    glVertex3f(rtX, rtY, depth / 2);
    glVertex3f(rtX, lbY, depth / 2);
    glVertex3f(rtX, lbY, -depth / 2);
    glVertex3f(rtX, rtY, -depth / 2);
    glEnd();

    // left
    glBegin(GL_LINE_LOOP);
    glVertex3f(lbX, lbY, depth / 2);
    glVertex3f(lbX, rtY, depth / 2);
    glVertex3f(lbX, rtY, -depth / 2);
    glVertex3f(lbX, lbY, -depth / 2);
    glEnd();
}

void mouseButton(int button, int state, int x, int y) {

    // только при начале движения, если нажата левая кнопка
    if (button == GLUT_LEFT_BUTTON) {

        // когда кнопка отпущена
        if (state == GLUT_UP) {
            xOrigin = 0;
            yOrigin = 0;
        } else {
            // нажата
            xOrigin = x;
            yOrigin = y;
        }
    }
}

void mouseMove(int x, int y) {

    if (xOrigin > 0 || yOrigin > 0) {
        // только если мышь зажата

        // просчет поворота фигуры
        xrot = (y - yOrigin) * 0.5f;
        yrot = (x - xOrigin) * 0.5f;
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    glLoadIdentity();                 // Reset the model-view matrix

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);


    glLineWidth(3); // ширина линии

    glPushMatrix();

    glRotatef(180, 0.0f, 0.0f, 1.0f);
    glTranslated(0, -3, 0);

    arc3d(90, 1, inCx, inCx, outCx, outCx, cz, 255, 255, 255); //дуга

    // крышечка для дуги
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 1);
    glVertex3f(inCx, 0, cz / 2);
    glTexCoord2d(1, 1);
    glVertex3f(outCx, 0, cz / 2);
    glTexCoord2d(1, 0);
    glVertex3f(outCx, 0, -cz / 2);
    glTexCoord2d(0, 0);
    glVertex3f(inCx, 0, -cz / 2);
    glEnd();

    // границы крышечки
    glColor3ub(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(inCx, 0, cz / 2);
    glVertex3f(outCx, 0, cz / 2);
    glVertex3f(outCx, 0, -cz / 2);
    glVertex3f(inCx, 0, -cz / 2);
    glEnd();

    //границы арки и гробика
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, inCx, cz / 2);
    glVertex3f(0, outCx, cz / 2);
    glVertex3f(0, outCx,  -cz / 2);
    glVertex3f(0, inCx,  -cz / 2);
    glEnd();

    glPopMatrix();

    rect(0, -3, 1.5, +3, cz, 255, 255, 255); // гробик

    glutSwapBuffers();
}


/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat) width / (GLfloat) height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // Set matrix: to operate on the Projection matrix
    glLoadIdentity();             // Reset

    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(60.0f, aspect, 0.1f, 100.0f);

    gluLookAt(
            0, 0, 10,
            0, 0, 0,
            0, 1, 0);

    // zNear и zFar – расстояния вдоль отрицательного
    // направления оси Oz, определяющие ближнюю и дальнюю плоскости отсечения.
}

// загрузка текстур
int LoadTexture(char *FileName) {
    struct {
        int W;
        int H;
        unsigned char *Image;
    } getTexture;

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

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char **argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); // Enable double buffered mode
    //glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowSize(1040, 680);   // Set the window's initial width & height
    glutInitWindowPosition(150, 150); // Position the window's initial top-left corner

    glutCreateWindow("L7-8");          // Create window with the given title

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest

    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    if (LoadTexture((char *) "../cat21.bmp") != 1) {
        printf("Не удалось загрузить изображение\n");
    }

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    glutIdleFunc(draw);
    glutDisplayFunc(draw);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event

    glutMainLoop(); // Enter the infinite event-processing loop
    return 0;
}