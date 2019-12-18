#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstdlib>

bool correct = true;

bool isDot(int c) {
    return (c == 44 || c == 46);
}

void  incorrectInput() {

    printf("Incorrect input! Try again.\n");
};

float getFloat(char str[]){
    float result = 0;
    int dotNumb = 0;
    int afterDot = 0;
    for (int i = 0; i < sizeof(str) && str[i] != 0; ++i) {
        int ascii = str[i];
        if ((ascii >= 48 && ascii <= 57) || isDot(ascii)) {
            if (isDot(ascii)) {
                dotNumb++;
            } else {
                float n = ascii - 48;
                if (dotNumb < 1) {
                    result  = result * (i > 0 ? 10 : 1) + n;
                } else if (dotNumb == 1) {
                    afterDot++;
                    result = (float) (result + n / pow(10, afterDot));
                } else {
                    correct = false;
                    return 0;
                }
            }
        } else {
            correct = false;
            return 0;
        }
    }
    return result;
}

int main() {
/*
    // Task 1
    const float e = 2.71828;
    float result;

    float a = 0;
    float b = 0;

    printf("Input a: ");
    if (scanf("%f", &a) != 1) {
        incorrectInput();
        correct = false;
    }
    printf("Input b: ");
    if (scanf("%f", &b) != 1) {
        incorrectInput();
        correct = false;
    }

    if (correct) {
        float ab = a * b;
        if (0.5 < ab && ab < 10) {
            result = (float) pow(e, (fabs(a) - fabs(b)));
        } else if (0.1 < ab && ab < 0.5) {
            result = (float) sqrt(fabs(a + b));
        } else {
            result = (float) (b * pow(b, 2));
        }
        printf("result: %g\n", result);
    }
    */


    /*
    // Task 2
    char c;
    char newDirection = 'x';
    int n;
    int intDir = 0;
    printf("Input C: ");
    if (scanf("%c", &c) != 1) incorrectInput();

    printf("Input N: ");
    if (scanf("%d", &n) != 1) incorrectInput();

    //      N:0
    //  W:3     E:1
    //      S:2

    // 0 - forward
    // 1 - left
    // -1 - right
    c = (char) toupper(c);
    switch (c) {
        case 'N': // C
            intDir = 0;
            break;
        case 'S': // Ю
            intDir = 2;
            break;
        case 'W': // З
            intDir = 3;
            break;
        case 'E': // В
            intDir = 1;
            break;
        default:incorrectInput();
    }

    intDir -= n;
    intDir = abs(intDir) % 3;

    switch (intDir) {
        case 0:
            newDirection = 'N'; // C
            break;
        case 1:
            newDirection = 'E'; // В
            break;
        case 2:
            newDirection = 'S'; // Ю
            break;
        case 3:
            newDirection = 'W'; // З
            break;
    }
    printf("New direction: %c\n", newDirection);

*/
    // Task 3
    int n, length;
    int numbSum = 0;
    int counter = 0;

    printf("Input N: ");

    int INPUT_STR_LENGTH = 100;
    char strA[INPUT_STR_LENGTH];
    scanf("%s", strA);
    n = (int) getFloat(strA);

    if(correct) {
        int numbsCount = (int) pow(10, n) - 1; // количсетво цифр n-ого разрадя
        //std::cout << numbsCount << std::endl;

        for (int numb = 1; numb <= numbsCount; ++numb) {
            length = 0;
            int c = numb;
            while (c > 0) { // считаем слинну для данного числа
                length++;
                c = c / 10;
            }
            //std::cout << numb << std::endl;
            c = numb;
            for (; length > 0;) { // считаем сумму цифр
                double step = pow(10, (length - 1));
                int a = (int) (c / step);
                c = (int) (c - (a * step));
                length--;
                numbSum += a;
            }

            int d = 0; // проверяем ясвляется ли он натуральным
            for (int i = 1; i <= 9; ++i) {
                if (numbSum % i == 0) {
                    d++;
                }
            }
            if (numbSum >= 1 && numbSum % numbSum == 0 && numbSum % 1 == 0 && d == 2) {
                counter++;
            }
        }

        std::cout << "result =" << counter << std::endl;
    }

    system("pause");
    return 0;
}