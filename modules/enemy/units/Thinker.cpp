//
// Created by wiskiw on 03.12.17.
//

#include "Thinker.h"


bool shouldShoot1(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    // стрелять или нет

    SW_Player player = thisGame->player;


    // стрелять, если игрок движется к врагу и находится в этом диапазоне
    const int START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_FAR_RANGE = 200;
    const int START_SHOOTING_IF_PLAYER_GO_TO_ENEMY_NEAR_RANGE = 15;

    const float topY = thisGame->borders.rightTopY;
    const float bottomY = player.pos.y;
    const float midY = abs(topY - bottomY);

    int xDiff = player.pos.x - enemy->pos.x; // расстояние до игрока от врага по оX (+/-)
    int yDiff = abs(player.pos.y - enemy->pos.y); // расстояние до игрока от врага по оУ (+)
    float bulletSpeedY = abs(enemy->gun.bullet.speed.y);

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
            if (player.hitBox.leftBottomX < enemy->pos.x && player.hitBox.rightTopX > enemy->pos.x) {
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


bool shouldShoot(GameFieldStruct *thisGame, SW_Enemy *enemy) {

    switch (enemy->type) {
        case 1:
            return shouldShoot1(thisGame, enemy);

    }

}