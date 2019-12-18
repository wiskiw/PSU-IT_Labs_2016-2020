#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "StackList.h"
#include "console_io_lib/console_io_lib.h"


int swap(StackList *pList);

// Фунцкия обработки возврат-кода функций
void processResult(int code) {
    switch (code) {
        case CODE_SUCCESS:
            printf(LightGreen, "Success!\n");
            break;
        case CODE_LIST_TO_SHORT:
            printf(LightRed, "Position not found! [%d]\n", CODE_LIST_TO_SHORT);
            break;
        case CODE_OUT_OF_BORDER:
            printf(LightRed, "Position not found! [%d]\n", CODE_OUT_OF_BORDER);
            break;
        default:
            break;
    }
}

int main() {
    // Member 10
    StackList *stackList = newList();
    while (true) {
        int tsN = -1;
        int iValA = 0;
        setConsoleTextColor(Yellow);
        printf("\t[1] - add item;\n");
        printf("\t[2] - remove item;\n");
        printf("\t[3] - show the list;\n");
        printf("\t[4] - clear list;\n");
        printf("\t[5] - task 24;\n");
        printf("\t[0] - exit \t\n: ");
        setConsoleTextColor(White);
        scanf("%d", &tsN);

        switch (tsN) {
            case 0:
                system("cls");
                clearList(stackList);
                return 0;
            case 1:
                system("cls");
                printf("Data: ");
                Data data;
                getchar();
                gets(data);
                printf("Index: ");
                scanf("%d", &iValA);
                processResult(addItem(stackList, data, iValA));
                break;
            case 2:
                system("cls");
                printf("Index: ");
                scanf("%d", &iValA);
                processResult(removeItem(stackList, iValA));
                break;
            case 3:
                system("cls");
                printList(stackList);
                break;
            case 4:
                system("cls");
                processResult(clearList(stackList));
                break;
            case 5:
                system("cls");
                processResult(swap(stackList));
                break;
            default:
                system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
        getchar();
    }
}

int swap(StackList *stackList) {
    StackListItem *itemA, *itemB, *tempItem;
    getItem(stackList, &itemA);

    StackList *tempList = newList();
    int size = 0;
    while (!isEmpty(stackList)) {
        size++;
        if (getItem(stackList, &tempItem) != CODE_SUCCESS) {
            clearList(tempList);
            return CODE_OUT_OF_BORDER;
        }
        addItem(tempList, tempItem->data);
    }
    getItem(tempList, &itemB);
    addItem(stackList, itemA->data);
    for (int j = 0; j < size - 1; j++) {
        getItem(tempList, &tempItem);
        addItem(stackList, tempItem->data);
    }
    addItem(stackList, itemB->data);
    clearList(tempList);
    return CODE_SUCCESS;
}