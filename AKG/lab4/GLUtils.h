#include<stdlib.h>

#include "GL/freeglut.h"

#include "GL/freeglut_ext.h"

void utlPrintExtList()
{

	const char* vendor = (const char*)glGetString(GL_VENDOR);


	const char* renderer = (const char*)glGetString(GL_RENDERER);

	const char* version = (const char*)glGetString(GL_VERSION);

	const char* extensions = (const char*)glGetString(GL_EXTENSIONS);


	printf("Vendor: %s\n Renderer : %s\n Version : %s\n ", vendor, renderer, version);
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

void usr_glClearMaterial() {
	GLfloat blackColor[] = { 0.0f,0.0f,0.0f,0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, blackColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blackColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);
	glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
	glMaterialf(GL_FRONT, GL_SHININESS, 0);
}

//метот для отображения эффекта прозрачных текстур
void glEnableTransparentTexcure(GLboolean _enabled)
{
	if (_enabled)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);


		glEnable(GL_BLEND);


		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDepthMask(GL_FALSE);
	}
	else {

		glDisable(GL_COLOR_MATERIAL);

		glDisable(GL_BLEND);

		glDepthMask(GL_TRUE);
	}
}
