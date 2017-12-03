//
// Created by wiskiw on 03.12.17.
//

#include "UI.h"
#include "../utils/Utils.h"

const float ELEMENT_HEIGHT = 15;
const float DIVINER_X = 10;
const float DIVINER_Y = 10;

float const UI_Z = 10;
const float UI_BACKGROUND_Z = 0;


const int HEALTH_BAR_POS = 2;
const SW_COLOR HEALTH_BAR_COLOR = {255, 0, 0};


const int RELOAD_BAR_POS = 3;
const SW_COLOR RELOAD_BAR_COLOR = {255, 0, 255};


const SW_COLOR GAME_BORDER_LINE_COLOR = {100, 100, 100};
const SW_COLOR UI_BACKGROUND_COLOR = {50, 50, 50};


float uiLineX;


float getHeight(int pos) {
    return (DIVINER_Y + ELEMENT_HEIGHT) * pos;
}

float getWidth() {
    return uiLineX - DIVINER_Y * 2;
}

void drawBar(float maxValue, float currentValue, SW_COLOR color, int pos) {
    float percent = currentValue * 100 / maxValue;
    percent = percent < 0 ? 0 : percent;
    percent = percent > 100 ? 100 : percent;
    float xPX = getWidth() * percent / 100;


    const float startY = getHeight(pos);
    const float startX = DIVINER_X;

    glPushMatrix();
    glBegin(GL_POLYGON);
    utilsSelectColor(color);
    glVertex3f(startX, startY, UI_Z);
    glVertex3f(startX, startY - ELEMENT_HEIGHT, UI_Z);
    glVertex3f(startX + xPX, startY - ELEMENT_HEIGHT, UI_Z);
    glVertex3f(startX + xPX, startY, UI_Z);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);

    color.A = 150;
    utilsSelectColor(color);
    glVertex3f(startX, startY, UI_Z + 0.01f);
    glVertex3f(startX, startY - ELEMENT_HEIGHT, UI_Z + 0.01f);
    glVertex3f(startX + getWidth(), startY - ELEMENT_HEIGHT, UI_Z + 0.01f);
    glVertex3f(startX + getWidth(), startY, UI_Z + 0.01f);
    glEnd();
    glLineWidth(1);

    glPopMatrix();

}

void drawHealth(GameFieldStruct *thisGame) {
    drawBar(PREF_PLAYER_DEFAULT_HEALTH, thisGame->player.health, HEALTH_BAR_COLOR, HEALTH_BAR_POS);
}

void drawGunReload(GameFieldStruct *thisGame) {
    float maxValue = thisGame->player.gun.gunSpeed;
    drawBar(maxValue, maxValue - thisGame->player.gun.waitBeforeShoot, RELOAD_BAR_COLOR, RELOAD_BAR_POS);
}

void drawGameBorder(GameFieldStruct *thisGame) {
    glPushMatrix();
    glLineWidth(4);
    glBegin(GL_LINES);
    utilsSelectColor(GAME_BORDER_LINE_COLOR);
    glVertex3f(uiLineX, thisGame->borders.leftBottomY, UI_Z);
    glVertex3f(uiLineX, thisGame->borders.rightTopY, UI_Z);
    glEnd();
    glLineWidth(1);
    glPopMatrix();

}

void drawInterfaceBackground(GameFieldStruct *thisGame) {
    glPushMatrix();
    glBegin(GL_POLYGON);
    utilsSelectColor(UI_BACKGROUND_COLOR);
    glVertex3f(0, 0, UI_BACKGROUND_Z);
    glVertex3f(0, thisGame->borders.rightTopY, UI_BACKGROUND_Z);
    glVertex3f(uiLineX, thisGame->borders.rightTopY, UI_BACKGROUND_Z);
    glVertex3f(uiLineX, 0, UI_BACKGROUND_Z);
    glEnd();
    glPopMatrix();
}


void uiInit(GameFieldStruct *thisGame, float leftPX) {
    uiLineX = leftPX;


}

void uiUpdate(GameFieldStruct *thisGame) {
    drawHealth(thisGame);
    drawGunReload(thisGame);
    drawGameBorder(thisGame);
    drawInterfaceBackground(thisGame);

}