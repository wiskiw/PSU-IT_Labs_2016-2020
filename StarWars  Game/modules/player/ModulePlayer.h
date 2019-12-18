//
// Created by wiskiw on 01.12.17.
//

#include <GL/glut.h>
#include "../../GameStructs.h"

#ifndef COURSE_PAPER_MODELPLAYER_H
#define COURSE_PAPER_MODELPLAYER_H

void mdlPlayerSetShootListener(void (*callback)(SW_Bullet));

void mdlPlayerSetHealthListener(void (*callback)(SW_Bullet));

void mdlPlayerSetTakeDropListener(void (*callback)(SW_Drop));

void mdlPlayerUpdate(GameFieldStruct *thisGame);

void mdlPlayerInit(GameFieldStruct *thisGame);

void mdlPlayerGoRight(GameFieldStruct *thisGame);

void mdlPlayerGoLeft(GameFieldStruct *thisGame);

void mdlPlayerShot(GameFieldStruct *thisGame);

#endif //COURSE_PAPER_MODELPLAYER_H
