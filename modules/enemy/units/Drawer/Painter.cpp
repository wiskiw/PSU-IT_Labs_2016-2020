//
// Created by wiskiw on 05.12.17.
//


#include "Painter.h"

const SW_Color ENEMY_HIT_BOX_COLOR = {255, 0, 255};

void redraw1(GameFieldStruct *thisGame, SW_Enemy *thisEnemy){
    float healthK = thisEnemy->health / 15.0f;
    switch (thisEnemy->type) {
        case 1:
        default:
            glBegin(GL_POLYGON);
            glColor3ub(255, 0, 0);
            glVertex3f(-10 * healthK, -10 * healthK, 0);
            glVertex3f(-10 * healthK, 10 * healthK, 0);
            glVertex3f(10 * healthK, 10 * healthK, 0);
            glVertex3f(10 * healthK, -10 * healthK, 0);
            glEnd();
    }
}



// вызов функции отрисовки по типу врага
void redrawEnemy(GameFieldStruct *thisGame, SW_Enemy *thisEnemy){
    glPushMatrix();
    glTranslatef(thisEnemy->pos.x, thisEnemy->pos.y, thisEnemy->pos.z);

    switch (thisEnemy->type){
        case 1:
            redraw1(thisGame, thisEnemy);
            break;
    }
    glPopMatrix();


    if (PREF_DRAW_HIT_BOX){
        utilsDrawBorders(thisEnemy->hitBox, ENEMY_HIT_BOX_COLOR, 1);
    }

}