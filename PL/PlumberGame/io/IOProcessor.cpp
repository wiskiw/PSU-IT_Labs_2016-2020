//
// Created by wiskiw on 01.12.17.
//

#include <GL/glut.h>
#include "IOProcessor.h"


/*
 обрабатывает все методы ввода в приложение
 */


const int PREF_KEYBOARD_INPUT_BUFFER_SIZE = 2;

struct IO_KeyInput {
    int key = 0;
    bool special = false;
};

IO_KeyInput keysDownBuffer[PREF_KEYBOARD_INPUT_BUFFER_SIZE];

void (*keyHoldListener)(int, int x, int y, bool special) = nullptr;

void (*keyPressListener)(int, int x, int y, bool special) = nullptr;

void (*keyReleaseListener)(int, int x, int y, bool special) = nullptr;

void (*mouseMoveListener)(int x, int y) = nullptr;

int mouseXpos = 0;
int mouseYpos = 0;


bool compare(IO_KeyInput keyA, IO_KeyInput keyB) {
    return keyA.key == keyB.key && keyA.special == keyB.special;
}

void setKeyHoldListener(void (*callback)(int, int, int, bool)) {
    keyHoldListener = callback;
};

void setKeyPressListener(void (*callback)(int, int, int, bool)) {
    keyPressListener = callback;
};

void setKeyReleaseListener(void (*callback)(int, int, int, bool)) {
    keyReleaseListener = callback;
};

void setMouseMoveListener(void (*callback)(int, int)) {
    mouseMoveListener = callback;
}

void updateMousePosition(int x, int y) {
    mouseXpos = x;
    mouseYpos = y;
}

void checkKeysBuffer() {
    for (int k = 0; k < PREF_KEYBOARD_INPUT_BUFFER_SIZE; k++) {
        IO_KeyInput key = keysDownBuffer[k];
        if (keyHoldListener != nullptr) {
            keyHoldListener(key.key, mouseXpos, mouseYpos, key.special);
        }
    }
}

void processKeyDown(int key, bool special) {

    if (keyPressListener != nullptr) {
        keyPressListener(key, mouseXpos, mouseYpos, special);
    }
    for (int k = 0; k < PREF_KEYBOARD_INPUT_BUFFER_SIZE; k++) {
        if (compare(keysDownBuffer[k], {key, special})) {
            return;
        }

        if (keysDownBuffer[k].key == -1 || k == PREF_KEYBOARD_INPUT_BUFFER_SIZE - 1) {
            keysDownBuffer[k].key = key;
            keysDownBuffer[k].special = special;
            IO_KeyInput releaseKey;
            if (k + 1 < PREF_KEYBOARD_INPUT_BUFFER_SIZE) {
                releaseKey = keysDownBuffer[k + 1];
                keysDownBuffer[k + 1].key = -1;
            } else {
                releaseKey = keysDownBuffer[0];
                keysDownBuffer[0].key = -1;
            }
            if (keyReleaseListener != nullptr) {
                keyReleaseListener(releaseKey.key, mouseXpos, mouseYpos, releaseKey.special);
            }
            return;
        }
    }
}

void processKeyUp(int key, bool special) {
    for (int k = 0; k < PREF_KEYBOARD_INPUT_BUFFER_SIZE; k++) {
        if (compare(keysDownBuffer[k], {key, special})) {
            keysDownBuffer[k].key = -1;

            if (keyReleaseListener != nullptr) {
                keyReleaseListener(key, mouseXpos, mouseYpos, special);
            }
        }
    }
}


void ioProcessNormalKeyDown(unsigned char key, int x, int y) {
    updateMousePosition(x, y);
    processKeyDown(key, false);
};

void ioProcessNormalKeyUp(unsigned char key, int x, int y) {
    updateMousePosition(x, y);
    processKeyUp(key, false);
};


void ioProcessSpecialKeyUp(int key, int x, int y) {
    updateMousePosition(x, y);
    processKeyUp(key, true);
}

void ioProcessSpecialKeyDown(int key, int x, int y) {
    updateMousePosition(x, y);
    processKeyDown(key, true);
}


int getMouseKey(int btn) {
    switch (btn) {
        case GLUT_RIGHT_BUTTON:
            return IO_MOUSE_RIGHT_BUTTON;
        case GLUT_LEFT_BUTTON:
            return IO_MOUSE_LEFT_BUTTON;
        case GLUT_MIDDLE_BUTTON:
            return IO_MOUSE_MIDDLE_BUTTON;
    }
}

void ioProcessMouseClick(int button, int state, int x, int y) {
    updateMousePosition(x, y);

    int mouseKey = getMouseKey(button);
    if (state == GLUT_UP) {
        processKeyUp(mouseKey, false);
    } else {
        processKeyDown(mouseKey, false);
    }
}

void ioProcessMouseMove(int x, int y) {
    updateMousePosition(x, y);
    if (mouseMoveListener != nullptr) {
        mouseMoveListener(mouseXpos, mouseYpos);
    }
}