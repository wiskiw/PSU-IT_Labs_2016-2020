//
// Created by wiskiw on 03.12.17.
//

#include <iostream>
#include <cstring>
#include "UI.h"
#include "../utils/Utils.h"
#include "dialog/Dialog.h"

float elementSize = 15;
const float MIN_ELEMENT_DIVINER = 4;
float divinerX = 10;
float divinerY = 10;
int maxElementPos = 0;

float const UI_Z = 15;

const SW_Color HEALTH_BAR_COLOR = {255, 0, 0};
const SW_Color RELOAD_BAR_COLOR = {255, 0, 255};


const SW_Color GAME_BORDER_LINE_COLOR = {100, 100, 100};
const SW_Color UI_BACKGROUND_COLOR = {50, 50, 50};


SW_Borders interfaceBorders;

void (*uiItemSelectListener)(GameState, int) = nullptr;

void setUpElementSizeAndDiviners() {
    // первоначальный просчёт пэдингов и размеров одного элемента
    float elementsWidthSum = MIN_ELEMENT_DIVINER;
    elementSize = (interfaceBorders.rightTopY - interfaceBorders.leftBottomY) - MIN_ELEMENT_DIVINER * 2;
    const float interfaceBordersWidth = interfaceBorders.rightTopX - interfaceBorders.leftBottomX;
    maxElementPos = 0;
    for (; elementsWidthSum < interfaceBordersWidth; ++maxElementPos) {
        elementsWidthSum += MIN_ELEMENT_DIVINER + elementSize;
    }
    elementsWidthSum -= MIN_ELEMENT_DIVINER + elementSize;

    divinerX = MIN_ELEMENT_DIVINER + (interfaceBordersWidth - (elementsWidthSum)) / (maxElementPos);
    divinerY = MIN_ELEMENT_DIVINER;
}

SW_Borders getDrawBorders(int cellPos, int cellSize) {
    SW_Borders drawBorders;
    drawBorders.leftBottomY = divinerY + interfaceBorders.leftBottomY;
    drawBorders.leftBottomX = divinerX + (divinerX + elementSize) * (cellPos - 1) + interfaceBorders.leftBottomX;
    drawBorders.rightTopY = drawBorders.leftBottomY + elementSize;
    drawBorders.rightTopX = drawBorders.leftBottomX + elementSize + (cellSize - 1) * (elementSize + divinerX);
    return drawBorders;
}

void drawBorders(SW_Color color, SW_Borders drawBorders) {
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    utilsSelectColor(color);
    glVertex3f(drawBorders.leftBottomX, drawBorders.leftBottomY, UI_Z + 0.01f);
    glVertex3f(drawBorders.leftBottomX, drawBorders.rightTopY, UI_Z + 0.01f);
    glVertex3f(drawBorders.rightTopX, drawBorders.rightTopY, UI_Z + 0.01f);
    glVertex3f(drawBorders.rightTopX, drawBorders.leftBottomY, UI_Z + 0.01f);
    glEnd();
    glLineWidth(1);
}

void drawBar(float maxValue, float currentValue, SW_Color color, SW_Borders borders) {
    float percent = currentValue * 100 / maxValue;
    percent = percent < 0 ? 0 : percent;
    percent = percent > 100 ? 100 : percent;
    float xPX = (borders.rightTopX - borders.leftBottomX) * percent / 100;

    glPushMatrix();

    glBegin(GL_POLYGON);
    color.A = 200;
    utilsSelectColor(color);
    glVertex3f(borders.leftBottomX, borders.leftBottomY, UI_Z);

    color.A = 255;
    utilsSelectColor(color);
    glVertex3f(borders.leftBottomX, borders.rightTopY, UI_Z);
    glVertex3f(borders.leftBottomX + xPX, borders.rightTopY, UI_Z);

    color.A = 200;
    utilsSelectColor(color);
    glVertex3f(borders.leftBottomX + xPX, borders.leftBottomY, UI_Z);
    glEnd();


    glBegin(GL_POLYGON);
    color.A = 120;
    utilsSelectColor(color);
    glVertex3f(borders.leftBottomX + xPX, borders.leftBottomY, UI_Z);

    color.A = 160;
    utilsSelectColor(color);
    glVertex3f(borders.leftBottomX + xPX, borders.rightTopY, UI_Z);

    color.A = 120;
    utilsSelectColor(color);
    glVertex3f(borders.rightTopX, borders.rightTopY, UI_Z);
    glVertex3f(borders.rightTopX, borders.leftBottomY, UI_Z);
    glEnd();

    color.A = 150;
    drawBorders(color, borders);

    glPopMatrix();

}

void drawHealth(GameFieldStruct *thisGame) {
    SW_Borders drawBorders = getDrawBorders(1, 5);
    drawBar(PREF_PLAYER_DEFAULT_HEALTH, thisGame->player.health, HEALTH_BAR_COLOR, drawBorders);
}

void drawGunReload(GameFieldStruct *thisGame) {
    SW_Borders drawBorders = getDrawBorders(6, 5);
    float maxValue = thisGame->player.gun.gunSpeed;
    drawBar(maxValue, maxValue - thisGame->player.gun.waitBeforeShoot, RELOAD_BAR_COLOR, drawBorders);
}

void drawScore(GameFieldStruct *thisGame) {
    const int CELL_SIZE = 2;
    void *FONT = GLUT_BITMAP_HELVETICA_18;
    const int FONT_HEIGHT = 18;
    SW_Color COLOR = {255, 255, 255};

    SW_Borders borders = getDrawBorders(maxElementPos - CELL_SIZE, CELL_SIZE);

    char scoreStr[16] = "";
    sprintf(scoreStr, "%d", thisGame->score);

    SW_Pos scoreTextPos;

    float textWidth = 0;
    const size_t len = strlen(scoreStr);
    for (unsigned int i = 0; i < len; i++)
        textWidth += glutBitmapWidth(FONT, scoreStr[i]);
    textWidth = textWidth / PREF_SCREEN_CROP_FACTOR;

    const float elementWidth = elementSize * CELL_SIZE + divinerX * (CELL_SIZE - 1);
    scoreTextPos.x = borders.leftBottomX + (elementWidth - textWidth) / 2;
    scoreTextPos.y = borders.leftBottomY +
                     ((borders.rightTopY - borders.leftBottomY) - FONT_HEIGHT / PREF_SCREEN_CROP_FACTOR / 2) / 2;
    scoreTextPos.z = UI_Z + 0.01f;
    utilsDrawText(scoreTextPos, COLOR, FONT, scoreStr);
    COLOR.A = 150;
    drawBorders(COLOR, borders);
}

void drawInterfaceBorder(GameFieldStruct *thisGame) {
    utilsDrawBorders(thisGame->interfaceBorders, GAME_BORDER_LINE_COLOR, 4);
}

void drawInterfaceBackground(GameFieldStruct *thisGame) {
    glPushMatrix();
    glBegin(GL_POLYGON);
    utilsSelectColor(UI_BACKGROUND_COLOR);
    glVertex3f(interfaceBorders.leftBottomX, interfaceBorders.leftBottomY, UI_Z - 0.01f);
    glVertex3f(interfaceBorders.leftBottomX, interfaceBorders.rightTopY, UI_Z - 0.01f);
    glVertex3f(interfaceBorders.rightTopX, interfaceBorders.rightTopY, UI_Z - 0.01f);
    glVertex3f(interfaceBorders.rightTopX, interfaceBorders.leftBottomY, UI_Z - 0.01f);
    glEnd();
    glPopMatrix();
}

void uiInit(GameFieldStruct *thisGame, void(*callback)(GameState, int)) {
    interfaceBorders = thisGame->interfaceBorders;
    uiItemSelectListener = callback;
    setUpElementSizeAndDiviners();
}

void uiUpdate(GameFieldStruct *thisGame) {
    GameState state = thisGame->gameState;

    if (state == GAME_STATE_PLAY || state == GAME_STATE_PAUSE_MENU) {
        drawHealth(thisGame);
        drawGunReload(thisGame);
        drawScore(thisGame);
        drawInterfaceBorder(thisGame);
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
        case GAME_STATE_GAME_OVER_SCREEN:
            dialogDrawGameOver(thisGame);
            break;
        case GAME_STATE_GAME_OVER_NEW_RECORD_SCREEN:
            dialogDrawGameOverNewRecord(thisGame);
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
        case GAME_STATE_GAME_OVER_NEW_RECORD_SCREEN:
        case GAME_STATE_GAME_OVER_SCREEN:
            select = dialogProcessAllGameOverInput(thisGame, key, x, y, special);
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