//
// Created by WiskiW on 30.04.2017.
//

#include <cstdio>
#include <console_io_lib/console_io_lib.h>
#include <conio.h>
#include "menu.h"


const int HEADER_LEN = 28;
const char *POINTER = "-> ";
const Color HEADER_COLOR = LightMagenta;
const Color POINTER_COLOR = White;
const Color SELECTION_COLOR = White;
const Color Back_ITEM_COLOR = DarkGray;
const Color ITEM_COLOR = DarkGray;

int menuLevels[5];
int currentLevel = 0;

void printItems(char *title, char **items, int num) {
    Color pColor = getConsoleTextColor();
    setConsoleTextColor(ITEM_COLOR);
    printf("\n");
    char diviner1[] = "========"; // 8
    char diviner2[] = "========================="; // 25
    diviner2[HEADER_LEN - (strlen(diviner1) + strlen(title))] = '\0';
    printf(HEADER_COLOR, "%s %s %s\n", diviner1, title, diviner2);
    printf(Back_ITEM_COLOR, "\t%s\n", items[0]);
    for (int i = 1; i < num; i++) {
        printf("\t%s\n", items[i]);
    }
    setConsoleTextColor(pColor);
}

void removeItems(char **items, int num) {
    COORD pos = getCursorPosition();
    for (int i = 0; i < num; i++) {
        setCursorTo(strlen(items[num - i - 1]) + 8, pos.Y - 1 - i);
        clearLine();
    }
    //удаление хэдера
    setCursorTo(HEADER_LEN + 2, pos.Y - num - 1); // + 2 под пробелы между дивинерами в хэдере
    clearLine();

    //удаление \n в printItems()
    setCursorTo(0, pos.Y - num - 2); // + 2 под пробелы между дивинерами в хэдере
    clearLine();

}

int goUp(int num, int pos) {
    if (pos <= 0) {
        //pos = num - 1;
    } else {
        pos--;
    }
    return pos;
}

int goDown(int num, int pos) {
    if (pos >= num - 1) {
        //pos = 0;
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
        printf(pPos == 0 ? Back_ITEM_COLOR : ITEM_COLOR, "    %s", items[pPos]);
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

int doCool(char *title, char **items, int itemsNumb) {
    int cPos = 1;
    printItems(title, items, itemsNumb);
    moveCursor(items, itemsNumb, -1, cPos);
    while (true) {
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
                case VK_RETURN:
                    //system("cls");
                    removeItems(items, itemsNumb);
                    //moveCursor(items, itemsNumb, cPos, -1); // удаление указателя
                    if (cPos == 0) {
                        currentLevel--;
                    } else {
                        menuLevels[currentLevel] = cPos;
                        currentLevel++;
                    }
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

int goBackMenu() {

}

int printMainMenu() {
    int itemsNumb = 4;
    char *title = (char *) "Main Menu";
    char **items = (char **) calloc(itemsNumb, sizeof(char *));
    items[0] = (char *) "[0] - Exit";
    items[1] = (char *) "[1] - Database";
    items[2] = (char *) "[2] - Item";
    items[3] = (char *) "[3] - List";
    return doCool(title, items, itemsNumb);
}

int printDatabaseMenu() {
    int itemsNumb = 3;
    char *title = (char *) "Database";
    char **items = (char **) calloc(itemsNumb, sizeof(char *));
    items[0] = (char *) "[0] - Back";
    items[1] = (char *) "[1] - Load";
    items[2] = (char *) "[2] - Save";
    return doCool(title, items, itemsNumb);
}

int confirmMenu() {
    int itemsNumb = 3;
    char *title = (char *) "Sure?";
    char **items = (char **) calloc(itemsNumb, sizeof(char *));
    items[0] = (char *) "[0] - Cancel";
    items[1] = (char *) "[1] - Yes";
    items[2] = (char *) "[2] - No";
    return doCool(title, items, itemsNumb);
}

int printItemMenu() {
    int itemsNumb = 5;
    char *title = (char *) "Item";
    char **items = (char **) calloc(itemsNumb, sizeof(char *));
    items[0] = (char *) "[0] - Back";
    items[1] = (char *) "[1] - Add";
    items[2] = (char *) "[2] - Show";
    items[3] = (char *) "[3] - Edit";
    items[4] = (char *) "[4] - Remove";
    return doCool(title, items, itemsNumb);
}

int printListMenu() {
    int itemsNumb = 5;
    char *title = (char *) "List";
    char **items = (char **) calloc(itemsNumb, sizeof(char *));
    items[0] = (char *) "[0] - Back";
    items[1] = (char *) "[1] - Sort";
    items[2] = (char *) "[2] - Filter";
    items[3] = (char *) "[3] - Search";
    items[4] = (char *) "[4] - Clean";
    return doCool(title, items, itemsNumb);
}

int printDirMenu() {
    int itemsNumb = 3;
    char *title = (char *) "Direction";
    char **items = (char **) calloc(itemsNumb, sizeof(char *));
    items[0] = (char *) "[0] - Cancel";
    items[1] = (char *) "[1] - Increment (a0-Z9)";
    items[2] = (char *) "[2] - Decrement (Z9-a0)";
    return doCool(title, items, itemsNumb);
}

int printFieldMenu() {
    int itemsNumb = 11;
    char *title = (char *) "Field";
    char **items = (char **) calloc(itemsNumb, sizeof(char *));
    items[0] = (char *) "[0] - Back";
    items[1] = (char *) "[1] - Name";
    items[2] = (char *) "[2] - Programming language";
    items[3] = (char *) "[3] - Author";
    items[4] = (char *) "[4] - Rate";
    items[5] = (char *) "[5] - Commit numb";
    items[6] = (char *) "[6] - Error numb";
    items[7] = (char *) "[7] - Fix error numb";
    items[8] = (char *) "[8] - Branch numb";
    items[9] = (char *) "[9] - Create date";
    items[10] = (char *) "[10] - Edit date";
    return doCool(title, items, itemsNumb);
}