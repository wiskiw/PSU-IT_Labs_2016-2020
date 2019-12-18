//
// Created by WiskiW on 10.05.2017.
//

#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#include "task3.h"


int wordListSize = 0;
char **wordList = NULL;// массив слов
int *wordNumbList = NULL; // массив для хранения числа вхождений слов
int maxWordNum = 0; // максимальное количество вхождений слова
int minWordNum = 0; // минимальное количество вхождений слова



int findWord(char *word) {
    for (int i = 0; i < wordListSize; i++) {
        //printf("cmp '%s':'%s'\n", word, wordList[i]);
        if (strcmp(word, wordList[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void task3() {
    wordListSize = 0;
    wordList = NULL;
    wordNumbList = NULL;
    maxWordNum = 0;
    minWordNum = 0;


    char *string = calloc(80, sizeof(char));
    printf("Enter the string: ");
    getchar();
    gets(string);

    char *word = strtok(string, " ");

    while (word != NULL) {
        int index = findWord(word);
        if (index == -1) {
            wordList = realloc(wordList, sizeof(char *) * (wordListSize + 1));
            wordList[wordListSize] = word;
            wordNumbList = realloc(wordNumbList, sizeof(int) * (wordListSize + 1));
            wordNumbList[wordListSize] = 1;
            wordListSize++;
        } else {
            wordNumbList[index] = wordNumbList[index] + 1;
        }
        word = strtok(NULL, " ");
    }

    if (wordListSize > 0) {
        // поиск слов с минимальным и максимальным числом повторений
        minWordNum = wordNumbList[0];
        maxWordNum = wordNumbList[0];
        for (int i = 0; i < wordListSize; i++) {
            if (minWordNum > wordNumbList[i]) {
                minWordNum = wordNumbList[i];
            }
            if (maxWordNum < wordNumbList[i]) {
                maxWordNum = wordNumbList[i];
            }
        }

        //printf("min num: %d\n", minWordNum);
        //printf("max num: %d\n", maxWordNum);

        if (minWordNum == maxWordNum) {
            // если все слова повторяются одинаковое количество раз
            printf("Nothing to show :| \n");
            return;
        }

        for (int i = 0; i < wordListSize; i++) {
            if (wordNumbList[i] == maxWordNum) {
                printf("word: '%s'\n", wordList[i]);
            }
        }
    } else {
        printf("No words found!\n");
    }
}