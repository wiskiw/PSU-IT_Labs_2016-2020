//
// Created by wiskiw on 05.12.17.
//


#include "Painter.h"
#include "../../../../resources/TextureManager.h"

const SW_Color ENEMY_HIT_BOX_COLOR = {255, 0, 255};

void redraw1(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {

    glScalef(1.5f, 1.5f, 0);
    switch (thisEnemy->state) {
        case ENEMY_STATE_GOING_RIGHT:
            // going left
            glRotated(34, false, true, false);
            glRotated(2, false, false, true);
            break;
        case ENEMY_STATE_GOING_LEFT:
            // going right
            glRotated(-34, false, true, false);
            glRotated(-2, false, false, true);
            break;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txtGetEnemyTexture(0));
    glBegin(GL_POLYGON);

    glColor4ub(1, 1, 1, 255);

    glTexCoord2f(0, 0);
    glVertex2f(-10, -10);
    glTexCoord2f(0, 1);
    glVertex2f(-10, 10);
    glTexCoord2f(1, 1);
    glVertex2f(10, 10);
    glTexCoord2f(1, 0);
    glVertex2f(10, -10);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void redraw2(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {
    float healthK = thisEnemy->health / thisEnemy->originHealth;
    if (healthK <= 0.5f) {
        healthK = 0.5f;
    }

    glScalef(healthK, healthK, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txtGetEnemyTexture(3));
    glBegin(GL_POLYGON);

    glColor4ub(1, 1, 1, 255);

    glTexCoord2f(0, 0);
    glVertex2f(-10, -10);
    glTexCoord2f(0, 1);
    glVertex2f(-10, 10);
    glTexCoord2f(1, 1);
    glVertex2f(10, 10);
    glTexCoord2f(1, 0);
    glVertex2f(10, -10);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


// вызов функции отрисовки по типу врага
void redrawEnemy(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {
    glPushMatrix();
    glTranslatef(thisEnemy->pos.x, thisEnemy->pos.y, thisEnemy->pos.z);

    switch (thisEnemy->type) {
        case 1:
            redraw1(thisGame, thisEnemy);
            break;
        case 2:
            redraw2(thisGame, thisEnemy);
            break;
    }
    glPopMatrix();


    if (PREF_DRAW_HIT_BOX) {
        utilsDrawHitBox(thisEnemy->hitBox, ENEMY_HIT_BOX_COLOR);
    }

}