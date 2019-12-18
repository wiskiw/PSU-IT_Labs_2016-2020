//
// Created by wiskiw on 02.12.17.
//

#ifndef COURSE_PAPER_UTILS_H
#define COURSE_PAPER_UTILS_H


#include "../GameStructs.h"

int random(int start, int end);

float random(float start, float end);

void utilsDrawBorders(SW_Borders borders, SW_Color color, int width, float z);

void utilsDrawHitBox(SW_Borders borders, SW_Color color);

void utilsSelectColor(SW_Color color);

void utilsConcatColors(SW_Color *colorResult, int r, int g, int b, int a);

void utilsMoveBorers(SW_Borders *borders, SW_Pos movPosValue);

void utilsMovePos(SW_Pos *pos, SW_Pos movPosValue);

void utilsDrawText(SW_Pos pos, SW_Color color, void *font, const char *string);

bool utilsIsPosInBorders(SW_Pos pos, SW_Borders borders);

void utilsConvertToGameWindowPosition(GameFieldStruct *thisGame, SW_Pos *pos);

#endif //COURSE_PAPER_UTILS_H
