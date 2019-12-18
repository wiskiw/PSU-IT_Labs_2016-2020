//Дан список записей типа СООБЩЕНИЕ. Упорядочить список по любому из полей в любом направлении.
//Поле и направление выбирает пользователь.
//В функцию сортировки должен передаваться указатель на функцию сравнения двух элементов.

//При реализации использовать указатели на функции и (или) массивы указателей на функции.
//В заданиях с массивами или списками размер и значения элементов вводятся пользователем.

//СООБЩЕНИЕ:
//-	номер устройства (целое трехзначное число)
//-	ID сообщения (целое восьмизначное число в 16-ричной системе);
//-	текст (строка 30 символов);
//-	дата и время отправления (в формате дд.мм.гггг чч:мм).
/*

2
101
1111111A
Hello World Text1
08.11.1995 03:11
102
11111B1A
Text Text2
10.11.2016 11:12
1



 */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

const unsigned int CODE_SUCCESS = 0;
const unsigned int CODE_IC_DEVICE_NUMBER = 1;
const unsigned int CODE_IC_ID = 2;
const unsigned int CODE_IC_TEXT = 3;

const unsigned int CODE_IC_DATE = 4;
const unsigned int CODE_IC_DATE_MINUTE = 10;
const unsigned int CODE_IC_DATE_HOUR = 11;
const unsigned int CODE_IC_DATE_DAY = 12;
const unsigned int CODE_IC_DATE_MONTH = 13;
const unsigned int CODE_IC_DATE_YEAR = 14;

struct Date {
    int day, month, year, hour, minute;
};

struct Message {
    unsigned int deviceNumber;
    unsigned long int id;
    char text[31];
    Date date;
};


Message *messageList;
int listSize;

bool isInt(char c) {
    return c >= '0' && c <= '9';
}

int getInt(char c) {
    return c - '0';
}

int scanMessage(Message *msg) {
    printf("Device number[100-999]: ");
    if (scanf("%d", &msg->deviceNumber) != 1 || msg->deviceNumber < 100 || msg->deviceNumber > 999) {
        return CODE_IC_DEVICE_NUMBER;
    }
    printf("ID [10000000-FFFFFFFF]: ");
    if (scanf("%lx", &msg->id) != 1 || msg->id < 0x10000000 || msg->id > 0xFFFFFFFF) {
        return CODE_IC_ID;
    }

    printf("Text [max30]: ");
    getchar();
    gets(msg->text);


    // Ввод даты/время
    char dateBuffer[17] = "";
    printf("Date [dd.mm.yyyy mm:hh]: ");
    gets(dateBuffer);
    if (strlen(dateBuffer) < 16 || dateBuffer[2] != '.' || dateBuffer[5] != '.' || dateBuffer[13] != ':') {
        return CODE_IC_DATE;
    }

    if (!isInt(dateBuffer[0]) || !isInt(dateBuffer[1])) {
        return CODE_IC_DATE_DAY;
    } else {
        msg->date.day = getInt(dateBuffer[0]) * 10 + getInt(dateBuffer[1]);
    }

    if (!isInt(dateBuffer[3]) || !isInt(dateBuffer[4])) {
        return CODE_IC_DATE_MONTH;
    } else {
        msg->date.month = getInt(dateBuffer[3]) * 10 + getInt(dateBuffer[4]);
    }

    if (!isInt(dateBuffer[6]) || !isInt(dateBuffer[7]) || !isInt(dateBuffer[8]) || !isInt(dateBuffer[9])) {
        return CODE_IC_DATE_YEAR;
    } else {
        msg->date.year = getInt(dateBuffer[6]) * 1000 + getInt(dateBuffer[7]) * 100
                         + getInt(dateBuffer[8]) * 10 + getInt(dateBuffer[9]);
    }

    if (!isInt(dateBuffer[11]) || !isInt(dateBuffer[12])) {
        return CODE_IC_DATE_MINUTE;
    } else {
        msg->date.minute = getInt(dateBuffer[11]) * 10 + getInt(dateBuffer[12]);
    }

    if (!isInt(dateBuffer[14]) || !isInt(dateBuffer[15])) {
        return CODE_IC_DATE_HOUR;
    } else {
        msg->date.hour = getInt(dateBuffer[14]) * 10 + getInt(dateBuffer[15]);
    }

    return CODE_SUCCESS;
}

void printError(int code) {
    switch (code) {
        case CODE_IC_DEVICE_NUMBER:
            printf("Incorrect DEVICE_NUMBER!\n");
            break;
        case CODE_IC_ID:
            printf("Incorrect ID!\n");
            break;
        default:
            printf("Incorrect some else! error code:%d\n", code);
    }
}

void scanList() {
    int code = 0;
    for (int i = 0; i < listSize; i++) {
        Message message;
        system("cls");
        printf("===Message #%d\n", i + 1);
        code = scanMessage(&message);
        if (code != CODE_SUCCESS) {
            printError(code);
            printf("Try again\n");
            i--;
        } else {
            messageList[i] = message;
        }
    }
    system("cls");
}

void printList() {
    printf("==== Messages List [%d] ===\n", listSize);
    for (int i = 0; i < listSize; i++) {
        Message cur = messageList[i];
        printf(" ---- MSG #%d\n", i + 1);
        printf("   deviceNumber: %d\n", cur.deviceNumber);
        printf("   id: '%lX'\n", cur.id);
        printf("   text: '%s'\n", cur.text);
        printf("   date: %02d.%02d.%d %02d:%02d\n", cur.date.day, cur.date.month, cur.date.year, cur.date.minute,
               cur.date.hour);
    }
}


int compareDeviceNumber(Message *msgA, Message *msgB) {
    return msgA->deviceNumber - msgB->deviceNumber;
}

int compareId(Message *msgA, Message *msgB) {
    if (msgA->id == msgB->id) {
        return 0;
    } else if (msgA->id > msgB->id) {
        return 1;
    } else {
        return -1;
    }
}

int compareText(Message *msgA, Message *msgB) {
    return strcmp(msgA->text, msgB->text);
}

int compareDate(Message *msgA, Message *msgB) {
    Date *dateA = &msgA->date;
    Date *dateB = &msgB->date;
    int val = 0;
    val = dateA->year - dateB->year;
    if (val != 0) {
        return val;
    }

    val = dateA->month - dateB->month;
    if (val != 0) {
        return val;
    }

    val = dateA->day - dateB->day;
    if (val != 0) {
        return val;
    }

    val = dateA->hour - dateB->hour;
    if (val != 0) {
        return val;
    }
    return dateA->minute - dateB->minute;
}

void swap(Message *msgA, Message *msgB) {
    Message msgTemp = *msgA;
    *msgA = *msgB;
    *msgB = msgTemp;
}

// Сортировка пузырем (По Убыванию)
void forwardBobbleSort(int (*compare)(Message *, Message *)) {
    for (int i = listSize - 1; i >= 0; i--) {
        for (int j = listSize - 1; j > i; j--) {
            Message *msgA = &messageList[j - 1];
            Message *msgB = &messageList[j];
            if (compare(msgA, msgB) >= 0) {
                swap(msgA, msgB);
            }
        }
    }
}

// Сортировка пузырем (По Возрастания)
void backwardBobbleSort(int (*compare)(Message *, Message *)) {
    for (int i = 0; i < listSize; i++) {
        for (int j = listSize - 1; j > i; j--) {
            Message *msgA = &messageList[j - 1];
            Message *msgB = &messageList[j];
            if (compare(msgA, msgB) <= 0) {
                swap(msgA, msgB);
            }
        }
    }
}


int main() {
    printf("The list size: ");
    scanf("%d", &listSize);
    messageList = (Message *) calloc((size_t) listSize, sizeof(Message));
    scanList();

    int field = 0;
    int (*compare)(Message *, Message *);
    int dir = 0;

    printf("\n ");
    while (1) {
        int tsN = -1;
        printf("\t[1] - print list;\n");
        printf("\t[2] - sort list;\n");
        printf("\t[0] - exit \t\n: ");

        scanf("%d", &tsN);
        getchar();
        switch (tsN) {
            case 0:
                system("cls");
                return 0;
            case 1:
                system("cls");
                printList();
                break;
            case 2:
                system("cls");
                printf("Sort field\n");
                printf("\tdeviceNumber: 1\n");
                printf("\tid          : 2\n");
                printf("\ttext        : 3\n");
                printf("\tdate        : 4\n");
                printf(":");
                scanf("%d", &field);
                switch (field) {
                    case 2:
                        compare = compareId;
                        break;
                    case 3:
                        compare = compareText;
                        break;
                    case 4:
                        compare = compareDate;
                        break;
                    default:
                        compare = compareDeviceNumber;
                        break;
                }

                printf("Sort direction\n");
                printf("\ta->Z: 1\n");
                printf("\tZ->a: 2\n");
                printf(":");
                scanf("%d", &dir);
                switch (dir) {
                    case 1:
                        forwardBobbleSort(compare);
                        break;
                    case 2:
                        backwardBobbleSort(compare);
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


