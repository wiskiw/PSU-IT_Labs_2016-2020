#ifndef TEXTURE_UTILS
#define TEXTURE_UTILS

#include "GL/freeglut.h"

#include "GL/freeglut_ext.h"

#include "FreeImage.h"

void utlLoadTexture(GLuint* texture, const char* imageFileName)
{
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imageFileName, 0);

	FIBITMAP* img = FreeImage_Load(format, imageFileName);
	BYTE* bDataPointer = FreeImage_GetBits(img);

	int iWidth = FreeImage_GetWidth(img);
	int iHeight = FreeImage_GetHeight(img);
	int iBPP = FreeImage_GetBPP(img);


	glGenTextures(1, texture);

	glBindTexture(GL_TEXTURE_2D, *texture);


	int iFormat = iBPP == 24 ? GL_BGR_EXT : iBPP == 8 ? GL_LUMINANCE : 0;

	printf("utlLoadTexture: %02d %02d %02d\n", iWidth, iHeight, iBPP);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, iFormat, GL_UNSIGNED_BYTE, bDataPointer);



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	FreeImage_Unload(img);
}
#endif


