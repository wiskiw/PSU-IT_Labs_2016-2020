//
// Created by wiskiw on 01.12.17.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "missing_default_case"

#include <GL/glut.h>
#include <iostream>
#include <climits>
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
    if (thisGame.globalTickTimer >= ULONG_MAX) {
        thisGame.globalTickTimer = 0;
    } else {
        thisGame.globalTickTimer++;
    }
}


void onRedraw() {
    checkKeysBuffer(); // проверка буфера клавиш
    updateGameTickTimer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    mdlPlayerUpdate(&thisGame);
    mdlBulletUpdateAll(&thisGame);
    mdlEnemyUpdateAll(&thisGame);
    mdlBackgroundUpdate(&thisGame);
    mdlDropUpdate(&thisGame);


    uiUpdate(&thisGame);

    glutSwapBuffers();
}

void onChangeSize(int width, int height) {
    glutReshapeWindow(WINDOW_X, WINDOW_Y);
}

void onEnemyShoot(SW_Bullet bullet) {
    mdlBulletAddNew(&thisGame, bullet);
}

void onEnemyKilled(SW_Enemy enemy) {
    // PREF_DROP_SPAWN_ENEMY_DROP_CHANCE - просчитывать динамически
    if (PREF_DROP_SPAWN_ENEMY_DROP_CHANCE != 0 && random(PREF_DROP_SPAWN_ENEMY_DROP_CHANCE, 10) == 10) {
        SW_Drop enemyDrop = mdlDropGetNew(&thisGame, DROP_SPAWN_TYPE_ENEMY);
        enemyDrop.pos = enemy.pos;
        mdlDropAddNew(&thisGame, enemyDrop);
    }
}

void onPlayerShoot(SW_Bullet bullet) {
    mdlBulletAddNew(&thisGame, bullet);
}

void onPlayerTakeDrop(SW_Drop drop) {
    mdlDropAction(&thisGame, drop);
}

void onPlayerDamage(SW_Player player) {
    //std::cout << "player health: " << player.health << std::endl;
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

    std::cout << "leftBottomX: " << thisGame.gameBorders.leftBottomX
              << " rightTopX: " << thisGame.gameBorders.rightTopX << std::endl;
    std::cout << "leftBottomY: " << thisGame.gameBorders.leftBottomY << " rightTopY: " << thisGame.gameBorders.rightTopY
              << std::endl;


    uiInit(&thisGame);

    mdlPlayerInit(&thisGame);
    mdlPlayerSetShootListener(onPlayerShoot);
    mdlPlayerSetHealthListener(onPlayerDamage);
    mdlPlayerSetTakeDropListener(onPlayerTakeDrop);

    mdlBulletInitAll(&thisGame);
    mdlDropInit(&thisGame);

    mdlEnemySetShootListener(onEnemyShoot);
    mdlEnemySetEnemyKilledListener(onEnemyKilled);
    mdlEnemyInitAll(&thisGame);
    mdlBackgroundInit(&thisGame);

    thisGame.gameState = GAME_STATE_PLAY;
}

void onKeyPress(int key, int x, int y) {
    uiProcessInputClick(&thisGame, key, x, y);
    switch (key) {
        case IO_KEY_SHOOT:
            if (thisGame.gameState == GAME_STATE_PLAY) {
                mdlPlayerShot(&thisGame);
            }
            break;
        case 27:
            // esc
            switch (thisGame.gameState) {
                case GAME_STATE_PLAY:
                    thisGame.gameState = GAME_STATE_PAUSE;
                    break;
                case GAME_STATE_PAUSE:
                    thisGame.gameState = GAME_STATE_PLAY;
                    break;
            }
            break;
    }
}

void onKeyHold(int key, int x, int y) {
    if (thisGame.gameState == GAME_STATE_PLAY) {
        switch (key) {
            case IO_KEY_GO_LEFT:
                // left arrow
                mdlPlayerGoLeft(&thisGame);
                break;
            case IO_KEY_GO_RIGHT:
                //right arrow
                mdlPlayerGoRight(&thisGame);
                break;
        }
    }
}

void onKeyRelease(int key, int x, int y) {
    if (thisGame.gameState == GAME_STATE_PLAY) {
        switch (key) {
            case IO_KEY_GO_RIGHT:
            case IO_KEY_GO_LEFT:
                //сбрасываем состояние игрока если отпущена клавиша вправо/влево
                thisGame.player.state = 2;
                break;
        }
    }
}

void onMouseMove(int x, int y) {
    uiProcessMouseMove(&thisGame, x, y);
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