#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <cstdio>

float SCALE = 2.5;

float outCx = 1.4f * SCALE;
float outCy = 1.7f * SCALE;

float inCx = 0.7f * SCALE;
float inCy = 0.9f * SCALE;

float cz = 0.5f * SCALE;

float red = 255;
float green = 255;
float blue = 255;


int xOrigin = 0;
int yOrigin = 0;

GLuint textureID;

GLfloat xrot;
GLfloat yrot;
GLfloat zrot;

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
    glVertex3f(0.0f, 0.0f, depth / 2);
    for (int i = 0; i <= slices; ++i) {
        double rad = i * 2 * M_PI / slices;
        glTexCoord2d(sin(rad) * x, cos(rad) * y);
        glVertex3f(sin(rad) * x, cos(rad) * y, depth / 2);
    }
    glEnd();

    //bottom of cylinder
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
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


    cylinder(360, 1, inCx, inCy, cz + 0.01, red, green, blue, 0); //inner
    cylinder(360, 1, outCx, outCy, cz, red, green, blue, 255); //outer
    borders(outCx, outCy, cz);
    borders(inCx, inCy, cz + 0.01);

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
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner


    glutCreateWindow("L7");          // Create window with the given title

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest

    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    if (LoadTexture((char *) "../texture.bmp") != 1) {
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