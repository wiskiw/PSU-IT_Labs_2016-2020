//
// Created by wiskiw on 01.12.17.
//

#include "ModulePlayer.h"
#include "../../utils/Utils.h"
#include "../../gp-elements/gun/gpeGun.h"
#include "../../gp-elements/gun/list/gun-list.h"
#include "../../gp-elements/bullet/list/bullet-list.h"

const float SCALE = 4;
const SW_Color PLAYER_HIT_BOX_COLOR = {255, 0, 255};


int previewSideShoot = 1;

void (*playerShootListener)(SW_Bullet) = nullptr;

void (*playerHealthListener)(SW_Player) = nullptr;

void (*playerTakeDrop)(SW_Drop) = nullptr;


void mdlPlayerSetShootListener(void (*callback)(SW_Bullet)) {
    playerShootListener = callback;
}

void mdlPlayerSetHealthListener(void (*callback)(SW_Player)) {
    playerHealthListener = callback;
}

void mdlPlayerSetTakeDropListener(void (*callback)(SW_Drop)) {
    playerTakeDrop = callback;
}


void checkPlayerForHit(GameFieldStruct *thisGame) {
    SW_Player *player = &thisGame->player;

    // в игрока попала пуля
    for (int i = 0; i < thisGame->bulletMap.maxNumber; ++i) {
        SW_Bullet *bullet = &thisGame->bulletMap.list[i];
        if (bullet->state == BULLET_STATE_UNDEFINED) {
            continue;
        }

        if (utilsIsPosInBorders(bullet->pos, player->hitBox)) {
            // hit

            bullet->state = BULLET_STATE_UNDEFINED;
            player->health -= bullet->damage;
            if (playerHealthListener != nullptr) {
                playerHealthListener(*player);
            }
        }
    }


    // игроком задел врага
    int enCounter = 0; // кол-во проверенных врагов из списка
    for (int k = 0; thisGame->enemyMap.number > 0 &&
                    enCounter < thisGame->enemyMap.number &&
                    k < thisGame->enemyMap.maxNumber; k++) {

        SW_Enemy *enemy = &thisGame->enemyMap.list[k];
        if (enemy->state == ENEMY_STATE_UNDEFINED) {
            continue;
        }
        enCounter++;

        if (utilsIsPosInBorders(enemy->pos, player->hitBox)) {
            // hit
            enemy->state = ENEMY_STATE_UNDEFINED;
            thisGame->enemyMap.number--;
            player->health -= enemy->health;
            if (playerHealthListener != nullptr) {
                playerHealthListener(*player);
            }
        }
    }

    // игрок подобрал дроп
    for (int i = 0; i < thisGame->dropMap.maxNumber; ++i) {
        SW_Drop *drop = &thisGame->dropMap.list[i];
        if (drop->state == DROP_STATE_UNDEFINED) {
            continue;
        }

        if (utilsIsPosInBorders(drop->pos, player->hitBox)) {
            // hit
            drop->state = DROP_STATE_UNDEFINED;
            const float previewPlayerHealth = player->health;
            if (playerTakeDrop != nullptr) {
                playerTakeDrop(*drop);
            }
            if (player->health != previewPlayerHealth){
                playerHealthListener(*player);
            }
        }
    }


}

void mdlPlayerUpdate(GameFieldStruct *thisGame) {
    SW_Player *player = &thisGame->player;

    gpeGunUpdateShootingDelay(&player->gun);
    glPushMatrix();
    glTranslatef(player->pos.x, player->pos.y, player->pos.z);

    switch (player->state) {
        case PLAYER_STATE_GOING_LEFT:
            // going left
            glRotated(15, false, true, false);
            glRotated(5, false, false, true);
            break;
        case PLAYER_STATE_STAY_FORWARD:
            // stay forward

            break;
        case PLAYER_STATE_GOING_RIGHT:
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
        utilsDrawBorders(player->hitBox, PLAYER_HIT_BOX_COLOR, 1);

    checkPlayerForHit(thisGame);
}

void mdlPlayerInit(GameFieldStruct *thisGame) {
    SW_Player *player = &thisGame->player;

    player->health = PREF_PLAYER_DEFAULT_HEALTH;
    player->state = PLAYER_STATE_STAY_FORWARD;
    player->speed.x = 5;
    player->pos.z = 2;
    player->pos.x = (thisGame->gameBorders.rightTopX - thisGame->gameBorders.leftBottomX) / 2 +
                    thisGame->gameBorders.leftBottomX;
    player->pos.y = thisGame->gameBorders.leftBottomY + 25;

    player->gun = gunsGetBengalGun();
    player->gun.bullet = bulletsGetSideneckBullet();
}

void mdlPlayerGoRight(GameFieldStruct *thisGame) {
    float hitBoxWidth = thisGame->player.hitBox.rightTopX - thisGame->player.hitBox.leftBottomX;
    if (thisGame->gameBorders.rightTopX - thisGame->player.hitBox.rightTopX > thisGame->player.speed.x) {
        thisGame->player.pos.x += thisGame->player.speed.x;
    } else {
        thisGame->player.pos.x = thisGame->gameBorders.rightTopX - hitBoxWidth / 2;
    }
    thisGame->player.state = PLAYER_STATE_GOING_RIGHT;
}

void mdlPlayerGoLeft(GameFieldStruct *thisGame) {
    float hitBoxWidth = thisGame->player.hitBox.rightTopX - thisGame->player.hitBox.leftBottomX;

    if (thisGame->player.hitBox.leftBottomX - thisGame->gameBorders.leftBottomX > thisGame->player.speed.x) {
        thisGame->player.pos.x -= thisGame->player.speed.x;
    } else {
        thisGame->player.pos.x = thisGame->gameBorders.leftBottomX + hitBoxWidth / 2;
    }
    thisGame->player.state = PLAYER_STATE_GOING_LEFT;
}

void mdlPlayerShot(GameFieldStruct *thisGame) {
    if (playerShootListener == nullptr) {
        return;
    }

    SW_Pos shotFrom = thisGame->player.pos;
    if (previewSideShoot > 0) {
        shotFrom.x = shotFrom.x + 5;
        previewSideShoot = -1;
    } else {
        shotFrom.x = shotFrom.x - 5;
        previewSideShoot = 1;
    }
    shotFrom.y = thisGame->player.hitBox.rightTopY + 1;

    SW_Bullet bullet = gpeGunShoot(&thisGame->player.gun, shotFrom);
    if (bullet.state != BULLET_STATE_UNDEFINED) {
        playerShootListener(bullet);
    }

}