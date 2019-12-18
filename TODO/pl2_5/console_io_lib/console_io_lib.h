//
// Created by WiskiW on 26.04.2017.
//

#include <cstdlib>
#include <afxres.h>
#include <cstdio>

#ifndef LIB_CONSOLE_IO_LIB_H
#define LIB_CONSOLE_IO_LIB_H


const int DEFAULT_WINDOW_WIDTH = 1128;
const int DEFAULT_WINDOW_HEIGHT = 600;

enum Color {
    Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray,
    LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

void setWindowSize(int width, int height);

Color getConsoleTextColor();

void setConsoleTextColor(Color color);

COORD getCursorPosition();

void setCursorTo(int x, int y);

int printf(Color color, const char *format, ...);

void removeC(int n);

void removeC(int n, char c);

void clearLine();

void beep();

#endif //LIB_CONSOLE_IO_LIB_H
