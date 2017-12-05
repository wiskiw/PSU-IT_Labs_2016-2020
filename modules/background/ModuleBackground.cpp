//
// Created by wiskiw on 01.12.17.
//

#include <cmath>
#include "ModuleBackground.h"
#include "../../utils/Utils.h"

const int COLORS_NUMBER = 3;
const float STARS_OPACITY = 0.4f;
const float STARS_SPEED_K = 0.8f; //коэффициент скорости движения звёзд

void chooseColor(int color) {
    switch (color) {
        case 1:
            //white
            glColor4ub(255, 255, 255, static_cast<GLubyte>(255 * STARS_OPACITY));
            break;
        case 2:
            //yellow
            glColor4ub(255, 233, 79, static_cast<GLubyte>(200 * STARS_OPACITY));
            break;
        case 3:
            //reed
            glColor4ub(255, 93, 12, static_cast<GLubyte>(255 * STARS_OPACITY));
            break;
        case 4:
            //purple
            glColor4ub(125, 66, 165, static_cast<GLubyte>(255 * STARS_OPACITY));
            break;
    }
}

// установка основных характеристик звёзд
void setBaseStarPreferences(SW_Star *star) {
    star->pos.z = -1;
    star->color = random(1, COLORS_NUMBER);
    star->size = static_cast<float>((rand()) / (static_cast <float> (RAND_MAX / 1.1)) + 0.7);
    star->speed.y = random(2.4f * STARS_SPEED_K, 5 * STARS_SPEED_K) * star->size;
}

// первоначально заполнение массива звёзд
void mdlBackgroundInit(GameFieldStruct *thisGame) {
    const int number = thisGame->background.starNumber;
    for (int k = 0; k < number; k++) {
        SW_Star *star = &thisGame->background.stars[k];
        star->pos.x = random(thisGame->gameBorders.leftBottomX, thisGame->gameBorders.rightTopX);
        star->pos.y = random(thisGame->gameBorders.leftBottomY, thisGame->gameBorders.rightTopY);
        setBaseStarPreferences(star);
    }
}

// создание новой звезда с верху игрового поля
void createStar(GameFieldStruct *thisGame, SW_Star *star) {
    setBaseStarPreferences(star);
    star->pos.x = random(thisGame->gameBorders.leftBottomX, thisGame->gameBorders.rightTopX);
    star->pos.y = thisGame->gameBorders.rightTopY;
};

void mdlBackgroundDraw(GameFieldStruct *thisGame) {
    const int number = thisGame->background.starNumber;
    for (int k = 0; k < number; k++) {

        SW_Star *star = &thisGame->background.stars[k];

        glPushMatrix();
        glTranslatef(star->pos.x, star->pos.y, 0);
        glBegin(GL_POLYGON);
        chooseColor(star->color);
        glVertex3f(0, 1 * star->size, star->pos.z);
        glVertex3f(1 * star->size, -1 * star->size, star->pos.z);
        glVertex3f(-1 * star->size, -1 * star->size, star->pos.z);
        glEnd();
        glPopMatrix();

        star->pos.y -= star->speed.y;
        if (star->pos.y <= thisGame->gameBorders.leftBottomY) {
            // отрисовка новой звезды, если старая выходит за границы игрового поля
            createStar(thisGame, star);
        }
    }
}

