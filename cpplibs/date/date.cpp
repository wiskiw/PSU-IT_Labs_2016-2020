//
// Created by WiskiW on 29.04.2017.
//

#include <cstring>
#include <stdlib.h>
#include "date.h"

int compareDay(Date dateA, Date dateB) {
    return dateA.day - dateB.day;
}

int compareMonth(Date dateA, Date dateB) {
    return dateA.month - dateB.month;
}

int compareYear(Date dateA, Date dateB) {
    return dateA.year - dateB.year;
}

int compareDate(Date dateA, Date dateB) {
    int year = compareYear(dateA, dateB);
    if (year > 0) {
        return year;
    }

    int month = compareMonth(dateA, dateB);
    if (month == 0) {
        return compareDay(dateA, dateA);
    } else {
        return month;
    }
}

char *dateToString(char *buffer, Date date) {
    // itoa - преобразует целое число value в строку string в формате radix
    // TODO : FIX 12.2.2018 date format
    char tempBuffer[5] = "";

    itoa(date.day, tempBuffer, 10);
    strcat(buffer, tempBuffer);
    strcat(buffer, ".");

    itoa(date.month, tempBuffer, 10);
    strcat(buffer, tempBuffer);
    strcat(buffer, ".");

    itoa(date.year, tempBuffer, 10);
    strcat(buffer, tempBuffer);

    buffer[10] = '\0';
    return buffer;
}


int isDateCorrect(Date date) {
    if (date.day > 31) {
        return INCORRECT_DAY;
    }
    if (date.month > 12) {
        return INCORRECT_MONTH;
    }
    return 0;
}


