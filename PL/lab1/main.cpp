#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) {

/*
    // Task 1
    int a, n;
    scanf("%x%d", &a, &n);

    int res = 1;
    for (int i = 0; i < n; i++) {
        res *= a;
    }

    printf("a^n (x10) =  %d \n", res);
    printf("a^n (x10) =  %o \n", res);
*/
/*
    // Task 2
    const float e = 2.71828;
    float x, y, z;
    scanf("%f%f%f", &x, &y, &z);
    float a1, a2, a3, result;

    a1 = (float) (pow(z, 1 / 3) * pow(tan(y), 2));
    a2 = (float) (y - pow(z, 2) / (x + y));
    a3 = (float) sqrt((fabs(x) + pow(e, y))); // (fabs(x) + pow(e, y)) > 0 !!!

    result = a3;
    result -= (a1/a2);
    result += pow(y,x);
    printf("result= %g\n", result);
*/


    // Task 3
    char a, b;
    scanf("%c\n%c", &a, &b);

    int result = (a-48) + (b-48) < 10 ? 0 : 1;
    printf("%d\n", result);


    /*
    // Task 4
    float a, b, c, d;
    scanf("%f%f%f%f", &a, &b, &c, &d);

    float middle = (a > 0 && a < c) || (a < 0 && a > c) ? a : (0 > a && 0 < c) || (0 < a && 0 > c) ? 0 : c;
    float max = b > c && b > d ? b : (c > b && c > d ? c : d);
    float min = b < a && b < d ? b : (a < b && a < d ? a : d);
    float result = middle * max / min;
    printf("%g", result);
*/



    system("pause");
    return 0;
}
