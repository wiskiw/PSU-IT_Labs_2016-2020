//
// Created by wiskiw on 03.12.17.
//

#ifndef COURSE_PAPER_UI_H
#define COURSE_PAPER_UI_H

#include "../GameStructs.h"


void uiInit(GameFieldStruct *thisGame, void(*uiItemSelectListener)(GameState, int));

void uiUpdate(GameFieldStruct *thisGame);

void uiProcessInput(GameFieldStruct *thisGame, int key, int x, int y, bool special);

void uiProcessMouseMove(GameFieldStruct *thisGame, int x, int y);


#endif //COURSE_PAPER_UI_H
