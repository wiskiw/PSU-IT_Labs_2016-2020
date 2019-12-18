#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <cstdio>
#include <iostream>

float Z = 1.25f; // толщина

// положение мыши при клике
int xOrigin = 0;
int yOrigin = 0;

GLuint textureID; // текстурка

// углы поворота мышью
GLfloat xrot;
GLfloat yrot;
GLfloat zrot;

// рисует параллелепипед
void line3d(GLfloat lbX, GLfloat lbY, GLfloat rtX, GLfloat rtY, GLfloat Z) {

    glColor3ub(255, 255, 255);

    // front/перед
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbY);
    glVertex3f(lbX, lbY, Z / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(lbX, rtY, Z / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, rtY, Z / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(rtX, lbY, Z / 2);
    glEnd();


    // rear/ зад
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbY);
    glVertex3f(lbX, lbY, -Z / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(lbX, rtY, -Z / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, rtY, -Z / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(rtX, lbY, -Z / 2);
    glEnd();

    //right
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbY);
    glVertex3f(rtX, rtY, Z / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(rtX, lbY, Z / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, lbY, -Z / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(rtX, rtY, -Z / 2);
    glEnd();

    // left
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbY);
    glVertex3f(lbX, lbY, Z / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(lbX, rtY, Z / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(lbX, rtY, -Z / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(lbX, lbY, -Z / 2);
    glEnd();

    //top/верх
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbY);
    glVertex3f(lbX, rtY, Z / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(rtX, rtY, Z / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, rtY, -Z / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(lbX, rtY, -Z / 2);
    glEnd();


    //bottom/низ
    glBegin(GL_POLYGON);
    glTexCoord2d(lbX, lbY);
    glVertex3f(lbX, lbY, Z / 2);
    glTexCoord2d(lbX, rtY);
    glVertex3f(lbX, lbY, -Z / 2);
    glTexCoord2d(rtX, rtY);
    glVertex3f(rtX, lbY, -Z / 2);
    glTexCoord2d(rtX, lbY);
    glVertex3f(rtX, lbY, Z / 2);
    glEnd();


    /* -- границы гробика -- */

    glColor3ub(1, 255, 1);
    Z-=0.03f;
    // front/перед
    glBegin(GL_LINE_LOOP);
    glVertex3f(lbX, lbY, Z / 2);
    glVertex3f(lbX, rtY, Z / 2);
    glVertex3f(rtX, rtY, Z / 2);
    glVertex3f(rtX, lbY, Z / 2);
    glEnd();

    // rear/ зад
    glBegin(GL_LINE_LOOP);
    glVertex3f(lbX, lbY, -Z / 2);
    glVertex3f(lbX, rtY, -Z / 2);
    glVertex3f(rtX, rtY, -Z / 2);
    glVertex3f(rtX, lbY, -Z / 2);
    glEnd();

    // right
    glBegin(GL_LINE_LOOP);
    glVertex3f(rtX, rtY, Z / 2);
    glVertex3f(rtX, lbY, Z / 2);
    glVertex3f(rtX, lbY, -Z / 2);
    glVertex3f(rtX, rtY, -Z / 2);
    glEnd();

    // left
    glBegin(GL_LINE_LOOP);
    glVertex3f(lbX, lbY, Z / 2);
    glVertex3f(lbX, rtY, Z / 2);
    glVertex3f(lbX, rtY, -Z / 2);
    glVertex3f(lbX, lbY, -Z / 2);
    glEnd();
}

void mouseClick(int button, int state, int x, int y) {

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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    glLoadIdentity();                 // Reset the model-view matrix

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);


    glLineWidth(3); // ширина линии

    line3d(-1.5f, -3, -2.5f, +3, Z); // левая часть
    line3d(1.5f, -3, 2.5f, +3, Z); // правая часть


    // --------------- наклонная часть
    GLfloat h = 1.5f; // высота наклонной линии
    glColor3ub(255, 255, 255);

    // перед
    glBegin(GL_POLYGON);
    glTexCoord2d(-1.5f, -3);
    glVertex3f(-1.5f, -3, Z / 2);
    glTexCoord2d(-1.5f, -3 + h);
    glVertex3f(-1.5f, -3 + h, Z / 2);
    glTexCoord2d(1.5f, +3);
    glVertex3f(1.5f, +3, Z / 2);
    glTexCoord2d(1.5f, +3 - h);
    glVertex3f(1.5f, +3 - h, Z / 2);
    glEnd();

    // зад
    glBegin(GL_POLYGON);
    glTexCoord2d(-1.5f, -3);
    glVertex3f(-1.5f, -3, -Z / 2);
    glTexCoord2d(-1.5f, -3 + h);
    glVertex3f(-1.5f, -3 + h, -Z / 2);
    glTexCoord2d(1.5f, +3);
    glVertex3f(1.5f, +3, -Z / 2);
    glTexCoord2d(1.5f, +3 - h);
    glVertex3f(1.5f, +3 - h, -Z / 2);
    glEnd();

    // верх
    glBegin(GL_POLYGON);
    glTexCoord2d(-1.5f, -3 + h);
    glVertex3f(-1.5f, -3 + h, Z / 2);
    glTexCoord2d(-1.5f, -3 + h);
    glVertex3f(-1.5f, -3 + h, -Z / 2);
    glTexCoord2d(1.5f, +3);
    glVertex3f(1.5f, +3, -Z / 2);
    glTexCoord2d(1.5f, +3);
    glVertex3f(1.5f, +3, Z / 2);
    glEnd();

    // низ
    glBegin(GL_POLYGON);
    glTexCoord2d(-1.5f, -3);
    glVertex3f(-1.5f, -3, Z / 2);
    glTexCoord2d(-1.5f, -3);
    glVertex3f(-1.5f, -3, -Z / 2);
    glTexCoord2d(1.5f, +3 - h);
    glVertex3f(1.5f, +3 - h, -Z / 2);
    glTexCoord2d(1.5f, +3 - h);
    glVertex3f(1.5f, +3 - h, Z / 2);
    glEnd();


    // --- обводка
    glColor3ub(0, 255, 0);
    // верх
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.5f, -3 + h, Z / 2);
    glVertex3f(-1.5f, -3 + h, -Z / 2);
    glVertex3f(1.5f, +3, -Z / 2);
    glVertex3f(1.5f, +3, Z / 2);
    glEnd();

    // низ
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.5f, -3, Z / 2);
    glVertex3f(-1.5f, -3, -Z / 2);
    glVertex3f(1.5f, +3 - h, -Z / 2);
    glVertex3f(1.5f, +3 - h, Z / 2);
    glEnd();


    glutSwapBuffers();
}


/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void changeSize(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
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
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(150, 80); // Position the window's initial top-left corner

    glutCreateWindow("LABA 8");          // Create window with the given title


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest

    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    if (LoadTexture((char *) "../texture2.bmp") != 1) {
        printf("Не удалось загрузить изображение\n");
    }

    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);

    glutIdleFunc(display);
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(changeSize);       // Register callback handler for window re-size event

    glutMainLoop(); // Enter the infinite event-processing loop
    return 0;
}