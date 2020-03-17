#include <stdio.h>

#include "freeglut/include/GL/freeglut.h"
#include "freeglut/include/GL/freeglut_ext.h"

#include "CameraMotionHelper.h"
#include "ModelDescription.h"
#include "GLUtils.h"
#include "TextureUtils.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

#define ESCAPE '\033'
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

CameraMotionHelper cameraMotionHelper;
GLfloat animationParam = 0.0f;
const GLuint MODEL_LIST = 1;
MODEL model;

void setupLight() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambientLight[] = { 1.0f, 1.0f , 1.0f , 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat specularLight[] = { 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	GLfloat ambientLight0[] = { 0.3f, 0.3f, 0.3f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);

	GLfloat fiffuseLight[] = { 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);

	setupLight();
}

void axis(GLfloat size) {
	glEnable(GL_COLOR_MATERIAL);

	GLfloat emissionColor[] = { 0.0, 0.0, 0.0, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);

	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(-size, 0.0f, 0.0f);
	glEnd();

	glRasterPos3f(-size, 0.0f, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'-');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'X');

	glRasterPos3f(size, 0.0f, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'+');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'X');

	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, -size, 0.0f);
	glEnd();

	glRasterPos3f(0.0f, -size, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'-');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Y');

	glRasterPos3f(0.0f, size, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'+');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Y');

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, 0.0f, -size);
	glEnd();

	glRasterPos3f(0.0f, 0.0f, -size);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'-');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Z');

	glRasterPos3f(0.0f, 0.0f, size);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'+');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'Z');

	glDisable(GL_COLOR_MATERIAL);
}

void renderLamp() {
	GLfloat emissionColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat ambientColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuseColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specularColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
	glMaterialf(GL_FRONT, GL_SHININESS, 20);

	glutSolidSphere(0.2f, 32, 32);
}

void renderModel() {
	glEnable(GL_TEXTURE_2D);

	glMaterialfv(GL_FRONT, GL_EMISSION, model.material.emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, model.material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, model.material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, model.material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, model.material.shininess);

	glBindTexture(GL_TEXTURE_2D, model.brickTexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();
	glTranslatef(3.0f, 0.0f, 3.0f);

	glCallList(MODEL_LIST);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, model.metalTexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_TEXTURE_GEN_S);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(animationParam * 0.01f, animationParam * 0.01f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(3.0f, 0.0f, -3.0f);

	glCallList(MODEL_LIST);

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);


	glBindTexture(GL_TEXTURE_2D, model.glassTexture);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-3.0f, 0.0f, -3.0f);

	glCallList(MODEL_LIST);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(cameraMotionHelper.getDistance(),
		cameraMotionHelper.getDistance(),
		cameraMotionHelper.getDistance(),
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glRotatef(cameraMotionHelper.getRotationXZ(), 1.0f, 0.0f, -1.0f);
	glRotatef(cameraMotionHelper.getRotationY(), 0.0f, 1.0f, 0.0f);

	glPushMatrix();

	GLfloat lightPos[] = { 3.0f, 7.0f, 7.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);

	renderLamp();
	glPopMatrix();
	axis(15.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	renderModel();
	glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat zNear = 1;
	GLfloat zFar = 200;

	gluPerspective(45.0, (float)w / (float)h, zNear, zFar);
}

void keyboardFunc(unsigned char key, int x, int y) {
	if (key == ESCAPE) exit(0);
}

void updateAnimation(int value) {
	animationParam += 0.05f;
	if (animationParam > 1000.0f)
		animationParam = 0.0f;

	glutPostRedisplay();
	glutTimerFunc(25, updateAnimation, 0);
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN)
			cameraMotionHelper.startMove(x, y);
		else cameraMotionHelper.endMove();
	}
}

void mouseMotionFunc(int x, int y) {
	cameraMotionHelper.move(x, y);
}

void mouseWheelFunc(int button, int dir, int x, int y) {
	if (dir < 0)
		cameraMotionHelper.increaseDistance();
	else cameraMotionHelper.decreaseDistance();
}

void compileModelList() {
	glNewList(MODEL_LIST, GL_COMPILE);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, model.normals);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, model.vertices);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, model.textureCoords);

	glDrawElements(GL_TRIANGLES, MODEL_INDEX_COUNT, GL_UNSIGNED_INT, model.indices);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glEndList();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Material & Textures");

	utlPrintExtList();
	model.initTexture();
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardFunc);
	glutMouseWheelFunc(mouseWheelFunc);
	glutTimerFunc(25, updateAnimation, 0);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotionFunc);
	compileModelList();
	glutMainLoop();

	return 0;
}
