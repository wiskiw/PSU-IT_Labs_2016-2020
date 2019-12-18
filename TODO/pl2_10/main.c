#include <stdio.h>
#include <stdlib.h>
#include "menu/Menu.h"
#include "tasks/task1/task1.h"
#include "tasks/task2/task2.h"
#include "tasks/task3/task3.h"
#include "tasks/task4/task4.h"

int main() {
    while (1) {
        int iValA = 0;
        int iValB = 0;
        char *charArray;
        double dValA = 0;
        float fValA = 0;
        switch (getMainMenuCode()) {
            case 0:
                return 0;
            case 1:
                system("cls");
                // ts   22
                scannTask1(&iValA, &dValA);
                printf("result: %lf", task1(iValA, dValA));
                break;
            case 2:
                system("cls");
                scanTask2(&charArray);
                task2(&charArray);
                printTask2(&charArray);
                break;
            case 3:
                system("cls");
                task3();
                break;
            case 4:
                system("cls");
                scanTask4(&fValA);
                task4(fValA, &iValA, &iValB);
                printTask4(iValA, iValB);
                break;
            default:
                printf("\tUnknown command, try again");
        }
        printf("\n");
        getchar();
    }
}