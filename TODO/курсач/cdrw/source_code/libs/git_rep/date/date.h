//
// Created by WiskiW on 29.04.2017.
//

#ifndef LIB_DATE_H
#define LIB_DATE_H

struct Date {
    int day;
    int month;
    int year;
};

int isDateCorrect(Date date);

int compareDate(Date dateA, Date dateB);

char *dateToString(char *buffer, Date date);

#endif //LIB_DATE_H
