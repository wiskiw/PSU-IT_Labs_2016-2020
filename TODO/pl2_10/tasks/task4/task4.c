//
// Created by WiskiW on 10.05.2017.
//

#include <stdio.h>
#include <math.h>
#include "task4.h"

const int ACCURACY = 6;

void scanTask4(float *d) {
    printf("Inter the float number: ");
    while (scanf("%f", d) != 1) {
        printf("Incorrect input, try again: ");
    }
}

int posRound(double d) {
    //return (int) (d);
    return (int) floor(d);
}


int negRound(double d) {
    return (int) ceil(d);
}

void task4(float d, int *a, int *b) {
    int (*myRound)(double);
    *a = 0;
    *b = 0;
    myRound = posRound;
/*
    if (d == 0) {
        return;
    } else if (d > 0) {
        myRound = posRound;
    } else {
        myRound = negRound;
    }
    */

    *a = myRound(d);
    int tempD = myRound((d - *a ) * pow(10, ACCURACY));
    int kPos = 0;
    for (int i = 0; i < ACCURACY; i++) {
        printf("temp: %d\n", tempD);
        if (tempD % 10 != 0) {
            kPos = ACCURACY  - i + 1;
        }
        tempD = tempD / 10;
    }
    //tempD = d - *a;
    *b = myRound((d - *a) * pow(10, kPos));
    printf("b: %d\n", *b);

    /*


    printf("temp0: %lf\n\n", tempD);
    while (myRound(tempD * pow(10, ACCURACY)) != 0) {
        printf("b: %d\n", *b);
        printf("temp: %lf\n", tempD);
        printf("plus: %d\n\n", myRound((tempD + 0.5) * 10));
        *b = *b * 10 + myRound((tempD + 0.5) * 10);
        tempD = (tempD + 0.5) * 10;
        tempD = tempD - myRound(tempD);
    }
     */
}

void printTask4(int a, int b) {
    printf("numb: %d . %d\n", a, b);
}
