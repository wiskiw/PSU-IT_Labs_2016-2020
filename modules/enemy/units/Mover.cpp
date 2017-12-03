//
// Created by wiskiw on 03.12.17.
//

#include "../../../utils/Utils.h"
#include "Mover.h"


void move1(GameFieldStruct *thisGame, SW_Enemy *enemy) {
    // решает куда и как двигаться
    SW_Player player = thisGame->player;

    float MAX_Y_SPEED = enemy->speed.y;
    float MAX_X_SPEED = enemy->speed.x;

    const float ANGRY_DISTANCE = 135;
    const float NEAR_X_BORDER = MAX_X_SPEED + (enemy->hitBox.rightTopX - enemy->hitBox.leftBottomX) * 2;

    const float TOP = thisGame->borders.rightTopY;
    const float BOTTOM = player.hitBox.rightTopY;
    const float MID_Y = BOTTOM + (TOP - BOTTOM) / 2;
    const float RIGHT = thisGame->borders.rightTopX;
    const float LEFT = thisGame->borders.leftBottomX;

    const int OCTA_Y = (TOP - BOTTOM) / 8;

    float xDiff = player.pos.x - enemy->pos.x; // расстояние до игрока от врага по оX (+/-)



    if (player.hitBox.leftBottomX > enemy->pos.x || player.hitBox.rightTopX < enemy->pos.x) {
        // если игрок не под врагом
        enemy->pos.y += MAX_Y_SPEED;
        enemy->state = 2;

        float xSpeedK = abs(xDiff) * 0.09f;
        xSpeedK = 1;

        if (abs(xDiff) <= ANGRY_DISTANCE) {
            if (xDiff < 0) {
                enemy->pos.x += MAX_X_SPEED * 0.5f * -1 * xSpeedK;
            } else {
                enemy->pos.x += MAX_X_SPEED * 0.5f * xSpeedK;
            }
        }
    } else {
        int dirK = 0;
        switch (enemy->state) {
            case 1:
                dirK = -1;
                break;
            case 2:
                dirK = random(1, 2) == 1 ? -1 : 1;
                enemy->state = 2 + dirK;
                break;
            case 3:
                dirK = 1;
                break;
        }
        enemy->pos.x += MAX_X_SPEED * 0.5f * dirK;
        enemy->pos.y += MAX_Y_SPEED * 0.5f;
    }


    // если близко стена
    if (RIGHT - enemy->pos.x <= NEAR_X_BORDER || enemy->pos.x - LEFT <= NEAR_X_BORDER) {
        enemy->state = 2;
    }


}


void moveEnemy(GameFieldStruct *thisGame, SW_Enemy *enemy) {

    switch (enemy->type) {
        case 1:
            move1(thisGame, enemy);

    }


}
