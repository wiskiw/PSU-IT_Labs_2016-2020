//
// Created by WiskiW on 10.05.2017.
//

#include <stdio.h>
#include <malloc.h>
#include "task2.h"


void scanTask2(char **array) {
    int size = 0;
    printf("Enter the size: ");
    while (scanf("%d", &size) != 1) {
        printf("Incorrect input, try again: ");
        int c = getchar();
        while (c != '\n')c = getchar();
    }
    *array = calloc(size + 1, sizeof(char));
    (*array)[size] = '\0';
    printf("Enter the array: ");
    getchar();
    gets(*array);
}

void removeItem(char **array, int index) {
    // сдвигает все msg на offset
    if (index >= 0) {
        int i = index;
        for (; (*array)[i + 1] != '\0'; i++) {
            array[i] = array[i + 1];
        }
        (*array)[i] = '\0';
    }
}

void task2(char **array) {
    for (int i = 0; (*array)[i] != '\0'; i++) {
        char c = (*array)[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            removeItem(array, i);
        }
    }
}


void printTask2(char **array) {
    printf("Char array: ");
    for (int i = 0; (*array)[i] != '\0'; i++) {
        printf("%c", (*array)[i]);
    }
}
