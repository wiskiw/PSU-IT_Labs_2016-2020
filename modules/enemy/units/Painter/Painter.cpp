//
// Created by wiskiw on 05.12.17.
//


#include "Painter.h"

const SW_Color ENEMY_HIT_BOX_COLOR = {255, 0, 255};

void redraw1(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {
    float healthK = thisEnemy->health / thisEnemy->originHealth;
    if (healthK <= 0.25f){
        healthK = 0.25f;
    }
    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex3f(-10 * healthK, -10 * healthK, 0);
    glVertex3f(-10 * healthK, 10 * healthK, 0);
    glVertex3f(10 * healthK, 10 * healthK, 0);
    glVertex3f(10 * healthK, -10 * healthK, 0);
    glEnd();
}

void redraw2(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {
    float healthK = thisEnemy->health / thisEnemy->originHealth;
    if (healthK <= 0.5f){
        healthK = 0.5f;
    }
    glBegin(GL_POLYGON);
    glColor3ub(255, 50, 200);
    glVertex3f(-7 * healthK, -7* healthK, 0);
    glVertex3f(-7 * healthK, 7* healthK, 0);
    glVertex3f(7 * healthK, 7 * healthK, 0);
    glVertex3f(7 * healthK, -7* healthK, 0);
    glEnd();
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
        utilsDrawBorders(thisEnemy->hitBox, ENEMY_HIT_BOX_COLOR, 1);
    }

}