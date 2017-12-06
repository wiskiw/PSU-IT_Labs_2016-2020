//
// Created by wiskiw on 03.12.17.
//

#ifndef COURSE_PAPER_UI_H
#define COURSE_PAPER_UI_H

#include "../GameStructs.h"


void uiInit(GameFieldStruct *thisGame);

void uiUpdate(GameFieldStruct *thisGame);

void uiProcessInputClick(GameFieldStruct *thisGame, int key, int x, int y);

void uiProcessMouseMove(GameFieldStruct *thisGame, int x, int y);


#endif //COURSE_PAPER_UI_H
