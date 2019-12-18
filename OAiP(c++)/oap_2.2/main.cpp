#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>


float triangleS(float a) {
    return (float) (pow(a, 2) * sqrt(3) / 4);
}

float calc(float a, float b, int op) {
    // Op: 1 — вычитание, 2 — умножение, 3 — деление, остальные значения — сложение.
    switch (op) {
        case 1:
            return a - b;
        case 2:
            return a * b;
        case 3:
            return a / b;
        default:
            return a + b;
    }
}

float calculateSum(int m, int n) {
    //(-1)n / (n*(n-1))
    float sum = 0;
    for (int i = n; i >= m; i--) {
        if (i - 1 == 0) {
            printf("(Attention! Skipping x/0 iteration)\n");
            continue;
        }
        float item = (float) (pow((-1), i) / (i * (i - 1)));
        sum += item;
    }
    return sum;

}

void smooth1(float *array, int size) {
    float iSum = 0;
    for (int i = 0; i < size; ++i) {
        iSum += array[i];
        array[i] = iSum / (i + 1);
    }
}

void printArray(float *array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%g ", array[i]);
    }
    printf("\n");
}

char *fillStr(char strTemplate[], int length) {
    char *result = new char[length + 1 ];
    for (int i = 0; i < length;) {
        for (int j = 0; strTemplate[j] != '\0'; ++j) {
            result[i] = strTemplate[j];
            i++;
        }
    }
    result[length] = '\0';
    return result;
}


void task1() {
    float a1, a2, a3;
    printf("triangle 1: ");
    scanf("%f", &a1);
    printf("triangle 2: ");
    scanf("%f", &a2);
    printf("triangle 3: ");
    scanf("%f", &a3);

    printf("S1: %f\n", triangleS(a1));
    printf("S2: %f\n", triangleS(a2));
    printf("S3: %f\n", triangleS(a3));

}

void task2() {
    float a, b;
    printf("a: ");
    scanf("%f", &a);
    printf("b: ");
    scanf("%f", &b);

    int n1, n2, n3;
    printf("Enter operations (n1, n2, n3): ");
    scanf("%d%d%d", &n1, &n2, &n3);

    printf("op 1: %g\n", calc(a, b, n1));
    printf("op 2: %g\n", calc(a, b, n2));
    printf("op 3: %g\n", calc(a, b, n3));

}

void task3() {
    int m, n;
    printf("Enter m, n: ");
    scanf("%d%d", &m, &n);
    printf("Sum between %d and %d: %f\n", m, n, calculateSum(m, n));
}

void task4() {
    int size;
    printf("Enter the array size: ");
    scanf("%d", &size);
    float array[size];
    printf("Enter the array: ");
    for (int i = 0; i < size; ++i) {
        scanf("%f", &array[i]);
    }

    for (int j = 0; j < 5; j++) {
        smooth1(array, size);
        printf("The %d smooth: ", j+1);
        printArray(array, size);
    }
}

void task5() {
    int resultSize;
    char templateStr1[101] = "";
    char templateStr2[101] = "";
    char templateStr3[101] = "";
    char templateStr4[101] = "";
    char templateStr5[101] = "";
    printf("Enter the result string length: ");
    scanf("%d", &resultSize);

    printf("Enter the 1st template string: ");
    scanf("%s", templateStr1);
    char *result = fillStr(templateStr1, resultSize);
    printf("Result string 1:  %s\n", result);
    /*
    printf("Enter the 2nd template string: ");
    scanf("%s", templateStr2);
    printf("Enter the 3rd template string: ");
    scanf("%s", templateStr3);
    printf("Enter the 4th template string: ");
    scanf("%s", templateStr4);
    printf("Enter the 5th template string: ");
    scanf("%s", templateStr5);

    char *result = fillStr(templateStr1, resultSize);
    printf("Result string 1:  %s\n", result);

    result = fillStr(templateStr2, resultSize);
    printf("Result string 2:  %s\n", result);

    result = fillStr(templateStr3, resultSize);
    printf("Result string 3:  %s\n", result);

    result = fillStr(templateStr4, resultSize);
    printf("Result string 4:  %s\n", result);

    result = fillStr(templateStr5, resultSize);
    printf("Result string 5:  %s\n", result);
*/
}

int main() {
    // Member 5

    while (true) {
        int tsN = -1;
        printf("\tEnter task number (0 to exit) : ");
        scanf("%d", &tsN);

        switch (tsN) {
            case 0:
                system("pause");
                return 0;
            case 1:
                printf("\n");
                task1();
                break;
            case 2:
                printf("\n");
                task2();
                break;
            case 3:
                printf("\n");
                task3();
                break;
            case 4:
                printf("\n");
                task4();
                break;
            case 5:
                printf("\n");
                task5();
                break;
            default:
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}
