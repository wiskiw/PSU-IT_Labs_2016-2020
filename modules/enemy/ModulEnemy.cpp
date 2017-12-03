//
// Created by wiskiw on 02.12.17.
//

#include "ModulEnemy.h"
#include "../../utils/Utils.h"

#include "units/Mover.h"
#include "units/Drawer.h"
#include "units/Thinker.h"


const int MAX_RE_SPAWN_TICK_COUNTER = 350;
int reSpawnTickCounter = MAX_RE_SPAWN_TICK_COUNTER;


void (*enemyShootListener)(SW_Bullet) = nullptr;

void mdlEnemySetShootListener(void (*callback)(SW_Bullet)) {
    enemyShootListener = callback;
}


// тип врага по параметрам игры
SW_Type getEnemyType(GameFieldStruct *thisGame) {


    return 1;
}

// задавать типы противников тут
void spawnEnemy(GameFieldStruct *thisGame) {
    SW_Enemy newEnemy;

    newEnemy.pos.x = random(thisGame->borders.leftBottomX + 50, thisGame->borders.rightTopX - 50);
    newEnemy.pos.y = thisGame->borders.rightTopY;
    newEnemy.pos.z = PREF_ENEMY_Z_POS;

    newEnemy.state = 2;
    newEnemy.type = getEnemyType(thisGame);
    switch (newEnemy.type) {
        case 1:
            newEnemy.health = 15;
            newEnemy.gun.gunSpeed = 15;

            newEnemy.speed.y = -0.6f;
            newEnemy.speed.x = 1.1f;

            newEnemy.gun.bullet.speed.y = -5;
            newEnemy.gun.bullet.speed.x = 0;

            newEnemy.gun.bullet.damage = 0.5;

            newEnemy.gun.ammorSize = 50;
            newEnemy.gun.ammorLeft = 50;

            newEnemy.gun.reloadTicks = 150;
            break;

        default:
            return;
    }


    // добавление в лист врагов
    for (int i = 0; i < thisGame->enemies.maxNumber; ++i) {
        if (thisGame->enemies.list[i].state == -1) {
            thisGame->enemies.number++;
            thisGame->enemies.list[i] = newEnemy;
            break;
        }
    }

}

void checkEnemyForHit(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    for (int i = 0; i < thisGame->bullets.maxsize; ++i) {
        SW_Bullet *bullet = &thisGame->bullets.list[i];
        if (bullet->state == -1) {
            continue;
        }

        const float bX = bullet->pos.x;
        const float bY = bullet->pos.y;

        if (bX >= enemy->hitBox.leftBottomX && bX <= enemy->hitBox.rightTopX &&
            bY >= enemy->hitBox.leftBottomY && bY <= enemy->hitBox.rightTopY) {
            // hit

            bullet->state = -1;
            enemy->health -= bullet->damage;
            if (enemy->health <= 0) {
                thisGame->enemies.number--;
                enemy->state = -1;
            }
        }
    }
}

void enemyShot(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    SW_Gun *gun = &enemy->gun;

    switch (gun->state) {
        case 1:
            // ready
            if (shouldShoot(thisGame, enemy)) {
                if (gun->ammorLeft <= 0) {
                    gun->state = 2;
                    gun->leftTicksForReload = gun->reloadTicks;
                } else {
                    if (gun->waitBeforeShoot <= 0) {
                        gun->waitBeforeShoot = gun->gunSpeed;

                        gun->bullet.state = 1;
                        gun->bullet.pos = enemy->pos;
                        gun->bullet.pos.y = enemy->hitBox.leftBottomY - 1;
                        if (enemyShootListener != nullptr) {
                            enemyShootListener(gun->bullet);
                        }
                        gun->ammorLeft--;
                    }
                }
            }
            gun->waitBeforeShoot--;
            break;
        case 2:
            // reload
            gun->leftTicksForReload--;
            if (gun->leftTicksForReload <= 0) {
                gun->state = 1;
                gun->ammorLeft = gun->ammorSize;
                gun->waitBeforeShoot = gun->gunSpeed;
            }
            break;
        default:
            return;
    }


}

void mdlEnemyDrawAll(GameFieldStruct *thisGame) {
    reSpawnTickCounter++;

    if (thisGame->enemies.number < thisGame->enemies.maxNumber &&
        reSpawnTickCounter >= MAX_RE_SPAWN_TICK_COUNTER / (thisGame->difficult / 2.0f)) {
        reSpawnTickCounter = 0;
        spawnEnemy(thisGame);
    }


    int enCounter = 0; // кол-во проверенных врагов из списка
    for (int k = 0; thisGame->enemies.number > 0 &&
                    enCounter < thisGame->enemies.number &&
                    k < thisGame->enemies.maxNumber; k++) {

        SW_Enemy *enemy = &thisGame->enemies.list[k];
        if (enemy->state == -1) {
            continue;
        }
        enCounter++;

        moveEnemy(thisGame, enemy);
        enemyShot(thisGame, enemy);
        checkEnemyForHit(thisGame, enemy);
        drawEnemy(thisGame, enemy);

    }


}


void mdlEnemyInitAll(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->enemies.maxNumber; ++i) {
        thisGame->enemies.list[i].state = -1;
    }
}
