#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <windows.h>

void incorrectInputException() {
    printf("Incorrect input! Try again.\n");
}

void printArray(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void task1() {
    char str[101] = "";
    char charSet[51] = "";
    printf("Enter the string: ");
    getchar();
    gets(str);

    printf("Enter the symbols: ");
    gets(charSet);

    puts("\nWords:");
    char *sp;
    sp = strtok(str, charSet);
    while (sp) {
        puts(sp);
        sp = strtok(NULL, charSet);
    }
}


int quarter(int x, int y) {
    if (x > 0) {
        if (y > 0) {
            return 1;
        } else if (x < 0) {
            return 4;
        } else {
            return 14;
        }
    } else if (x < 0) {
        if (y > 0) {
            return 2;
        } else if (x < 0) {
            return 3;
        } else {
            return 23;
        }
    }
}

void task2() {
    int x, y;
    printf("X(int): ");
    if (scanf("%d", &x) != 1) {
        incorrectInputException();
        return;
    };

    printf("Y(int): ");
    if (scanf("%d", &y) != 1) {
        incorrectInputException();
        return;
    };

    int result = quarter(x, y);
    if (result / 10 > 0) {
        printf("quartet between: %d-%d\n", result / 10, result % 10);
    } else {
        printf("quartet: %d\n", result);
    }
}


void task3() {



    int n, m;
    int *arrayPtr;
    printf("n=");
    scanf("%d", &n);
    arrayPtr = (int *) calloc(n, sizeof(int));
    getchar();

    printf("array(1): ");
    printArray(arrayPtr, n);


    printf("m=");
    scanf("%d", &m);

    arrayPtr = (int *) realloc(arrayPtr, (size_t) (n + m));

    for (int j = 0; j < n + m; j++) {
        if (j < n) {
            arrayPtr[j] = 0;
        } else {
            arrayPtr[j] = 13;
        }
    }


    printf("array(2): ");
    printArray(arrayPtr, n + m);

    if (arrayPtr)
        free(arrayPtr);
}


struct Nackl {
    int numb;
    char date[11];
    float sum;
    char fio[21];
};


void printTableHead() {
    printf("%5s     ", "NUMB:");
    printf("%15s     ", "DATE:");
    printf("%12s     ", "SUM:");
    printf("%25s     ", "FIO:");
    printf("\n");
}

void printNucklTable(Nackl *nackl) {
    printf("%5d     ", nackl->numb);
    printf("%15s     ", nackl->date);
    printf("%12.2f     ", nackl->sum);
    printf("%25s     ", nackl->fio);
    printf("\n");
}


void task4() {
    Nackl **list = (Nackl **) malloc(0); // инициализируем пустой массив указателей
    for (int i = 1; 1; ++i) {
        list = (Nackl **) realloc(list, i * sizeof(list)); // расширяем памяь под новую запись в массиве

        printf("\nEnter new struct(Number, Date, Sum, FIO): \n");
        Nackl nackl;
        printf("\tNumb(int): ");
        scanf("%d", &nackl.numb);
        printf("\tDate (dd.mm.yyyy): ");
        scanf("%s", nackl.date);
        printf("\tSum(float):");
        scanf("%f", &nackl.sum);


        printf("\tFIO(20 max):");
        //getchar();
        gets(nackl.fio);

        list[i - 1] = &nackl; // записваем в массив

        char c;
        do {
            printf("\nPress 'Enter' to add new record; '1' - to show the list; '0' to exit: ");
            c = (char) getchar();
            getchar();
            if (c == '0') {
                return;
            } else if (c == '1') {
                printf("\n");
                printTableHead();
                for (int j = 0; j < i; j++) {
                    printNucklTable(list[j]);
                }
                printf("\n");
                //getchar();
            }
            //getchar();
        } while (c != '\n');
    }
}

int main() {
    while (true) {
        int tsN = -1;
        printf("\tEnter task number 1-4 (0 to exit) : ");
        scanf("%d", &tsN);

        switch (tsN) {
            case 0:
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
            default:
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}