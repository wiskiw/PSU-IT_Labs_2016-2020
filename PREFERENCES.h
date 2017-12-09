//
// Created by wiskiw on 02.12.17.
//

#ifndef COURSE_PAPER_PREFERENCES_H
#define COURSE_PAPER_PREFERENCES_H

const char PREF_RECORDS_FILE_NAME[] = "example.txt";
const char PREF_DEFAULT_RECORD_NAME[] = "none";
const char PREF_RECORDS_FILE_SUPER_CHAR = '~';

const float PREF_SCREEN_CROP_FACTOR = 1.7f;

const int PREF_BULLET_Z_POS = 2;
const int PREF_ENEMY_Z_POS = 3;
const float PREF_DROP_Z_POS = 1.9f;

const float PREF_PLAYER_DEFAULT_HEALTH = 2;
const int PREF_GAME_DEFAULT_DIFFICULT = 3;

const int PREF_STARS_NUMBER = 16;
const int PREF_BULLET_BUFFER_SIZE = 30;
const int PREF_ENEMY_BUFFER_SIZE = 12;


// ==== DIALOG / MENU ======
const int PREF_RECORD_LIST_SIZE = 10;
const int PREF_RECORD_LIST_MAX_NAME_LENGTH = 16;
const int PREF_POINTER_BLINK_TICKS = 24;


// ==== INPUT / OUTPUT ======
const int PREF_IO_KEY_ENTER = 13;
const int PREF_IO_KEY_BACK = 27; // esc
const int PREF_IO_KEY_GO_LEFT = 100;
const int PREF_IO_KEY_GO_RIGHT = 102;
const int PREF_IO_KEY_SHOOT = 32;
const int PREF_IO_KEY_BACKSPACE = 8;
// ================


// ==== DROP ======
const int PREF_DROP_SPAWN_ENEMY_DROP_CHANCE = 4; // 0 - 10
const int PREF_DROP_BUFFER_SIZE = 10;
const float PREF_DROP_SPEED_Y = -0.5f;

// максимальная степень расширения дропа при мерцании
const float PREF_DROP_MAX_SCALE_STATE = 1.6f;

// кол-во тиков которое будет мерцать дроп перед исчезновением
const float PREF_DROP_PRE_REMOVE_BLINK_TIME = 200;

// процент от PREF_DROP_PRE_REMOVE_BLINK_TIME за который производится ускорение мерцания
const int PREF_DROP_SPEED_UP_PERCENT = 30;

const float PREF_DROP_MAX_SPEED_UP_FACTOR = 2.2f; // максимальный коэффициент ускорения перед уничтожением


//ширина, высота хитбокса дрока (Предпочтительно использование этих параметров при отрисовки дрока)
const float PREF_DROP_HEIGHT = 10.0f;
const float PREF_DROP_WIDTH = 10.0f;
// ================



const int PREF_KEYBOARD_INPUT_BUFFER_SIZE = 4;

const bool PREF_DRAW_HIT_BOX = false;


#endif //COURSE_PAPER_PREFERENCES_H
