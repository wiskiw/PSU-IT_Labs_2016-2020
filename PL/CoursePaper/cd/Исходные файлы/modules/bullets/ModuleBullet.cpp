//
// Created by wiskiw on 02.12.17.
//

#include "ModuleBullet.h"
#include "../../utils/Utils.h"
#include "../../resources/TextureManager.h"

void mdlBulletUpdateAll(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->bulletMap.maxNumber; ++i) {
        SW_Bullet bullet = thisGame->bulletMap.list[i];
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


            if (thisGame->gameState == GAME_STATE_PLAY) {
                bullet.pos.y += bullet.speed.y;
                if (bullet.pos.y >= thisGame->gameBorders.rightTopY ||
                    bullet.pos.y <= thisGame->gameBorders.leftBottomY) {
                    thisGame->bulletMap.list[i].state = BULLET_STATE_UNDEFINED;
                } else {
                    thisGame->bulletMap.list[i] = bullet;
                }
            }
        }
    }
}


void mdlBulletDrawBulletHit(SW_Bullet bullet) {
    const float scale = bullet.damage / 3 * random(1.2f, 1.6f);
    glPushMatrix();
    glTranslatef(bullet.pos.x, bullet.pos.y, PREF_HIT_Z_POS);
    glRotatef(random(0, 360), false, false, true);
    glScalef(scale, scale, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txtGetRandomHitTexture());
    glBegin(GL_POLYGON);
    glColor4ub(1, 1, 1, 255);
    glTexCoord2f(0, 0);
    glVertex2f(-5, -5);
    glTexCoord2f(0, 1);
    glVertex2f(-5, 5);
    glTexCoord2f(1, 1);
    glVertex2f(5, 5);
    glTexCoord2f(1, 0);
    glVertex2f(5, -5);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}

// добавление пули в кэш
void mdlBulletAddNew(GameFieldStruct *thisGame, SW_Bullet bullet) {
    if (bullet.state == BULLET_STATE_UNDEFINED) {
        return;
    } else {
        bullet.pos.z = PREF_BULLET_Z_POS;
    }

    for (int i = 0; i < thisGame->bulletMap.maxNumber; ++i) {
        if (thisGame->bulletMap.list[i].state == BULLET_STATE_UNDEFINED) {
            thisGame->bulletMap.list[i] = bullet;
            if (i + 1 < thisGame->bulletMap.maxNumber) {
                thisGame->bulletMap.list[i + 1].state = BULLET_STATE_UNDEFINED;
            } else {
                thisGame->bulletMap.list[0].state = BULLET_STATE_UNDEFINED;
            }
            break;
        }
    }
}

void mdlBulletInitAll(GameFieldStruct *thisGame) {
    for (int i = 0; i < thisGame->bulletMap.maxNumber; ++i) {
        thisGame->bulletMap.list[i].state = BULLET_STATE_UNDEFINED;
    }
}
