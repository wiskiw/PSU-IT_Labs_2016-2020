//
// Created by wiskiw on 05.12.17.
//

#ifndef COURSE_PAPER_ENEMYGENERATOR_H
#define COURSE_PAPER_ENEMYGENERATOR_H


#include "../../../GameStructs.h"
#include "../../../utils/Utils.h"

SW_Enemy getEnemy(GameFieldStruct *thisGame, SW_Type enemyType);

SW_Enemy getRandomAvailableEnemy(GameFieldStruct *thisGame, const float maxAvailableEnemyHealth);


#endif //COURSE_PAPER_ENEMYGENERATOR_H
