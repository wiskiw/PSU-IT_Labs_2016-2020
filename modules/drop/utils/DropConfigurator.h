//
// Created by wiskiw on 06.12.17.
//

#ifndef COURSE_PAPER_DROPCONFIGURATOR_H
#define COURSE_PAPER_DROPCONFIGURATOR_H


#include "../../../GameStructs.h"


SW_Type getRandomWorldDropType();

SW_Type getRandomEnemyDropType();

SW_Drop getDrop(GameFieldStruct *thisGame, SW_Type dropType);



#endif //COURSE_PAPER_DROPCONFIGURATOR_H
