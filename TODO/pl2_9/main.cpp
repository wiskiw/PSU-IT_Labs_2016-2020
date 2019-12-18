#include <stdio.h>
#include <malloc.h>
#include <string.h>

int cmdSearchA = 0;
int cmdSearchKey = 0;

int iterN = 0;
int searchN = 0;


struct Date {
    int day;
    int month;
    int year;
};

struct Number {
    int numb;
    char name[31];
    Date date;
    char plan[31];
};

int listSize = 0;
Number *list = NULL;

//Формат ввода: Номер ФИО владельца Дата подключения «Тарифный план»
// 1234567 SName FName PName 12.35.9876 "Plan Name"
// cmd: pl2_9 a:binary k:2266448

/*

 1234567 SName FName PName 02.11.9876 "Plan Name A"
 1122334 SNameB FNameA PNameD 22.01.1876 "Plan Name B128"
 3336669 RR. Mr Sam 02.01.2000 "Plan Name Premium"
 1111111 RR. Mr Sam2 02.01.2001 "Plan Name Premium"

 pl2_9 a:binary k:1236547

 pl2_9 a:linear k:1111111


 */

int getStartPos(char line[]) {
    int i = 0;
    for (; line[i] == ' ' && line[i] != '\n'; i++);
    return i;
}

bool isInt(char c) {
    return c >= '0' && c <= '9';
}

int getInt(char c) {
    return c - '0';
}

int readNumber(Number *number, char line[]) {
    char buff[8] = "";
    strncpy(buff, line, 7 + getStartPos(line));

    number->numb = atoi(buff);
    return 0;
}

int readName(Number *number, char line[]) {
    int sPos = 7 + getStartPos(line) + 1;
    int ePos = sPos;
    int spaceN = 0;
    for (; line[ePos] != '\0' && spaceN < 3; ePos++) {
        if (line[ePos] == ' ') {
            spaceN++;
        }
    }
    ePos--;
    if (spaceN < 3 || ePos - sPos > 30) {
        return 1;
    }
    strncpy(number->name, line + sPos, ePos - sPos);
    number->name[ePos - sPos - 1] = '\0';
    return 0;
}

int readDate(Number *number, char line[]) {
    char *c = strchr(line, '"');
    if (c == NULL) {
        return 1;
    }
    int ePos = strlen(line) - strlen(c - 1);
    int sPos = ePos - 10;
    char dateBuffer[11] = "";


    strncpy(dateBuffer, line + sPos, ePos - sPos);
    //printf("date: '%s'\n", dateBuffer);

    if (dateBuffer[2] != '.' || dateBuffer[5] != '.') {
        return 1;
    }

    if (!isInt(dateBuffer[0]) || !isInt(dateBuffer[1])) {
        return 1;
    } else {
        number->date.day = getInt(dateBuffer[0]) * 10 + getInt(dateBuffer[1]);
    }

    if (!isInt(dateBuffer[3]) || !isInt(dateBuffer[4])) {
        return 1;
    } else {
        number->date.month = getInt(dateBuffer[3]) * 10 + getInt(dateBuffer[4]);
    }

    if (!isInt(dateBuffer[6]) || !isInt(dateBuffer[7]) || !isInt(dateBuffer[8]) || !isInt(dateBuffer[9])) {
        return 1;
    } else {
        number->date.year = getInt(dateBuffer[6]) * 1000 + getInt(dateBuffer[7]) * 100
                            + getInt(dateBuffer[8]) * 10 + getInt(dateBuffer[9]);
    }
    return 0;
}

int readPlan(Number *number, char line[]) {
    char *c = strchr(line, '"');
    if (c == NULL) {
        return 1;
    }
    int sPos = strlen(line) - strlen(c) + 1;


    c = strrchr(line, '"');
    if (c == NULL) {
        return 1;
    }
    int ePos = strlen(line) - strlen(c);


    if (ePos - sPos > 30 || ePos - sPos < 1) {
        return 1;
    }
    strncpy(number->plan, line + sPos, ePos - sPos);
    number->plan[ePos - sPos] = '\0';
    return 0;
}

void afterMain();

void printNumber(Number *number) {
    printf("\n-----------------------------\n");
    printf("Numb: '%d'\n", number->numb);
    printf("name: '%s'\n", number->name);
    printf("plan: '%s'\n", number->plan);
    printf("date: '%02d.%02d.%04d'\n", number->date.day, number->date.month, number->date.year);
    printf("-----------------------------\n\n");
}

Number *linearSearch(int key) {
    searchN++;
    for (int i = 0; i < listSize; i++) {
        iterN++;
        if (list[i].numb == key) {
            return &list[i];
        }
    }
    return NULL;
}

void swap(Number *nA, Number *nB) {
    struct Number nTemp = *nA;
    *nA = *nB;
    *nB = nTemp;
}

void minimaxSort() {
    // a0-Z9
    int s = listSize;
    while (s > 0) {
        int maxpos = 0;
        for (int i = 0; i < s; i++) {
            if (list[i].numb > list[maxpos].numb) {
                maxpos = i;
            }
        }
        if (maxpos != s - 1) {
            swap(&list[maxpos], &list[s - 1]);
        }
        s--;
    }
}

int bSearch(int leftB, int rightB, int key) {
    int center = 0;
    while (1) {
        iterN++;
        center = (leftB + rightB) / 2; // поиск серединного индекс
        if (key < list[center].numb) {
            rightB = center - 1;
        } else if (key > list[center].numb) {
            leftB = center + 1;
        } else {
            // если ключ совпал
            return center;
        }
        if (leftB > rightB) {
            return -1;
        }
    }
}


Number *binarySearch(int key) {
    // запуск рекусривной функции бинарного поиска
    searchN++;
    int index = bSearch(0, listSize, key);
    if (index != -1) {
        return &list[index];
    } else {
        return NULL;
    }
}

void processSearchResult(Number *number) {
    if (number == NULL) {
        getchar();
        printf("\n-----------------------------\n");
        printf("Nothing did not found\n");
        printf("-----------------------------\n\n");
    } else {
        printNumber(number);
        getchar();
    }
}


int main(int argc, char **argv) {
    if (argc == 3) {
        printf("------------------------\n");
        printf(" Search settings:\n");
        if (argv[1][2] == 'b') {
            cmdSearchA = 2;
            printf("   Search algorithm: BINARY\n");
        } else if (argv[1][2] == 'l') {
            cmdSearchA = 1;
            printf("   Search algorithm: LINEAR\n");
        }

        cmdSearchKey = atoi(argv[2] + 2);
        if (cmdSearchKey != 0) {
            printf("   Search key: %d\n", cmdSearchKey);
        }
        printf("------------------------\n\n");
    }


    while (1) {
        printf("Enter the numb of numbers: ");
        if (scanf("%d", &listSize)) {
            getchar();
            break;
        } else {
            system("cls");
            printf("Incorrect number numb! Try again. \n");
            //scanf("%s");
            getchar();
        };
    }

    char buffer[256];
    Number newNumber;

    for (int i = 0; i < listSize; i++) {
        list = (Number *) realloc(list, sizeof(Number) * (i + 1));
        printf("\nEnter the number #%d: ", i + 1);
        gets(buffer);

        int callback = 0;
        callback += readNumber(&newNumber, buffer);
        callback += readName(&newNumber, buffer);
        callback += readDate(&newNumber, buffer);
        callback += readPlan(&newNumber, buffer);

        if (callback > 0) {
            printf("Incorrect number format! Try again. \n");
            i--;
        } else {
            list[i] = newNumber;
        }
    }


    if (listSize <= 0) {
        printf("List is empty!\n");
    } else {
        minimaxSort();
        system("cls");
        if (cmdSearchA == 0) {
            afterMain();
        } else {
            Number *number;
            switch (cmdSearchA) {
                case 1:
                    number = linearSearch(cmdSearchKey);
                    processSearchResult(number);
                    break;
                case 2:
                    number = binarySearch(cmdSearchKey);
                    processSearchResult(number);
                    break;
            }
        }
    }

    system("pause");
    return 0;
}

void afterMain() {
    while (1) {
        printf("Select option\n");
        printf("\tlinear search - 1\n");
        printf("\tbinary search - 2\n ");
        printf("\tshow stats - 3\n: ");
        char searchTypeBuffer[2] = "";
        searchTypeBuffer[0] = '\0';
        gets(searchTypeBuffer);
        if (searchTypeBuffer[0] == '\0' || searchTypeBuffer[0] == '\n') {
            return;
        } else {
            system("cls");
        }
        int searchType = atoi(searchTypeBuffer);
        if (searchType < 1 || searchType > 3) {
            printf("Incorrect input!\n");
            continue;
        }
        int keyNumb = 0;
        if (searchType != 3) {
            printf("Key(phone number): ");
            if (scanf("%d", &keyNumb) != 1 || keyNumb < 1000000 || keyNumb > 9999999) {
                printf("Incorrect number!\n");
                getchar();
                continue;
            }
        }


        Number *number = NULL;
        switch (searchType) {
            case 1:
                number = linearSearch(keyNumb);
                processSearchResult(number);
                break;
            case 2:
                number = binarySearch(keyNumb);
                processSearchResult(number);
                break;
            case 3:
                // stats
                if (searchN == 0) {
                    printf("Now stats yet\n");
                } else {
                    float f = (float) iterN / searchN;
                    //printf("iterN: %d\n", iterN);
                    //printf("searchN: %d\n", searchN);
                    printf("Average iteration each search: %g\n", f);
                }
                break;
        }

    }
}