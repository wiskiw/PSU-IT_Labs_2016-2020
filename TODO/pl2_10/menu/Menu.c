//
// Created by WiskiW on 10.05.2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"

void printMainMenu(){
    printf("\t[1] - task 1;\n");
    printf("\t[2] - task 2;\n");
    printf("\t[3] - task 3;\n");
    printf("\t[0] - exit \t\n: ");
}

int getMainMenuCode(){
    printMainMenu();
    int code = 0;
    while (scanf("%d", &code) != 1) {
        system("cls");
        printf("\tIncorrect command, try again\n");
        printMainMenu();
        getchar();
    }
    return code;
}