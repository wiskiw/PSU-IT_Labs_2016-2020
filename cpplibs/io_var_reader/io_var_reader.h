//
// Created by WiskiW on 26.04.2017.
//

#ifndef LIB_IO_PARCER_H
#define LIB_IO_PARCER_H


#include "date.h"

void readString(char *buffer, const char *msg, int minLength, int maxLength, bool allowEmpty);

void readDate(Date *date, const char *msg, bool allowEmpty);

void readDate(Date *date, const char *msg, Date minDate, bool allowEmpty);

void readUnsignedInt(int *intValue, const char *msg, int minValue, int maxValue);

void readUnsignedFloat(float *floatValueBuffer, const char *msg, float minValue, float maxValue);


#endif //LIB_IO_PARCER_H
