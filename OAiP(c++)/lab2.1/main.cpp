#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>


int main() {
/*
    // var 14;
    // Task 1
    char str[101];
    char resultStr[303];
    printf("Input string: ");
    gets(str);
    sprintf(resultStr, "%s%s%s%s%s", str, ", ", str, ", ", str);
    puts(resultStr);
    sprintf(resultStr, "%s%d", "length=", strlen(str));
    puts(resultStr);
*/

    // Task 2
    /*
    char str[101];
    char charSet[51]= "12345";
    gets(str);
    gets(charSet);

    puts("\nWords:");
    char *sp;
    sp = strtok(str, charSet);
    while (sp) {
        puts(sp);
        sp = strtok(NULL, charSet);
    }
*/
    // Task 3
    /*

    I - 1
    V - 5
    X - 10
    L - 50
    C - 100
    D - 500
    M - 1000

    // lim: 1 - 3999

    char dStr[101];
    char resultStr[101] = "";
    gets(dStr);
    int numb = atol(dStr);


    int m, cm, d, c, xc, l, x, ix, v, i;
    for (m = 1000; numb >= m; numb -= 1000) {
        strcat(resultStr, "M");
    }
    for (cm = 900; numb >= cm; numb -= 900) {
        strcat(resultStr, "CM");
    }
    for (d = 500; numb >= d; numb -= 500) {
        strcat(resultStr, "D");
    }
    if (numb >= 400) {
        strcat(resultStr, "CD");
        numb -= 400;
    } else {
        for (c = 100; numb >= c; numb -= 100) {
            strcat(resultStr, "C");
        }
    }
    for (xc = 90; numb >= xc; numb -= 90) {
        strcat(resultStr, "XC");
    }
    for (l = 50; numb >= l; numb -= 50) {
        strcat(resultStr, "L");
    }
    if (numb >= 40) {
        strcat(resultStr, "XL");
        numb -= 40;
    } else {
        for (x = 10; numb >= x; numb -= 10) {
            strcat(resultStr, "X");
        }
    }
    for (ix = 9; numb >= ix; numb -= 9) {
        strcat(resultStr, "IX");
    }
    for (v = 5; numb >= v; numb -= 5) {
        strcat(resultStr, "V");
    }
    if (numb >= 4) {
        strcat(resultStr, "IV");
        //numb -= 4;
    } else {
        for (i = 1; numb >= i; numb -= 1) {
            strcat(resultStr, "I");
        }
    }
    puts(resultStr);
*/


/*
    // Task 4
    int n;
    char result[50] = "";
    scanf("%d", &n);

    int additionN = n;
    int length = 0;
    for (int j = 0; additionN > 0; ++j) {
        length++;
        additionN /= 10;
    }


    for (int i = length; i > 0; i--) {
        int k = (n % 10) + 48;
        //printf("k=%d\n", k-48);
        result[i - 1] = (char) k;
        n = n / 10;
    }

    printf("%s\n", result);
*/
/*
    // Task 5
    char inputStr[80];
    char last[80] = "\n";
    gets(inputStr);


    char *sp;
    sp = strtok(inputStr, " ");
    while (sp) {
        if (strcmp(last, sp) == -1){
            strcpy(last, sp);
        }

        //puts(sp);
        sp = strtok(NULL, " ");
    }
    puts(last);
*/
    system("pause");


    return 0;
}