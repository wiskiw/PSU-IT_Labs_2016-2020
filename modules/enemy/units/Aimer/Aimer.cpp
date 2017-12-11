//
// Created by wiskiw on 05.12.17.
//

#include <iostream>
#include "Aimer.h"


bool isTargetLocked1(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {
    // стрелять или нет

    SW_Player player = thisGame->player;


    // стрелять, если игрок движется к врагу и находится в этом диапазоне (враг сверху экрана)
    const float START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_FAR_RANGE = 195 * PREF_SCREEN_CROP_FACTOR;
    const float START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_NEAR_RANGE = 55 * PREF_SCREEN_CROP_FACTOR;

    const float topY = thisGame->gameBorders.rightTopY;
    const float bottomY = player.pos.y;
    const float midY = abs(topY - bottomY);

    float xDiff = player.pos.x - thisEnemy->pos.x; // расстояние до игрока от врага по оX (+/-)
    float yDiff = abs(player.pos.y - thisEnemy->pos.y); // расстояние до игрока от врага по оУ (+)
    float bulletSpeedY = abs(thisEnemy->gun.bullet.speed.y);

    const float SPEED_K = abs(player.speed.x); // Коэффициент горизонтальной скорости игрока
    const float HEIGHT_K = yDiff / 277; // Коэффициент горизонтальной скорости игрока

    const float nearValue = START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_NEAR_RANGE * SPEED_K * HEIGHT_K / bulletSpeedY;
    const float farValue = START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_FAR_RANGE * SPEED_K * HEIGHT_K / bulletSpeedY;

    switch (player.state) {
        case PLAYER_STATE_GOING_LEFT:
            // user going left
            if (xDiff >= nearValue && xDiff <= farValue) {
                return true;
            }
            break;
        case PLAYER_STATE_STAY_FORWARD:
            // user staw forward
            if (player.hitBox.leftBottomX < thisEnemy->pos.x && player.hitBox.rightTopX > thisEnemy->pos.x) {
                // если игрок под врагом
                return true;
            }
            break;
        case PLAYER_STATE_GOING_RIGHT:
            // user going right
            if (xDiff <= -nearValue && xDiff >= -farValue) {
                return true;
            }
            break;

    }
    return false;
}

bool isTargetLocked2(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {
    // стрелять или нет

    SW_Player player = thisGame->player;
    float PLAYER_UNDER_ENEMY_X_PADDING = 20;

    if (player.hitBox.leftBottomX - PLAYER_UNDER_ENEMY_X_PADDING <= thisEnemy->pos.x &&
        player.hitBox.rightTopX + PLAYER_UNDER_ENEMY_X_PADDING >= thisEnemy->pos.x) {
        // если игрок под врагом
        return true;
    }
    return false;
}


// вызов функции ведения стрельбы по типу врага
// функция решает нужно ли стрелять
// возвращает true/false соответственное
bool isTargetLocked(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {
    switch (thisEnemy->type) {
        case 1:
            return isTargetLocked1(thisGame, thisEnemy);
        case 2:
            return isTargetLocked2(thisGame, thisEnemy);
    }
    return false;

}
