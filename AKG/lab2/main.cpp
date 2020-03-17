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

//объект-помощник для поворота едены с помощью курсора мыши
CameraMotionHelper cameraMotionHelper;
//значение угла для анимации вращения модели
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

//метод настройки источников освещения
void setupLight()
{
	//включение освещения
	glEnable(GL_LIGHTING);
	//включение точечного источника света 0 (нулевой лампы)
	//всего может быть 8 источников света
	glEnable(GL_LIGHT0);
	//установка фоновой освещенности //белый цвет
	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	//настройка точечного источника света:
	//в модели освещения Фонга свет представляется в виде трех составляющих
	//зеркальная (отвечает за блики)
	GLfloat specularLight[] = { 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//фоновая (равномерный серый цвет)
	GLfloat ambientLightO[] = { 0.3f, 0.3f, 0.3f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightO);
	//рассеянная (белый цвет)
	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
}

void init()
{
	//установка общего фона (черный цвет)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//активирование функции глубины
	glEnable(GL_DEPTH_TEST);
	//автоматическое привидение нормалей к единичной длине
	//затратная процедура, нужна при изменении размеров моделей
	//и для правильного расчета освещения
	glEnable(GL_NORMALIZE);
	//отключаем задание материалов объектов одним параметром
	//glColor3f
	//для задания материала объектов мы будем использовать
	//команду glMaterialfv
	glDisable(GL_COLOR_MATERIAL);
	//настройка источников освещения
	setupLight();
}


void fam()
{
	//включаем задание материалов объектов одним параметром glColor3f
	//для непосредственного задания цвета линий
	glEnable(GL_COLOR_MATERIAL);
	//сбрасываем настройки материала, чтобы материал
	//не оказывал воздействие на цвет линий
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

//метод прорисовки координатных осей
//параметр задает размер осей
void axis(GLfloat size)
{
	//включаем задание материалов объектов одним параметром glColor3f
	//для непосредственного задания цвета линий
	glEnable(GL_COLOR_MATERIAL);
	//сбрасываем настройки материала, чтобы материал
	//не оказывал воздействие на цвет линий
	GLfloat emissionColor[] = { 0.0, 0.0, 0.0, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
	//устанавливаем толщину линий
	glLineWidth(2.0f);
	//прорисовка оси X с помощью отрезка
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(-size, 0.0f, 0.0f);
	glEnd();
	//прорисовка названия начала оси X - "-Х"
	glRasterPos3f(-size, 0.0f, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) '-');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)'X');
	//прорисовка названия конца оси X - "+Х"
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
	//отключаем использование непосредственного задания цвета
	glDisable(GL_COLOR_MATERIAL);
}

//метод прорисовки модели "лампочки"
void renderLamp()
{
	//Когда речь идет о свойствах материала в приложении к освещению,
	//то имеется в виду его способность воспринимать каждую из трех
	//компонент цвета каждой составляющей освещенности.

	//собственное свечение объекта
	//наша "лампочка" светится белым цветом
	GLfloat emissionColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//остальные составляющие материала оставляем "черными"
	//так как они в нашем случае не влияют на конечный (белый)
	//цвет модели
	GLfloat ambientColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuseColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specularColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
	glMaterialf(GL_FRONT, GL_SHININESS, 20);
	//в библиотеке GLUT существует ряд методов
	//для прорисовки простых примитивов
	//в данном случае сферы
	glutSolidSphere(0.2f, 32, 32);
}

//метод отрисовки модели
void renderModel()
{
	//установим материал модели "бронза"
	//собственное свечение материала
	//наш объект не имеет собственного свечения
	GLfloat ercissionColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, ercissionColor);

	//фоновое освещение материала (цвет в тени)
	GLfloat arcbientColor[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, arcbientColor);

	//рассеянный свет от материала
	GLfloat diffuseColor[] = { 0.714f, 0.4284f, 0.18144f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

	//бликовая (зеркальная) составляющая
	GLfloat specularColor[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	//целое или вещественное значение в диапазоне от 0 до 128, которое определяет
	//степень зеркального отражения материала
	glMaterialf(GL_FRONT, GL_SHININESS, 128 * 0.2f);

	//непосредственно прорисовка объекта

	//зададим массив нормалей для каждой вершины
	//!!! Для создания корректного освещения сцены нужно правильно установить нормали
	//!!! нормаль - вектор перпендикулярный поверхности освещения
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normalArr);

	//зададим массив вершин модели
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexArr);

	//glDrawArrays метод для прорисовки полигонов по заданному алгоритму
	//(GL_TRIANGLES) согласно массиву вершин и нормалей заданных ранее
	glDrawArrays(GL_TRIANGLES, 0, 66);

	//методы glDisableClientState вызываются в конце прорисовки модели
	//для каждого из использованных массивов данных
	//мы использовали массив вершин и массив нормалей
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	fam();
}

//Функция управляет всем выводок на экран
void display()
{
	//Команда glClear очишает буферы, а параметр buf определяет буферы,
	//которые нужно очистить. Типичная программа вызывает команду
	//glClear(GL_COLOR_3UFFER_3IT | GL_DEPTH_3UFFER_3IT)
	//для очистки буферов цвета и глубины.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//выбираем видовую матрицу
	glMatrixMode(GL_MODELVIEW);

	//сбрасываем матрицу
	glLoadIdentity();

	//устанавливаем наблюдателя относительно нулевой //координаты е пространстве
	//положение наблюдателя получаем от объекта-помощника
	gluLookAt(cameraMotionHelper.getDistance(),
		cameraMotionHelper.getDistance(),
		cameraMotionHelper.getDistance(),
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	//поворачиваем всю наблюдаемую систему по вертикали
	//(управление сценой курсором мыши)
	//угол поворота получаем от объекта-помощника
	glRotatef(cameraMotionHelper.getRotationXZ(), 1.0f, 0.0f, -1.0f);

	//поворачиваем всю наблюдаемую систему по горизонтали
	//(управление сценой курсором мыши)
	//угол поворота получаем от объекта-помощника
	glRotatef(cameraMotionHelper.getRotationY(), 0.0f, 1.0f, 1.0f);
	//управление положением источника света

	//сохраняем текущую видовую матрицу в стек
	glPushMatrix();
	//установка позиции источника освещения
	GLfloat lightPos[] = { 5.0f, 5.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//установка позиции модельки "лампочки"
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	//прорисовка "лампочки"
	renderLamp();

	//извлекаем видовую матрицу из стека
	glPopMatrix();

	//прорисовка глобальной системы координат
	axis(15.0f);

	//смешение модельки относительно глобальной оси
	//glTranslatef(2.0f, 2.0f, -2.0f);

	//поворот модельки на заданный угол
	//относительно осей X и Z
	glRotatef(-animationAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef(animationTranslate, 0.0f, animationTranslate);
	//прорисовка собственной системы координат модели
	//axis(5.0f);

	//изменения размера модели
	//преобразование выполняем после прорисовки
	//собственной системы координат
	glScalef(0.5f, 1.5f, 1.5f);

	//прорисовка модели
	renderModel();

	//кох*ханда охрены кадров
	//(для двойной буфферизахщи)
	glutSwapBuffers();
}

//Функция вызывается при изменении размеров окна
void reshape(GLint w, GLint h)
{
	//устанавливаем размеры области отображения
	glViewport(0, 0, w, h);

	//выбираем для настройки матрицу проекций
	glMatrixMode(GL_PROJECTION);

	//сбросим выбранную матрицу (матрицу проекций)
	//заменяет текущую матрицу на единичную
	glLoadIdentity();

	//настройка перспективной проекции
	GLfloat zNear = 1;
	GLfloat zFar = 200;
	//Параметры zFar и zNear задают расстояние от наблюдателя
	//до плоскостей отсечения по глубине и должны быть положительными
	gluPerspective(45.0, (float)w / (float)h, zNear, zFar);
}

//Функция обрабатывает сообщения от клавиатуры
void keyboardFunc( unsigned char key, int x, int )
{
	if (key == ESCAPE) exit(0);
}

//метод получения событий таймера
//используем для реализации анимаций
void updateAnimation(int value)
{
	//для анимации вращения модели
	//изменяем угол вращения по таймеру
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

	//посылаем сообщение для перерисовки сцены
	glutPostRedisplay();

	//запускаем таймер заново
	glutTimerFunc(25, updateAnimation, 0);
}

//метод получения сообщений от мыли (нажатие клавиш)
//будем использовать его для управления отображением сиены
void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) //поступило событие от левой кнопки мыши
	{
		if (state == GLUT_DOWN) //нажатие кнопки мыши
		{
			//запоминаем начальные координаты в которой
			//нажали левую кнопку мыши
			//сообщаем объекту-помощнику что начат поворот сцены
			cameraMotionHelper.startMove(x, y);
		}
		else
		{
			//кнопка мыши была отжата,
			//поэтому заканчиваем поворот сцены
			//сообщаем объекту-помощнику что поворот сцены окончен
			cameraMotionHelper.endMove();
		}
	}
}

//метод получения событий перемещения курсора мыши
//при любой нажатой кнопке мьспи
void mouseMotionFunc(int x, int y)
{
	//сообщаем объекту-помощнику новые координаты курсора
	cameraMotionHelper.move(x, y);
}

//метод получения событий от колеса мыши
//используется для приближения и отдаления камеры наблюдателя
void mouseWheelFunc(int button, int dir, int x, int y)
{
	//в зависимости от направления прокрутки колеса
	//сообщаем объекту-помощнику либо увеличить дистанцию
	//до наблюдаемой точки - либо уменьшить
	if (dir < 0)
		cameraMotionHelper.increaseDistance();
	else
		cameraMotionHelper.decreaseDistance();
}

//метод для расчета нормалей для каждой вершины каждого треугольника модели
//!!! т.к. мы используем алгоритм прорисовки
//!!! GL_TRIANGLES (т.е. каждый треугольник прорисовываем отдельно),
//!!! то нормали мы расчитываем независимо для каждой вершины
void calcModelNormals(const GLfloat* v, GLfloat* n, GLuint vertexCount)
{
	for (GLuint i = 0; i < vertexCount - 2; i += 3)
	{
		vec3 a = vec3(v[i * 3 + 0], v[i * 3 + 1], v[i * 3 + 2]);
		vec3 b = vec3(v[i * 3 + 3], v[i * 3 + 4], v[i * 3 + 5]);
		vec3 c = vec3(v[i * 3 + 6], v[i * 3 + 7], v[i * 3 + 8]);

		vec3 norm = glm::normalize(glm::cross(b - a, c - a));

		//в нашем случае в каждом треугольнике нормали сориентированы одинаково
		memcpy_s(&n[i * 3 + 0], sizeof(GLfloat)* 3, value_ptr(norm), sizeof(GLfloat)*3);
		memcpy_s(&n[i * 3 + 3], sizeof(GLfloat)* 3, value_ptr(norm), sizeof(GLfloat)*3);
		memcpy_s(&n[i * 3 + 6], sizeof(GLfloat)* 3, value_ptr(norm), sizeof(GLfloat)*3);
	}
}

int main(int argc, char** argv)
{
	//Функция glutlnit(&argc, argv) производит начальную инициализацию
	//самой библиотеки GLUT,
	glutInit(&argc, argv);

	//Команда glutlmtDisplayMode (GLUT_RG3) инициализирует буфер кадра и
	//настраивает полноцветный(непалитровый) режим RGB.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	//glutlnitWindowSize(Width, Height) используется для
	//задания начальных размеров окна.
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//задать положение создаваемого окна относительно
	//верхнего левого угла экрана
	glutInitWindowPosition(100, 100);

	//Эта команда создаёт окно с заголовком, который вы укажете в качестве
	//параметра и возвращает HANDLER окна в виде числа int.
	//Этот HANDLER обычно используется для последующих операций
	//над этим окном, таких как изменение параметров окна и закрытие окна.
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
	//рассчитаем нормали для вершин нашей модели
	calcModelNormals(vertexArr, normalArr, 36);

	init();

	//регистрируем функцию перерисовки сцены
	glutDisplayFunc(display);

	//регистрируем функцию изменения размера окна
	glutReshapeFunc(reshape);

	//регистрируем функцию получения событий от клавиатуры
	glutKeyboardFunc(keyboardFunc);

	//регистрируем функцию получения событий от колеса мыши
	glutMouseWheelFunc(mouseWheelFunc);

	//регистрируем функцию получения событий от таймера
	//для реализации анимаций
	glutTimerFunc(25, updateAnimation, 0);

	//регистрируем функцию получения событий от кнопок мыли
	glutMouseFunc(mouseFunc);

	//регистрируем функцию получения событий от движения курсора
	glutMotionFunc(mouseMotionFunc);
	//Контроль всех событий и вызов нужных функций происходит внутри цикла
	//обработки сообщений в функции glutMainLoop().
	glutMainLoop();
	return 0;

}
