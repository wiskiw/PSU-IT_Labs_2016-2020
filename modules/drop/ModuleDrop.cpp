//
// Created by wiskiw on 06.12.17.
//

#include "ModuleDrop.h"
#include "../../utils/Utils.h"
#include "utils/Painter/Painter.h"
#include "utils/Action/Action.h"
#include "utils/DropConfigurator.h"


void mdlDropInit(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->dropMap.maxNumber; ++i) {
        thisGame->dropMap.list[i].state = DROP_STATE_UNDEFINED;
    }
}

void moveDrop(GameFieldStruct *thisGame, SW_Drop *drop) {
    const float MAX_SCALE_K = (drop->hitBox.rightTopY - drop->hitBox.leftBottomY) * PREF_DROP_MAX_SCALE_STATE / 2;
    if ((drop->hitBox.leftBottomY + PREF_DROP_SPEED_Y) - MAX_SCALE_K <= thisGame->gameBorders.leftBottomY) {
        // упал
        drop->pos.y = thisGame->gameBorders.leftBottomY +
                      (drop->hitBox.rightTopY - drop->hitBox.leftBottomY) / 2 + MAX_SCALE_K;
        drop->hitBox.rightTopY = drop->pos.y + PREF_DROP_HEIGHT / 2;
        drop->hitBox.leftBottomY = drop->pos.y - PREF_DROP_HEIGHT / 2;
        drop->livingTime++;
    } else {
        // падает
        drop->pos.y += PREF_DROP_SPEED_Y;
        SW_Pos moveHitBoxValue;
        moveHitBoxValue.y = PREF_DROP_SPEED_Y;
        utilsMoveBorers(&drop->hitBox, moveHitBoxValue);
    }
}

void mdlDropAddNew(GameFieldStruct *thisGame, SW_Drop drop) {
    if (drop.state == DROP_STATE_UNDEFINED) {
        return;
    }

    drop.pos.z = PREF_DROP_Z_POS;
    drop.hitBox.leftBottomX = -PREF_DROP_WIDTH / 2;
    drop.hitBox.leftBottomY = -PREF_DROP_HEIGHT / 2;
    drop.hitBox.rightTopX = PREF_DROP_WIDTH / 2;
    drop.hitBox.rightTopY = PREF_DROP_HEIGHT / 2;

    utilsMoveBorers(&drop.hitBox, drop.pos);


    for (int i = 0; i < thisGame->dropMap.maxNumber; ++i) {
        if (thisGame->dropMap.list[i].state == DROP_STATE_UNDEFINED) {
            thisGame->dropMap.list[i] = drop;
            if (i + 1 < thisGame->dropMap.maxNumber) {
                thisGame->dropMap.list[i + 1].state = DROP_STATE_UNDEFINED;
            } else {
                thisGame->dropMap.list[0].state = DROP_STATE_UNDEFINED;
            }
            break;
        }
    }
}

void mdlDropUpdate(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->dropMap.maxNumber; ++i) {
        SW_Drop *drop = &thisGame->dropMap.list[i];

        if (drop->state != DROP_STATE_UNDEFINED) {
            if (thisGame->gameState == GAME_STATE_PLAY) {
                moveDrop(thisGame, drop);

                if (drop->timeToLive > 0 && drop->livingTime >= drop->timeToLive) {
                    // время жизни истекло
                    drop->state = DROP_STATE_UNDEFINED;
                }
            }

            redrawDrop(thisGame, drop);
        }
    }
}

void mdlDropAction(GameFieldStruct *thisGame, SW_Drop drop) {
    activateDropAction(thisGame, &drop);
}

SW_Drop mdlDropGetNew(GameFieldStruct *thisGame, DropSpawnType dropSpawnType) {

    SW_Type type = dropSpawnType == DROP_SPAWN_TYPE_ENEMY ? getRandomEnemyDropType() : getRandomWorldDropType();

    return getDrop(thisGame, type);
}
