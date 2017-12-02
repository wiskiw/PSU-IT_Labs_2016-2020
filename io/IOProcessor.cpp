//
// Created by wiskiw on 01.12.17.
//

#include "IOProcessor.h"
#include "../PREFERENCES.h"

int keysDownBuffer[PREF_KEYBOARD_INPUT_BUFFER_SIZE];

void (*keyHoldListener)(int) = nullptr;

void (*keyPressListener)(int) = nullptr;

void (*keyReleaseListener)(int) = nullptr;

void setKeyHoldListener(void (*callback)(int)) {
    keyHoldListener = callback;
};

void setKeyPressListener(void (*callback)(int)) {
    keyPressListener = callback;
};

void setKeyReleaseListener(void (*callback)(int)) {
    keyReleaseListener = callback;
};

void checkKeysBuffer() {
    for (int k = 0; k < PREF_KEYBOARD_INPUT_BUFFER_SIZE; k++) {
        int key = keysDownBuffer[k];
        if (keyHoldListener != nullptr) {
            keyHoldListener(key);
        }
    }
}

void processKeyDown(int key) {
    // обязательно удаляем нажатие клавиши влево/вправо, если нажата клавиша вправо/влево
    if (key == IO_KEY_GO_LEFT) {
        processSpecialKeyUp(IO_KEY_GO_RIGHT, 0, 0);
    } else if (key == IO_KEY_GO_RIGHT) {
        processSpecialKeyUp(IO_KEY_GO_LEFT, 0, 0);
    }
    if (keyPressListener != nullptr) {
        keyPressListener(key);
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
                keyReleaseListener(releaseKey);
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
                keyReleaseListener(key);
            }
        }
    }
}


void processNormalKeyDown(unsigned char key, int x, int y) {
    processKeyDown(key);
};

void processNormalKeyUp(unsigned char key, int x, int y) {
    processKeyUp(key);
};


void processSpecialKeyUp(int key, int x, int y) {
    processKeyUp(key);
}

void processSpecialKeyDown(int key, int x, int y) {
    processKeyDown(key);
}