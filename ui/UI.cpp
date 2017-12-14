//
// Created by wiskiw on 03.12.17.
//

#include <iostream>
#include <cstring>
#include "UI.h"
#include "../utils/Utils.h"
#include "dialog/Dialog.h"
#include "../resources/MusicManager.h"

float elementSize = 15;
const float MIN_ELEMENT_DIVINER = 4;
float divinerX = 10;
float divinerY = 10;
int maxElementPos = 0;

void *CELLS_NAME_FONT = GLUT_BITMAP_HELVETICA_12;
const float CELLS_NAME_FONT_HEIGHT = 12 / PREF_SCREEN_CROP_FACTOR;
SW_Color CELLS_NAME_TEXT_COLOR = {255, 255, 255};


const SW_Color HEALTH_BAR_COLOR = {255, 0, 0};
char HEALTH_BAR_NAME[] = "Health";


const SW_Color PRE_RECORD_BAR_COLOR = {255, 0, 255};

char SCORE_CELL_NAME[] = "Score";


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

void drawElementBorders(SW_Color color, SW_Borders drawBorders) {
    utilsDrawBorders(drawBorders, color, 2, PREF_UI_Z_POS + 0.2f);
}

float getCellNameHeight() {
    return CELLS_NAME_FONT_HEIGHT + (divinerY + MIN_ELEMENT_DIVINER) / 2;
}

void drawCellText(SW_Borders borders, const char *string) {
    SW_Pos textPos;
    textPos.x = borders.leftBottomX;
    textPos.y = borders.rightTopY - CELLS_NAME_FONT_HEIGHT;
    textPos.z = PREF_UI_Z_POS;
    utilsDrawText(textPos, CELLS_NAME_TEXT_COLOR, CELLS_NAME_FONT, string);
}

void drawBar(float maxValue, float currentValue, SW_Color color, SW_Borders borders) {
    float percent = currentValue * 100 / maxValue;
    percent = percent < 0 ? 0 : percent;
    percent = percent > 100 ? 100 : percent;
    float xPX = (borders.rightTopX - borders.leftBottomX) * percent / 100;
    borders.rightTopY -= getCellNameHeight(); // для названия

    SW_Color colorBright = color;
    colorBright.A = 255;

    SW_Color colorDark = color;
    colorDark.A = 200;

    SW_Color colorEmptyBright = color;
    colorEmptyBright.A = 160;

    SW_Color colorEmptyDark = color;
    colorEmptyDark.A = 120;

    SW_Color colorBorders = color;
    colorBorders.A = 150;

    //utilsConcatColors(&colorDark, -55, -55, -55, 0);
    //utilsConcatColors(&colorEmptyBright, -90, -90, -90, 0);
    //utilsConcatColors(&colorEmptyDark, -120, -120, -120, 0);
    //utilsConcatColors(&colorEmptyDark, 20, 20, 20, 0);
    //utilsConcatColors(&colorBorders, -140, -140, -140, 0);


    glPushMatrix();

    glBegin(GL_POLYGON);
    utilsSelectColor(colorDark);
    glVertex3f(borders.leftBottomX, borders.leftBottomY, PREF_UI_Z_POS);

    utilsSelectColor(colorBright);
    glVertex3f(borders.leftBottomX, borders.rightTopY, PREF_UI_Z_POS);
    glVertex3f(borders.leftBottomX + xPX, borders.rightTopY, PREF_UI_Z_POS);

    utilsSelectColor(colorDark);
    glVertex3f(borders.leftBottomX + xPX, borders.leftBottomY, PREF_UI_Z_POS);
    glEnd();


    glBegin(GL_POLYGON);
    utilsSelectColor(colorEmptyDark);
    glVertex3f(borders.leftBottomX + xPX, borders.leftBottomY, PREF_UI_Z_POS);

    utilsSelectColor(colorEmptyBright);
    glVertex3f(borders.leftBottomX + xPX, borders.rightTopY, PREF_UI_Z_POS);
    glVertex3f(borders.rightTopX, borders.rightTopY, PREF_UI_Z_POS);

    utilsSelectColor(colorEmptyDark);
    glVertex3f(borders.rightTopX, borders.leftBottomY, PREF_UI_Z_POS);
    glEnd();

    drawElementBorders(colorBorders, borders);

    glPopMatrix();

}

void drawHealth(GameFieldStruct *thisGame) {
    SW_Borders drawBorders = getDrawBorders(1, 5);
    drawBar(PREF_PLAYER_DEFAULT_HEALTH, thisGame->player.health, HEALTH_BAR_COLOR, drawBorders);
    drawCellText(drawBorders, HEALTH_BAR_NAME);
}

std::string getPrettyStringInt(int val) {
    std::string str = std::to_string(val);
    switch (val) {
        case 1:
            str += "st";
            break;
        case 2:
            str += "nd";
            break;
        case 3:
            str += "rd";
            break;
        default:
            str += "th";
            break;
    }
    return str;
}

void drawNextRecordBar(GameFieldStruct *thisGame) {
    int nextPlaceInTableIndex;
    const int thisGameScore = thisGame->score;
    int nextScore = 0;
    for (nextPlaceInTableIndex = PREF_RECORD_LIST_SIZE - 1;
         nextPlaceInTableIndex >= 0; nextPlaceInTableIndex--) {
        SW_Record record = thisGame->recordList[nextPlaceInTableIndex];
        if (record.type != RECORD_TYPE_UNDEFINED && thisGameScore <= record.score) {
            nextScore = record.score;
            break;
        } else if (nextPlaceInTableIndex == 0 && thisGameScore > record.score) {
            // absolute record
            nextPlaceInTableIndex = -1;
            break;
        }
    }


    SW_Borders drawBorders = getDrawBorders(6, 5);
    std::string recordBarNameBuffer;
    if (nextPlaceInTableIndex == -1) {
        recordBarNameBuffer = "INCREDIBLE PLAYER!!1";
    } else {
        recordBarNameBuffer = "Until " + getPrettyStringInt(nextPlaceInTableIndex + 1) + " place";
    }
    drawCellText(drawBorders, recordBarNameBuffer.c_str());

    if (nextPlaceInTableIndex != -1 && thisGameScore <= nextScore) {
        int scoreVal = 0;
        int maxScoreVal = 0;

        // nextPlaceInTableIndex + 1 - текущий позиция в рекордах(индекс в массиве)
        if (nextPlaceInTableIndex + 1 >= PREF_RECORD_LIST_SIZE ||
            thisGame->recordList[nextPlaceInTableIndex + 1].type == RECORD_TYPE_UNDEFINED) {
            // до последнего места
            maxScoreVal = nextScore;
            scoreVal = thisGameScore;
        } else {
            int currentTablePosScore = thisGame->recordList[nextPlaceInTableIndex + 1].score;
            maxScoreVal = nextScore - currentTablePosScore;
            scoreVal = thisGameScore - currentTablePosScore;
        }

        drawBar(maxScoreVal, scoreVal, PRE_RECORD_BAR_COLOR, drawBorders);
    } else {
        drawBar(1, 1, PRE_RECORD_BAR_COLOR, drawBorders);
    }

    if (nextPlaceInTableIndex < PREF_RECORD_LIST_SIZE - 1) {
        // record in table
        void *FONT = GLUT_BITMAP_HELVETICA_18;
        const float FONT_HEIGHT = 18 / PREF_SCREEN_CROP_FACTOR;
        std::string barTextBuffer;

        SW_Color TEXT_COLOR;
        if (nextPlaceInTableIndex == -1) {
            barTextBuffer = "ABSOLUTE WINNER!";
            TEXT_COLOR = {255, 255, 255};
        } else {
            barTextBuffer = getPrettyStringInt(nextPlaceInTableIndex + 2) + " place";
            TEXT_COLOR = {255, 255, 255, 125};
        }

        SW_Pos scoreTextPos;
        float textWidth = 0;
        for (unsigned int i = 0; i < barTextBuffer.length(); i++)
            textWidth += glutBitmapWidth(FONT, barTextBuffer[i]);
        textWidth = textWidth / PREF_SCREEN_CROP_FACTOR;


        drawBorders.rightTopY -= getCellNameHeight();
        const float elementWidth = drawBorders.rightTopX - drawBorders.leftBottomX;
        scoreTextPos.x = drawBorders.leftBottomX + (elementWidth - textWidth) / 2;
        scoreTextPos.y = drawBorders.leftBottomY +
                         ((drawBorders.rightTopY - drawBorders.leftBottomY) -
                          FONT_HEIGHT / 2) / 2;
        scoreTextPos.z = PREF_UI_Z_POS + 0.01f;
        utilsDrawText(scoreTextPos, TEXT_COLOR, FONT, barTextBuffer.c_str());
    }
}

void drawScore(GameFieldStruct *thisGame) {
    const int CELL_SIZE = 2;
    void *FONT = GLUT_BITMAP_HELVETICA_18;
    const float FONT_HEIGHT = 18 / PREF_SCREEN_CROP_FACTOR;
    SW_Color COLOR = {255, 255, 255};

    SW_Borders borders = getDrawBorders(maxElementPos - CELL_SIZE, CELL_SIZE);
    drawCellText(borders, SCORE_CELL_NAME);

    char scoreStr[16] = "";
    sprintf(scoreStr, "%d", thisGame->score);

    SW_Pos scoreTextPos;

    float textWidth = 0;
    const size_t len = strlen(scoreStr);
    for (unsigned int i = 0; i < len; i++)
        textWidth += glutBitmapWidth(FONT, scoreStr[i]);
    textWidth = textWidth / PREF_SCREEN_CROP_FACTOR;

    const float elementWidth = elementSize * CELL_SIZE + divinerX * (CELL_SIZE - 1);
    borders.rightTopY -= getCellNameHeight();
    scoreTextPos.x = borders.leftBottomX + (elementWidth - textWidth) / 2;
    scoreTextPos.y = borders.leftBottomY +
                     ((borders.rightTopY - borders.leftBottomY) - FONT_HEIGHT / 2) / 2;
    scoreTextPos.z = PREF_UI_Z_POS + 0.01f;
    utilsDrawText(scoreTextPos, COLOR, FONT, scoreStr);
    COLOR.A = 150;
    drawElementBorders(COLOR, borders);
}

void drawInterfaceBorder(GameFieldStruct *thisGame) {
    utilsDrawBorders(thisGame->interfaceBorders, GAME_BORDER_LINE_COLOR, 2, PREF_UI_Z_POS + 0.5f);
}

void drawInterfaceBackground(GameFieldStruct *thisGame) {
    glPushMatrix();
    glBegin(GL_POLYGON);
    utilsSelectColor(UI_BACKGROUND_COLOR);
    glVertex3f(interfaceBorders.leftBottomX, interfaceBorders.leftBottomY, PREF_UI_Z_POS - 0.01f);
    glVertex3f(interfaceBorders.leftBottomX, interfaceBorders.rightTopY, PREF_UI_Z_POS - 0.01f);
    glVertex3f(interfaceBorders.rightTopX, interfaceBorders.rightTopY, PREF_UI_Z_POS - 0.01f);
    glVertex3f(interfaceBorders.rightTopX, interfaceBorders.leftBottomY, PREF_UI_Z_POS - 0.01f);
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
        drawInterfaceBorder(thisGame);
        drawInterfaceBackground(thisGame);
        drawHealth(thisGame);
        drawNextRecordBar(thisGame);
        drawScore(thisGame);
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
                mscPauseCurrentMusic();
                mscPlayMenuMusic(true, RM_MUSIC_VOLUME_LOW);
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