//
// Created by wiskiw on 01.12.17.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "missing_default_case"

#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include "GameStructs.h"
#include "utils/Utils.h"
#include "modules/player/ModulePlayer.h"
#include "io/IOProcessor.h"
#include "modules/background/ModuleBackground.h"
#include "modules/bullets/ModuleBullet.h"
#include "modules/enemy/ModulEnemy.h"
#include "ui/UI.h"
#include "modules/drop/ModuleDrop.h"


const int WINDOW_X = 1100;
const int WINDOW_Y = 590;

GameFieldStruct thisGame;

void updateGameTickTimer() {
    if (thisGame.globalTickTimer >= 10000) {
        thisGame.globalTickTimer = 0;
    } else {
        thisGame.globalTickTimer++;
    }
}

void saveRecordTableToFile() {
    std::ofstream recordFile(PREF_RECORDS_FILE_NAME);
    if (recordFile.is_open()) {
        for (int i = 0; i < PREF_RECORD_LIST_SIZE; ++i) {
            SW_Record record = thisGame.recordList[i];
            recordFile << (char) record.type << PREF_RECORDS_FILE_SUPER_CHAR;
            if (record.type != RECORD_TYPE_UNDEFINED) {
                recordFile << record.name << PREF_RECORDS_FILE_SUPER_CHAR;
            } else {
                recordFile << PREF_DEFAULT_RECORD_NAME << PREF_RECORDS_FILE_SUPER_CHAR;
            }
            recordFile << record.score << std::endl;
        }
        recordFile.close();
        std::cout << "[INFO] Records file successfully saved" << std::endl;
    } else {
        std::cout << "[ERR] Unable to create records file" << std::endl;
    }
}

void readRecordsTableFromFile() {
    std::ifstream recordFile(PREF_RECORDS_FILE_NAME);
    if (recordFile.is_open()) {
        std::string lineBuffer;

        for (int i = 0; getline(recordFile, lineBuffer); ++i) {
            SW_Record record;
            const size_t superCharPos = lineBuffer.find(PREF_RECORDS_FILE_SUPER_CHAR, 2);

            switch (lineBuffer.at(0)) {
                case 'k': {
                    record.type = RECORD_TYPE_OK;

                    std::string nameStr = lineBuffer.substr(2, superCharPos - 2);
                    std::string scoreStr = lineBuffer.substr(superCharPos + 1);

                    strcpy(record.name, nameStr.c_str());
                    record.score = std::stoi(scoreStr);

                    //std::cout << nameStr << ":" << scoreStr << std::endl;
                    break;
                }
                case 'u': {
                    record.type = RECORD_TYPE_UNDEFINED;
                    break;
                }
            }
            thisGame.recordList[i] = record;
        }

        recordFile.close();
    } else {
        std::cout << "[WARN] Record table not found" << std::endl;
    }

}

int getPlayerPositionInRecordTable() {
    // возвращает номер строки в таблице рекордов для записи
    int newScore = thisGame.score;
    for (int i = 0; i < PREF_RECORD_LIST_SIZE; ++i) {
        SW_Record record = thisGame.recordList[i];

        if (record.type == RECORD_TYPE_UNDEFINED || record.score < newScore) {
            return i + 1;
        }
    }
    return PREF_RECORD_LIST_SIZE + 1;
}

void onRedraw() {
    checkKeysBuffer(); // проверка буфера клавиш
    updateGameTickTimer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // вызываем методы обновления игровых структур только в состоянии PLAY или PAUSE_MENU
    if (thisGame.gameState == GAME_STATE_PLAY || thisGame.gameState == GAME_STATE_PAUSE_MENU) {
        mdlPlayerUpdate(&thisGame);
        mdlBulletUpdateAll(&thisGame);
        mdlEnemyUpdateAll(&thisGame);
        mdlBackgroundUpdate(&thisGame);
        mdlDropUpdate(&thisGame);
    }


    uiUpdate(&thisGame);

    glutSwapBuffers();
}

void onChangeSize(int width, int height) {
    glutReshapeWindow(WINDOW_X, WINDOW_Y);
}

void onEnemyShoot(SW_Bullet bullet) {
    mdlBulletAddNew(&thisGame, bullet);
}

void onEnemyDamage(SW_Enemy enemy, SW_Bullet bullet) {
    if (enemy.health <= 0) {
        // убит

        // TODO: PREF_DROP_SPAWN_ENEMY_DROP_CHANCE - просчитывать динамически
        if (PREF_DROP_SPAWN_ENEMY_DROP_CHANCE != 0 &&
            random(PREF_DROP_SPAWN_ENEMY_DROP_CHANCE, 10) == 10) {

            SW_Drop enemyDrop = mdlDropGetNew(&thisGame, DROP_SPAWN_TYPE_ENEMY);
            enemyDrop.pos = enemy.pos;
            mdlDropAddNew(&thisGame, enemyDrop);
        }

        thisGame.score += enemy.originHealth;
    }
}

void onPlayerShoot(SW_Bullet bullet) {
    mdlBulletAddNew(&thisGame, bullet);
}

void onPlayerTakeDrop(SW_Drop drop) {
    mdlDropAction(&thisGame, drop);
}

void updateRecordTable(int pos, int score) {
    // обновление массива рекордов
    SW_Record *list = thisGame.recordList;
    const int posIndex = pos - 1;

    // сдвиг записей
    for (int i = PREF_RECORD_LIST_SIZE - 1; i > posIndex; i--) {
        list[i] = list[i - 1];
    }

    list[posIndex].score = score;
    list[posIndex].type = RECORD_TYPE_OK;
    strncpy(list[posIndex].name, PREF_DEFAULT_RECORD_NAME, strlen(PREF_DEFAULT_RECORD_NAME) + 1);
}

void onPlayerHealthChanged(SW_Player player) {
    if (player.health <= 0) {
        thisGame.positionInRecordTable = getPlayerPositionInRecordTable();
        if (thisGame.positionInRecordTable <= PREF_RECORD_LIST_SIZE) {
            // игра окончена: новый рекорд
            std::cout << "[INFO] GAME OVER - New record: " << thisGame.score << std::endl;

            updateRecordTable(thisGame.positionInRecordTable, thisGame.score);
            thisGame.gameState = GAME_STATE_ADD_NEW_RECORD;
        } else {
            // игра окончена
            std::cout << "[INFO] GAME OVER: " << thisGame.score << std::endl;

            // TODO: debug only
            thisGame.gameState = GAME_STATE_PAUSE_MENU;
        }
    }
}

void initGame() {
    srand(time(0));

    thisGame.windowX = WINDOW_X;
    thisGame.windowY = WINDOW_Y;

    // TODO: Left padding
    const int STAT_X = 150;

    thisGame.gameBorders.leftBottomX = STAT_X;
    thisGame.gameBorders.rightTopX = static_cast<int>(WINDOW_X / PREF_SCREEN_CROP_FACTOR);
    thisGame.gameBorders.leftBottomY = 0;
    thisGame.gameBorders.rightTopY = static_cast<int>(WINDOW_Y / PREF_SCREEN_CROP_FACTOR);

    thisGame.interfaceBorders.leftBottomX = 0;
    thisGame.interfaceBorders.leftBottomY = 0;
    thisGame.interfaceBorders.rightTopX = thisGame.gameBorders.leftBottomX;
    thisGame.interfaceBorders.rightTopY = thisGame.gameBorders.rightTopY;

    std::cout << "[DEBUG] leftBottomX: " << thisGame.gameBorders.leftBottomX
              << " rightTopX: " << thisGame.gameBorders.rightTopX << std::endl;
    std::cout << "[DEBUG] leftBottomY: " << thisGame.gameBorders.leftBottomY << " rightTopY: " << thisGame.gameBorders.rightTopY
              << std::endl;

    readRecordsTableFromFile();
}

GameFieldStruct createNewGame() {

    thisGame.globalTickTimer = 0;
    thisGame.positionInRecordTable = PREF_RECORD_LIST_SIZE + 1;
    thisGame.score = 0;
    thisGame.difficult = PREF_GAME_DEFAULT_DIFFICULT;

    mdlPlayerInit(&thisGame);
    mdlPlayerSetShootListener(onPlayerShoot);
    mdlPlayerSetHealthListener(onPlayerHealthChanged);
    mdlPlayerSetTakeDropListener(onPlayerTakeDrop);

    mdlBulletInitAll(&thisGame);
    mdlDropInit(&thisGame);

    mdlEnemySetShootListener(onEnemyShoot);
    mdlEnemySetEnemyDamageListener(onEnemyDamage);
    mdlEnemyInitAll(&thisGame);
    mdlBackgroundInit(&thisGame);

    return thisGame;
}

void onKeyPress(int key, int x, int y, bool special) {
    std::cout << "[DEBUG] KEY PRESSED[" << (special == true ? 's' : 'n') << "]: " << key << std::endl;

    uiProcessInput(&thisGame, key, x, y, special);
    switch (thisGame.gameState) {
        case GAME_STATE_PLAY:

            // обязательно удаляем нажатие клавиши влево/вправо, если нажата клавиша вправо/влево
            if (key == PREF_IO_KEY_GO_LEFT) {
                ioProcessSpecialKeyUp(PREF_IO_KEY_GO_RIGHT, 0, 0);
            } else if (key == PREF_IO_KEY_GO_RIGHT) {
                ioProcessSpecialKeyUp(PREF_IO_KEY_GO_LEFT, 0, 0);
            }

            if (key == PREF_IO_KEY_SHOOT) {
                mdlPlayerShot(&thisGame);
            }

            break;
    }
}

void onKeyHold(int key, int x, int y, bool special) {
    if (thisGame.gameState == GAME_STATE_PLAY) {
        switch (key) {
            case PREF_IO_KEY_GO_LEFT:
                // left arrow
                if (special) mdlPlayerGoLeft(&thisGame);
                break;
            case PREF_IO_KEY_GO_RIGHT:
                //right arrow
                if (special) mdlPlayerGoRight(&thisGame);
                break;
        }
    }
}

void onKeyRelease(int key, int x, int y, bool special) {
    if (thisGame.gameState == GAME_STATE_PLAY) {
        switch (key) {
            case PREF_IO_KEY_GO_RIGHT:
            case PREF_IO_KEY_GO_LEFT:
                //сбрасываем состояние игрока если отпущена клавиша вправо/влево
                thisGame.player.state = 2;
                break;
        }
    }
}

void onMouseMove(int x, int y) {
    uiProcessMouseMove(&thisGame, x, y);
}

void onUIItemSelect(GameState state, int select) {
    switch (state) {
        case GAME_STATE_MAIN_MENU:
            switch (select) {
                case 2:
                    // play
                    createNewGame();
                    thisGame.gameState = GAME_STATE_PLAY;
                    break;
                case 1:
                    // record list
                    thisGame.gameState = GAME_STATE_RECORD_LIST;
                    break;
                default:
                    // exit
                    exit(0);
            }
            break;
        case GAME_STATE_PAUSE_MENU:
            switch (select) {
                case 0:
                    // main menu
                    thisGame.gameState = GAME_STATE_MAIN_MENU;
                    break;
                case 1:
                    // continue
                    thisGame.gameState = GAME_STATE_PLAY;
                    break;
            }
            break;
        case GAME_STATE_RECORD_LIST:
            switch (select) {
                case 0:
                    // back
                    thisGame.gameState = GAME_STATE_MAIN_MENU;
                    break;
            }
            break;
        case GAME_STATE_ADD_NEW_RECORD:
            switch (select) {
                case 0:
                    // save
                    saveRecordTableToFile();
                    thisGame.gameState = GAME_STATE_MAIN_MENU;
                    break;
            }
            break;
    }
}

int main(int args, char **argv) {

    setKeyHoldListener(onKeyHold);
    setKeyPressListener(onKeyPress);
    setKeyReleaseListener(onKeyRelease);
    setMouseMoveListener(onMouseMove);


    glutInit(&args, argv);

    int posX = (glutGet(GLUT_SCREEN_WIDTH) - WINDOW_X) / 2;
    int posY = (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_Y) / 2;

    glutInitWindowPosition(posX, posY);
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Star Wars");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 0);

    glViewport(0, 0, WINDOW_X, WINDOW_Y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_X / PREF_SCREEN_CROP_FACTOR, 0, WINDOW_Y / PREF_SCREEN_CROP_FACTOR, -50, 50);
    glMatrixMode(GL_MODELVIEW);

    initGame();

    uiInit(&thisGame, onUIItemSelect);

    glutReshapeFunc(onChangeSize);

    glutKeyboardFunc(ioProcessNormalKeyDown);
    glutKeyboardUpFunc(ioProcessNormalKeyUp);

    glutSpecialFunc(ioProcessSpecialKeyDown);
    glutSpecialUpFunc(ioProcessSpecialKeyUp);

    glutMouseFunc(ioProcessMouseClick);
    glutMotionFunc(ioProcessMouseMove);
    glutPassiveMotionFunc(ioProcessMouseMove);

    glutDisplayFunc(onRedraw);

    glutMainLoop();
    return 0;
}

#pragma clang diagnostic pop