//
// Created by wiskiw on 06.12.17.
//

#ifndef COURSE_PAPER_MODULEDROP_H
#define COURSE_PAPER_MODULEDROP_H

#include "../../GameStructs.h"

enum DropSpawnType {
    DROP_SPAWN_TYPE_ENEMY, DROP_SPAWN_TYPE_WORLD
};


void mdlDropInit(GameFieldStruct *thisGame);

void mdlDropAddNew(GameFieldStruct *thisGame, SW_Drop drop);

void mdlDropUpdate(GameFieldStruct *thisGame);

void mdlDropAction(GameFieldStruct *thisGame, SW_Drop drop);

SW_Drop mdlDropGetNew(GameFieldStruct *thisGame, DropSpawnType dropSpawnType);


#endif //COURSE_PAPER_MODULEDROP_H
