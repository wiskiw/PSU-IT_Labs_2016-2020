//
// Created by wiskiw on 01.12.17.
//

#ifndef COURSE_PAPER_IOPROCESSOR_H
#define COURSE_PAPER_IOPROCESSOR_H


const int IO_KEY_GO_LEFT = 100;
const int IO_KEY_GO_RIGHT = 102;
const int IO_KEY_SHOOT = 32;

const int IO_MOUSE_LEFT_BUTTON = -2;
const int IO_MOUSE_RIGHT_BUTTON = -3;
const int IO_MOUSE_MIDDLE_BUTTON = -4;

void setKeyPressListener(void (*keyPressListener)(int, int x, int y));

void setKeyHoldListener(void (*keyHoldListener)(int, int x, int y));

void setKeyReleaseListener(void (*keyReleaseListener)(int, int x, int y));

void setMouseMoveListener(void (*callback)(int, int));

void checkKeysBuffer(); // проверка буфера клавиш и вызова функции калбэка

void ioProcessNormalKeyDown(unsigned char key, int x, int y);

void ioProcessNormalKeyUp(unsigned char key, int x, int y);

void ioProcessSpecialKeyDown(int key, int x, int y);

void ioProcessSpecialKeyUp(int key, int x, int y);

void ioProcessMouseClick(int button, int state, int x, int y);

void ioProcessMouseMove(int x, int y);


#endif //COURSE_PAPER_IOPROCESSOR_H
