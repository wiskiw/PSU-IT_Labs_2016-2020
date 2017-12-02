//
// Created by wiskiw on 02.12.17.
//

#include <iostream>
#include <cmath>
#include "ModulEnemy.h"
#include "../../utils/Utils.h"


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

void drawEnemy(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    glPushMatrix();
    glTranslatef(enemy->pos.x, enemy->pos.y, enemy->pos.z);

    float healthK = enemy->health / 15.0f;

    switch (enemy->type) {
        case 1:
        default:

            glBegin(GL_POLYGON);
            glColor3ub(255, 0, 0);
            glVertex3f(-10 * healthK, -10 * healthK, 0);
            glVertex3f(-10 * healthK, 10 * healthK, 0);
            glVertex3f(10 * healthK, 10 * healthK, 0);
            glVertex3f(10 * healthK, -10 * healthK, 0);
            glEnd();

            enemy->hitBox.leftBottomX = enemy->pos.x - 10;
            enemy->hitBox.leftBottomY = enemy->pos.y - 10;
            enemy->hitBox.rightTopX = enemy->pos.x + 10;
            enemy->hitBox.rightTopY = enemy->pos.y + 10;


    }
    glPopMatrix();

    if (PREF_DRAW_HIT_BOX)
        utilsDrawBorders(enemy->hitBox);

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

void moveEnemy(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    // решает куда и как двигаться
    SW_Player player = thisGame->player;

    float MAX_Y_SPEED = enemy->speed.y;
    float MAX_X_SPEED = enemy->speed.x;

    const float ANGRY_DISTANCE = 135;
    const float NEAR_X_BORDER = MAX_X_SPEED + (enemy->hitBox.rightTopX - enemy->hitBox.leftBottomX) * 2;

    const int TOP = thisGame->borders.rightTopY;
    const int BOTTOM = player.hitBox.rightTopY;
    const int MID_Y = BOTTOM + (TOP - BOTTOM) / 2;
    const int RIGHT = thisGame->borders.rightTopX;
    const int LEFT = thisGame->borders.leftBottomX;

    const int OCTA_Y = (TOP - BOTTOM) / 8;

    float xDiff = player.pos.x - enemy->pos.x; // расстояние до игрока от врага по оX (+/-)



    if (player.hitBox.leftBottomX > enemy->pos.x || player.hitBox.rightTopX < enemy->pos.x) {
        // если игрок не под врагом
        enemy->pos.y += MAX_Y_SPEED;
        enemy->state = 2;
        if (abs(xDiff) <= ANGRY_DISTANCE) {
            if (xDiff < 0) {
                enemy->pos.x += MAX_X_SPEED * 0.5f * -1;
            } else {
                enemy->pos.x += MAX_X_SPEED * 0.5f;
            }
        }
    } else {
        int dirK = 0;
        switch (enemy->state) {
            case 1:
                dirK = -1;
                break;
            case 2:
                dirK = random(1, 2) == 1 ? -1 : 1;
                enemy->state = 2 + dirK;
                break;
            case 3:
                dirK = 1;
                break;
        }
        enemy->pos.x += MAX_X_SPEED * 0.5f * dirK;
        enemy->pos.y += MAX_Y_SPEED * 0.5f;
    }


    // если близко стена
    if (RIGHT - enemy->pos.x <= NEAR_X_BORDER || enemy->pos.x - LEFT <= NEAR_X_BORDER) {
        enemy->state = 2;
    }


}

bool shouldItShoot(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    // стрелять или нет

    SW_Player player = thisGame->player;


    // стрелять, если игрок движется к врагу и находится в этом диапазоне
    const int START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_FAR_RANGE = 200;
    const int START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_NEAR_RANGE = 15;

    const float topY = thisGame->borders.rightTopY;
    const float bottomY = player.pos.y;
    const float midY = abs(topY - bottomY);

    int xDiff = player.pos.x - enemy->pos.x; // расстояние до игрока от врага по оX (+/-)
    int yDiff = abs(player.pos.y - enemy->pos.y); // расстояние до игрока от врага по оУ (+)
    float bulletSpeedY = abs(enemy->gun.bullet.speed.y);

    const float SPEED_K = abs(player.speed.x / 1.67f); // Коэффициент горизонтальной скорости игрока

    switch (player.state) {
        case 1:
            // user going left
            if (xDiff >= START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_NEAR_RANGE * SPEED_K / bulletSpeedY &&
                xDiff <= START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_FAR_RANGE * SPEED_K / bulletSpeedY) {
                return true;
            }
            break;
        case 2:
            // user staw forward
            if (player.hitBox.leftBottomX < enemy->pos.x && player.hitBox.rightTopX > enemy->pos.x) {
                // если игрок под врагом
                return true;
            }
            break;
        case 3:
            // user going right
            if (xDiff <= -START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_NEAR_RANGE * SPEED_K / bulletSpeedY &&
                xDiff >= -START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_FAR_RANGE * SPEED_K / bulletSpeedY) {
                return true;
            }
            break;

    }


    return false;
}

void enemyShot(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    SW_Gun *gun = &enemy->gun;

    switch (gun->state) {
        case 1:
            // ready
            if (shouldItShoot(thisGame, enemy)) {
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
