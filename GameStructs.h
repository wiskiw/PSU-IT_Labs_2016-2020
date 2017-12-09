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
    GAME_STATE_MAIN_MENU, GAME_STATE_PLAY, GAME_STATE_PAUSE_MENU, GAME_STATE_ADD_NEW_RECORD, GAME_STATE_RECORD_LIST
};

typedef int SW_State;
typedef int SW_Type;

struct SW_Color {
    GLubyte R = 0;
    GLubyte G = 0;
    GLubyte B = 0;
    GLubyte A = 255;
};

struct SW_Speed {
    float x = 0;
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

enum BulletState {
    BULLET_STATE_NORMAL, BULLET_STATE_UNDEFINED
};

struct SW_Bullet {
    SW_Color color = {0, 255, 0};
    SW_Pos pos;
    SW_Speed speed;
    SW_State state = BULLET_STATE_NORMAL;
    float damage;
};

enum GunState {
    GUN_STATE_OK, GUN_STATE_RELOAD, GUN_STATE_SHOOTING_DELAY,
};
struct SW_Gun {
    int waitBeforeShoot = 0; // переменная для хранения оставшихся тиков до выстрела
    int gunSpeed; // тики между выстрелами
    int reloadTicks; // количество тиков для перезарядки
    int ammorSize; // количество патронов в обойме
    int ammorLeft = 0; // количество оставшихся патронов в обойме
    SW_Bullet bullet;

    SW_State state = GUN_STATE_OK;
    // state 1 - ready
    // state 2 - reload
};

enum EnemyState {
    ENEMY_STATE_GOING_LEFT, ENEMY_STATE_GOING_RIGHT, ENEMY_STATE_STAY_FORWARD, ENEMY_STATE_UNDEFINED
};

struct SW_Enemy {
    SW_Pos pos;
    SW_Pos gunPosValue; // относительно центра родителя;
    SW_Speed speed;
    SW_Type type;
    SW_Borders hitBox;
    float health;
    float originHealth;
    SW_Gun gun;
    EnemyState state = ENEMY_STATE_UNDEFINED;
};

struct SW_Enemy_Map {
    float enemiesHealth = 0; // здоровье всех врагов на поле
    const static int maxNumber = PREF_ENEMY_BUFFER_SIZE;
    SW_Enemy list[maxNumber];
    int number;
};


enum PlayerState {
    PLAYER_STATE_GOING_LEFT, PLAYER_STATE_GOING_RIGHT, PLAYER_STATE_STAY_FORWARD,
};

struct SW_Player {
    SW_Borders hitBox;
    SW_Gun gun;

    SW_State state = PLAYER_STATE_STAY_FORWARD;

    float health;
    SW_Pos pos;
    SW_Speed speed;
};

struct SW_Background {
    SW_Type type;
    const static int starNumber = PREF_STARS_NUMBER;

    SW_Star stars[starNumber];
};


struct SW_Bullet_Map {
    const static int maxNumber = PREF_BULLET_BUFFER_SIZE;
    SW_Bullet list[maxNumber];
};

enum DropState {
    DROP_STATE_NORMAL, DROP_STATE_UNDEFINED
};

struct SW_Drop {
    int timeToLive = -1; // -1 пока есть место в буфере
    int livingTime = 0; // сколько прожил после падения
    SW_Type type;
    DropState state = DROP_STATE_UNDEFINED;
    SW_Pos pos;
    SW_Borders hitBox;
    float scaleState = 1;
    bool scaleGrownUp = true;
};

struct SW_Drop_Map {
    const static int maxNumber = PREF_DROP_BUFFER_SIZE;
    SW_Drop list[maxNumber];
};

enum RecordType {
    RECORD_TYPE_OK = 'k', RECORD_TYPE_UNDEFINED = 'u'
};

struct SW_Record {
    RecordType type = RECORD_TYPE_UNDEFINED;
    char name[PREF_RECORD_LIST_MAX_NAME_LENGTH + 1] = "";
    int score = 0;
};

struct GameFieldStruct {
    unsigned long int globalTickTimer = 0;
    float windowX = 0;
    float windowY = 0;

    // состояние
    GameState gameState = GAME_STATE_MAIN_MENU;

    int difficult;
    int score = 0;

    // TODO: DEBUG ON:Y
    int positionInRecordTable = PREF_RECORD_LIST_SIZE - 4;

    // границы игрового поля
    SW_Borders gameBorders;

    SW_Borders interfaceBorders;


    SW_Background background;
    SW_Bullet_Map bulletMap;
    SW_Enemy_Map enemyMap;
    SW_Drop_Map dropMap;
    SW_Player player;

    SW_Record recordList[PREF_RECORD_LIST_SIZE];
};

#endif //COURSE_PAPER_GAME_STRUCTS_H
