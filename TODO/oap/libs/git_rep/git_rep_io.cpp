//
// Created by WiskiW on 29.04.2017.
//

#include <limits.h>
#include <console_io_lib/console_io_lib.h>
#include <date/date.cpp>
#include <conio.h>
#include <fstream>
#include "git_rep_io.h"

const char WARNING_INCORRECT_DATE[] = "Incorrect date format, try again!";
const char WARNING_INCORRECT_DATE_DAY[] = "Incorrect date day, try again!";
const char WARNING_INCORRECT_DATE_MONTH[] = "Incorrect date month, try again!";
const char WARNING_TOO_EARLY_DATE[] = "Date cannot be early than %s!";
const char WARNING_EMPTY_STRING[] = "The string cannot be empty, try again!";
const char WARNING_STRING_TOO_SHORT[] = "The string cannot be shorter than %d!";

const char WARNING_INT_VALUE_TOO_BIG[] = "The value cannot be bigger than %d!";
const char WARNING_INT_VALUE_TOO_SMALL[] = "The value cannot be smaller than %d!";

const char WARNING_FLOAT_VALUE_TOO_BIG[] = "The value cannot be bigger than %g!";
const char WARNING_FLOAT_VALUE_TOO_SMALL[] = "The value cannot be smaller than %g!";

const bool ENABLE_BEEP = true;
const int WARNING_MSG_TIME = 1000;

const Color msgColor = LightGray;
const Color warningColor = LightMagenta;

void readDate(Date *date, const char *msg, bool allowEmpty);

void mBeep() {
    if (ENABLE_BEEP) {
        beep();
    }
}

int keyVerification(int c) {
    // проверка символа на корректность
    if ((c >= 32 && c <= 126) || c == VK_BACK || c == VK_RETURN) {
        return c;
    }
    return 0;
}

int getInt(int c) {
    if (c == '\0') {
        return 0;
    }
    return c - '0';
}

bool isDot(int key) {
    return key == VK_OEM_PERIOD || key == VK_OEM_COMMA || key == VK_SPACE || key == '.' || key == ',';
}

bool goAfterDot(int startPosX, int index) {
    switch (index) {
        case 2:
            setCursorTo(startPosX + 3, -1);
            return true;
        case 4:
            setCursorTo(startPosX + 6, -1);
            return true;
        default:
            return false;
    }
}

void readDate(Date *date, const char *msg, Date minDate, bool allowEmpty) {
    int startPosX = 0; // = длинна начального сообщения
    if (msg != nullptr) {
        printf(msgColor, msg);
        startPosX = strlen(msg);
    }

    char buffer[9] = "";  // формат хранения даты 11.22.3344 : "11223344"

    // отрисовка шаблона
    setCursorTo(startPosX, -1);
    printf("__.__.____");
    setCursorTo(startPosX, -1);

    int key = 0;
    int index = 0;

    while (true) {
        if (_kbhit()) {
            key = _getch();
            if (keyVerification(key) == 0) {
                continue;
            }
            if (key == VK_RETURN) {
                // выход, если нажат ENTER
                break;
            }
            switch (key) {
                case VK_BACK: // BACKSPACE
                    index = strlen(buffer);
                    if (index == 0) { // еси уперлись в лувую границу экрана
                        //mBeep();
                        continue;
                    }
                    buffer[index - 1] = '\0'; // едаляем символ с буфера

                    // по необходимости установка курсора перед точкой
                    switch (index) {
                        case 2:
                            setCursorTo(startPosX + 2, -1);
                            break;
                        case 4:
                            setCursorTo(startPosX + 5, -1);
                            break;
                    }
                    removeC(1, '_'); // удаление одного символа из консоли
                    break;
                default:
                    index = strlen(buffer);
                    if (index >= 8) { // проверка превышения длинны
                        mBeep();
                    } else if (isDot(key)) {
                        // Если нажата точка
                        if (!goAfterDot(startPosX, index)) {
                            // если точка нажата не в нужный момент - БИП!
                            mBeep();
                        }
                    } else {
                        if (key < '0' || key > '9') { // Проверка валидности клавиши
                            mBeep();
                        } else {
                            goAfterDot(startPosX, index); // перемещение курсора вправо
                            buffer[index] = (char) key; // сохранение нажатой клавиши
                            printf("%c", key); // отрисовка нажатой клавиши
                        }

                    }
            }
        }
    }

    // Форматирование года, если в нем менее 4 цифр: 15__ -> 0015
    int len = strlen(buffer);
    if (len > 4 && len < 8) {
        int spaceN = 8 - len; // кол-во оставшихся '_'
        setCursorTo(startPosX + 6, -1);
        for (int j = 0; j < spaceN; j++) {
            printf("0");
        }
        for (int k = 0; k < 4 - spaceN; k++) {
            printf("%c", buffer[k + 4]);
        }
    }

    // соранение значений в структуру
    date->day = getInt(buffer[0]) * 10 + getInt(buffer[1]);
    date->month = getInt(buffer[2]) * 10 + getInt(buffer[3]);
    date->year = getInt(buffer[4]) * 1000 + getInt(buffer[5]) * 100 +
                 getInt(buffer[6]) * 10 + getInt(buffer[7]);


    if (compareDate(*date, minDate) < 0) {
        printf("\n");

        char strDate[11] = "";
        printf(warningColor, WARNING_TOO_EARLY_DATE, dateToString(strDate, minDate));

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX + 15, getCursorPosition().Y - 1); // перемещение курсора вверх и на 15 вправо
        clearLine(); // очистка верхней строки
        readDate(date, msg, minDate, allowEmpty); // рекурсивный вызов
        return;
    }


    int res = isDateCorrect(*date);
    char *warMsg = nullptr;
    switch (res) {
        case INCORRECT_DAY:
            warMsg = (char *) WARNING_INCORRECT_DATE_DAY;
            break;
        case INCORRECT_MONTH:
            warMsg = (char *) WARNING_INCORRECT_DATE_MONTH;
            break;
        default:
            break;
    }
    if (res != 0) {
        printf("\n");
        printf(warningColor, warMsg);

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX + 15, getCursorPosition().Y - 1); // перемещение курсора вверх и на 15 вправо
        clearLine(); // очистка верхней строки
        readDate(date, msg, allowEmpty); // рекурсивный вызов
        return;
    }


    if (allowEmpty) { // выходим без проверки, если разрешена пустая структура
        printf("\n");
        return;
    }

    // Проверка введенных данных
    if (date->day == 0 || date->month == 0 || date->year == 0) {
        printf("\n");
        printf(warningColor, WARNING_INCORRECT_DATE);

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX + 15, getCursorPosition().Y - 1); // перемещение курсора вверх и на 15 вправо
        clearLine(); // очистка верхней строки
        readDate(date, msg, allowEmpty); // рекурсивный вызов
        return;
    }
    printf("\n");
}

void readDate(Date *date, const char *msg, bool allowEmpty) {
    Date nullDate;
    nullDate.day = 0;
    nullDate.month = 0;
    nullDate.year = 0;
    readDate(date, msg, nullDate, allowEmpty);
}

void readString(char *buffer, const char *msg, int minLength, int maxLength, bool allowEmpty) {
    int startPosX = 0; // = длинна начального сообщения
    if (msg != nullptr) {
        printf(msgColor, msg);
        startPosX = strlen(msg);
    }

    memset(buffer, '\0', maxLength); // обнуление буфера

    int key = 0;
    while (true) {
        if (_kbhit()) {
            key = _getch();
            if (keyVerification(key) == 0) {
                continue;
            }

            if (key == VK_RETURN) {
                break;
            }
            switch (key) {
                case VK_BACK:
                    if (strlen(buffer) == 0) {
                        //mBeep();
                        continue;
                    }
                    removeC(1);
                    buffer[strlen(buffer) - 1] = '\0';
                    break;
                default:
                    if (strlen(buffer) >= maxLength) {
                        mBeep();
                    } else {
                        printf("%c", key);
                        buffer[strlen(buffer)] = (char) key;
                    }
            }
        }
    }

    // Проверка введенных данных
    printf("\n");
    if (!allowEmpty && strlen(buffer) == 0) {
        printf(warningColor, WARNING_EMPTY_STRING);

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX, getCursorPosition().Y - 1); // перемещение курсора вверх и вправо
        clearLine(); // очистка верхней строки
        readString(buffer, msg, minLength, maxLength, allowEmpty); // рекурсивный вызов
        return;
    }

    if (strlen(buffer) < minLength) {
        printf(warningColor, WARNING_STRING_TOO_SHORT, minLength);

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX + strlen(buffer), getCursorPosition().Y - 1); // перемещение курсора вверх и вправо
        clearLine(); // очистка верхней строки
        readString(buffer, msg, minLength, maxLength, allowEmpty); // рекурсивный вызов
        return;
    }
}

void readUnsignedInt(int *intValue, const char *msg, int minValue, int maxValue) {
    int startPosX = 0; // = длинна начального сообщения
    if (msg != nullptr) {
        printf(msgColor, msg);
        startPosX = strlen(msg);
    }
    setCursorTo(startPosX, -1);
    int maxNumbCount = 0; // макцимальное кол-во цифр при вводе
    int temp = maxValue;
    while (temp != 0) {
        maxNumbCount++;
        temp = temp / 10;
        printf("_");
    }
    setCursorTo(startPosX, -1);


    char strBuffer[12];
    memset(strBuffer, '\0', 12); // обнуление буфера

    int key = 0;
    while (true) {
        if (_kbhit()) {
            key = _getch();
            if (keyVerification(key) == 0) {
                continue;
            }
            if (key == VK_RETURN) {
                break;
            }
            switch (key) {
                case VK_BACK:
                    if (strlen(strBuffer) == 0) {
                        continue;
                    }
                    removeC(1, '_');
                    strBuffer[strlen(strBuffer) - 1] = '\0';
                    break;
                default:
                    if (strlen(strBuffer) >= maxNumbCount) {
                        mBeep();
                    } else {
                        if (key < '0' || key > '9') {
                            mBeep();
                        } else {
                            printf("%c", key);
                            strBuffer[strlen(strBuffer)] = (char) key;
                        }
                    }
            }
        }
    }
    *intValue = atol(strBuffer);
    int valueNumbCount = strlen(strBuffer); // число введенных цифр

    if (valueNumbCount < maxNumbCount) { // очистка лишних '_'
        setCursorTo(startPosX + valueNumbCount, -1);
        for (int i = 0; i < maxNumbCount - valueNumbCount; i++) {
            printf(" ");
        }
    }

    if (*intValue > maxValue) { // проверка превышения значения
        printf("\n");
        printf(warningColor, WARNING_INT_VALUE_TOO_BIG, maxValue);

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX, getCursorPosition().Y - 1); // перемещение курсора вверх и вправо
        clearLine(); // очистка верхней строки
        readUnsignedInt(intValue, msg, minValue, maxValue); // рекурсивный вызов
        return;
    }

    if (*intValue < minValue) { // проверка превышения значения
        printf("\n");
        printf(warningColor, WARNING_INT_VALUE_TOO_SMALL, minValue);

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX, getCursorPosition().Y - 1); // перемещение курсора вверх и вправо
        clearLine(); // очистка верхней строки
        readUnsignedInt(intValue, msg, minValue, maxValue); // рекурсивный вызов
        return;
    }

    printf("\n");

}

void readUnsignedFloat(float *floatValueBuffer, const char *msg, float minValue, float maxValue) {
    int startPosX = 0; // = длинна начального сообщения
    if (msg != nullptr) {
        printf(msgColor, msg);
        startPosX = strlen(msg);
    }
    int maxNumbCount = 0; // макцимальное кол-во цифр при вводе
    float temp = maxValue;
    while ((int) temp != 0) {
        maxNumbCount++;
        temp = temp / 10;
        printf("_");
    }
    maxNumbCount += 3; // + .__
    printf(".__");
    setCursorTo(startPosX, -1);


    char strBuffer[12];
    memset(strBuffer, '\0', 12); // обнуление буфера

    int key = 0;
    int index = 0;
    while (true) {
        if (_kbhit()) {
            key = _getch();
            if (keyVerification(key) == 0) {
                continue;
            }
            if (key == VK_RETURN) {
                break;
            }
            switch (key) {
                case VK_BACK:
                    index = strlen(strBuffer);
                    if (index == 0) {
                        continue;
                    }
                    if (index == maxNumbCount - 2) {
                        setCursorTo(startPosX + maxNumbCount - 3, -1);
                        strBuffer[index - 1] = '\0';
                    }
                    removeC(1, '_');
                    strBuffer[strlen(strBuffer) - 1] = '\0';
                    break;
                default:
                    if (strlen(strBuffer) >= maxNumbCount) {
                        mBeep();
                    } else {
                        index = strlen(strBuffer);
                        if (index == maxNumbCount - 3) {
                            if (isDot(key)) {
                                strBuffer[maxNumbCount - 3] = '.';
                                setCursorTo(getCursorPosition().X + 1, -1);
                            } else if (key >= '0' || key <= '9') {
                                strBuffer[maxNumbCount - 3] = '.';
                                strBuffer[index + 1] = (char) key;
                                setCursorTo(getCursorPosition().X + 1, -1);
                                printf("%c", key);
                            } else {
                                mBeep();
                            }
                        } else if (key < '0' || key > '9') {
                            mBeep();
                        } else {
                            printf("%c", key);
                            strBuffer[strlen(strBuffer)] = (char) key;
                        }
                    }
            }
        }
    }
    *floatValueBuffer = ((float) atof(strBuffer));
    int valueNumbCount = strlen(strBuffer); // число введенных символов

    if (valueNumbCount < maxNumbCount) { // очистка лишних '_'
        int diff = maxNumbCount - valueNumbCount;
        if (diff == 2 || diff == 3) {
            setCursorTo(startPosX + maxNumbCount - 2, -1);
            printf("0 ");
        } else {
            setCursorTo(startPosX + valueNumbCount, -1);
            for (int i = 0; i < diff; i++) {
                printf(" ");
            }
        }
    }

    if (*floatValueBuffer > maxValue) { // проверка превышения значения
        printf("\n");
        printf(warningColor, WARNING_FLOAT_VALUE_TOO_BIG, maxValue);

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX, getCursorPosition().Y - 1); // перемещение курсора вверх и вправо
        clearLine(); // очистка верхней строки
        readUnsignedFloat(floatValueBuffer, msg, minValue, maxValue); // рекурсивный вызов
        return;
    }

    if (*floatValueBuffer < minValue) { // проверка превышения значения
        printf("\n");
        printf(warningColor, WARNING_FLOAT_VALUE_TOO_SMALL, minValue);

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX, getCursorPosition().Y - 1); // перемещение курсора вверх и вправо
        clearLine(); // очистка верхней строки
        readUnsignedFloat(floatValueBuffer, msg, minValue, maxValue); // рекурсивный вызов
        return;
    }


    printf("\n");


}

void scanGitRep(GitRep *gitRep) {
    readString(gitRep->name, "Rep. name: ", 3, 35, false);
    readString(gitRep->pl, "Programing language: ", 0, 35, false);
    readString(gitRep->author, "Rep. author: ", 3, 35, false);
    readUnsignedFloat(&gitRep->rate, "Rep. rate: ", -1, 5);
    readUnsignedInt(&gitRep->commitNumb, "Number of commits: ", -1, INT_MAX);
    readUnsignedInt(&gitRep->errorNumb, "Number of errors: ", -1, INT_MAX);
    readUnsignedInt(&gitRep->fixErrorNumb, "Number of fixed errors: ", -1, INT_MAX);
    readUnsignedInt(&gitRep->branchNumb, "Number of branches: ", -1, INT_MAX);
    readDate(&gitRep->createDate, "Create date: ", false);
    readDate(&gitRep->editDate, "Edit date: ", gitRep->createDate, false);
}


void printGitRep(GitRep gitRep) {
    printf("\nRep. name: %s\n", gitRep.name);
    printf("Programing language: %s\n", gitRep.pl);
    printf("Rep. author: %s\n", gitRep.author);
    printf("Rep. rate: %g\n", gitRep.rate);
    printf("Number of commits: %d\n", gitRep.commitNumb);
    printf("Number of errors: %d\n", gitRep.errorNumb);
    printf("Number of fixed errors: %d\n", gitRep.fixErrorNumb);
    printf("Number of branches: %d\n", gitRep.branchNumb);

    char strDate[11] = "";
    printf("Create date: %s\n", dateToString(strDate, gitRep.createDate));
    printf("Edit date: %s\n", dateToString(strDate, gitRep.editDate));
}


void printGitRepList(GitRep *gitRepList, int gitRepNumb) {
    if (gitRepNumb == 0) {
        printf("The list is empty.\n");
        return;
    }

    // TODO Finish printGitRepList();
    printf(LightGray, "\t Array [%d]: \n", gitRepNumb);
    printf("%-15s     ", "NAME:");
    printf("%-10s     ", "SIZE:");
    printf("%-10s     ", "PRISE:");
    printf("\n");


    for (int i = 0; i < gitRepNumb; i++) {
        GitRep rep = gitRepList[i];
        printf("%15s     ", rep.name);
        printf("\n");
    }


}


void saveToFile(std::ofstream &dbFile, GitRep gitRep) {
    dbFile << gitRep.name << '\n';
    dbFile << gitRep.pl << '\n';
    dbFile << gitRep.author << '\n';
    dbFile << gitRep.rate << '\n';
    dbFile << gitRep.commitNumb << '\n';
    dbFile << gitRep.errorNumb << '\n';
    dbFile << gitRep.fixErrorNumb << '\n';
    dbFile << gitRep.branchNumb << '\n';
    dbFile << '\t' << gitRep.createDate.day << '\n';
    dbFile << gitRep.createDate.month << '\n';
    dbFile << gitRep.createDate.year << '\n';
    dbFile << '\t' << gitRep.editDate.day << '\n';
    dbFile << gitRep.editDate.month << '\n';
    dbFile << gitRep.editDate.year << '\n' << '\n';
}

