#include <stdlib.h>

#include "GL/freeglut.h"

#include "GL/freeglut_ext.h"


#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

using namespace glm;
using namespace std;



void utlCalcModelNormals(const GLfloat* v, const GLuint* i, GLfloat* n, GLuint vCount, GLuint iCount)

{

	vector<vec3>* normals = new vector<vec3>[vCount];
	memset(n, 0, sizeof(GLfloat) * vCount * 3);

	for (GLuint j = 0; j < iCount - 2; j += 3)
	{
		vec3 a = vec3(v[i[j + 0] * 3 + 0], v[i[j + 0] * 3 + 1], v[i[j + 0] * 3 + 2]);
		vec3 b = vec3(v[i[j + 1] * 3 + 0], v[i[j + 1] * 3 + 1], v[i[j + 1] * 3 + 2]);
		vec3 c = vec3(v[i[j + 2] * 3 + 0], v[i[j + 2] * 3 + 1], v[i[j + 2] * 3 + 2]);

		vec3 norm = glm::normalize(glm::cross(b - a, c - a));
		normals[i[j + 0]].push_back(norm);
		normals[i[j + 1]].push_back(norm);
		normals[i[j + 2]].push_back(norm);

		for (GLuint j = 0; j < vCount; j++)
		{

			vec3 vNormal = vec3(0.0f);
			if (normals[j].size() > 0) {

				vNormal = normals[j][0];

				for (GLuint k = 1; k < normals[j].size(); k++)
					vNormal += normals[j][k];

				vNormal = glm::normalize(vNormal);

				memcpy_s(&n[j * 3], sizeof(GLfloat) * 3, glm::value_ptr(vNormal), sizeof(GLfloat) * 3);
			}
		}
		//delete[] normals;
	}

}