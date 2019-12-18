#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <mem.h>

struct Data {
    short unsigned int day;
    //unsigned int month;
    unsigned month:4; // 0-15
    unsigned int year;
};

struct MSG {
    unsigned int address;
    char message[51];
    struct Data date;
};

struct MSG *msgList;
unsigned int size;

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

void scanList() {
    printf("Enter the list size: ");
    while (1) {
        if (scanf("%d", &size) != 1) {
            printf("Incorrect input! Try again: \n");
        } else {
            break;
        }
    }
    getchar();

    printf("Message format: address[9999] message[max:50] date[dd.mm.yyyy] \n\n");
    for (int i = 0; i < size; i++) {
        msgList = realloc(msgList, (i + 1) * sizeof(struct MSG));
        struct MSG newMSg;
        printf("New message #%d :", (i + 1));
        char inputStr[256];
        gets(inputStr);
        if (inputStr[0] == '\0') {
            printf("String cannot be empty! Try again: \n");
            i--;
            continue;
        }

        // Пвроверка на некорректные символы в строке
        if (isCorrectInput(inputStr) != 0) {
            i--;
            continue;
        }

        // парсинг адреса
        if (parseAddress(inputStr, &newMSg) != 0) {
            i--;
            continue;
        }

        // парсинг сообщения
        if (parseMessage(inputStr, &newMSg) != 0) {
            i--;
            continue;
        }

        // парсинг даты
        if (parseDate(inputStr, &newMSg) != 0) {
            i--;
            continue;
        }

        msgList[i] = newMSg;
    }


}

void printList() {
    if (size == 0) {
        printf("List is empty!\n");
        return;
    }
    printf(" ==== Size: %d ===\n", size);
    for (int i = 0; i < size; i++) {
        struct MSG cur = msgList[i];
        printf("\tMSG #%d\n", i + 1);
        printf("address: %d\n", cur.address);
        printf("message: '%s'\n", cur.message);
        printf("date: %d.%d.%d\n", cur.date.day, cur.date.month, cur.date.year);
    }
}


int compareMessages(struct MSG *msgA, struct MSG *msgB) {
    if (msgA->address == msgB->address) {
        /*
        strcmp(a,b)
           >0 : a>b
           <0 : a<b
           =0 : a=b
        */
        return strcmp(msgA->message, msgB->message);
    } else {
        return msgA->address - msgB->address;
    }
}

void swap(struct MSG *msgA, struct MSG *msgB) {
    struct MSG msgTemp = *msgA;
    *msgA = *msgB;
    *msgB = msgTemp;
}

// Сортировка Хоара (с рекурсивным вызовом) (По убыванию)
void hoare(int first, int last) {
    int i = first, j = last;
    struct MSG *x = &msgList[(first + last) / 2];
    do {
        while (compareMessages(&msgList[i], x) > 0) i++;
        while (compareMessages(&msgList[j], x) < 0) j--;

        if (i <= j) {
            if (compareMessages(&msgList[i], &msgList[j]) < 0) {
                swap(&msgList[i], &msgList[j]);
            }
            i++;
            j--;
        }
    } while (i <= j);
    if (i < last) hoare(i, last);
    if (first < j) hoare(first, j);
}

void shortList() {
    hoare(0, size - 1);
}

int main() {
    msgList = NULL;

    scanList();

    printList();
    shortList();

    printList();

    system("pause");
    return 0;
}