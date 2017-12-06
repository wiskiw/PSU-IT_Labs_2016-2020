//
// Created by wiskiw on 03.12.17.
//

#include <iostream>
#include "UI.h"
#include "../utils/Utils.h"
#include "menu/Menu.h"

const float ELEMENT_HEIGHT = 15;
const float DIVINER_X = 10;
const float DIVINER_Y = 10;

float const UI_Z = 10;
const float UI_BACKGROUND_Z = 0;


const int HEALTH_BAR_POS = 2;
const SW_Color HEALTH_BAR_COLOR = {255, 0, 0};


const int RELOAD_BAR_POS = 3;
const SW_Color RELOAD_BAR_COLOR = {255, 0, 255};


const SW_Color GAME_BORDER_LINE_COLOR = {100, 100, 100};
const SW_Color UI_BACKGROUND_COLOR = {50, 50, 50};


SW_Borders interfaceBorders;

float getHeight(int pos) {
    return (DIVINER_Y + ELEMENT_HEIGHT) * pos;
}

float getWidth() {
    return (interfaceBorders.rightTopX - interfaceBorders.leftBottomX) - DIVINER_Y * 2;
}

void drawBar(float maxValue, float currentValue, SW_Color color, int pos) {
    float percent = currentValue * 100 / maxValue;
    percent = percent < 0 ? 0 : percent;
    percent = percent > 100 ? 100 : percent;
    float xPX = getWidth() * percent / 100;


    const float startY = interfaceBorders.leftBottomY + getHeight(pos);
    const float startX = interfaceBorders.leftBottomX + DIVINER_X;

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
    utilsDrawBorders(thisGame->gameBorders, GAME_BORDER_LINE_COLOR, 4);
}

void drawInterfaceBackground(GameFieldStruct *thisGame) {
    glPushMatrix();
    glBegin(GL_POLYGON);
    utilsSelectColor(UI_BACKGROUND_COLOR);
    glVertex3f(interfaceBorders.leftBottomX, interfaceBorders.leftBottomY, UI_BACKGROUND_Z);
    glVertex3f(interfaceBorders.leftBottomX, interfaceBorders.rightTopY, UI_BACKGROUND_Z);
    glVertex3f(interfaceBorders.rightTopX, interfaceBorders.rightTopY, UI_BACKGROUND_Z);
    glVertex3f(interfaceBorders.rightTopX, interfaceBorders.leftBottomY, UI_BACKGROUND_Z);
    glEnd();
    glPopMatrix();
}


void uiInit(GameFieldStruct *thisGame) {
    interfaceBorders = thisGame->interfaceBorders;

}

void uiUpdate(GameFieldStruct *thisGame) {
    drawHealth(thisGame);
    drawGunReload(thisGame);
    drawGameBorder(thisGame);
    drawInterfaceBackground(thisGame);


    switch (thisGame->gameState) {
        case GAME_STATE_PLAY:


            break;
        case GAME_STATE_PAUSE:
            menuDrawPause(thisGame);
            break;
    }
}

void uiProcessInputClick(GameFieldStruct *thisGame, int key, int x, int y) {
    switch (thisGame->gameState) {
        case GAME_STATE_PLAY:

            break;
        case GAME_STATE_PAUSE:
            menuProcessPauseMenuItemClick(thisGame, key, x, y);
            break;
    }
}

void uiProcessMouseMove(GameFieldStruct *thisGame, int x, int y) {
    switch (thisGame->gameState) {
        case GAME_STATE_PLAY:


            break;
        case GAME_STATE_PAUSE:
            menuProcessPauseMenuItemFocus(thisGame, x, y);
            break;
    }
}