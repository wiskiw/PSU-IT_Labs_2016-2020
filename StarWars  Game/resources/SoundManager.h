//
// Created by wiskiw on 10.12.17.
//

#ifndef COURSE_PAPER_SOUNDMANAGER_H
#define COURSE_PAPER_SOUNDMANAGER_H

#include "../GameStructs.h"

void sndInit(GameFieldStruct *thisGame);

void sndPlayerShot();

void sndEnemyShot();

void sndEnemyDead();

void sndPlayerDamage();

void sndEnemyDamage();

void sndButtonSelect();

void sndButtonClick();

void sndTakeDrop();

#endif //COURSE_PAPER_SOUNDMANAGER_H
