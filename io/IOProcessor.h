//
// Created by wiskiw on 01.12.17.
//

#ifndef COURSE_PAPER_IOPROCESSOR_H
#define COURSE_PAPER_IOPROCESSOR_H


const int IO_KEY_GO_LEFT = 100;
const int IO_KEY_GO_RIGHT = 102;
const int IO_KEY_SHOOT = 32;


void setKeyPressListener(void (*keyPressListener)(int));

void setKeyHoldListener(void (*keyHoldListener)(int));

void setKeyReleaseListener(void (*keyReleaseListener)(int));

void checkKeysBuffer(); // проверка буфера клавиш и вызова функции калбэка

void processNormalKeyDown(unsigned char key, int x, int y);

void processNormalKeyUp(unsigned char key, int x, int y);

void processSpecialKeyDown(int key, int x, int y);

void processSpecialKeyUp(int key, int x, int y);


#endif //COURSE_PAPER_IOPROCESSOR_H
