//
// Created by wiskiw on 06.12.17.
//

#ifndef COURSE_PAPER_MENU_H
#define COURSE_PAPER_MENU_H


#include "../../GameStructs.h"


void menuDrawPause(GameFieldStruct *thisGame);

void menuProcessPauseMenuItemClick(GameFieldStruct *thisGame, int key, int x, int y);

void menuProcessPauseMenuItemFocus(GameFieldStruct *thisGame, int x, int y);


#endif //COURSE_PAPER_MENU_H
