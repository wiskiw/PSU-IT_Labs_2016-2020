//
// Created by wiskiw on 06.12.17.
//

#include "Action.h"


void action1(GameFieldStruct *thisGame, SW_Drop *thisDrop) {
    thisGame->player.health = PREF_PLAYER_DEFAULT_HEALTH;
}

void action2(GameFieldStruct *thisGame, SW_Drop *thisDrop) {
    for (int k = 0; k < thisGame->enemyMap.maxNumber; k++) {
        SW_Enemy *enm = &thisGame->enemyMap.list[k];
        if (enm->state != ENEMY_STATE_UNDEFINED){
            thisGame->score += enm->score;
            enm->state = ENEMY_STATE_UNDEFINED;
        }
    }
    thisGame->enemyMap.number = 0;
    thisGame->enemyMap.enemiesHealth = 0;
}


void activateDropAction(GameFieldStruct *thisGame, SW_Drop *thisDrop) {
    switch (thisDrop->type) {
        case 1:
            // health drop
            action1(thisGame, thisDrop);
            break;
        case 2:
            // kill enemies drop
            action2(thisGame, thisDrop);
            break;
    }
}
