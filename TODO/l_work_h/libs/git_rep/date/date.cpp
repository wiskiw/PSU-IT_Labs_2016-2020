//
// Created by WiskiW on 29.04.2017.
//

#include <cstring>
#include <stdlib.h>
#include <cstdio>
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
    memset(buffer, '\0', 11); // обнуление буфера
    sprintf(buffer, "%02d.%02d.%04d", date.day, date.month, date.year);
    return buffer;
}

int getDayNumb(int month) {
    if (month >= 1 && month <= 12) {
        return 28 + (month + month / 8) % 2 + 2 % month + 1 / month * 2;
    }
}

int isDateCorrect(Date date) {
    if (date.day > getDayNumb(date.month)) {
        return INCORRECT_DAY;
    }
    if (date.month > 12) {
        return INCORRECT_MONTH;
    }
    return 0;
}


