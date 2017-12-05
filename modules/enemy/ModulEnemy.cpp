//
// Created by wiskiw on 02.12.17.
//

#include "ModulEnemy.h"
#include "../../utils/Utils.h"

#include "units/EnemyGenerator.h"
#include "../../gp-elements/gun/gpeGun.h"
#include "units/Mover/Mover.h"
#include "units/Aimer/Aimer.h"
#include "units/Drawer/Painter.h"


const int MAX_RE_SPAWN_TICK_COUNTER = 350;


void (*enemyShootListener)(SW_Bullet) = nullptr;

void mdlEnemySetShootListener(void (*callback)(SW_Bullet)) {
    enemyShootListener = callback;
}

void spawnEnemy(GameFieldStruct *thisGame) {
    SW_Enemy newEnemy = getEnemy(thisGame);
    newEnemy.state = ENEMY_STATE_STAY_FORWARD;

    thisGame->enemies.enemiesHealth += newEnemy.health;

    // добавление в лист врагов
    for (int i = 0; i < thisGame->enemies.maxNumber; ++i) {
        if (thisGame->enemies.list[i].state == ENEMY_STATE_UNDEFINED) {
            thisGame->enemies.number++;
            thisGame->enemies.list[i] = newEnemy;
            break;
        }
    }

}

void checkEnemyForHit(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    for (int i = 0; i < thisGame->bullets.maxsize; ++i) {
        SW_Bullet *bullet = &thisGame->bullets.list[i];
        if (bullet->state == BULLET_STATE_UNDEFINED) {
            continue;
        }

        const float bX = bullet->pos.x;
        const float bY = bullet->pos.y;

        if (bX >= enemy->hitBox.leftBottomX && bX <= enemy->hitBox.rightTopX &&
            bY >= enemy->hitBox.leftBottomY && bY <= enemy->hitBox.rightTopY) {
            // hit


            bullet->state = BULLET_STATE_UNDEFINED;
            enemy->health -= bullet->damage;
            thisGame->enemies.enemiesHealth -= bullet->damage;
            if (enemy->health <= 0) {
                thisGame->enemies.number--;
                enemy->state = ENEMY_STATE_UNDEFINED;
            }
        }
    }
}

void mdlEnemyDrawAll(GameFieldStruct *thisGame) {

    if (thisGame->enemies.number < thisGame->enemies.maxNumber &&
        (thisGame->globalTickTimer % (MAX_RE_SPAWN_TICK_COUNTER / (thisGame->difficult / 2)) == 0) ||
        thisGame->globalTickTimer == 10) {
        spawnEnemy(thisGame);
    }


    int enCounter = 0; // кол-во проверенных врагов из списка
    for (int k = 0; thisGame->enemies.number > 0 &&
                    enCounter < thisGame->enemies.number &&
                    k < thisGame->enemies.maxNumber; k++) {

        SW_Enemy *enemy = &thisGame->enemies.list[k];
        if (enemy->state == ENEMY_STATE_UNDEFINED) {
            continue;
        }
        enCounter++;

        // перемещение врага и его хитбокса
        SW_Pos movPosValue = moveEnemy(thisGame, enemy);
        utilsMovePos(&enemy->pos, movPosValue);
        utilsMoveBorers(&enemy->hitBox, movPosValue);


        SW_Pos gunPos = enemy->pos;
        utilsMovePos(&gunPos, enemy->gunPosValue);


        gpeGunUpdateShootingDelay(&enemy->gun);
        if (enemyShootListener != nullptr && isTargetLocked(thisGame, enemy)) {
            SW_Bullet bullet = gpeGunShoot(&enemy->gun, gunPos);
            if (bullet.state != BULLET_STATE_UNDEFINED) {
                enemyShootListener(bullet);
            }
        }

        checkEnemyForHit(thisGame, enemy);
        redrawEnemy(thisGame, enemy);

    }


}


void mdlEnemyInitAll(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->enemies.maxNumber; ++i) {
        thisGame->enemies.list[i].state = ENEMY_STATE_UNDEFINED;
    }
}
