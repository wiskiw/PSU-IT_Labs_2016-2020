//
// Created by wiskiw on 02.12.17.
//

#include "ModuleBullet.h"
#include "../../utils/Utils.h"

void mdlBulletDrawAll(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->bullets.maxsize; ++i) {
        SW_Bullet bullet = thisGame->bullets.list[i];
        if (bullet.state != BULLET_STATE_UNDEFINED) {

            glPushMatrix();
            const float SPEED_K = bullet.speed.y * 0.3f;
            glTranslatef(bullet.pos.x, bullet.pos.y + 6 * SPEED_K, 0);
            utilsSelectColor(bullet.color);


            glBegin(GL_POLYGON);
            glVertex3f(0, 1, bullet.pos.z);
            glVertex3f(1, -6 * SPEED_K, bullet.pos.z);
            glVertex3f(-1, -6 * SPEED_K, bullet.pos.z);

            glEnd();
            glPopMatrix();


            bullet.pos.y += bullet.speed.y;
            if (bullet.pos.y >= thisGame->gameBorders.rightTopY || bullet.pos.y <= thisGame->gameBorders.leftBottomY) {
                thisGame->bullets.list[i].state = BULLET_STATE_UNDEFINED;
            } else {
                thisGame->bullets.list[i] = bullet;
            }
        }
    }
}

// добавление пули в кэш
void mdlBulletAddNew(GameFieldStruct *thisGame, SW_Bullet bullet) {
    if (bullet.state == BULLET_STATE_UNDEFINED) {
        return;
    } else {
        bullet.pos.z = PREF_BULLET_Z_POS;
    }

    for (int i = 0; i < thisGame->bullets.maxsize; ++i) {
        if (thisGame->bullets.list[i].state == BULLET_STATE_UNDEFINED) {
            thisGame->bullets.list[i] = bullet;
            if (i + 1 < thisGame->bullets.maxsize) {
                thisGame->bullets.list[i + 1].state = BULLET_STATE_UNDEFINED;
            } else {
                thisGame->bullets.list[0].state = BULLET_STATE_UNDEFINED;
            }
            break;
        }
    }
}

void mdlBulletInitAll(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->bullets.maxsize; ++i) {
        thisGame->bullets.list[i].state = BULLET_STATE_UNDEFINED;
    }
}
