//
// Created by wiskiw on 06.12.17.
//

#include <cstring>
#include <iostream>
#include "Menu.h"
#include "../../utils/Utils.h"
#include "../../io/IOProcessor.h"

const SW_Color MENU_BACKGROUND_COLOR = {50, 50, 50};
const SW_Color MENU_UNDERMENU_BACKGROUND_COLOR = {1, 1, 1, 100};

const SW_Color MENU_ITEM_TEXT_COLOR_NORMAL = {255, 255, 255};
const SW_Color MENU_ITEM_BACKGROUND_COLOR_NORMAL = {25, 25, 25};

const SW_Color MENU_ITEM_TEXT_COLOR_FOCUS = {1, 255, 255};
const SW_Color MENU_ITEM_BACKGROUND_COLOR_FOCUS = {35, 35, 35};

const SW_Color MENU_ITEM_TEXT_COLOR_PRESSED = {1, 255, 255};
const SW_Color MENU_ITEM_BACKGROUND_COLOR_PRESSED = {25, 25, 25};

const SW_Color MENU_ITEM_TEXT_COLOR_DISABLE = {1, 255, 255};
const SW_Color MENU_ITEM_BACKGROUND_COLOR_DISABLE = {25, 25, 25};


const float DIVINER_X = 5;
const float DIVINER_Y = 5;
const float ITEM_X = 150;
const float ITEM_Y = 25;
const float MENU_Z = 15;

void *MENU_ITEM_FONT = GLUT_BITMAP_HELVETICA_18;
const float MENU_ITEM_FONT_CHAR_HEIGHT = 18 / PREF_SCREEN_CROP_FACTOR;


enum GameMenuItemState {
    GAME_MENU_ITEM_STATE_NORMAL, GAME_MENU_ITEM_STATE_FOCUS,
    GAME_MENU_ITEM_STATE_PRESSED, GAME_MENU_ITEM_STATE_DISABLE
};

struct GAME_Menu_Item {
    int pos = 1;
    char label[255] = "set label!";
    GameMenuItemState state = GAME_MENU_ITEM_STATE_NORMAL;
};

struct GAME_Menu {
    const static int itemBufferSize = 10;
    GAME_Menu_Item items[itemBufferSize];
    int itemsNumber = 0;

};

GAME_Menu pauseMenu;


float getStringWidthPX(char *s) {
    int width = 0;
    const size_t len = strlen(s);
    for (unsigned int i = 0; i < len; i++)
        width += glutBitmapWidth(MENU_ITEM_FONT, s[i]);
    return width / PREF_SCREEN_CROP_FACTOR;
}

void colorUndermenuBackground(GameFieldStruct *thisGame) {
    float x = thisGame->windowX / PREF_SCREEN_CROP_FACTOR;
    float y = thisGame->windowY / PREF_SCREEN_CROP_FACTOR;
    glPushMatrix();
    glTranslatef(0, 0, MENU_Z - 0.05f);
    glBegin(GL_POLYGON);
    utilsSelectColor(MENU_UNDERMENU_BACKGROUND_COLOR);
    glVertex2f(0, 0);
    glVertex2f(0, y);
    glVertex2f(x, y);
    glVertex2f(x, 0);
    glEnd();
    glPopMatrix();
}

SW_Borders getMenuItemBorders(int index, SW_Pos menuBackgroundPos) {
    SW_Borders menuItemBorders;
    menuItemBorders.leftBottomX = menuBackgroundPos.x + DIVINER_X;
    menuItemBorders.leftBottomY = menuBackgroundPos.y + DIVINER_Y + (DIVINER_Y + ITEM_Y) * index;
    menuItemBorders.rightTopX = menuItemBorders.leftBottomX + ITEM_X;
    menuItemBorders.rightTopY = menuItemBorders.leftBottomY + ITEM_Y;
    return menuItemBorders;
}

SW_Color getMenuItemBackgroundColor(GameMenuItemState state) {
    switch (state) {
        case GAME_MENU_ITEM_STATE_FOCUS:
            return MENU_ITEM_BACKGROUND_COLOR_FOCUS;
        case GAME_MENU_ITEM_STATE_PRESSED:
            return MENU_ITEM_BACKGROUND_COLOR_PRESSED;
        case GAME_MENU_ITEM_STATE_DISABLE:
            return MENU_ITEM_BACKGROUND_COLOR_DISABLE;
        default:
            return MENU_ITEM_BACKGROUND_COLOR_NORMAL;
    }
}

SW_Color getMenuItemTextColor(GameMenuItemState state) {
    switch (state) {
        case GAME_MENU_ITEM_STATE_FOCUS:
            return MENU_ITEM_TEXT_COLOR_FOCUS;
        case GAME_MENU_ITEM_STATE_PRESSED:
            return MENU_ITEM_TEXT_COLOR_PRESSED;
        case GAME_MENU_ITEM_STATE_DISABLE:
            return MENU_ITEM_TEXT_COLOR_DISABLE;
        default:
            return MENU_ITEM_TEXT_COLOR_NORMAL;
    }
}

int getMenuItemUnderMouse(GameFieldStruct *thisGame, GAME_Menu menu, int x, int y) {
    // адаптация под экран
    y = static_cast<int>((thisGame->windowY - y) / PREF_SCREEN_CROP_FACTOR);
    x = static_cast<int>(x / PREF_SCREEN_CROP_FACTOR);

    const float menuBackgroundX = ITEM_X + 2 * DIVINER_X;
    const float menuBackgroundY = (ITEM_Y + DIVINER_Y) * menu.itemsNumber + DIVINER_Y;

    const float menuBackgroundPoxX = thisGame->windowX / 2 / PREF_SCREEN_CROP_FACTOR - (menuBackgroundX / 2);
    const float menuBackgroundPoxY = thisGame->windowY / 2 / PREF_SCREEN_CROP_FACTOR - (menuBackgroundY / 2);

    for (int i = 0; i < menu.itemsNumber; ++i) {
        SW_Borders menuItemBorders = getMenuItemBorders(i, {menuBackgroundPoxX, menuBackgroundPoxY});

        if (x >= menuItemBorders.leftBottomX && x <= menuItemBorders.rightTopX &&
            y >= menuItemBorders.leftBottomY && y <= menuItemBorders.rightTopY) {
            return i;
        }
    }
    return -1;
}

void menuUpdateMenuItemState(GameFieldStruct *thisGame, GAME_Menu *menu, GameMenuItemState state, int x, int y) {
    const int menuItem = getMenuItemUnderMouse(thisGame, *menu, x, y);
    if (menuItem != -1) {
        menu->items[menuItem].state = state;
    } else {
        for (int i = 0; i < pauseMenu.itemsNumber; ++i) {
            menu->items[i].state = GAME_MENU_ITEM_STATE_NORMAL;
        }
    }
}

void drawMenu(GameFieldStruct *thisGame, GAME_Menu menu) {
    colorUndermenuBackground(thisGame);

    const float menuBackgroundX = ITEM_X + 2 * DIVINER_X;
    const float menuBackgroundY = (ITEM_Y + DIVINER_Y) * menu.itemsNumber + DIVINER_Y;

    const float menuBackgroundPoxX = thisGame->windowX / 2 / PREF_SCREEN_CROP_FACTOR - (menuBackgroundX / 2);
    const float menuBackgroundPoxY = thisGame->windowY / 2 / PREF_SCREEN_CROP_FACTOR - (menuBackgroundY / 2);

    glPushMatrix();
    glTranslatef(menuBackgroundPoxX, menuBackgroundPoxY, MENU_Z);
    glBegin(GL_POLYGON);
    utilsSelectColor(MENU_BACKGROUND_COLOR);
    glVertex2f(0, 0);
    glVertex2f(0, menuBackgroundY);
    glVertex2f(menuBackgroundX, menuBackgroundY);
    glVertex2f(menuBackgroundX, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(menuBackgroundPoxX, menuBackgroundPoxY, MENU_Z + 0.01f);
    for (int i = 0; i < menu.itemsNumber; ++i) {
        SW_Borders menuItemBorders = getMenuItemBorders(i, {});

        GameMenuItemState state = menu.items[i].state;
        SW_Color bgColor = getMenuItemBackgroundColor(state);
        SW_Color textColor = getMenuItemTextColor(state);


        char *menuItemLabel = menu.items[i].label;
        SW_Pos pos = {menuItemBorders.leftBottomX + (ITEM_X - getStringWidthPX(menuItemLabel)) / 2,
                      menuItemBorders.leftBottomY + (ITEM_Y - MENU_ITEM_FONT_CHAR_HEIGHT) / 2, MENU_Z + 0.02f};
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
void menuDrawPause(GameFieldStruct *thisGame) {
    pauseMenu.itemsNumber = 2;
    strncpy(pauseMenu.items[1].label, "Continue", 9);
    strncpy(pauseMenu.items[0].label, "Exit", 5);
    drawMenu(thisGame, pauseMenu);
}

void menuProcessPauseMenuItemClick(GameFieldStruct *thisGame, int key, int x, int y) {
    if (key != IO_MOUSE_LEFT_BUTTON) {
        return;
    }
    const int menuItem = getMenuItemUnderMouse(thisGame, pauseMenu, x, y);
    switch (menuItem) {
        case 0:
            exit(0);
            break;
        case 1:
            thisGame->gameState = GAME_STATE_PLAY;
            break;
    }
}

void menuProcessPauseMenuItemFocus(GameFieldStruct *thisGame, int x, int y) {
    menuUpdateMenuItemState(thisGame, &pauseMenu, GAME_MENU_ITEM_STATE_FOCUS, x, y);
}
// ====================