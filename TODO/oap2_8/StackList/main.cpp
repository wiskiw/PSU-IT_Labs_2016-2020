#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "StackList.h"
#include "console_io_lib/console_io_lib.h"


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
        printf("\t[0] - exit \t\n: ");
        setConsoleTextColor(White);
        scanf("%d", &tsN);

        switch (tsN) {
            case 0:
                system("cls");
                freeList(stackList);
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
            default:
                system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
        getchar();
    }
}