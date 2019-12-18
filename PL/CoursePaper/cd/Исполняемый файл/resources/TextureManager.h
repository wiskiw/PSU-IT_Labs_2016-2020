//
// Created by wiskiw on 12.12.17.
//

#ifndef COURSE_PAPER_TEXTUREMANAGER_H
#define COURSE_PAPER_TEXTUREMANAGER_H


#include "../GameStructs.h"

void txtInit(GameFieldStruct *thisGame);

GLuint txtGetPlayerTexture();

GLuint txtGetPlanerTexture(int index);

GLuint txtGetEnemyTexture(int index);

GLuint txtGetDropTexture(int index);

GLuint txtGetRandomHitTexture();

GLuint txtGetEggTexture(int index);

GLuint txtGetMainMenuBackgroundTexture();

int txtGetRandomPlanerTextureIndex();

#endif //COURSE_PAPER_TEXTUREMANAGER_H
