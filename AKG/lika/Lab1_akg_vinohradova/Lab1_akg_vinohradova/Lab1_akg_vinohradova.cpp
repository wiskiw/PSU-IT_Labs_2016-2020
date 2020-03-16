// Lab1_akg_vinohradova.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <glut.h>
#include <math.h>

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(-30, -45);
	glColor3f(1,1,0);
	glVertex2f(-60, 15);
	glColor3f(0,1,0);
	glVertex2f(0, 60);
	glColor3f(0,0,1);
	glVertex2f(60, 15);
	glColor3f(1,0,1);
	glVertex2f(30, -45);
	glEnd();


	glLineWidth(3.0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);

	glVertex2f(-30, -45);
	glVertex2f(-60, 15);
	glVertex2f(0, 60);
	glVertex2f(60, 15);
	glVertex2f(30, -45);
	glVertex2f(-30, -45);
	glEnd();


	glFlush();

	glPopMatrix();

	glutSwapBuffers();
}




void SetupRC()
{
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
}




void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	glViewport(0, 0, w, h);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();



	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(900, 700);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Points Example");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0;
}
