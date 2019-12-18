#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mem.h>

/*
 1
 111 "A text" 01.09.2000
 1
 333 "C text" 01.05.2016
 1
 222 "D text" 01.05.2008
 1
 222 "B text" 01.06.2016
 2

 */


typedef struct Data {
    short unsigned int day;
    //unsigned int month;
    unsigned month:4; // 0-15
    unsigned int year;
} DATA;

struct MSG {
    unsigned int address;
    char message[51];
    struct Data date;
};

struct MSG *msgList;
unsigned int listSize;
unsigned int maxListSize;

bool isCorrectChar(char c) {
    int bellow = 32;
    int upper = 122;
    if (c < bellow || c > upper) {
        printf("Incorrect character in string! Try again.\n");
        return false;
    }
    return true;
}


int isCorrectInput(char *inputStr) {
    int nQuotes = 0;
    int correct = true;
    for (int j = 0; inputStr[j] != '\0'; j++) {
        if (inputStr[j] == '"') nQuotes++;
        if (correct && !isCorrectChar(inputStr[j])) {
            correct = false;
        }
    }
    if (!correct) {
        //printf("Incorrect character in the string! Try again.\n");
        return 1;
    }
    if (!(nQuotes == 0 || nQuotes == 2)) {
        printf("Incorrect quotes numb in the string! Try again.\n");
        return 2;
    }
    return 0;
}

int parseAddress(char *input, struct MSG *msg) {
    char tempStr[strlen(input)];
    strcpy(tempStr, input);

    char *addressStr = strtok(tempStr, " ");
    int value = atoi(addressStr);
    if (value == 0) {
        printf("Address contains illegal characters! Try again.\n");
        return 3;
    }
    if (value > 9999) {
        printf("Address cannot be more than 9999! Try again.\n");
        return 1;
    }
    if (value < 1) {
        printf("Address cannot consist negative value! Try again.\n");
        return 2;
    }
    msg->address = (unsigned int) value;
    return 0;
}

int parseMessage(char *input, struct MSG *msg) {
    char tempStr[strlen(input)];
    strcpy(tempStr, input);

    char *messageString = NULL;

    // проверяем наличие двойных кавычек
    if (strrchr(tempStr, '"') != NULL) {
        strtok(tempStr, "\"");
        messageString = strtok(NULL, "\"");
    } else {
        strtok(tempStr, " ");
        messageString = strtok(NULL, " ");
    }
    int len = strlen(messageString);
    if (len < 1) {
        printf("Message is too short! Try again.\n");
        return 1;
    }
    if (len > 50) {
        printf("Message is too long! Try again.\n");
        return 2;
    }
    strcpy(msg->message, messageString);
    return 0;
}

int getInt(char c) {
    return c - '0';
}

int parseDate(char *input, struct MSG *msg) {
    char tempStr[strlen(input)];
    strcpy(tempStr, input);

    // убираем пробелы в конце строки
    for (int i = strlen(tempStr) - 1; i >= 0; i--) {
        if (tempStr[i] == ' ') {
            tempStr[i] = '\0';
        } else {
            break;
        }
    }

    // выбираем дату в отдельную строку
    char dateStr[11] = "";
    int dotNumb = 0;
    for (int j = 0; j < 10; j++) {
        int rootIndex = strlen(tempStr) - 10 + j;
        char c = tempStr[rootIndex];
        if ((c >= '0' && c <= '9') || rootIndex >= 0) {
            dateStr[j] = c;
            if (dateStr[j] == '.') {
                dotNumb++;
            }
        } else {
            printf("Incorrect structure format! Try again.\n");
            return 1;

        }
    }
    if (dotNumb != 2) {
        printf("Incorrect date format! Try again.\n");
        return 2;
    }

    int tempVar;
    tempVar = getInt(dateStr[0]) * 10 + getInt(dateStr[1]);
    if (tempVar < 1 || tempVar > 31) {
        printf("Incorrect date format! Try again.\n");
        return 3;
    } else {
        msg->date.day = (unsigned short) tempVar;
    }

    tempVar = getInt(dateStr[3]) * 10 + getInt(dateStr[4]);
    if (tempVar < 1 || tempVar > 12) {
        printf("Incorrect date format! Try again.\n");
        return 3;
    } else {
        msg->date.month = (unsigned short) tempVar;
    }

    tempVar = getInt(dateStr[6]) * 1000 + getInt(dateStr[7]) * 100 + getInt(dateStr[8]) * 10 + getInt(dateStr[9]);
    if (tempVar < 1 || tempVar > 9999) {
        printf("Incorrect date format! Try again.\n");
        return 3;
    } else {
        msg->date.year = (unsigned short) tempVar;
    }

    //printf("\ndate: %d.%d.%d\n", msg->date.day, msg->date.month, msg->date.year);
    return 0;
}

const int CODE_SUCCESS = 0;
const int CODE_OUT_OF_BORDER_INDEX = 1;
const int CODE_FULL_LIST = 2;

int scanMsg() {
    if (listSize + 1 > maxListSize) {
        printf("List is full!\n");
        return CODE_FULL_LIST;
    }
    printf("Message format: address[9999] message[max:50] date[dd.mm.yyyy] \n");
    printf("New message #%d :", listSize + 1);

    struct MSG newMSg;

    char inputStr[256];
    gets(inputStr);
    if (inputStr[0] == '\0') {
        printf("String cannot be empty! Try again: \n");
        return scanMsg();
    }

    // Пвроверка на некорректные символы в строке
    if (isCorrectInput(inputStr) != 0) {
        return scanMsg();
    }

    // парсинг адреса
    if (parseAddress(inputStr, &newMSg) != 0) {
        return scanMsg();
    }

    // парсинг сообщения
    if (parseMessage(inputStr, &newMSg) != 0) {
        return scanMsg();
    }

    // парсинг даты
    if (parseDate(inputStr, &newMSg) != 0) {
        return scanMsg();
    }


    msgList = realloc(msgList, (listSize + 1) * sizeof(struct MSG));
    msgList[listSize] = newMSg;
    listSize++;
    return CODE_SUCCESS;
}

void printList() {
    printf("==== Messages List [%d/%d] ===\n", listSize, maxListSize);
    for (int i = 0; i < listSize; i++) {
        struct MSG cur = msgList[i];
        printf(" ---- MSG #%d\n", i + 1);
        printf("   address: %d\n", cur.address);
        printf("   message: '%s'\n", cur.message);
        printf("   date: %d.%d.%d\n", cur.date.day, cur.date.month, cur.date.year);
    }
}

int hideItem(int index, int offset) {
    // сдвигает все msg на offset
    if (index + offset > listSize) {
        return CODE_OUT_OF_BORDER_INDEX;
    }

    //msgList + index = msgList + index + offset;
    if (index >= 0) {
        for (int i = index; i + offset < listSize; i++) {
            msgList[i] = msgList[i + offset];
        }
    }
    // в результате сдвига в конце списка остаются два равных элемента, удалаем последний
    free(&msgList[listSize - 1]);
    listSize--;
    return CODE_SUCCESS;
}

int removeMsg(int index) {
    if (index > listSize) {
        printf("Index is out of border!\n");
        return CODE_OUT_OF_BORDER_INDEX;
    }

    hideItem(index, 1);
    printf("Msg has been removed!\n");
    return CODE_SUCCESS;
}

int compareDate(DATA *dateA, DATA *dateB) {
    //return dateA->year - dateB->year;
    int year = dateA->year - dateB->year;
    if (year != 0) {
        return year;
    }

    int month = dateA->month - dateB->month;
    if (month != 0) {
        return month;
    } else {
        return dateA->day - dateB->day;
    }
}

int compareMessages(struct MSG *msgA, struct MSG *msgB, int field) {
    int res = 0;
    switch (field) {
        case 1:
            // address
            res = msgA->address - msgB->address;
            break;
        case 2:
            // text
            res = strcmp(msgA->message, msgB->message);
            break;
        default:
            // date
            res = compareDate(&msgA->date, &msgB->date);
            break;
    }
    if (res == 0 && field < 3) {
        res = compareMessages(msgA, msgB, field + 1);
    }
    return res;
}

void swap(struct MSG *msgA, struct MSG *msgB) {
    struct MSG msgTemp = *msgA;
    *msgA = *msgB;
    *msgB = msgTemp;
}

// Сортировка пузырем (По Возрастания)
void backwardBobbleSort(int sortField) {
    for (int i = 0; i < listSize; i++) {
        for (int j = listSize - 1; j > i; j--) {
            struct MSG *msgA = &msgList[j - 1];
            struct MSG *msgB = &msgList[j];
            if (compareMessages(msgA, msgB, sortField) <= 0) {
                swap(msgA, msgB);
            }
        }
    }
}

// Сортировка пузырем (По Убыванию)
void forwardBobbleSort(int sortField) {
    for (int i = listSize - 1; i >= 0; i--) {
        for (int j = listSize - 1; j > i; j--) {
            struct MSG *msgA = &msgList[j - 1];
            struct MSG *msgB = &msgList[j];
            if (compareMessages(msgA, msgB, sortField) >= 0) {
                swap(msgA, msgB);
            }
        }
    }
}

int main() {
    printf("Max list size: ");
    scanf("%d", &maxListSize);
    printf("\n ");
    while (1) {
        int tsN = -1;
        printf("\t[1] - add message;\n");
        printf("\t[2] - print list;\n");
        printf("\t[3] - remove message;\n");
        printf("\t[4] - short list;\n");
        printf("\t[0] - exit \t\n: ");

        scanf("%d", &tsN);
        getchar();
        int iVarA = 0;
        int iVarB = 0;
        switch (tsN) {
            case 0:
                system("cls");
                return 0;
            case 1:
                system("cls");
                scanMsg();
                break;
            case 2:
                system("cls");
                printList();
                break;
            case 3:
                system("cls");
                printf("Index to remove: ");
                scanf("%d", &iVarA);
                removeMsg(iVarA);
                break;
            case 4:
                system("cls");

                printf("Sort field\n");
                printf("\taddress: 1\n");
                printf("\tmessage: 2\n");
                printf("\tdate   : 3\n");
                printf(":");
                scanf("%d", &iVarA);

                printf("Sort direction\n");
                printf("\ta->Z: 1\n");
                printf("\tZ->a: 2\n");
                printf(":");
                scanf("%d", &iVarB);
                switch (iVarB) {
                    case 1:
                        forwardBobbleSort(iVarA);
                        break;
                    case 2:
                        backwardBobbleSort(iVarA);
                        break;
                    default:
                        printf("Unknown direction!\n");
                }
                break;
            default:
                system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}