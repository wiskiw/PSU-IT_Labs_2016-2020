//
// Created by wiskiw on 02.12.17.
//

#ifndef COURSE_PAPER_PREFERENCES_H
#define COURSE_PAPER_PREFERENCES_H


const float PREF_SCREEN_CROP_FACTOR = 1.7f;

const int PREF_BULLET_Z_POS = 2;
const int PREF_ENEMY_Z_POS = 3;
const float PREF_DROP_Z_POS = 1.9f;

const float PREF_PLAYER_DEFAULT_HEALTH = 100;

const int PREF_STARS_NUMBER = 16;
const int PREF_BULLET_BUFFER_SIZE = 30;
const int PREF_ENEMY_BUFFER_SIZE = 12;


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
