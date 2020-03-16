#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <freeglut\freeglut.h>
#include <freeglut\freeglut_ext.h>
#include <FreeImage.h>

using namespace std;

void display();

bool twinkle = false;
                 
GLfloat tilt = 90.0f;                    
GLfloat spin;

GLuint texture;

const int num = 50;

typedef struct                        
{
	int r, g, b;                  
	GLfloat dist;                   
	GLfloat angle;                  
}
stars;                      
stars star[num];

void LoadTexture(GLuint* texture, const char* imageFileName) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imageFileName, 0);
	FIBITMAP* img = FreeImage_Load(format, imageFileName);
	BYTE* bDataPointer = FreeImage_GetBits(img);
	int iWidth = FreeImage_GetWidth(img);
	int iHeight = FreeImage_GetHeight(img);
	int iBPP = FreeImage_GetBPP(img);

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	int iFormat = iBPP == 24 ? GL_BGR_EXT : iBPP == 8 ? GL_LUMINANCE : 0;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, iFormat, GL_UNSIGNED_BYTE, bDataPointer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	FreeImage_Unload(img);
}

void InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);                    
		
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	for (int loop = 0; loop<num; loop++)
		{
			star[loop].angle = 0.0f;
			star[loop].dist = (float(loop) / num)*5.0f;
			star[loop].r = rand() % 256;
			star[loop].g = rand() % 256;
			star[loop].b = rand() % 256;
		}
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture);

	for (int loop = 0; loop<num; loop++)
	{
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -5.0f);
		glRotatef(tilt, 1.0f, 0.0f, 0.0f);
		glRotatef(star[loop].angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(star[loop].dist, 0.0f, 0.0f);
		glRotatef(-star[loop].angle, 0.0f, 1.0f, 0.0f);
		glRotatef(-tilt, 1.0f, 0.0f, 0.0f);
		
		if (twinkle)
			{
			glColor4ub(star[loop].r, star[loop].g, star[loop].b, 255);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
				glEnd();                     
			}
		glRotatef(spin, 0.0f, 0.0f, 1.0f);
							
		glColor4ub(star[loop].r, star[loop].g, star[loop].b, 255);
		glBegin(GL_QUADS); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();    

		spin += 0.01f;
		star[loop].angle += float(loop) / num;
		star[loop].dist -= 0.01f;
		if (star[loop].dist < 0.0f)
			{
				star[loop].dist += 5.0f;
				star[loop].r = rand() % 256;
				star[loop].g = rand() % 256;
				star[loop].b = rand() % 256;
			}
	}

	glFlush();
	glutSwapBuffers();
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 5.0f;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(30, update, 0);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	if (key == 't') {
		twinkle = !twinkle;
	}
	if (key == 'w')
		tilt += 0.5f;
	if (key == 's')
		tilt -= 0.5f;
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Galaxy");
	glutReshapeFunc(ChangeSize);
	glEnable(GL_TEXTURE_2D);
	LoadTexture(&texture, "star.jpg");
	InitGL();
	glutDisplayFunc(display);
	glutKeyboardFunc(KeyboardFunc);
	glutTimerFunc(30, update, 0);
	glutMainLoop();
	return 0;

}