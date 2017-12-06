//
// Created by wiskiw on 01.12.17.
//

#include <GL/glut.h>
#include "IOProcessor.h"
#include "../PREFERENCES.h"

int keysDownBuffer[PREF_KEYBOARD_INPUT_BUFFER_SIZE];

void (*keyHoldListener)(int, int x, int y) = nullptr;

void (*keyPressListener)(int, int x, int y) = nullptr;

void (*keyReleaseListener)(int, int x, int y) = nullptr;

void (*mouseMoveListener)(int x, int y) = nullptr;

int mouseXpos = 0;
int mouseYpos = 0;


void setKeyHoldListener(void (*callback)(int, int, int)) {
    keyHoldListener = callback;
};

void setKeyPressListener(void (*callback)(int, int, int)) {
    keyPressListener = callback;
};

void setKeyReleaseListener(void (*callback)(int, int, int)) {
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
        int key = keysDownBuffer[k];
        if (keyHoldListener != nullptr) {
            keyHoldListener(key, mouseXpos, mouseYpos);
        }
    }
}

void processKeyDown(int key) {
    // обязательно удаляем нажатие клавиши влево/вправо, если нажата клавиша вправо/влево
    if (key == IO_KEY_GO_LEFT) {
        ioProcessSpecialKeyUp(IO_KEY_GO_RIGHT, 0, 0);
    } else if (key == IO_KEY_GO_RIGHT) {
        ioProcessSpecialKeyUp(IO_KEY_GO_LEFT, 0, 0);
    }
    if (keyPressListener != nullptr) {
        keyPressListener(key, mouseXpos, mouseYpos);
    }
    for (int k = 0; k < PREF_KEYBOARD_INPUT_BUFFER_SIZE; k++) {
        if (keysDownBuffer[k] == key) {
            return;
        }

        if (keysDownBuffer[k] == -1 || k == PREF_KEYBOARD_INPUT_BUFFER_SIZE - 1) {
            keysDownBuffer[k] = key;
            int releaseKey = 0;
            if (k + 1 < PREF_KEYBOARD_INPUT_BUFFER_SIZE) {
                releaseKey = keysDownBuffer[k + 1];
                keysDownBuffer[k + 1] = -1;
            } else {
                releaseKey = keysDownBuffer[0];
                keysDownBuffer[0] = -1;
            }
            if (keyReleaseListener != nullptr) {
                keyReleaseListener(releaseKey, mouseXpos, mouseYpos);
            }
            return;
        }
    }
}

void processKeyUp(int key) {
    for (int k = 0; k < PREF_KEYBOARD_INPUT_BUFFER_SIZE; k++) {
        if (keysDownBuffer[k] == key) {
            keysDownBuffer[k] = -1;

            if (keyReleaseListener != nullptr) {
                keyReleaseListener(key, mouseXpos, mouseYpos);
            }
        }
    }
}


void ioProcessNormalKeyDown(unsigned char key, int x, int y) {
    updateMousePosition(x, y);
    processKeyDown(key);
};

void ioProcessNormalKeyUp(unsigned char key, int x, int y) {
    updateMousePosition(x, y);
    processKeyUp(key);
};


void ioProcessSpecialKeyUp(int key, int x, int y) {
    updateMousePosition(x, y);
    processKeyUp(key);
}

void ioProcessSpecialKeyDown(int key, int x, int y) {
    updateMousePosition(x, y);
    processKeyDown(key);
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
        processKeyUp(mouseKey);
    } else {
        processKeyDown(mouseKey);
    }
}

void ioProcessMouseMove(int x, int y) {
    updateMousePosition(x, y);
    if (mouseMoveListener != nullptr) {
        mouseMoveListener(mouseXpos, mouseYpos);
    }
}