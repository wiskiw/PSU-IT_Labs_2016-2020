#include <limits.h>
#include <conio.h>
#include <fstream>
#include <git_rep/date/date.cpp>
#include "../../codes.h"
#include "../../preferences.h"
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

const Color warningColor = LightMagenta;

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

void readDate(Date *date, const char *msg, const Date *defaultValue, Date *minDate, bool allowEmpty) {
    int startPosX = 0; // = длинна начального сообщения
    if (msg != nullptr) {
        printf(MSG_COLOR, msg);
        startPosX = strlen(msg);
    }

    char buffer[9] = "";  // формат хранения даты 11.22.3344 : "11223344"

    if (defaultValue != NULL) {
        char tintBuff[11] = "";
        dateToString(tintBuff, *defaultValue);
        printf(INPUT_COLOR, tintBuff);
        // день
        buffer[0] = tintBuff[0];
        buffer[1] = tintBuff[1];
        // месяц
        buffer[2] = tintBuff[3];
        buffer[3] = tintBuff[4];
        // год
        buffer[4] = tintBuff[6];
        buffer[5] = tintBuff[7];
        buffer[6] = tintBuff[8];
        buffer[7] = tintBuff[9];
    } else {
        // отрисовка шаблона
        setCursorTo(startPosX, -1);
        printf("__.__.____");
        setCursorTo(startPosX, -1);
    }

    int key = 0;
    int index = 0;

    while (true) {
        if (_kbhit()) {
            key = _getch();
            if (keyVerification(key) == 0) {
                continue;
            }
            if (key == VK_RETURN) {
                if (strlen(buffer) < 5) {
                    mBeep();
                } else {
                    break;
                }
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
                            printf(INPUT_COLOR, "%c", key); // отрисовка нажатой клавиши
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


    if (minDate != NULL && compareDate(*date, *minDate) < 0) {
        printf("\n");

        char strDate[11] = "";
        printf(warningColor, WARNING_TOO_EARLY_DATE, dateToString(strDate, *minDate));

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX + 15, getCursorPosition().Y - 1); // перемещение курсора вверх и на 15 вправо
        clearLine(); // очистка верхней строки
        readDate(date, msg, defaultValue, minDate, allowEmpty); // рекурсивный вызов
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
        readDate(date, msg, defaultValue, minDate, allowEmpty); // рекурсивный вызов
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
        readDate(date, msg, defaultValue, minDate, allowEmpty); // рекурсивный вызов
        return;
    }
    printf("\n");
}

void readString(char *buffer, const char *msg, const char *defaultValue, int minLength, int maxLength, bool allowEmpty) {
    int startPosX = 0; // = длинна начального сообщения
    maxLength++;
    if (msg != nullptr) {
        printf(MSG_COLOR, msg);
        startPosX = strlen(msg);

    }

    if (defaultValue != NULL) {
        char tintMsg[strlen(defaultValue)]; // переменная соде
        strcpy(tintMsg, defaultValue);
        memset(buffer, '\0', maxLength); // обнуление буфера
        // Отрисовка текста поумолчанию
        strcpy(buffer, tintMsg);
        printf(INPUT_COLOR, tintMsg);
    } else {
        memset(buffer, '\0', maxLength); // обнуление буфера

    }

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
                    if (strlen(buffer) >= maxLength - 1) {
                        mBeep();
                    } else {
                        printf(INPUT_COLOR, "%c", key);
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
        readString(buffer, msg, defaultValue, minLength, maxLength, allowEmpty); // рекурсивный вызов
        return;
    }

    if (strlen(buffer) < minLength) {
        printf(warningColor, WARNING_STRING_TOO_SHORT, minLength);

        Sleep(WARNING_MSG_TIME);
        while (kbhit())getch(); // очистка возможно введенных символов во время сна

        clearLine(); // очистка строки с warning_msg
        setCursorTo(startPosX + strlen(buffer), getCursorPosition().Y - 1); // перемещение курсора вверх и вправо
        clearLine(); // очистка верхней строки
        readString(buffer, msg, defaultValue, minLength, maxLength, allowEmpty); // рекурсивный вызов
        return;
    }
}

void readUnsignedInt(int *intValue, const char *msg, int defaultValue, int minValue, int maxValue) {
    int startPosX = 0; // = длинна начального сообщения
    if (msg != nullptr) {
        printf(MSG_COLOR, msg);
        startPosX = strlen(msg);
    }
    setCursorTo(startPosX, -1);
    int maxNumbCount = 0; // макцимальное кол-во цифр при вводе
    int temp = maxValue;

    char strBuffer[12];
    memset(strBuffer, '\0', 12); // обнуление буфера


    if (defaultValue != -1) {
        printf(INPUT_COLOR, "%d", defaultValue);
        sprintf(strBuffer, "%d", defaultValue);
        do {
            defaultValue = defaultValue / 10;
            temp = temp / 10;
            maxNumbCount++;
        } while (defaultValue != 0);

    }

    while (temp != 0) {
        maxNumbCount++;
        temp = temp / 10;
        printf("_");
    }
    setCursorTo(startPosX + strlen(strBuffer), -1); // + strlen(strBuffer) = длина значения по умолчанию



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
                            printf(INPUT_COLOR, "%c", key);
                            strBuffer[strlen(strBuffer)] = (char) key;
                        }
                    }
            }
        }
    }
    int valueNumbCount = strlen(strBuffer); // число введенных цифр
    *intValue = atol(strBuffer);
    if (*intValue == 0) {
        printf(INPUT_COLOR, "0");
        valueNumbCount = 1;
    }

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
        readUnsignedInt(intValue, msg, defaultValue, minValue, maxValue); // рекурсивный вызов
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
        readUnsignedInt(intValue, msg, defaultValue, minValue, maxValue); // рекурсивный вызов
        return;
    }

    printf("\n");

}

void readUnsignedFloat(float *floatValueBuffer, const char *msg, float defaultValue, float minValue, float maxValue) {
    int startPosX = 0; // = длинна начального сообщения
    if (msg != nullptr) {
        printf(MSG_COLOR, msg);
        startPosX = strlen(msg);
    }

    float temp = maxValue;
    int maxNumbCount = 0; // макцимальное кол-во цифр при вводе

    char strBuffer[12];
    memset(strBuffer, '\0', 12); // обнуление буфера

    if (defaultValue != -1) {
        sprintf(strBuffer, "%.2f", defaultValue);
        printf(INPUT_COLOR, "%s", strBuffer);
        do {
            defaultValue = defaultValue / 10;
            temp = temp / 10;
            maxNumbCount++;
        } while ((int) defaultValue != 0);
    }


    while ((int) temp != 0) {
        maxNumbCount++;
        temp = temp / 10;
        printf("_");
    }

    if (defaultValue == -1) {
        printf(".__");
    }
    maxNumbCount += 3; // + .__
    setCursorTo(startPosX + strlen(strBuffer), -1);


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
                                printf(INPUT_COLOR, "%c", key);
                            } else {
                                mBeep();
                            }
                        } else if (key < '0' || key > '9') {
                            mBeep();
                        } else {
                            printf(INPUT_COLOR, "%c", key);
                            strBuffer[strlen(strBuffer)] = (char) key;
                        }
                    }
            }
        }
    }
    int valueNumbCount = strlen(strBuffer); // число введенных символов
    *floatValueBuffer = ((float) atof(strBuffer));
    if (*floatValueBuffer == 0) {
        printf(INPUT_COLOR, "0.0");
        valueNumbCount = 3;
    }


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
        readUnsignedFloat(floatValueBuffer, msg, defaultValue, minValue, maxValue); // рекурсивный вызов
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
        readUnsignedFloat(floatValueBuffer, msg, defaultValue, minValue, maxValue); // рекурсивный вызов
        return;
    }


    printf("\n");


}

void scanGitRep(GitRep *gitRep) {
    readString(gitRep->name, "Rep. name: ", NULL, 3, 35, false);
    readString(gitRep->pl, "Programing language: ", NULL, 0, 35, false);
    readString(gitRep->author, "Rep. author: ", NULL, 3, 35, false);
    readUnsignedFloat(&gitRep->rate, "Rep. rate: ", -1, -1, MAX_RATE);
    readUnsignedInt(&gitRep->commitNumb, "Number of commits: ", -1, -1, MAX_COMMIT_NUMB);
    readUnsignedInt(&gitRep->errorNumb, "Number of errors: ", -1, -1, MAX_ERROR_NUMB);
    readUnsignedInt(&gitRep->fixErrorNumb, "Number of fixed errors: ", -1, -1, MAX_FIX_ERROR_NUMB);
    readUnsignedInt(&gitRep->branchNumb, "Number of branches: ", -1, -1, MAX_BRANCH_NUMB);
    readDate(&gitRep->createDate, "Create date: ", NULL, NULL, false);
    readDate(&gitRep->editDate, "Edit date: ", NULL, &gitRep->createDate, false);
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

void editGitRep(GitRep gitRep) {


}


char *getUnderline(int tableSize, char *data, Gravity gravity) {
    int dataLen = strlen(data);

    int startPos;
    switch (gravity) {
        case Left:
            startPos = 0;
            break;
        case Right:
            startPos = tableSize - dataLen;
            break;
        default:
            startPos = (tableSize - dataLen) / 2;

    }
    char *result = (char *) calloc((size_t) (tableSize + 1), sizeof(char));
    memset(result, '_', (size_t) tableSize);
    result[tableSize] = '\0';
    for (int i = startPos; i < dataLen + startPos; i++) {
        if (i > tableSize - 1) {
            break;
        }
        char c = data[i - startPos];
        if (c == ' ') {
            result[i] = '_';
        } else {
            result[i] = c;
        }
    }
    return result;
}

void printTableHeader() {
    const Color TABLE_HEADER_COLOR = LightMagenta;
    printf(TABLE_HEADER_COLOR, "%s\n", getUnderline(123, (char *) "GIT-REP LIST", Center));
    printf(TABLE_HEADER_COLOR, "|%s", "POS");
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(15, (char *) "Name", Center));
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(10, (char *) "Pog. Lang.", Center));
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(10, (char *) "Author", Center));
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(4, (char *) "Rate", Center));
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(11, (char *) "Comm. Numb.", Center));
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(10, (char *) "Err. Numb.", Center));
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(15, (char *) "Fix. Err. Numb.", Center));
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(13, (char *) "Branch. Numb.", Center));
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(11, (char *) "Create Date", Center));
    printf(TABLE_HEADER_COLOR, "|%s", getUnderline(10, (char *) "Edit Date", Center));
    printf(TABLE_HEADER_COLOR, "|\n");
}

void printItemRow(int index, GitRep rep) {
    char *tempBuff = (char *) malloc(sizeof(char) * 11);

    sprintf(tempBuff, "%03d", index);
    printf("|%s", getUnderline(3, tempBuff, Left));

    printf("|%s", getUnderline(15, rep.name, Left));
    printf("|%s", getUnderline(10, rep.pl, Left));
    printf("|%s", getUnderline(10, rep.author, Left));

    sprintf(tempBuff, "%3.2f", rep.rate);
    printf("|%s", getUnderline(4, tempBuff, Right));

    sprintf(tempBuff, "%d", rep.commitNumb);
    printf("|%s", getUnderline(11, tempBuff, Right));

    sprintf(tempBuff, "%d", rep.errorNumb);
    printf("|%s", getUnderline(10, tempBuff, Right));

    sprintf(tempBuff, "%d", rep.fixErrorNumb);
    printf("|%s", getUnderline(15, tempBuff, Right));

    sprintf(tempBuff, "%d", rep.branchNumb);
    printf("|%s", getUnderline(13, tempBuff, Right));

    dateToString(tempBuff, rep.createDate);
    printf("|%s", getUnderline(11, tempBuff, Right));

    dateToString(tempBuff, rep.editDate);
    printf("|%s", getUnderline(10, tempBuff, Right));

    printf("|\n");
    free(tempBuff);
}

int printGitRepArrayList(GitRep *gitRepList, int gitRepNumb) {
    if (gitRepNumb == 0) {
        return CODE_EMPTY_LIST;
    }
    printTableHeader();
    for (int i = 0; i < gitRepNumb; i++) {
        printItemRow(i, gitRepList[i]);
    }
    return CODE_SUCCESS;
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

void swap(GitRep *a, GitRep *b) {
    GitRep temp = *a;
    *a = *b;
    *b = temp;
}

int compareGitReps(GitRep *a, GitRep *b, GitRepField field, bool fullComp) {
    switch (field) {
        case Name:
            if (fullComp) {
                return stricmp(a->name, b->name);
            } else {
                return strstr(a->name, b->name) != NULL ? 0 : compareGitReps(a, b, field, true);
            }
        case Pl:
            if (fullComp) {
                return stricmp(a->pl, b->pl);
            } else {
                return strstr(a->pl, b->pl) != NULL ? 0 : compareGitReps(a, b, field, true);
            }
        case Author:
            if (fullComp) {
                return stricmp(a->author, b->author);
            } else {
                return strstr(a->author, b->author) != NULL ? 0 : compareGitReps(a, b, field, true);
            }
        case Rate:
            if (fullComp) {
                return (int) (a->rate * 100 - b->rate * 100);
            } else {
                char bufferA[9] = "";
                char bufferB[9] = "";
                sprintf(bufferA, "%g", a->rate);
                sprintf(bufferB, "%g", b->rate);
                if (strlen(bufferA) < strlen(bufferB)) {
                    bufferB[strlen(bufferA)] = '\0';
                } else {
                    bufferA[strlen(bufferB)] = '\0';
                }
                return strstr(bufferA, bufferB) != NULL ? 0 : compareGitReps(a, b, field, true);
            }

        case CommitNumb:
            if (fullComp) {
                return a->commitNumb - b->commitNumb;
            } else {
                char bufferA[9] = "";
                char bufferB[9] = "";
                sprintf(bufferA, "%d", a->commitNumb);
                sprintf(bufferB, "%d", b->commitNumb);
                return strstr(bufferA, bufferB) != NULL ? 0 : compareGitReps(a, b, field, true);
            }
        case ErrorNumb:
            if (fullComp) {
                return a->errorNumb - b->errorNumb;
            } else {
                char bufferA[9] = "";
                char bufferB[9] = "";
                sprintf(bufferA, "%d", a->errorNumb);
                sprintf(bufferB, "%d", b->errorNumb);
                return strstr(bufferA, bufferB) != NULL ? 0 : compareGitReps(a, b, field, true);
            }
        case FixErrorNumb:
            if (fullComp) {
                return a->fixErrorNumb - b->fixErrorNumb;
            } else {
                char bufferA[9] = "";
                char bufferB[9] = "";
                sprintf(bufferA, "%d", a->fixErrorNumb);
                sprintf(bufferB, "%d", b->fixErrorNumb);
                return strstr(bufferA, bufferB) != NULL ? 0 : compareGitReps(a, b, field, true);
            }
        case BranchNumb:
            if (fullComp) {
                return a->branchNumb - b->branchNumb;
            } else {
                char bufferA[9] = "";
                char bufferB[9] = "";
                sprintf(bufferA, "%d", a->branchNumb);
                sprintf(bufferB, "%d", b->branchNumb);
                return strstr(bufferA, bufferB) != NULL ? 0 : compareGitReps(a, b, field, true);
            }
        case CreateDate:
            return compareDate(a->createDate, b->createDate);
        case EditDate:
            return compareDate(a->editDate, b->editDate);
        default:
            return 0;
    }
}

void hoareSort(GitRep *gitRepList, int first, int last, SortDirection dir, GitRepField field) {
    int i = first, j = last;
    int k = (dir == Inc ? -1 : 1);
    GitRep *x = &gitRepList[(first + last) / 2];
    do {
        while ((compareGitReps(&gitRepList[i], x, field, true) * k) > 0) i++;
        while ((compareGitReps(&gitRepList[j], x, field, true) * k) < 0) j--;

        if (i <= j) {
            if ((compareGitReps(&gitRepList[i], &gitRepList[j], field, true) * k) < 0) {
                swap(&gitRepList[i], &gitRepList[j]);
            }
            i++;
            j--;
        }
    } while (i <= j);
    if (i < last) hoareSort(gitRepList, i, last, dir, field);
    if (first < j) hoareSort(gitRepList, first, j, dir, field);
}

void sortGitRepArrayList(GitRep **gitRepList, int gitRepNumb, SortDirection dir, GitRepField field) {
    hoareSort(*gitRepList, 0, gitRepNumb - 1, dir, field);
}


