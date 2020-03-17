
#include "GL/freeglut.h"

#include "GL/freeglut_ext.h"


#include "MathUtils.h"


#include "TextureUtils.h"

const GLuint MODEL_VERTEX_COUNT = 40;


const GLfloat MODEL_VERTICES[MODEL_VERTEX_COUNT * 3] =
{
	// Front face
		-0.4, -0.9, -1.0, 0.4, -0.9, -1.0, 0.4, 0.9, -1.0, -0.4, 0.9, -1.0,

	// Back face
		-0.4, -0.4, 1.0, 0.4, -0.4, 1.0, 0.4, 0.4, 1.0, -0.4, 0.4, 1.0,

	// Top face
		-0.4, 0.4, -1.0, 0.4, 0.4, -1.0, 0.4, 0.4, 1.0, -0.4, 0.4, 1.0,
		-0.4, 0.9, -1.0, 0.4, 0.9, -1.0, 0.4, 0, -2.0, -0.4, 0, -2.0,

	// Bottom face
		-0.4, -0.4, -1.0, 0.4, -0.4, -1.0, 0.4, -0.4, 1.0, -0.4, -0.4, 1.0,
		-0.4, -0.9, -1.0, 0.4, -0.9, -1.0, 0.4, 0, -2.0, -0.4, 0, -2.0,

	// Right face
		0.4, -0.4, -1.0, 0.4, 0.4, -1.0, 0.4, 0.4, 1.0, 0.4, -0.4, 1.0,		 
		0.4, 0.0, -2.0, 0.4, 0.0, -2.0, 0.4, -0.9, -1.0, 0.4, 0.9, -1.0,

	// Left face
		-0.4, -0.4, -1.0, -0.4, 0.4, -1.0, -0.4, 0.4, 1.0, -0.4, -0.4, 1.0,		 
		-0.4, -0.9, -1.0, -0.4, 0.9, -1.0, -0.4, 0.0, -2.0, -0.4, 0.0, -2.0,
};

const GLfloat MODEL_TEXTURE_COORDS[MODEL_VERTEX_COUNT*2] =
{
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
};

const GLuint MODEL_INDEX_COUNT = 60;


const GLuint MODEL_INDICES[MODEL_INDEX_COUNT] =
{
0, 1, 2, 0, 2, 3, // front
6, 5, 4, 7, 6, 4, // back

10, 9, 8, 11, 10, 8, // top
14, 13, 12, 15, 14, 12, // top

16, 17, 18, 16, 18, 19, // bottom
20, 21, 22, 20, 22, 23, // bottom

24, 25, 26, 24, 26, 27,// right
28, 29, 30, 28, 30, 31, // right

34, 33, 32, 35, 34, 32, // lett
38, 37, 36, 39, 38, 36, // lett
};


struct MATERIAL

{

	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];
	GLfloat shininess;

};


struct MODEL

{

	GLfloat vertices[MODEL_VERTEX_COUNT * 3];
	GLfloat textureCoords[MODEL_VERTEX_COUNT * 2];

	GLfloat normals[MODEL_VERTEX_COUNT * 3];
	GLuint indices[MODEL_INDEX_COUNT];


	GLuint glassTexture;


	GLuint brickTexture;


	GLuint metalTexture;

	GLuint cubicTexture;

	MATERIAL material;

	void initTexture()

	{
		utlLoadTexture(&glassTexture, "glass.jpg");
		utlLoadTexture(&brickTexture, "brick.jpg");
		utlLoadTexture(&metalTexture, "metal.jpg");
	}

	MODEL()
	{
		memcpy_s(vertices, MODEL_VERTEX_COUNT * 3 * sizeof(GLfloat), MODEL_VERTICES, MODEL_VERTEX_COUNT * 3 * sizeof(GLfloat));
		memcpy_s(textureCoords, MODEL_VERTEX_COUNT * 2 * sizeof(GLfloat), MODEL_TEXTURE_COORDS, MODEL_VERTEX_COUNT * 2 * sizeof(GLfloat));
		memcpy_s(indices, MODEL_INDEX_COUNT * 1 * sizeof(GLuint), MODEL_INDICES, MODEL_INDEX_COUNT * 1 * sizeof(GLuint));

		utlCalcModelNormals(vertices, indices, normals, MODEL_VERTEX_COUNT, MODEL_INDEX_COUNT);

		GLfloat emissionColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		memcpy_s(material.emission, sizeof(GLfloat) * 4, emissionColor, sizeof(GLfloat) * 4);

		GLfloat ambientColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		memcpy_s(material.ambient, sizeof(GLfloat) * 4, ambientColor, sizeof(GLfloat) * 4);

		GLfloat diffuseColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		memcpy_s(material.diffuse, sizeof(GLfloat) * 4, diffuseColor, sizeof(GLfloat) * 4);

		GLfloat specularColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		memcpy_s(material.specular, sizeof(GLfloat) * 4, specularColor, sizeof(GLfloat) * 4);

		material.shininess = 128 * 0.2f;
	}
};

