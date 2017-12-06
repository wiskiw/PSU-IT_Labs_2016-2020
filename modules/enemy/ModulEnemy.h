//
// Created by wiskiw on 02.12.17.
//

#ifndef COURSE_PAPER_MODULENEMY_H
#define COURSE_PAPER_MODULENEMY_H

#include "../../GameStructs.h"

void mdlEnemySetShootListener(void (*callback)(SW_Bullet));

void mdlEnemySetEnemyKilledListener(void (*callback)(SW_Enemy));

void mdlEnemyUpdateAll(GameFieldStruct *thisGame);

void mdlEnemyInitAll(GameFieldStruct *thisGame);


#endif //COURSE_PAPER_MODULENEMY_H
