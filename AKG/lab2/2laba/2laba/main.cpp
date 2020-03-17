#include <stdlib.h>
#include <stdio.h>

//nomsmmuaen 6u6morexy GLUT ws nana freeglut
//nonommvensuo x mpoeKty HeoGxommo nomKmouTS
//freeglut.1ib

#include "freeglut/include/GL/freeglut.h"
#include "freeglut/include/GL/freeglut_ext.h"

#include "CameraMotionHelper.h"
#include "ModelDescription.h"
//nommmmienne mavevanmecnoi 6uBmorenn GLM
#include "glm\glm.hpp"

#include "glm\gtc\type_ptr.hpp"

using namespace glm;

#define ESCAPE '\033'

//wauamsnoe paspenesme oxpana

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//������-�������� ��� �������� ����� � ������� ������� ���� 
CameraMotionHelper cameraMotionHelper;
//�������� ���� ��� �������� �������� ������ 
GLfloat animationAngle = 0.0f;
GLfloat animationTranslate = 0.0f;
GLfloat animationTranslate1 = 0.1f;

void printExtList(const char* extensions)
{
	char name[1024];

	int i = 0, j = 0;

	printf("Supported extensions:\n");
	for (i = 0, j = 0; extensions[i] != '\0'; i++)
	{
		if (!isspace(extensions[i]))
			name[j++] = extensions[i];
		else
		{
			name[j] = '\0';
			printf("\t%s\n", name);
			j = 0;
		}
	}

	if (j > 0)
	{
		name[j] = '\0';
		printf("\t%s\n", name);
	}
}

//����� ��������� ���������� ��������� 
void setupLight()
{
	//��������� ��������� 
	glEnable(GL_LIGHTING);
	//��������� ��������� ��������� ����� 0 (������� �����)
	//����� ����� ���� 8 ���������� ����� 
	glEnable(GL_LIGHT0);
	//��������� ������� ������������ //����� ����
	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	//��������� ��������� ��������� �����:
	//� ������ ��������� ����� ���� �������������� � ���� ���� ������������
	//���������� (�������� �� �����)
	GLfloat specularLight[] = { 1.0, 1.0, 1.0 }; 
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//������� (����������� ����� ����)
	GLfloat ambientLightO[] = { 0.3f, 0.3f, 0.3f }; 
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightO);
	//���������� (����� ����)
	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0 }; 
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
}

void init()
{
	//��������� ������ ���� (������ ����) 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//������������� ������� ������� 
	glEnable(GL_DEPTH_TEST);
	//�������������� ���������� �������� � ��������� ����� 
	//��������� ���������, ����� ��� ��������� �������� ������� 
	//� ��� ����������� ������� ��������� 
	glEnable(GL_NORMALIZE);
	//��������� ������� ���������� �������� ����� ���������� 
	//glColor3f
	//��� ������� ��������� �������� �� ����� ������������ 
	//������� glMaterialfv 
	glDisable(GL_COLOR_MATERIAL);
	//��������� ���������� ��������� 
	setupLight();
}


void fam()
{
	//�������� ������� ���������� �������� ����� ���������� glColor3f 
	//��� ����������������� ������� ����� ����� 
	glEnable(GL_COLOR_MATERIAL);
	//���������� ��������� ���������, ����� �������� 
	//�� �������� ����������� �� ���� ����� 
	GLfloat emissionColor[] = { 0.0, 0.0, 0.0, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);


	glRasterPos3f(-2.0f, -2.0f, 2.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) 'B');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'O');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) 'R');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'O');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) 'D');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'I');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) 'C');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'H');
	glDisable(GL_COLOR_MATERIAL);
}

//����� ���������� ������������ ���� 
//�������� ������ ������ ���� 
void axis(GLfloat size)
{
	//�������� ������� ���������� �������� ����� ���������� glColor3f 
	//��� ����������������� ������� ����� ����� 
	glEnable(GL_COLOR_MATERIAL);
	//���������� ��������� ���������, ����� �������� 
	//�� �������� ����������� �� ���� ����� 
	GLfloat emissionColor[] = { 0.0, 0.0, 0.0, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
	//������������� ������� �����
	glLineWidth(2.0f);
	//���������� ��� X � ������� ������� 
	glBegin(GL_LINES); 
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(-size, 0.0f, 0.0f);
	glEnd();
	//���������� �������� ������ ��� X - "-�" 
	glRasterPos3f(-size, 0.0f, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) '-');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'X');
	//���������� �������� ����� ��� X - "+�" 
	glRasterPos3f(size, 0.0f, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) ' + ');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'X');

	glBegin(GL_LINES); 
	glColor3f(0.0f, 1.0f, 0.0f); 
	glVertex3f(0.0f, size, 0.0f); 
	glVertex3f(0.0f, -size, 0.0f); 
	glEnd();

	glRasterPos3f(0.0f, -size, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) '-');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Y');

	glRasterPos3f(0.0f, size, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) ' + ');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Y');

	glBegin(GL_LINES); 
	glColor3f(0.0f, 0.0f, 1.0f); 
	glVertex3f(0.0f, 0.0f, size); 
	glVertex3f(0.0f, 0.0f, -size); 
	glEnd();

	glRasterPos3f(0.0f, 0.0f, -size);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) '-'); 
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Z');
	glRasterPos3f(0.0f, 0.0f, size);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) ' + '); 
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Z');
	//��������� ������������� ����������������� ������� ����� 
	glDisable(GL_COLOR_MATERIAL);
}

//����� ���������� ������ "��������" 
void renderLamp()
{
	//����� ���� ���� � ��������� ��������� � ���������� � ���������, 
	//�� ������� � ���� ��� ����������� ������������ ������ �� ���� 
	//��������� ����� ������ ������������ ������������.

	//����������� �������� �������
	//���� "��������" �������� ����� ������
	GLfloat emissionColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//��������� ������������ ��������� ��������� "�������"
	//��� ��� ��� � ����� ������ �� ������ �� �������� (�����)
	//���� ������
	GLfloat ambientColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuseColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specularColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor); 
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor); 
	glMaterialf(GL_FRONT, GL_SHININESS, 20);
	//� ���������� GLUT ���������� ��� ������� 
	//��� ���������� ������� ���������� 
	//� ������ ������ ����� 
	glutSolidSphere(0.2f, 32, 32);
}

//����� ��������� ������ 
void renderModel()
{
	//��������� �������� ������ "������"
	//����������� �������� ��������� 
	//��� ������ �� ����� ������������ �������� 
	GLfloat ercissionColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, ercissionColor);

	//������� ��������� ��������� (���� � ����)
	GLfloat arcbientColor[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, arcbientColor);

	//���������� ���� �� ���������
	GLfloat diffuseColor[] = { 0.714f, 0.4284f, 0.18144f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

	//�������� (����������) ������������
	GLfloat specularColor[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	//����� ��� ������������ �������� � ��������� �� 0 �� 128, ������� ���������� 
	//������� ����������� ��������� ��������� 
	glMaterialf(GL_FRONT, GL_SHININESS, 128 * 0.2f);

	//��������������� ���������� �������

	//������� ������ �������� ��� ������ �������
	//!!! ��� �������� ����������� ��������� ����� ����� ��������� ���������� ������� 
	//!!! ������� - ������ ���������������� ����������� ��������� 
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normalArr);

	//������� ������ ������ ������ 
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexArr);

	//glDrawArrays ����� ��� ���������� ��������� �� ��������� ��������� 
	//(GL_TRIANGLES) �������� ������� ������ � �������� �������� ����� 
	glDrawArrays(GL_TRIANGLES, 0, 66);

	//������ glDisableClientState ���������� � ����� ���������� ������ 
	//��� ������� �� �������������� �������� ������ 
	//�� ������������ ������ ������ � ������ �������� 
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	fam();
}

//������� ��������� ���� ������� �� ����� 
void display()
{
	//������� glClear ������� ������, � �������� buf ���������� ������, 
	//������� ����� ��������. �������� ��������� �������� ������� 
	//glClear(GL_COLOR_3UFFER_3IT | GL_DEPTH_3UFFER_3IT)
	//��� ������� ������� ����� � �������.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//�������� ������� ������� 
	glMatrixMode(GL_MODELVIEW);

	//���������� ������� 
	glLoadIdentity();

	//������������� ����������� ������������ ������� //���������� � ������������
	//��������� ����������� �������� �� �������-��������� 
	gluLookAt(cameraMotionHelper.getDistance(),
		cameraMotionHelper.getDistance(),
		cameraMotionHelper.getDistance(),
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	//������������ ��� ����������� ������� �� ��������� 
	//(���������� ������ �������� ����)
	//���� �������� �������� �� �������-���������
	glRotatef(cameraMotionHelper.getRotationXZ(), 1.0f, 0.0f, -1.0f);

	//������������ ��� ����������� ������� �� ����������� 
	//(���������� ������ �������� ����)
	//���� �������� �������� �� �������-���������
	glRotatef(cameraMotionHelper.getRotationY(), 0.0f, 1.0f, 1.0f);
	//���������� ���������� ��������� �����

	//��������� ������� ������� ������� � ���� 
	glPushMatrix();
	//��������� ������� ��������� ��������� 
	GLfloat lightPos[] = { 5.0f, 5.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//��������� ������� �������� "��������" 
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	//���������� "��������" 
	renderLamp();

	//��������� ������� ������� �� ����� 
	glPopMatrix();

	//���������� ���������� ������� ��������� 
	axis(15.0f);

	//�������� �������� ������������ ���������� ��� 
	//glTranslatef(2.0f, 2.0f, -2.0f);

	//������� �������� �� �������� ���� 
	//������������ ���� X � Z
	glRotatef(-animationAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef(animationTranslate, 0.0f, animationTranslate);
	//���������� ����������� ������� ��������� ������ 
	//axis(5.0f);

	//��������� ������� ������
	//�������������� ��������� ����� ���������� 
	//����������� ������� ��������� 
	glScalef(0.5f, 1.5f, 1.5f);

	//���������� ������ 
	renderModel();

	//���*����� ������ ������ 
	//(��� ������� ������������) 
	glutSwapBuffers();
}

//������� ���������� ��� ��������� �������� ���� 
void reshape(GLint w, GLint h)
{
	//������������� ������� ������� �����������
	glViewport(0, 0, w, h);

	//�������� ��� ��������� ������� �������� 
	glMatrixMode(GL_PROJECTION);

	//������� ��������� ������� (������� ��������)
	//�������� ������� ������� �� ��������� 
	glLoadIdentity();

	//��������� ������������� �������� 
	GLfloat zNear = 1;
	GLfloat zFar = 200;
	//��������� zFar � zNear ������ ���������� �� �����������
	//�� ���������� ��������� �� ������� � ������ ���� ��������������
	gluPerspective(45.0, (float)w / (float)h, zNear, zFar);
}

//������� ������������ ��������� �� ���������� 
void keyboardFunc( unsigned char key, int x, int )
{
	if (key == ESCAPE) exit(0);
}

//����� ��������� ������� ������� 
//���������� ��� ���������� �������� 
void updateAnimation(int value)
{
	//��� �������� �������� ������ 
	//�������� ���� �������� �� ������� 
	animationAngle += 1.0f;
	animationTranslate += animationTranslate1;

	if (animationAngle > 360) 
		animationAngle -= 360;

	if (animationTranslate > 3.0f){
		animationTranslate1 = -0.1f;
	}

	if (animationTranslate < -3.0f){
		animationTranslate1 = 0.1f;
	}

	//�������� ��������� ��� ����������� ����� 
	glutPostRedisplay();

	//��������� ������ ������ 
	glutTimerFunc(25, updateAnimation, 0);
}

//����� ��������� ��������� �� ���� (������� ������)
//����� ������������ ��� ��� ���������� ������������ ����� 
void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) //��������� ������� �� ����� ������ ���� 
	{
		if (state == GLUT_DOWN) //������� ������ ����	
		{
			//���������� ��������� ���������� � ������� 
			//������ ����� ������ ����
			//�������� �������-��������� ��� ����� ������� ����� 
			cameraMotionHelper.startMove(x, y);
		}
		else
		{
			//������ ���� ���� ������,
			//������� ����������� ������� �����
			//�������� �������-��������� ��� ������� ����� ������� 
			cameraMotionHelper.endMove();
		}
	}
}

//����� ��������� ������� ����������� ������� ���� 
//��� ����� ������� ������ ����� 
void mouseMotionFunc(int x, int y)
{
	//�������� �������-��������� ����� ���������� ������� 
	cameraMotionHelper.move(x, y);
}
		
//����� ��������� ������� �� ������ ����
//������������ ��� ����������� � ��������� ������ ����������� 
void mouseWheelFunc(int button, int dir, int x, int y)
{
	//� ����������� �� ����������� ��������� ������ 
	//�������� �������-��������� ���� ��������� ��������� 
	//�� ����������� ����� - ���� ��������� 
	if (dir < 0)
		cameraMotionHelper.increaseDistance();
	else
		cameraMotionHelper.decreaseDistance();
}

//����� ��� ������� �������� ��� ������ ������� ������� ������������ ������ 
//!!! �.�. �� ���������� �������� ����������
//!!! GL_TRIANGLES (�.�. ������ ����������� ������������� ��������),
//!!! �� ������� �� ����������� ���������� ��� ������ �������
void calcModelNormals(const GLfloat* v, GLfloat* n, GLuint vertexCount)
{
	for (GLuint i = 0; i < vertexCount - 2; i += 3)
	{
		vec3 a = vec3(v[i * 3 + 0], v[i * 3 + 1], v[i * 3 + 2]); 
		vec3 b = vec3(v[i * 3 + 3], v[i * 3 + 4], v[i * 3 + 5]); 
		vec3 c = vec3(v[i * 3 + 6], v[i * 3 + 7], v[i * 3 + 8]);

		vec3 norm = glm::normalize(glm::cross(b - a, c - a));

		//� ����� ������ � ������ ������������ ������� �������������� ��������� 
		memcpy_s(&n[i * 3 + 0], sizeof(GLfloat)* 3, value_ptr(norm), sizeof(GLfloat)*3);
		memcpy_s(&n[i * 3 + 3], sizeof(GLfloat)* 3, value_ptr(norm), sizeof(GLfloat)*3);
		memcpy_s(&n[i * 3 + 6], sizeof(GLfloat)* 3, value_ptr(norm), sizeof(GLfloat)*3);
	}
}

int main(int argc, char** argv)
{
	//������� glutlnit(&argc, argv) ���������� ��������� ������������� 
	//����� ���������� GLUT, 
	glutInit(&argc, argv);

	//������� glutlmtDisplayMode (GLUT_RG3) �������������� ����� ����� � 
	//����������� ������������(������������) ����� RGB. 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	//glutlnitWindowSize(Width, Height) ������������ ��� 
	//������� ��������� �������� ����. 
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//������ ��������� ������������ ���� ������������ 
	//�������� ������ ���� ������ 
	glutInitWindowPosition(100, 100);

	//��� ������� ������ ���� � ����������, ������� �� ������� � �������� 
	//��������� � ���������� HANDLER ���� � ���� ����� int.
	//���� HANDLER ������ ������������ ��� ����������� ��������
	//��� ���� �����, ����� ��� ��������� ���������� ���� � �������� ����.
	glutCreateWindow("Light, Transformations, Material");

	//The glGetString function returns a string describing the current CpenGL connection. 

	//GL_VENDOR
	//Returns the company responsible for this Oper.GL implementation.
	//This name does not change from release to release, 
	const char* vendor = (const char*)glGetString(GL_VENDOR);

	//GL_REUDERER
	//Returns the name of the rer.derer. This name is
	//typically specific to a particular configuration of a hardware platform.
	//It does not change from release to release.
	const char* renderer = (const char*)glGetString(GL_RENDERER);

	//GL_VERSION
	//Returns a version or release number.
	const char* version = (const char*)glGetString(GL_VERSION);

	//GL_EXTENSIONS
	//Returns a space-separated list of supported extensions to OpenGL. 
	const char* extensions = (const char*)glGetString(GL_EXTENSIONS);

	printf(" Vendor: %s\n Renderer: %s\n Version: %s\n ", vendor, renderer, version);
	printExtList(extensions);
	//���������� ������� ��� ������ ����� ������
	calcModelNormals(vertexArr, normalArr, 36);

	init();

	//������������ ������� ����������� ����� 
	glutDisplayFunc(display);

	//������������ ������� ��������� ������� ���� 
	glutReshapeFunc(reshape);

	//������������ ������� ��������� ������� �� ���������� 
	glutKeyboardFunc(keyboardFunc);

	//������������ ������� ��������� ������� �� ������ ���� 
	glutMouseWheelFunc(mouseWheelFunc);

	//������������ ������� ��������� ������� �� ������� 
	//��� ���������� �������� 
	glutTimerFunc(25, updateAnimation, 0);

	//������������ ������� ��������� ������� �� ������ ����
	glutMouseFunc(mouseFunc);

	//������������ ������� ��������� ������� �� �������� �������
	glutMotionFunc(mouseMotionFunc);
	//�������� ���� ������� � ����� ������ ������� ���������� ������ ����� 
	//��������� ��������� � ������� glutMainLoop(). 
	glutMainLoop();
	return 0;

}