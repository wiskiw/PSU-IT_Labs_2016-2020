//
// Created by wiskiw on 06.12.17.
//

#ifndef COURSE_PAPER_MENU_H
#define COURSE_PAPER_MENU_H

#include "../../GameStructs.h"

// ==== Pause Menu ====
void dialogDrawPauseMenu(GameFieldStruct *thisGame);

int dialogProcessPauseMenuRowClick(GameFieldStruct *thisGame, int key, int x, int y);

void dialogProcessPauseMenuRowFocus(GameFieldStruct *thisGame, int x, int y);


// ==== Main Menu ====
void dialogDrawMainMenu(GameFieldStruct *thisGame);

int dialogProcessMainMenuRowClick(GameFieldStruct *thisGame, int key, int x, int y);

void dialogProcessMainMenuRowFocus(GameFieldStruct *thisGame, int x, int y);


// ==== Records ====
void dialogDrawRecordList(GameFieldStruct *thisGame);

int dialogProcessRecordListBottomButtonClick(GameFieldStruct *thisGame, int key, int x, int y);

void dialogProcessRecordListBottomButtonFocus(GameFieldStruct *thisGame, int x, int y);

void dialogDrawRecordListAddNew(GameFieldStruct *thisGame);

int dialogProcessRecordListAddNewInput(GameFieldStruct *thisGame, int key, int x, int y, bool special);


// ==== Game over ====
void dialogDrawGameOver(GameFieldStruct *thisGame);

void dialogDrawGameOverNewRecord(GameFieldStruct *thisGame);

int dialogProcessAllGameOverInput(GameFieldStruct *thisGame, int key, int x, int y, bool special);

#endif //COURSE_PAPER_MENU_H
