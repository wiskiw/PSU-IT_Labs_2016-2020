#include <iostream>
#include <cstdlib>
#include "QueueList.h"
#include "console_io_lib/console_io_lib.h"

void processResult(int code) {
    switch (code) {
        case CODE_SUCCESS:
            printf(LightGreen, "Success!\n");
            break;
        case CODE_NO_MEMORY:
            printf(LightRed, "No memory! [%d]\n", code);
            break;
        case CODE_OUT_OF_BORDER:
            printf(LightRed, "Position not found! [%d]\n", code);
            break;
        default:
            printf(LightRed, "Error: %d\n", code);
            break;
    }
}

int main() {
    // Member 10
    QueueList *list = newList();
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
                freeList(list);
                return 0;
            case 1:
                system("cls");
                printf("Data: ");
                Data data;
                scanf("%f", &data);
                processResult(addItem(list, data));
                break;
            case 2:
                system("cls");
                processResult(removeItem(list));
                break;
            case 3:
                system("cls");
                printList(list);
                break;
            default:
                system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
        getchar();
    }
}