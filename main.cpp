//
// Created by wiskiw on 01.12.17.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "missing_default_case"

#include <GL/glut.h>
#include <iostream>
#include "GameStructs.h"
#include "modules/player/ModulePlayer.h"
#include "io/IOProcessor.h"
#include "modules/background/ModuleBackground.h"
#include "modules/bullets/ModuleBullet.h"
#include "modules/enemy/ModulEnemy.h"


const int WINDOW_X = 990;
const int WINDOW_Y = 550;

const float SCREEN_CROP_FACTOR = 2;

GameFieldStruct thisGame;


void onRedraw() {
    checkKeysBuffer(); // проверка буфера клавиш
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mdlPlayerDraw(&thisGame);
    mdlBulletDrawAll(&thisGame);
    mdlEnemyDrawAll(&thisGame);
    mdlBackgroundDraw(&thisGame);

    glutSwapBuffers();
}

void onChangeSize(int width, int height) {
    glutReshapeWindow(WINDOW_X, WINDOW_Y);
}

void onEnemyShoot(SW_Bullet bullet) {
    mdlBulletAddNew(&thisGame, bullet);
}

void onPlayerShoot(SW_Bullet bullet) {
    mdlBulletAddNew(&thisGame, bullet);
}

void onPlayerDamage(SW_Player player) {
    std::cout << "player health: " << player.health << std::endl;
}

void initGame() {
    srand(time(0));


    // TODO: Left padding
    const int STAT_X = 0;


    thisGame.borders.leftBottomX = STAT_X;
    thisGame.borders.rightTopX = static_cast<int>(WINDOW_X / SCREEN_CROP_FACTOR);
    thisGame.borders.leftBottomY = 0;
    thisGame.borders.rightTopY = static_cast<int>(WINDOW_Y / SCREEN_CROP_FACTOR);

    std::cout << "leftBottomX: " << thisGame.borders.leftBottomX
              << " rightTopX: " << thisGame.borders.rightTopX << std::endl;
    std::cout << "leftBottomY: " << thisGame.borders.leftBottomY << " rightTopY: " << thisGame.borders.rightTopY
              << std::endl;


    mdlPlayerInit(&thisGame);
    mdlPlayerSetShootListener(onPlayerShoot);
    mdlPlayerSetHealthListener(onPlayerDamage);

    mdlBulletInitAll(&thisGame);

    mdlEnemySetShootListener(onEnemyShoot);
    mdlEnemyInitAll(&thisGame);
    mdlBackgroundInit(&thisGame);
}

void onKeyPress(int key) {

    switch (key) {
        case IO_KEY_SHOOT:
            mdlPlayerShot(&thisGame);
            break;
    }
}

void onKeyHold(int key) {
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

void onKeyRelease(int key) {
    switch (key) {
        case IO_KEY_GO_RIGHT:
        case IO_KEY_GO_LEFT:
            //сбрасываем состояние игрока если отпущена клавиша вправо/влево
            thisGame.player.state = 2;
            break;
    }
}

int main(int args, char **argv) {

    setKeyHoldListener(onKeyHold);
    setKeyPressListener(onKeyPress);
    setKeyReleaseListener(onKeyRelease);


    glutInit(&args, argv);
    glutInitWindowPosition(240, 70);
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
    glOrtho(0, WINDOW_X / SCREEN_CROP_FACTOR, 0, WINDOW_Y / SCREEN_CROP_FACTOR, -50, 50);
    glMatrixMode(GL_MODELVIEW);

    initGame();

    glutReshapeFunc(onChangeSize);

    glutKeyboardFunc(processNormalKeyDown);
    glutKeyboardUpFunc(processNormalKeyUp);

    glutSpecialFunc(processSpecialKeyDown);
    glutSpecialUpFunc(processSpecialKeyUp);

    glutDisplayFunc(onRedraw);

    glutMainLoop();
    return 0;
}

#pragma clang diagnostic pop