//
// Created by wiskiw on 03.12.17.
//

#include "UI.h"
#include "../utils/Utils.h"
#include "dialog/Dialog.h"

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

void (*uiItemSelectListener)(GameState, int) = nullptr;

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


void uiInit(GameFieldStruct *thisGame, void(*callback)(GameState, int)) {
    interfaceBorders = thisGame->interfaceBorders;
    uiItemSelectListener = callback;
}

void uiUpdate(GameFieldStruct *thisGame) {
    GameState state = thisGame->gameState;

    if (state == GAME_STATE_PLAY || state == GAME_STATE_PAUSE_MENU) {
        drawHealth(thisGame);
        drawGunReload(thisGame);
        drawGameBorder(thisGame);
        drawInterfaceBackground(thisGame);
    }

    switch (thisGame->gameState) {
        case GAME_STATE_PLAY:

            break;
        case GAME_STATE_MAIN_MENU:
            dialogDrawMainMenu(thisGame);
            break;
        case GAME_STATE_PAUSE_MENU:
            dialogDrawPauseMenu(thisGame);
            break;
        case GAME_STATE_RECORD_LIST:
            dialogDrawRecordList(thisGame);
            break;
        case GAME_STATE_ADD_NEW_RECORD:
            dialogDrawRecordListAddNew(thisGame);
            break;
    }
}

void uiProcessInput(GameFieldStruct *thisGame, int key, int x, int y, bool special) {
    const GameState state = thisGame->gameState;
    int select = -1;
    switch (state) {
        case GAME_STATE_PLAY:
            if (key == PREF_IO_KEY_BACK) {
                thisGame->gameState = GAME_STATE_PAUSE_MENU;
            }
            break;
        case GAME_STATE_MAIN_MENU:
            if (key == PREF_IO_KEY_ENTER) {
                select = 2;
            } else {
                select = dialogProcessMainMenuRowClick(thisGame, key, x, y);
            }
            break;
        case GAME_STATE_PAUSE_MENU:
            if (key == PREF_IO_KEY_BACK || key == PREF_IO_KEY_ENTER) {
                select = 1;
            } else {
                select = dialogProcessPauseMenuRowClick(thisGame, key, x, y);
            }
            break;
        case GAME_STATE_RECORD_LIST:
            if (key == PREF_IO_KEY_BACK) {
                select = 0;
            } else {
                select = dialogProcessRecordListBottomButtonClick(thisGame, key, x, y);
            }
            break;
        case GAME_STATE_ADD_NEW_RECORD:
            if (key == PREF_IO_KEY_BACK || key == PREF_IO_KEY_ENTER) {
                select = 0;
            } else {
                select = dialogProcessRecordListAddNewInput(thisGame, key, x, y, special);
            }
            break;
    }

    if (select != -1 && uiItemSelectListener != nullptr) {
        uiItemSelectListener(state, select);
    }
}

void uiProcessMouseMove(GameFieldStruct *thisGame, int x, int y) {
    switch (thisGame->gameState) {
        case GAME_STATE_PLAY:

            break;
        case GAME_STATE_MAIN_MENU:
            dialogProcessMainMenuRowFocus(thisGame, x, y);
            break;
        case GAME_STATE_PAUSE_MENU:
            dialogProcessPauseMenuRowFocus(thisGame, x, y);
            break;
        case GAME_STATE_RECORD_LIST:
        case GAME_STATE_ADD_NEW_RECORD:
            dialogProcessRecordListBottomButtonFocus(thisGame, x, y);
            break;
    }
}