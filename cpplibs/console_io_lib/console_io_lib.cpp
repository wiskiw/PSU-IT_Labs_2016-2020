//
// Created by WiskiW on 26.04.2017.
//

#include <afxres.h>
#include <cstdio>
#include "console_io_lib.h"

void removeC(int n, char c) {
    char backspaces[n + 1];
    for (int i = 0; i < n; i++) {
        backspaces[i] = '\b';
    }
    backspaces[n] = '\0';
    printf(backspaces);

    for (int i = 0; i < n; i++) {
        backspaces[i] = c;
    }
    backspaces[n] = '\0';
    printf(backspaces);

    for (int i = 0; i < n; i++) {
        backspaces[i] = '\b';
    }
    backspaces[n] = '\0';
    printf(backspaces);
}

void removeC(int n) {
    removeC(n,' ');
}

void clearLine(){
    removeC(getCursorPosition().X);
}

void beep() {
    printf("\a");
}

int printf(Color color, const char *format, ...) {
    Color previewColor = getConsoleTextColor();
    setConsoleTextColor(color);
    va_list vl;
    va_start(vl, format);
    int ret = vprintf(format, vl);
    va_end(vl);
    setConsoleTextColor(previewColor);
    return ret;
}

COORD getCursorPosition() {
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hOut, &SBInfo);
    return SBInfo.dwCursorPosition;
}

void setCursorTo(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cPos = getCursorPosition();
    if (x != -1) cPos.X = (SHORT) x;
    if (y != -1) cPos.Y = (SHORT) y;
    SetConsoleCursorPosition(hCon, cPos);
}

Color getConsoleTextColor() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        return (Color) csbi.wAttributes;
    }
    return White;
}

void setConsoleTextColor(Color color) {
    /*
    Name         | Value
    Black        |   0
    Blue         |   1
    Green        |   2
    Cyan         |   3
    Red          |   4
    Magenta      |   5
    Brown        |   6
    Light Gray   |   7
    Dark Gray    |   8
    Light Blue   |   9
    Light Green  |   10
    Light Cyan   |   11
    Light Red    |   12
    Light Magenta|   13
    Yellow       |   14
    White        |   15

     */

    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void setWindowSize(int width, int height){
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    MoveWindow(console, r.left, r.top, width, height, TRUE); // 800 width, 100 height
}