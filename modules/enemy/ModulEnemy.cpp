//
// Created by wiskiw on 02.12.17.
//

#include "ModulEnemy.h"
#include "../../utils/Utils.h"

#include "units/EnemyConfigurator.h"
#include "../../gp-elements/gun/gpeGun.h"
#include "units/Mover/Mover.h"
#include "units/Aimer/Aimer.h"
#include "units/Painter/Painter.h"


const int MAX_RE_SPAWN_TICK_COUNTER = 350;


void (*enemyShootListener)(SW_Bullet) = nullptr;

void (*enemyDamageListener)(SW_Enemy, SW_Bullet) = nullptr;

void (*enemyCrossBorderListener)(SW_Enemy) = nullptr;

void mdlEnemySetShootListener(void (*callback)(SW_Bullet)) {
    enemyShootListener = callback;
}

void mdlEnemySetCrossBorderListener(void (*callback)(SW_Enemy)) {
    enemyCrossBorderListener = callback;
}

void mdlEnemySetEnemyDamageListener(void (*callback)(SW_Enemy, SW_Bullet)) {
    enemyDamageListener = callback;
}

void spawnEnemy(GameFieldStruct *thisGame) {
    SW_Enemy newEnemy = getEnemy(thisGame, getRandomEnemyType());
    newEnemy.state = ENEMY_STATE_STAY_FORWARD;

    thisGame->enemyMap.enemiesHealth += newEnemy.health;

    // добавление в лист врагов
    for (int i = 0; i < thisGame->enemyMap.maxNumber; ++i) {
        if (thisGame->enemyMap.list[i].state == ENEMY_STATE_UNDEFINED) {
            thisGame->enemyMap.number++;
            thisGame->enemyMap.list[i] = newEnemy;
            break;
        }
    }

}

void checkEnemyForHit(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    for (int i = 0; i < thisGame->bulletMap.maxNumber; ++i) {
        SW_Bullet *bullet = &thisGame->bulletMap.list[i];
        if (bullet->state == BULLET_STATE_UNDEFINED) {
            continue;
        }

        if (utilsIsPosInBorders(bullet->pos, enemy->hitBox)) {
            // hit

            bullet->state = BULLET_STATE_UNDEFINED;
            enemy->health -= bullet->damage;
            thisGame->enemyMap.enemiesHealth -= bullet->damage;
            if (enemy->health <= 0) {
                // killed
                thisGame->enemyMap.number--;
                enemy->state = ENEMY_STATE_UNDEFINED;
            }
            if (enemyDamageListener != nullptr) {
                enemyDamageListener(*enemy, *bullet);
            }
        }
    }
}

void mdlEnemyUpdateAll(GameFieldStruct *thisGame) {
    if (thisGame->gameState == GAME_STATE_PLAY) {
        if (thisGame->enemyMap.number < thisGame->enemyMap.maxNumber &&
            (thisGame->globalTickTimer % (MAX_RE_SPAWN_TICK_COUNTER / (thisGame->difficult / 2)) == 0) ||
            thisGame->globalTickTimer == 10) {
            spawnEnemy(thisGame);
        }
    }


    int enCounter = 0; // кол-во проверенных врагов из списка
    for (int k = 0; thisGame->enemyMap.number > 0 &&
                    enCounter < thisGame->enemyMap.number &&
                    k < thisGame->enemyMap.maxNumber; k++) {

        SW_Enemy *enemy = &thisGame->enemyMap.list[k];
        if (enemy->state == ENEMY_STATE_UNDEFINED) {
            continue;
        }
        enCounter++;

        if (thisGame->gameState == GAME_STATE_PLAY) {
            // перемещение врага и его хитбокса
            SW_Pos movPosValue = moveEnemy(thisGame, enemy);
            utilsMovePos(&enemy->pos, movPosValue);
            utilsMoveBorers(&enemy->hitBox, movPosValue);

            SW_Pos gunPos = enemy->pos;
            utilsMovePos(&gunPos, enemy->gunPosValue);

            if (!utilsIsPosInBorders(enemy->pos, thisGame->gameBorders)){
                enemy->state = ENEMY_STATE_UNDEFINED;
                enCounter--;
                thisGame->enemyMap.number--;
                if (enemyCrossBorderListener != nullptr){
                    enemyCrossBorderListener(*enemy);
                }
            } else {
                gpeGunUpdateShootingDelay(&enemy->gun);
                if (enemyShootListener != nullptr && isTargetLocked(thisGame, enemy)) {
                    SW_Bullet bullet = gpeGunShoot(&enemy->gun, gunPos);
                    if (bullet.state != BULLET_STATE_UNDEFINED) {
                        enemyShootListener(bullet);
                    }
                }

                checkEnemyForHit(thisGame, enemy);
            }
        }

        redrawEnemy(thisGame, enemy);

    }


}


void mdlEnemyInitAll(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->enemyMap.maxNumber; ++i) {
        thisGame->enemyMap.list[i].state = ENEMY_STATE_UNDEFINED;
    }
}
