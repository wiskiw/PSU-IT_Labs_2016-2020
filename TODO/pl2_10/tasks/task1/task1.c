//
// Created by WiskiW on 10.05.2017.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "task1.h"

double ctg(double i) {
    return sin(i) / cos(i);
}

void scannTask1(int *n, double *x){
    printf("Enter X: ");
    scanf("%lf", x);

    printf("Select the function(1-4): ");
    scanf("%d", n);


}

double task1(int n, double x) {
    switch (n) {
        case 1:
            return pow((fabs(ctg(x) * cos(x)) / 5), 1 / 2);
        case 2:
            return (pow(x, 2) - x) / log(pow(x, 2));
        case 3:
            return (x - 5) / pow(x, 2) * exp(x);
        case 4:
            return pow(fabs(1 + 3 * pow(x, 2 / 3)), 1 / 2);
        default:
            return -1;
    }
}