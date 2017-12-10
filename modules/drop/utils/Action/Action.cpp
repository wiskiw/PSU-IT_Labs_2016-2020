//
// Created by wiskiw on 06.12.17.
//

#include "Action.h"


void action1(GameFieldStruct *thisGame, SW_Drop *thisDrop) {
    thisGame->player.health = PREF_PLAYER_DEFAULT_HEALTH;
}


void activateDropAction(GameFieldStruct *thisGame, SW_Drop *thisDrop) {
    switch (thisDrop->type) {
        case 1:
            action1(thisGame, thisDrop);
            break;
    }
}
