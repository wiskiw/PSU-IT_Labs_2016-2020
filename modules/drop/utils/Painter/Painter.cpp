//
// Created by wiskiw on 06.12.17.
//

#include "Painter.h"
#include "../../../../utils/Utils.h"
#include "../../../../resources/TextureManager.h"


const SW_Color DROP_HIT_BOX_COLOR = {255, 0, 255};


void redraw1(GameFieldStruct *thisGame, SW_Drop *drop) {
    glEnable(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txtGetDropTexture(6));
    glBegin(GL_POLYGON);

    glColor4ub(0, 0, 0, 255);
    glTexCoord2f(0, 0);
    glVertex2f(-PREF_DROP_WIDTH / 2, -PREF_DROP_HEIGHT / 2);
    glTexCoord2f(0, 1);
    glVertex2f(-PREF_DROP_WIDTH / 2, PREF_DROP_HEIGHT / 2);
    glTexCoord2f(1, 1);
    glVertex2f(PREF_DROP_WIDTH / 2, PREF_DROP_HEIGHT / 2);
    glTexCoord2f(1, 0);
    glVertex2f(PREF_DROP_WIDTH / 2, -PREF_DROP_HEIGHT / 2);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void redraw2(GameFieldStruct *thisGame, SW_Drop *drop) {
    glEnable(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txtGetDropTexture(7));

    glBegin(GL_POLYGON);
    glColor4ub(0, 0, 0, 255);
    glTexCoord2f(0, 0);
    glVertex2f(-PREF_DROP_WIDTH / 2, -PREF_DROP_HEIGHT / 2);
    glTexCoord2f(0, 1);
    glVertex2f(-PREF_DROP_WIDTH / 2, PREF_DROP_HEIGHT / 2);
    glTexCoord2f(1, 1);
    glVertex2f(PREF_DROP_WIDTH / 2, PREF_DROP_HEIGHT / 2);
    glTexCoord2f(1, 0);
    glVertex2f(PREF_DROP_WIDTH / 2, -PREF_DROP_HEIGHT / 2);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}


float getScaleFactor(SW_Drop *thisDrop) {
    // начальное и конечное значение livingTime периода увеличения скорости мерцания
    const float speedUpStartTimeValue = thisDrop->timeToLive - PREF_DROP_PRE_REMOVE_BLINK_TIME;
    const float speedUpEndTimeValue = thisDrop->timeToLive -
                                      (PREF_DROP_PRE_REMOVE_BLINK_TIME * (100 - PREF_DROP_SPEED_UP_PERCENT) / 100);


    float deltaScale = 0.015f;

    if (thisDrop->timeToLive > 0) {
        // deltaTime - остаток времени до уничтожения дропа
        int deltaTime = thisDrop->timeToLive - thisDrop->livingTime;
        if (deltaTime <= PREF_DROP_PRE_REMOVE_BLINK_TIME) {
            if (thisDrop->livingTime <= speedUpEndTimeValue) {
                const float currentDeltaSpeedUp = thisDrop->livingTime - speedUpStartTimeValue;
                const float speedUpPercent = currentDeltaSpeedUp * 100 /
                                             (speedUpEndTimeValue - speedUpStartTimeValue);
                deltaScale *= 1 + speedUpPercent / 100 / PREF_DROP_MAX_SPEED_UP_FACTOR;
            } else {
                deltaScale *= PREF_DROP_MAX_SPEED_UP_FACTOR;
            }
        }
    }

    return deltaScale;
}

void updateDropScale(SW_Drop *thisDrop) {
    float *scale = &thisDrop->scaleState;
    if (*scale >= PREF_DROP_MAX_SCALE_STATE) {
        thisDrop->scaleGrownUp = false;
    }
    if (*scale <= 1) {
        thisDrop->scaleGrownUp = true;
    }

    if (thisDrop->scaleGrownUp) {
        *scale += getScaleFactor(thisDrop);
    } else {
        *scale -= getScaleFactor(thisDrop);
    }
}

// вызов функции отрисовки по типу дропа
void redrawDrop(GameFieldStruct *thisGame, SW_Drop *thisDrop) {
    if (thisGame->gameState == GAME_STATE_PLAY) {
        updateDropScale(thisDrop);
    }


    glPushMatrix();
    glTranslatef(thisDrop->pos.x, thisDrop->pos.y, thisDrop->pos.z);
    glScalef(thisDrop->scaleState, thisDrop->scaleState, 1);


    // Добавлять методы рисования тут
    switch (thisDrop->type) {
        case 1:
            redraw1(thisGame, thisDrop);
            break;
        case 2:
            redraw2(thisGame, thisDrop);
            break;
    }


    glPopMatrix();
    if (PREF_DRAW_HIT_BOX) {
        utilsDrawHitBox(thisDrop->hitBox, DROP_HIT_BOX_COLOR);
    }
}