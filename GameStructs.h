//
// Created by wiskiw on 01.12.17.
//
#include <GL/glut.h>
#include "PREFERENCES.h"

#ifndef COURSE_PAPER_GAME_STRUCTS_H
#define COURSE_PAPER_GAME_STRUCTS_H

// SW_ - Star Wars
// SW_State = -1 - undefined

enum GameState {
    GAME_STATE_MENU, GAME_STATE_PLAY, GAME_STATE_PAUSE
};

typedef int SW_State;
typedef int SW_Type;

struct SW_COLOR {
    int R = 0;
    int G = 0;
    int B = 0;
    int A = 0;
};

struct SW_Speed {
    float x = 1;
    float y = 0;
};

struct SW_Pos {
    float x = 0;
    float y = 0;
    float z = 0;
};

struct SW_Borders {
    float leftBottomX;
    float leftBottomY;
    float rightTopX;
    float rightTopY;
};

struct SW_Star {
    SW_Pos pos;
    SW_Speed speed;
    int color = 0;
    float size = 1;
};

struct SW_Bullet {
    SW_Pos pos;
    SW_Speed speed;

    SW_State state = 1;
    // state -1 для пустой пули

    float damage;
};

struct SW_Gun {
    int waitBeforeShoot = 0; // переменная для хранения оставшихся тиков до выстрела
    int gunSpeed; // тики между выстрелами
    int reloadTicks; // количество тиков для перезарядки
    int leftTicksForReload; // оставшееся количество тиков до конца перезарядки
    int ammorSize; // количество патронов в обойме
    int ammorLeft = 0; // количество оставшихся патронов в обойме
    SW_Bullet bullet;

    SW_State state = 1;
    // state 1 - ready
    // state 2 - reload
};

struct SW_Enemy {
    SW_Pos pos;
    SW_Speed speed;
    SW_Type type;
    SW_State state = -1;
    SW_Borders hitBox;
    float health;
    SW_Gun gun;

};

struct SW_Enemies {
    const static int maxNumber = PREF_ENEMY_BUFFER_SIZE;
    SW_Enemy list[maxNumber];
    int number;
};

struct SW_Player {
    SW_Borders hitBox;
    SW_Gun gun;

    SW_State state;
    // 1 - going left
    // 2 - going forward
    // 3 - going right
    // TODO: dead[1-4];

    float health = PREF_PLAYER_DEFAULT_HEALTH;
    SW_Pos pos;
    SW_Speed speed;
};

struct SW_Background {
    SW_Type type;
    const static int starNumber = PREF_STARS_NUMBER;

    SW_Star stars[starNumber];

};


struct SW_Bullets {
    const static int maxsize = PREF_BULLET_BUFFER_SIZE;
    SW_Bullet list[maxsize];
};

struct GameFieldStruct {
    // состояние
    GameState gameState = GAME_STATE_MENU;
    int difficult = 3;
    SW_Background background;

    // границы игрового поля
    SW_Borders borders;

    SW_Bullets bullets;
    SW_Enemies enemies;

    SW_Player player;

};

#endif //COURSE_PAPER_GAME_STRUCTS_H
