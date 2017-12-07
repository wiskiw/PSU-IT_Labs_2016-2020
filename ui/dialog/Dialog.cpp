//
// Created by wiskiw on 06.12.17.
//

#include <cstring>
#include <iostream>
#include "Dialog.h"
#include "../../utils/Utils.h"
#include "../../io/IOProcessor.h"

const SW_Color DIALOG_BACKGROUND_COLOR = {50, 50, 50};
const SW_Color DIALOG_UNDERDIALOG_BACKGROUND_COLOR = {1, 1, 1, 100};

const SW_Color MENU_ITEM_TEXT_COLOR_NORMAL = {255, 255, 255};
const SW_Color MENU_ITEM_BACKGROUND_COLOR_NORMAL = {25, 25, 25};

const SW_Color MENU_ITEM_TEXT_COLOR_FOCUS = {1, 255, 255};
const SW_Color MENU_ITEM_BACKGROUND_COLOR_FOCUS = {35, 35, 35};

const SW_Color MENU_ITEM_TEXT_COLOR_PRESSED = {1, 255, 255};
const SW_Color MENU_ITEM_BACKGROUND_COLOR_PRESSED = {25, 25, 25};

const SW_Color MENU_ITEM_TEXT_COLOR_DISABLE = {1, 255, 255};
const SW_Color MENU_ITEM_BACKGROUND_COLOR_DISABLE = {25, 25, 25};


const SW_Color RECORD_LIST_ROW_TEXT_COLOR_NORMAL = {255, 255, 255};
const SW_Color RECORD_LIST_ROW_BACKGROUND_COLOR_NORMAL = {25, 25, 25};


const float DIVINER_X = 5;
const float DIVINER_Y = 5;
const float MENU_ITEM_WIDTH = 150;
const float MENU_ITEM_HEIGHT = 25;
const float DIALOG_Z_POS = 15;

void *MENU_ITEM_FONT = GLUT_BITMAP_HELVETICA_18;
const float MENU_ITEM_FONT_CHAR_HEIGHT = 18 / PREF_SCREEN_CROP_FACTOR;


enum DialogButtonState {
    DIALOG_BUTTON_STATE_NORMAL, DIALOG_BUTTON_STATE_FOCUS,
    DIALOG_BUTTON_STATE_PRESSED, DIALOG_BUTTON_STATE_DISABLE
};

struct DialogButton {
    int pos = 1;
    char label[255] = "set label!";
    DialogButtonState state = DIALOG_BUTTON_STATE_NORMAL;
};

struct GAME_Menu {
    const static int itemBufferSize = 10;
    DialogButton items[itemBufferSize];
    int itemsNumber = 0;

};

GAME_Menu mainMenu;
GAME_Menu pauseMenu;


float getStringWidthPX(char *s) {
    int width = 0;
    const size_t len = strlen(s);
    for (unsigned int i = 0; i < len; i++)
        width += glutBitmapWidth(MENU_ITEM_FONT, s[i]);
    return width / PREF_SCREEN_CROP_FACTOR;
}

void colorUnderdialogBackground(GameFieldStruct *thisGame) {
    float x = thisGame->windowX / PREF_SCREEN_CROP_FACTOR;
    float y = thisGame->windowY / PREF_SCREEN_CROP_FACTOR;
    glPushMatrix();
    glTranslatef(0, 0, DIALOG_Z_POS - 0.05f);
    glBegin(GL_POLYGON);
    utilsSelectColor(DIALOG_UNDERDIALOG_BACKGROUND_COLOR);
    glVertex2f(0, 0);
    glVertex2f(0, y);
    glVertex2f(x, y);
    glVertex2f(x, 0);
    glEnd();
    glPopMatrix();
}

void drawDialogBackground(SW_Pos backgroundPos, float dialogWidth, float dialogHeight) {
    glPushMatrix();
    glTranslatef(backgroundPos.x, backgroundPos.y, DIALOG_Z_POS);
    glBegin(GL_POLYGON);
    utilsSelectColor(DIALOG_BACKGROUND_COLOR);
    glVertex2f(0, 0);
    glVertex2f(0, dialogHeight);
    glVertex2f(dialogWidth, dialogHeight);
    glVertex2f(dialogWidth, 0);
    glEnd();
    glPopMatrix();
}

SW_Pos getStartDrawingPosition(GameFieldStruct *thisGame, float dialogWidth, float dialogHeight) {
    SW_Pos dialogPos;
    dialogPos.x = thisGame->windowX / 2 / PREF_SCREEN_CROP_FACTOR - (dialogWidth / 2);
    dialogPos.y = thisGame->windowY / 2 / PREF_SCREEN_CROP_FACTOR - (dialogHeight / 2);
    dialogPos.z = DIALOG_Z_POS;
    return dialogPos;
}

SW_Borders getMenuItemBorders(int index, SW_Pos menuBackgroundPos, float itemWidth, float itemHeight) {
    SW_Borders menuItemBorders;
    menuItemBorders.leftBottomX = menuBackgroundPos.x + DIVINER_X;
    menuItemBorders.leftBottomY = menuBackgroundPos.y + DIVINER_Y + (DIVINER_Y + itemHeight) * index;
    menuItemBorders.rightTopX = menuItemBorders.leftBottomX + itemWidth;
    menuItemBorders.rightTopY = menuItemBorders.leftBottomY + itemHeight;
    return menuItemBorders;
}

SW_Color getMenuItemBackgroundColor(DialogButtonState state) {
    switch (state) {
        case DIALOG_BUTTON_STATE_FOCUS:
            return MENU_ITEM_BACKGROUND_COLOR_FOCUS;
        case DIALOG_BUTTON_STATE_PRESSED:
            return MENU_ITEM_BACKGROUND_COLOR_PRESSED;
        case DIALOG_BUTTON_STATE_DISABLE:
            return MENU_ITEM_BACKGROUND_COLOR_DISABLE;
        default:
            return MENU_ITEM_BACKGROUND_COLOR_NORMAL;
    }
}

SW_Color getMenuItemTextColor(DialogButtonState state) {
    switch (state) {
        case DIALOG_BUTTON_STATE_FOCUS:
            return MENU_ITEM_TEXT_COLOR_FOCUS;
        case DIALOG_BUTTON_STATE_PRESSED:
            return MENU_ITEM_TEXT_COLOR_PRESSED;
        case DIALOG_BUTTON_STATE_DISABLE:
            return MENU_ITEM_TEXT_COLOR_DISABLE;
        default:
            return MENU_ITEM_TEXT_COLOR_NORMAL;
    }
}

void drawButton(SW_Borders buttonBorders, DialogButton button) {
    SW_Color bgColor = getMenuItemBackgroundColor(button.state);
    SW_Color textColor = getMenuItemTextColor(button.state);

    glPushMatrix();
    glTranslatef(0, 0, DIALOG_Z_POS + 0.01f);
    glBegin(GL_POLYGON);
    utilsSelectColor(bgColor);
    glVertex2f(buttonBorders.leftBottomX, buttonBorders.leftBottomY);
    glVertex2f(buttonBorders.leftBottomX, buttonBorders.rightTopY);
    glVertex2f(buttonBorders.rightTopX, buttonBorders.rightTopY);
    glVertex2f(buttonBorders.rightTopX, buttonBorders.leftBottomY);
    glEnd();
    SW_Pos pos = {buttonBorders.leftBottomX +
                  (buttonBorders.rightTopX - buttonBorders.leftBottomX - getStringWidthPX(button.label)) / 2,
                  buttonBorders.leftBottomY +
                  (buttonBorders.rightTopY - buttonBorders.leftBottomY - MENU_ITEM_FONT_CHAR_HEIGHT) / 2, 0.02f};
    utilsDrawText(pos, textColor, MENU_ITEM_FONT, button.label);
    glPopMatrix();
}

bool isInButton(GameFieldStruct *thisGame, SW_Borders buttonBorders, int x, int y) {
    // * 1.0f - конвертация к float, иначе компилятор выдаёт предупреждение
    SW_Pos mousePos = {x * 1.0f, y * 1.0f};
    utilsConvertToGameWindowPosition(thisGame, &mousePos);
    return utilsIsPosInBorders(mousePos, buttonBorders);
}


int getMenuRowUnderMouse(GameFieldStruct *thisGame, GAME_Menu menu, int x, int y) {
    // * 1.0f - конвертация к float, иначе компилятор выдаёт предупреждение
    SW_Pos mousePos = {x * 1.0f, y * 1.0f};

    utilsConvertToGameWindowPosition(thisGame, &mousePos);

    const float menuBackgroundWidth = MENU_ITEM_WIDTH + 2 * DIVINER_X;
    const float menuBackgroundHeight = (MENU_ITEM_HEIGHT + DIVINER_Y) * menu.itemsNumber + DIVINER_Y;

    SW_Pos menuBackgroundPox = getStartDrawingPosition(thisGame, menuBackgroundWidth, menuBackgroundHeight);

    for (int i = 0; i < menu.itemsNumber; ++i) {
        SW_Borders menuItemBorders = getMenuItemBorders(i, menuBackgroundPox, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);

        if (utilsIsPosInBorders(mousePos, menuItemBorders)) {
            return i;
        }
    }
    return -1;
}

void menuUpdateMenuItemState(GameFieldStruct *thisGame, GAME_Menu *menu, DialogButtonState state, int x, int y) {
    const int menuItem = getMenuRowUnderMouse(thisGame, *menu, x, y);
    if (menuItem != -1) {
        menu->items[menuItem].state = state;
    } else {
        for (int i = 0; i < menu->itemsNumber; ++i) {
            menu->items[i].state = DIALOG_BUTTON_STATE_NORMAL;
        }
    }
}

void drawMenu(GameFieldStruct *thisGame, GAME_Menu menu) {
    colorUnderdialogBackground(thisGame);

    const float menuBackgroundWidth = MENU_ITEM_WIDTH + 2 * DIVINER_X;
    const float menuBackgroundHeight = (MENU_ITEM_HEIGHT + DIVINER_Y) * menu.itemsNumber + DIVINER_Y;

    SW_Pos menuBackgroundPos = getStartDrawingPosition(thisGame, menuBackgroundWidth, menuBackgroundHeight);

    glPushMatrix();
    glTranslatef(menuBackgroundPos.x, menuBackgroundPos.y, DIALOG_Z_POS);
    glBegin(GL_POLYGON);
    utilsSelectColor(DIALOG_BACKGROUND_COLOR);
    glVertex2f(0, 0);
    glVertex2f(0, menuBackgroundHeight);
    glVertex2f(menuBackgroundWidth, menuBackgroundHeight);
    glVertex2f(menuBackgroundWidth, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, DIALOG_Z_POS + 0.01f);
    for (int i = 0; i < menu.itemsNumber; ++i) {
        SW_Borders menuItemBorders = getMenuItemBorders(i, menuBackgroundPos, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);

        DialogButtonState state = menu.items[i].state;
        SW_Color bgColor = getMenuItemBackgroundColor(state);
        SW_Color textColor = getMenuItemTextColor(state);


        char *menuItemLabel = menu.items[i].label;
        SW_Pos pos = {menuItemBorders.leftBottomX + (MENU_ITEM_WIDTH - getStringWidthPX(menuItemLabel)) / 2,
                      menuItemBorders.leftBottomY + (MENU_ITEM_HEIGHT - MENU_ITEM_FONT_CHAR_HEIGHT) / 2,
                      DIALOG_Z_POS + 0.02f};
        utilsDrawText(pos, textColor, MENU_ITEM_FONT, menuItemLabel);

        utilsSelectColor(bgColor);
        glBegin(GL_POLYGON);
        glVertex2f(menuItemBorders.leftBottomX, menuItemBorders.leftBottomY);
        glVertex2f(menuItemBorders.leftBottomX, menuItemBorders.rightTopY);
        glVertex2f(menuItemBorders.rightTopX, menuItemBorders.rightTopY);
        glVertex2f(menuItemBorders.rightTopX, menuItemBorders.leftBottomY);
        glEnd();
    }
    glPopMatrix();
}
// ========================================================



// ==== Pause Menu ====
void dialogDrawPauseMenu(GameFieldStruct *thisGame) {
    pauseMenu.itemsNumber = 2;
    strncpy(pauseMenu.items[1].label, "Continue", 9);
    strncpy(pauseMenu.items[0].label, "Main Menu", 10);
    drawMenu(thisGame, pauseMenu);
}

int dialogProcessPauseMenuRowClick(GameFieldStruct *thisGame, int key, int x, int y) {
    if (key != IO_MOUSE_LEFT_BUTTON) {
        return -1;
    }

    int row = getMenuRowUnderMouse(thisGame, pauseMenu, x, y);
    if (row != -1) {
        pauseMenu.items[row].state = DIALOG_BUTTON_STATE_NORMAL;
    }
    return row;
}

void dialogProcessPauseMenuRowFocus(GameFieldStruct *thisGame, int x, int y) {
    menuUpdateMenuItemState(thisGame, &pauseMenu, DIALOG_BUTTON_STATE_FOCUS, x, y);
}
// ====================


// ==== Main Menu ====
void dialogDrawMainMenu(GameFieldStruct *thisGame) {
    mainMenu.itemsNumber = 3;
    strncpy(mainMenu.items[2].label, "Play", 5);
    strncpy(mainMenu.items[1].label, "Records", 8);
    strncpy(mainMenu.items[0].label, "Exit", 5);
    drawMenu(thisGame, mainMenu);
}

int dialogProcessMainMenuRowClick(GameFieldStruct *thisGame, int key, int x, int y) {
    if (key != IO_MOUSE_LEFT_BUTTON) {
        return -1;
    }
    int row = getMenuRowUnderMouse(thisGame, mainMenu, x, y);
    if (row != -1) {
        mainMenu.items[row].state = DIALOG_BUTTON_STATE_NORMAL;
    }
    return row;
}

void dialogProcessMainMenuRowFocus(GameFieldStruct *thisGame, int x, int y) {
    menuUpdateMenuItemState(thisGame, &mainMenu, DIALOG_BUTTON_STATE_FOCUS, x, y);
}
// ====================


// ==== Records ====
const int UNDER_RECORDS_BUTTON_ROW_INDEX = 0;
DialogButton underRecordsButton;

// настройки таблицы
const float RECORD_LIST_ROW_ITEMS_X_DIVINER = 2.5f; // расстояние между элементами строки
const int P_SIZE = 3; // кол-во элементов строки
const int RECORD_LIST_ROW_ITEMS_NAME_INDEX = 1; // индекс элемента в строке с именем
const int RECORD_LIST_ROW_ITEMS_P[P_SIZE] = {10, 60, 30}; // процентное соотношение размеров элементов строки

const float RECORD_LIST_ROW_HEIGHT = MENU_ITEM_HEIGHT; // высота строки
const float RECORD_LIST_ROW_WIDTH = MENU_ITEM_WIDTH * 2; // ширина строки

const float RECORD_LIST_BACKGROUND_HEIGHT = (RECORD_LIST_ROW_HEIGHT + DIVINER_Y) *
                                            (PREF_RECORD_LIST_SIZE + 1) +
                                            DIVINER_Y; // PREF_RECORD_LIST_SIZE + 1 - для кнопки назад
const float RECORD_LIST_BACKGROUND_WIDTH = RECORD_LIST_ROW_WIDTH + DIVINER_X * 2;

bool isPointerVisible = true; // состояние курсора

SW_Borders getRecordListRowItemBorders(SW_Borders recordListRowBorders, int rowItemIndex) {
    // rowItemIndex - индекс элемента в строке (индекс столбца)
    // rowItemIndex - границы строки

    // вычисление координат элемента строки
    SW_Borders itemBorders = recordListRowBorders;

    for (int k = 0; k < rowItemIndex; ++k) {
        itemBorders.leftBottomX += (RECORD_LIST_ROW_WIDTH * RECORD_LIST_ROW_ITEMS_P[k] / 100)
                                   + RECORD_LIST_ROW_ITEMS_X_DIVINER / 2;
    }

    for (int k = P_SIZE - 1; k > rowItemIndex; k--) {
        itemBorders.rightTopX -= (RECORD_LIST_ROW_WIDTH * RECORD_LIST_ROW_ITEMS_P[k] / 100)
                                 + RECORD_LIST_ROW_ITEMS_X_DIVINER / 2;
    }
    return itemBorders;
    // -----------------------
}

void drawRecordList(GameFieldStruct *thisGame, SW_Pos backgroundPos) {
    // Отрисовка таблицы
    glPushMatrix();
    glTranslatef(0, 0, DIALOG_Z_POS + 0.01f);
    for (int recordRowIndex = 0; recordRowIndex < PREF_RECORD_LIST_SIZE; ++recordRowIndex) {
        SW_Record record = thisGame->recordList[recordRowIndex];

        // границы строки таблицы
        SW_Borders recordListRowBorders = getMenuItemBorders(PREF_RECORD_LIST_SIZE - recordRowIndex,
                                                             backgroundPos,
                                                             RECORD_LIST_ROW_WIDTH, RECORD_LIST_ROW_HEIGHT);

        // цикл прохода по строке
        for (int rowItemIndex = 0; rowItemIndex < P_SIZE; ++rowItemIndex) {

            // вычисление координат элемента строки
            SW_Borders itemBorders = getRecordListRowItemBorders(recordListRowBorders, rowItemIndex);

            // Отрисовка элемента строки
            char strBuffer[255] = "";
            switch (rowItemIndex) {
                case 0:
                    sprintf(strBuffer, "%d", (recordRowIndex + 1));
                    break;
                case 1:
                    strncpy(strBuffer, record.name, strlen(record.name));
                    break;
                case 2:
                    sprintf(strBuffer, "%d", record.score);
                    break;
            }

            SW_Pos pos = {itemBorders.leftBottomX +
                          ((itemBorders.rightTopX - itemBorders.leftBottomX) - getStringWidthPX(strBuffer)) / 2,
                          recordListRowBorders.leftBottomY +
                          (RECORD_LIST_ROW_HEIGHT - MENU_ITEM_FONT_CHAR_HEIGHT) / 2, 0.02f};
            utilsDrawText(pos, RECORD_LIST_ROW_TEXT_COLOR_NORMAL, MENU_ITEM_FONT, strBuffer);


            glBegin(GL_POLYGON);
            utilsSelectColor(RECORD_LIST_ROW_BACKGROUND_COLOR_NORMAL);
            glVertex2f(itemBorders.leftBottomX, recordListRowBorders.leftBottomY);
            glVertex2f(itemBorders.leftBottomX, recordListRowBorders.rightTopY);
            glVertex2f(itemBorders.rightTopX, recordListRowBorders.rightTopY);
            glVertex2f(itemBorders.rightTopX, recordListRowBorders.leftBottomY);
            glEnd();
        }
    }
    glPopMatrix();
}

void drawRecordsDialog(GameFieldStruct *thisGame, DialogButton bottomButton) {
    // Отрисовка фона окна
    SW_Pos recordBackgroundPos =
            getStartDrawingPosition(thisGame, RECORD_LIST_BACKGROUND_WIDTH, RECORD_LIST_BACKGROUND_HEIGHT);

    drawDialogBackground(recordBackgroundPos, RECORD_LIST_BACKGROUND_WIDTH, RECORD_LIST_BACKGROUND_HEIGHT);

    drawRecordList(thisGame, recordBackgroundPos);

    // границы кнопки назад
    SW_Borders underRecordListButtonBorders =
            getMenuItemBorders(0, recordBackgroundPos, RECORD_LIST_ROW_WIDTH, RECORD_LIST_ROW_HEIGHT);

    drawButton(underRecordListButtonBorders, bottomButton);
}

bool isMouseOnBottomButton(GameFieldStruct *thisGame, int x, int y) {
    SW_Pos recordBackgroundPos =
            getStartDrawingPosition(thisGame, RECORD_LIST_BACKGROUND_WIDTH, RECORD_LIST_BACKGROUND_HEIGHT);
    SW_Borders backButtonBorders = getMenuItemBorders(UNDER_RECORDS_BUTTON_ROW_INDEX, recordBackgroundPos,
                                                      RECORD_LIST_ROW_WIDTH, RECORD_LIST_ROW_HEIGHT);
    return isInButton(thisGame, backButtonBorders, x, y);
}

void dialogProcessRecordListBottomButtonFocus(GameFieldStruct *thisGame, int x, int y) {
    if (isMouseOnBottomButton(thisGame, x, y)) {
        underRecordsButton.state = DIALOG_BUTTON_STATE_FOCUS;
    } else {
        underRecordsButton.state = DIALOG_BUTTON_STATE_NORMAL;
    }
}

// --- RECORD LIST ---

void dialogDrawRecordList(GameFieldStruct *thisGame) {
    strncpy(underRecordsButton.label, "Back", 5);
    underRecordsButton.pos = UNDER_RECORDS_BUTTON_ROW_INDEX;
    drawRecordsDialog(thisGame, underRecordsButton);
}

int dialogProcessRecordListBottomButtonClick(GameFieldStruct *thisGame, int key, int x, int y) {
    if (key == IO_MOUSE_LEFT_BUTTON && isMouseOnBottomButton(thisGame, x, y)) {
        underRecordsButton.state = DIALOG_BUTTON_STATE_NORMAL;
        return UNDER_RECORDS_BUTTON_ROW_INDEX;
    } else {
        return -1;
    }
}


// --- ADDING NEW RECORD ---

void dialogDrawRecordListAddNew(GameFieldStruct *thisGame) {
    strncpy(underRecordsButton.label, "Save", 5);
    underRecordsButton.pos = UNDER_RECORDS_BUTTON_ROW_INDEX;

    drawRecordsDialog(thisGame, underRecordsButton);


    const int posInRecordTable = thisGame->positionInRecordTable;
    if (isPointerVisible && posInRecordTable <= PREF_RECORD_LIST_SIZE) {
        char *nameString = thisGame->recordList[posInRecordTable - 1].name;
        const int indexInRecordTable = posInRecordTable - 1;

        // позиция диалога
        SW_Pos recordsBackgroundPos =
                getStartDrawingPosition(thisGame, RECORD_LIST_BACKGROUND_WIDTH, RECORD_LIST_BACKGROUND_HEIGHT);
        drawDialogBackground(recordsBackgroundPos, RECORD_LIST_BACKGROUND_WIDTH, RECORD_LIST_BACKGROUND_HEIGHT);

        // границы строки таблицы
        SW_Borders recordListRowBorders =
                getMenuItemBorders(PREF_RECORD_LIST_SIZE - indexInRecordTable, recordsBackgroundPos,
                                   RECORD_LIST_ROW_WIDTH, RECORD_LIST_ROW_HEIGHT);

        // границы элемента в строке с именем(колонка с именем)
        SW_Borders itemBorders = getRecordListRowItemBorders(recordListRowBorders, RECORD_LIST_ROW_ITEMS_NAME_INDEX);

        glPushMatrix();
        glTranslatef(0, 0, DIALOG_Z_POS + 0.02f);
        SW_Pos pos = {itemBorders.leftBottomX + (itemBorders.rightTopX - itemBorders.leftBottomX) / 2 +
                      getStringWidthPX(nameString) / 2,
                      recordListRowBorders.leftBottomY + (RECORD_LIST_ROW_HEIGHT - MENU_ITEM_FONT_CHAR_HEIGHT) / 2,
                      0.02f};

        utilsDrawText(pos, MENU_ITEM_TEXT_COLOR_NORMAL, MENU_ITEM_FONT, const_cast<char *>("_"));
        glPopMatrix();
    }

    // Обновление состояния курсора
    if (thisGame->globalTickTimer % PREF_POINTER_BLINK_TICKS == 0) {
        isPointerVisible = isPointerVisible ? false : true;
    }
}

int dialogProcessRecordListAddNewInput(GameFieldStruct *thisGame, int key, int x, int y, bool special) {
    // ввод с клавиатуры
    if (!special) {
        const int posIntRecordTable = thisGame->positionInRecordTable;
        char *nameBuffer = thisGame->recordList[posIntRecordTable - 1].name;

        // http://www.asciitable.com/
        if (strlen(nameBuffer) < PREF_RECORD_LIST_MAX_NAME_LENGTH &&
            ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')
             || (key >= '0' && key <= '9') || (key >= '!' && key <= '/'))) {

            nameBuffer[strlen(nameBuffer)] = static_cast<char>(key);
            nameBuffer[strlen(nameBuffer)] = '\0';
        } else if (key == PREF_IO_KEY_BACKSPACE) {
            nameBuffer[strlen(nameBuffer) - 1] = '\0';
        }
    }


    if (isMouseOnBottomButton(thisGame, x, y) && key == IO_MOUSE_LEFT_BUTTON) {
        return UNDER_RECORDS_BUTTON_ROW_INDEX;
    } else {
        return -1;
    }
}
// ====================
