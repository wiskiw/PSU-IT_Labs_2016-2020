//
// Created by wiskiw on 05.12.17.
//

#include "Aimer.h"


bool isTargetLocked1(GameFieldStruct *thisGame, SW_Enemy *thisEnemy){
    // стрелять или нет

    SW_Player player = thisGame->player;


    // стрелять, если игрок движется к врагу и находится в этом диапазоне
    const int START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_FAR_RANGE = 200;
    const int START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_NEAR_RANGE = 15;

    const float topY = thisGame->gameBorders.rightTopY;
    const float bottomY = player.pos.y;
    const float midY = abs(topY - bottomY);

    float xDiff = player.pos.x - thisEnemy->pos.x; // расстояние до игрока от врага по оX (+/-)
    float yDiff = abs(player.pos.y - thisEnemy->pos.y); // расстояние до игрока от врага по оУ (+)
    float bulletSpeedY = abs(thisEnemy->gun.bullet.speed.y);

    const float SPEED_K = abs(player.speed.x / 1.67f); // Коэффициент горизонтальной скорости игрока

    switch (player.state) {
        case 1:
            // user going left
            if (xDiff >= START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_NEAR_RANGE * SPEED_K / bulletSpeedY &&
                xDiff <= START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_FAR_RANGE * SPEED_K / bulletSpeedY) {
                return true;
            }
            break;
        case 2:
            // user staw forward
            if (player.hitBox.leftBottomX < thisEnemy->pos.x && player.hitBox.rightTopX > thisEnemy->pos.x) {
                // если игрок под врагом
                return true;
            }
            break;
        case 3:
            // user going right
            if (xDiff <= -START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_NEAR_RANGE * SPEED_K / bulletSpeedY &&
                xDiff >= -START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_FAR_RANGE * SPEED_K / bulletSpeedY) {
                return true;
            }
            break;

    }
    return false;
}

// вызов функции ведения стрельбы по типу врага
// функция решает нужно ли стрелять
// возвращает true/false соответственное
bool isTargetLocked(GameFieldStruct *thisGame, SW_Enemy *thisEnemy){
    switch (thisEnemy->type){
        case 1:
            return isTargetLocked1(thisGame, thisEnemy);
    }
    return false;

}
