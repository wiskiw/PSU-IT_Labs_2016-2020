//
// Created by WiskiW on 30.04.2017.
//

#include <cstdio>
#include <console_io_lib/console_io_lib.h>
#include <conio.h>
#include "menu.h"

const char *POINTER = "-> ";
const Color  POINTER_COLOR = Yellow;
const Color  SELECTION_COLOR = Yellow;
const Color  ITEM_COLOR = Brown;

void printItems(char **items, int num) {
    Color pColor = getConsoleTextColor();
    setConsoleTextColor(ITEM_COLOR);
    for (int i = 0; i < num; i++) {
        printf("\t%s\n", items[i]);
    }
    setConsoleTextColor(pColor);
}

int goUp(int num, int pos) {
    if (pos <= 0) {
        pos = num - 1;
    } else {
        pos--;
    }
    return pos;
}

int goDown(int num, int pos) {
    if (pos >= num - 1) {
        pos = 0;
    } else {
        pos++;
    }
    return pos;
}

int moveCursor(char **items, int num, int pPos, int nPos) {
    COORD previewCord = getCursorPosition();
    if (pPos >= num || nPos >= num) {
        return pPos;
    }

    int menuLine = getCursorPosition().Y - num;
    if (pPos >= 0) {
        setCursorTo(8, menuLine + pPos);
        removeC(4);
        printf(ITEM_COLOR, "    %s", items[pPos]);
    }
    if (nPos >= 0) {
        setCursorTo(8 - strlen(POINTER), menuLine + nPos);
        printf(POINTER_COLOR, "%s", POINTER);
        printf(SELECTION_COLOR, "%s", items[nPos]);
        //printf("\t%s\n", );
        setCursorTo(previewCord.X, previewCord.Y);
        return nPos;
    } else {
        setCursorTo(previewCord.X, previewCord.Y);
        return pPos;
    }
}

int doCool(char **items, int itemsNumb){
    int cPos = 1;
    printItems(items, itemsNumb);
    moveCursor(items, itemsNumb, -1, cPos);
    while (true) {
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
                case VK_RETURN:
                    moveCursor(items, itemsNumb, cPos, -1); // удаление указателя
                    return cPos;
                default:
                    if (key == 72 || key == 75) {
                        cPos = moveCursor(items, itemsNumb, cPos, goUp(itemsNumb, cPos));
                    } else if (key == 80 || key == 77) {
                        cPos = moveCursor(items, itemsNumb, cPos, goDown(itemsNumb, cPos));
                    } else if (key >= 48 && key <= 57 && key - 48 < itemsNumb) {
                        int numb = key - 48;
                        cPos = moveCursor(items, itemsNumb, cPos, numb);
                    }
                    break;
            }
        }
    }
}

int mainMenu() {
    int itemsNumb = 8;
    char **items = (char **) calloc(itemsNumb, sizeof(char *));
    items[0] = (char *) "[0] - exit";
    items[1] = (char *) "[1] - add new GitRep;";
    items[2] = (char *) "[2] - show a GitRep;";
    items[3] = (char *) "[3] - show the GitRep list;";
    items[4] = (char *) "[4] - save the GitRep list;";
    items[5] = (char *) "[5] - load the GitRep list;";
    items[6] = (char *) "[6] - free memory;";
    items[7] = (char *) "[7] - remove file;";
    return doCool(items, itemsNumb);
}