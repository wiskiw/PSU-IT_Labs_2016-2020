//
// Created by wiskiw on 02.12.17.
//

#include <iostream>
#include "ModuleBullet.h"

void mdlBulletDrawAll(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->bullets.maxsize; ++i) {
        SW_Bullet bullet = thisGame->bullets.list[i];
        if (bullet.state != -1) {

            glPushMatrix();
            const float SPEED_K = bullet.speed.y * 0.3f;
            glTranslatef(bullet.pos.x, bullet.pos.y + 6 * SPEED_K, 0);
            glColor3ub(57, 237, 45);


            glBegin(GL_POLYGON);
            glVertex3f(0, 1, bullet.pos.z);
            glVertex3f(1, -6 * SPEED_K, bullet.pos.z);
            glVertex3f(-1, -6 * SPEED_K, bullet.pos.z);

            glEnd();
            glPopMatrix();


            bullet.pos.y += bullet.speed.y;
            if (bullet.pos.y >= thisGame->borders.rightTopY || bullet.pos.y <= thisGame->borders.leftBottomY) {
                thisGame->bullets.list[i].state = -1;
            } else {
                thisGame->bullets.list[i] = bullet;
            }
        }
    }
}

// добавление пули в кэш
void mdlBulletAddNew(GameFieldStruct *thisGame, SW_Bullet bullet) {
    if (bullet.state == -1) {
        return;
    } else {
        bullet.pos.z = PREF_BULLET_Z_POS;
    }

    for (int i = 0; i < thisGame->bullets.maxsize; ++i) {
        if (thisGame->bullets.list[i].state == -1) {
            thisGame->bullets.list[i] = bullet;
            if (i + 1 < thisGame->bullets.maxsize) {
                thisGame->bullets.list[i + 1].state = -1;
            } else {
                thisGame->bullets.list[0].state = -1;
            }
            break;
        }
    }
}

void mdlBulletInitAll(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->bullets.maxsize; ++i) {
        thisGame->bullets.list[i].state = -1;
    }
}
