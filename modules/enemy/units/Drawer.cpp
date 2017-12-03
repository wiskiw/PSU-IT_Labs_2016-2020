//
// Created by wiskiw on 03.12.17.
//

#include "Drawer.h"
#include "../../../utils/Utils.h"


void draw1(GameFieldStruct *thisGame, SW_Enemy *enemy) {
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


void drawEnemy(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    switch (enemy->type) {
        case 1:
            draw1(thisGame, enemy);

    }
}