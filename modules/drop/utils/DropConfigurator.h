//
// Created by wiskiw on 06.12.17.
//

#ifndef COURSE_PAPER_DROPCONFIGURATOR_H
#define COURSE_PAPER_DROPCONFIGURATOR_H


#include "../../../GameStructs.h"


SW_Drop getRandomEnemyDrop(GameFieldStruct *thisGame);

SW_Drop getRandomWorldDrop(GameFieldStruct *thisGame);

SW_Drop getDrop(GameFieldStruct *thisGame, SW_Type dropType);


#endif //COURSE_PAPER_DROPCONFIGURATOR_H
