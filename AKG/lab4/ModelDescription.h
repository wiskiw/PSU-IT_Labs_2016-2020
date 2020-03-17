#include "GL/freeglut.h"
#include "GL/freeglut_ext.h"
#include <vector>
#include "MathUtils.h"
#include "TextureUtils.h"

using namespace std;

#define URND(max) fabs(rand()%(int)(max*100.0f)/100.0f)

#define RND(max) -max+fabs(rand()%(int)(max*2*100.0f)/100.0f)


float vXZ0 = 0.05f;
float vY0 = 1.0f;

struct SPRITE
{
	GLfloat p[3]; //положение частицы GLfloat c[4]; //цвет частицы GLfloat s; //размер частицы
	GLfloat c[4]; //вектор ускорения частицы GLfloat g; //вектор силы тяжести
	GLfloat s; //время жизни частицы, только для режима 3

	GLfloat v[3];
	GLfloat g;

	GLfloat t;

	double sinq;
	double cosq;

	bool xy;
	bool xz = true;

	double qwe = 1.0f;
	double xP = 0.0f, xO = 0.0f;

	void step()
	{
		
			//p[0] += 0;//v[0];
			//p[1] += v[1];// +g;
			//p[2] += v[2];

			//v[1] *= 0.99f;

			//g *= 1.01f;

			if (p[1] > 25.0f)
				reset();


			cosq = sqrt(1.0 - (pow(sinq, 2)));
			if (xy) {

				
				sinq += 1 / 10.0;
				if (sinq >= 1.0f) {
					xy = false;
				}
				cosq = cosq * (-1.0);
			}
			else {
				sinq -= 1 / 10.0;
				if (sinq <= -1.0f) {
					xy = true;
				}
			}
			p[0] = 1 * 5 * sinq * qwe;
			p[1] += 0.05f;
			if (p[0] > 0) {
				xP -= 0.03;
				p[0] = 1 * 5 * sinq / (1.0 + xO);
				p[2] = 1 * 5 * cosq / (1.0 +xO);
			}
			if (p[0] < 0) {
				xO += 0.03;
				p[0] = 1 * 5 * sinq / (1.0 - xP);
				p[2] = 1 * 5 * cosq / (1.0 - xP);
			}
			
			
			t *= 0.95f;

			if (t < 0.1f)
				reset();

			/*if (p[2] >= 1.0f)
				xz = false;
			else if (p[2] <= -1.0f)
				xz = true;
			if(xz == true)
				p[2] += 0.1f;
			else
				p[2] -= 0.1f;*/
			//изменяем положение частицы согласно //векторам ускорения Р[0] += v[0]; р[1] += v[l] + g;
			//уменьшаем вертикальное ускорение v[l] *= 0.99f;
			//увеличиваем силу тяжести g *= 1.01f;
			//если частица достигла 0 по вертикали //задаем новые параметры частицы if (р[1] <= 0.0f) reset();
		
	}

		void reset()
		{

			c[0] = 0.5f;
			c[1] = 0.5f;
			c[2] = 0.5f;
			c[3] = 0.8f;

			p[0] = 0.0f;
			p[1] = 0.0f;
			p[2] = 0.0f;

			s = 0.2f;

			v[0] = RND(vXZ0);
			v[1] = URND(vY0);
			v[2] = RND(vXZ0);

			t = URND(1000.0f);
			g = -0.5f;

			xy = false;
			xz = true;
			sinq = 0;
			cosq = 0;
			double qwe = 1.0f;
			xO = 0.0;
			xP = 0.0;
		}		
		
		SPRITE()
		{
			reset();
		}
	};


	typedef vector<SPRITE> SPRITES;
	SPRITES modelSprites;
	void modelInitSprites()
	{
		modelSprites.clear();
		//инициализируем систему на 100 частиц 
		for (int i=0; i<300; i++)
			modelSprites.push_back(SPRITE());
	}