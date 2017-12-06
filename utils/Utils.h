//
// Created by wiskiw on 02.12.17.
//

#ifndef COURSE_PAPER_UTILS_H
#define COURSE_PAPER_UTILS_H


#include "../GameStructs.h"

int random(int start, int end);

float random(float start, float end);

void utilsDrawBorders(SW_Borders borders, SW_Color color, int width);

void utilsSelectColor(SW_Color color);

void utilsMoveBorers(SW_Borders *borders, SW_Pos movPosValue);

void utilsMovePos(SW_Pos *pos, SW_Pos movPosValue);

void utilsDrawText(SW_Pos pos, SW_Color color, void *font, char *string);

#endif //COURSE_PAPER_UTILS_H
