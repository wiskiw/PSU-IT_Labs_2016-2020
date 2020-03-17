#include <stdio.h>
#include <stdlib.h>

#include "freeglut/include/GL/freeglut.h"
#include "freeglut/include/GL/freeglut_ext.h"

#include "CameraMotionHelper.h"
#include "ModelDescription.h"
#include "GLUtils.h"
#include "TextureUtils.h"
#include "MathUtils.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

#define ESCAPE '\033'
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

CameraMotionHelper cameraMotionHelper;
GLfloat animationParam = 0.0f;
GLuint particleTexture;

void setupLight() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambientLight[] = { 1.0f, 1.0f , 1.0f , 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat specularLight[] = { 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	GLfloat ambientLight0[] = { 0.3f, 0.3f, 0.3f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);

	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	setupLight();
	modelInitSprites();
}

void axis(GLfloat size) {
	glEnable(GL_COLOR_MATERIAL);

	GLfloat emissionColor[] = { 0.0, 0.0, 0.0, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);

	glLineWidth(1.0f);

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

void renderSprites()
{
	//рисуем каждую частицу
	for (SPRITES::iterator i = modelSprites.begin(); i != modelSprites.end(); i++)
	{
		//сохран¤ем модельную матрицу в стек 
		glPushMatrix();
		//устанавливаем положение частицы 
		glTranslatef(i->p[0], i->p[1], i->p[2]);
		//создаем billboard матрицу из текущей 
		//особенность данного преобразовани¤ в том 
		//что поверхность спрайта всегда повернута к наблюдателю 
		double MV[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, MV);
		//utlMakeBillboard(MV, MV); 
		glLoadMatrixd(MV);
		//измен¤ем размер частицы 
		glScalef(i->s, i->s, i->s);
		//рисуем спрайт как квадрат с заданным цветом 
		glBegin(GL_QUADS);
		glColor4f(i->c[0], i->c[1], i->c[2], i->c[3]);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);
		glEnd();
		//извлекаем модельную матрицу из стека 
		glPopMatrix();
	}
}

//M@TOR, OTPUCOBKM CuCcTeMbI YaCcTHY
void renderModel() {
	//c6poc Bcex napameTpoB MaTepnana
	usr_glClearMaterial();

	//genaem 6bydep rny6uHbl BOCTYNHbIM TOMbKO ANA YTeHVA
	//peweHve npo6nemsl npopucoBkw npo3spa4Hbix O6beKTOB B HYxXHOM nopagKe
	glDepthMask(GL_FALSE);

	//BKnO4aeM PexuM 3afaHnvA UBeTa MaTepnana
	glEnable(GL_COLOR_MATERIAL);

	//otTKno4uM ocBelWeHve
	glDisable(GL_LIGHTING);

	//Bknio4aem TeKCTypnpoBaHue
	glEnable(GL_TEXTURE_2D);

	//Bknio4aem cMeuMBae
	glEnable(GL_BLEND);

	glEnable(GL_CULL_FACE);

	//3agaemM NapameTpbl cmewuBaHvaA Takum o6pa30m
	//4T06bl Ha Cnpaite OTpuCcOBaNacb TONbKO
	//"6enaa" YacTb TeKCTypbl Cc NpospayHocTbI
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//3afaeM HENOCpeACTBeHHO TeKCTypy
	glBindTexture(GL_TEXTURE_2D, particleTexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//pucyemM HenocpeACcTBeHHO Camu cnpaitol
	renderSprites();

	//oTKnio4aem BbI6paHble pexumbl
	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glDepthMask(GL_TRUE);

	//BKnONuM OcBeweHue
	glEnable(GL_LIGHTING);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//ycTaHaBnuBaem HabnigaTeNnA OTHOCUTeNbHO HyNeBonK
	//KOOPAMHAaTbI B NpocTpaHcTBe
	//nonoxeHue HabmiogaTena nonyyaem OT O6beKTa-NOMOUHUKA
	gluLookAt(cameraMotionHelper.getDistance(), cameraMotionHelper.getDistance(),
		cameraMotionHelper.getDistance(),
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	//nopopauuBaem BC Habnigaemyi cucTemy no BepTuKann

	//(ynpaBneHue cueHoK KypCcopomM mbIuIn )

	//yron noBopota nonyyaem oT O6beKTa-NOMOUHUKA
	glRotatef(cameraMotionHelper.getRotationXZ(), 1.0f, 0.0f, -1.0f);

	//noBopaynBaem Bc HaGningaemyi cucTemy no ropu30HTann
	//(ynpaBneHve cueHow Kypcopom mobili)

	//yron noBopota nonyyaem OT O6beKTAa-NOMOWHUKA
	glRotatef(cameraMotionHelper.getRotationY(), 0.0f, 1.0f, 0.0f);

	//ynpasnexve nonoxeHvem ucTOuHuKa cBeTa

	//coxpaHAem Tekyly BYAOByW MaTpuuy B CTeK
	glPushMatrix();

	//ycTaHOBKa NMo3vunun UCTOYHUKAa OCBeLjeHNA
	GLfloat lightPos[] = { 3.0f, 7.0f, 7.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//ycTaHOBKa no3vuvn mMogenbKM УnamMnoyKu"
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);

	//npopucosKka УnamnoyKn"
	renderLamp();

	//w3Bnekaem BUgOByW MaTpULy v3 cTeKa
	glPopMatrix();

	//npopucoBKa rno6anbHOW cucTembl KOOpANHaT
	axis(15.0f);

	//npopucoska mogenn
	renderModel();

	//KOMaHfa CMeHbI KaspoB
	//(ganA gBOKHOK 6bydbepn3aunn)
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
	if (key == 'w')
	{
		for (int i = 0; i < 50; i++)
			modelSprites.push_back(SPRITE());
		printf("sprite count = %d\n", modelSprites.size());
	}
	if (key == 's')
	{
		for (int i = 0; i < 50 && modelSprites.size() > 0; i++)
			modelSprites.erase(modelSprites.begin());
		printf("sprite count = %d\n", modelSprites.size());
	}
	if (key == 'd')
	{
		vXZ0 += 0.01f;
		printf("vxXZ@ = %.03f\n", vXZ0);
	}
	if (key == 'a')
	{
		if (vXZ0 - 0.02f > 0.0f)
			vXZ0 -= 0.01f;
		printf("vxXZ0 = %.03f\n", vXZ0);
	}
	if (key == 'r')
	{
		vY0 += 0.01f;
		printf("vY0 = %.03f\n", vY0);
	}
	if (key == 'f')
	{
		vY0 -= 0.01f;
		if (vY0 <= 0.0f)
			vY0 = 0.01f;
		printf("vY0 = %.03f\n", vY0);
	}
}

void updateAnimation(int value) {
	for (SPRITES::iterator i = modelSprites.begin(); i != modelSprites.end(); i++)
		i->step();

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

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Particles");

	utlPrintExtList();
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardFunc);
	glutMouseWheelFunc(mouseWheelFunc);
	glutTimerFunc(25, updateAnimation, 0);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotionFunc);
	utlLoadTexture(&particleTexture, "sprite.jpg");
	glutMainLoop();

	return 0;
}
