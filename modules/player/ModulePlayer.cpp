//
// Created by wiskiw on 01.12.17.
//

#include <iostream>
#include "ModulePlayer.h"
#include "../../utils/Utils.h"

const float SCALE = 4;

int previewSideShoot = 1;

void (*playerShootListener)(SW_Bullet) = nullptr;

void (*playerHealthListener)(SW_Player) = nullptr;


void mdlPlayerSetShootListener(void (*callback)(SW_Bullet)) {
    playerShootListener = callback;
}

void mdlPlayerSetHealthListener(void (*callback)(SW_Player)) {
    playerHealthListener = callback;
}


void checkPlayerForHit(GameFieldStruct *thisGame) {
    SW_Player *player = &thisGame->player;
    for (int i = 0; i < thisGame->bullets.maxsize; ++i) {
        SW_Bullet *bullet = &thisGame->bullets.list[i];
        if (bullet->state == -1) {
            continue;
        }

        const float bX = bullet->pos.x;
        const float bY = bullet->pos.y;

        if (bX >= player->hitBox.leftBottomX && bX <= player->hitBox.rightTopX &&
            bY >= player->hitBox.leftBottomY && bY <= player->hitBox.rightTopY) {
            // hit

            bullet->state = -1;
            player->health -= bullet->damage;
            if (playerHealthListener != nullptr) {
                playerHealthListener(*player);
            }
        }
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

        const float bX = enemy->pos.x;
        const float bY = enemy->pos.y;

        if (bX >= player->hitBox.leftBottomX && bX <= player->hitBox.rightTopX &&
            bY >= player->hitBox.leftBottomY && bY <= player->hitBox.rightTopY) {
            // hit

            enemy->state = -1;
            thisGame->enemies.number--;
            player->health -= enemy->health;
            if (playerHealthListener != nullptr) {
                playerHealthListener(*player);
            }
        }
    }
}

void mdlPlayerDraw(GameFieldStruct *thisGame) {
    thisGame->player.gun.waitBeforeShoot--;


    SW_Player *player = &thisGame->player;
    glPushMatrix();
    glTranslatef(player->pos.x, player->pos.y, player->pos.z);

    switch (player->state) {
        case 1:
            // going left
            glRotated(15, false, true, false);
            glRotated(5, false, false, true);
            break;
        case 2:
            // stay forward

            break;
        case 3:
            // going right
            glRotated(-15, false, true, false);
            glRotated(-5, false, false, true);

            break;
    }

    glBegin(GL_POLYGON);
    glColor3ub(183, 183, 183);
    glVertex3f(0 * SCALE, 5 * SCALE, 0);
    glVertex3f(5 * SCALE, -5 * SCALE, 0);
    glVertex3f(-5 * SCALE, -5 * SCALE, 0);
    glEnd();
    glPopMatrix();

    player->hitBox.leftBottomX = static_cast<int>(player->pos.x - 5 * SCALE);
    player->hitBox.leftBottomY = static_cast<int>(player->pos.y - 5 * SCALE);
    player->hitBox.rightTopX = static_cast<int>(player->pos.x + 5 * SCALE);
    player->hitBox.rightTopY = static_cast<int>(player->pos.y + 5 * SCALE);

    if (PREF_DRAW_HIT_BOX)
        utilsDrawBorders(player->hitBox);

    checkPlayerForHit(thisGame);
}

void mdlPlayerInit(GameFieldStruct *thisGame) {
    SW_Player *player = &thisGame->player;

    player->speed.x = 5;
    player->pos.z = 2;
    player->pos.x = thisGame->borders.leftBottomX;
    player->pos.y = thisGame->borders.leftBottomY + 25;

    player->gun.bullet.damage = 5;
    player->gun.bullet.speed.x = 0;
    player->gun.bullet.speed.y = 5;

    player->gun.gunSpeed = PREF_PLAYER_DEFAULT_GUN_SPEED;
}

void mdlPlayerGoRight(GameFieldStruct *thisGame) {
    if (thisGame->borders.rightTopX - thisGame->player.pos.x > thisGame->player.speed.x) {
        thisGame->player.pos.x += thisGame->player.speed.x;
    } else {
        thisGame->player.pos.x = thisGame->borders.rightTopX;
    }
    thisGame->player.state = 3;
}

void mdlPlayerGoLeft(GameFieldStruct *thisGame) {
    if (thisGame->player.pos.x - thisGame->borders.leftBottomX > thisGame->player.speed.x) {
        thisGame->player.pos.x -= thisGame->player.speed.x;
    } else {
        thisGame->player.pos.x = thisGame->borders.leftBottomX;
    }
    thisGame->player.state = 1;
}

void mdlPlayerShot(GameFieldStruct *thisGame) {
    if (playerShootListener == nullptr) {
        return;
    }

    SW_Bullet bullet = thisGame->player.gun.bullet;
    SW_Gun *gun = &thisGame->player.gun;

    if (gun->waitBeforeShoot <= 0) {
        gun->waitBeforeShoot = gun->gunSpeed;

        bullet.pos = thisGame->player.pos;
        if (previewSideShoot > 0) {
            bullet.pos.x = bullet.pos.x + 5;
            previewSideShoot = -1;
        } else {
            bullet.pos.x = bullet.pos.x - 5;
            previewSideShoot = 1;
        }
        bullet.pos.y = thisGame->player.hitBox.rightTopY + 1;
        playerShootListener(bullet);


        gun->ammorLeft--;
    }

}