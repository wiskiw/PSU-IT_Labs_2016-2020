//
// Created by wiskiw on 05.12.17.
//

#include "Mover.h"


SW_Pos move1(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {
    SW_Player player = thisGame->player;

    SW_Pos returnPos = {0, 0, 0};


    float PLAYER_UNDER_ENEMY_X_PADDING = 20;
    float MAX_Y_SPEED = thisEnemy->speed.y;
    float MAX_X_SPEED = thisEnemy->speed.x;

    const float ANGRY_DISTANCE = 135;
    const float NEAR_X_BORDER = MAX_X_SPEED + (thisEnemy->hitBox.rightTopX - thisEnemy->hitBox.leftBottomX) * 2;

    const float TOP = thisGame->gameBorders.rightTopY;
    const float BOTTOM = player.hitBox.rightTopY;
    const float RIGHT = thisGame->gameBorders.rightTopX;
    const float LEFT = thisGame->gameBorders.leftBottomX;

    const float OCTA_Y = (TOP - BOTTOM) / 8;

    float xDiff = player.pos.x - thisEnemy->pos.x; // расстояние до игрока от врага по оX (+/-)

    float randomizeXSpeed = random(0.42f, 0.45f);

    if (player.hitBox.leftBottomX > thisEnemy->pos.x + PLAYER_UNDER_ENEMY_X_PADDING ||
        player.hitBox.rightTopX < thisEnemy->pos.x - PLAYER_UNDER_ENEMY_X_PADDING) {
        // если игрок не под врагом
        returnPos.y = MAX_Y_SPEED;
        thisEnemy->state = ENEMY_STATE_STAY_FORWARD;

        float xSpeedK = abs(xDiff) * 0.09f;
        xSpeedK = 1;

        if (abs(xDiff) <= ANGRY_DISTANCE) {
            if (xDiff < 0) {
                returnPos.x= -MAX_X_SPEED * randomizeXSpeed * xSpeedK;
            } else {
                returnPos.x = MAX_X_SPEED * randomizeXSpeed * xSpeedK;
            }
        }
    } else {
        int dirK = 0;
        switch (thisEnemy->state) {
            case (ENEMY_STATE_GOING_LEFT):
                dirK = -1;
                break;
            case ENEMY_STATE_STAY_FORWARD:
                if (random(1, 2) == 1) {
                    thisEnemy->state = ENEMY_STATE_GOING_LEFT;
                } else {
                    thisEnemy->state = ENEMY_STATE_GOING_RIGHT;
                }
                break;
            case ENEMY_STATE_GOING_RIGHT:
                dirK = 1;
                break;
        }
        returnPos.x= MAX_X_SPEED * randomizeXSpeed * dirK;
        returnPos.y= MAX_Y_SPEED * 0.5f;
    }


    // если близко стена
    if (RIGHT - thisEnemy->pos.x <= NEAR_X_BORDER || thisEnemy->pos.x - LEFT <= NEAR_X_BORDER) {
        thisEnemy->state = ENEMY_STATE_STAY_FORWARD;
    }

    return returnPos;

}




// вызов функии перемещения врага по типу(решает куда и как двигаться)
// возвращает SW_Pos, на которые необходимо сдвинуться
SW_Pos moveEnemy(GameFieldStruct *thisGame, SW_Enemy *thisEnemy) {
    switch (thisEnemy->type) {
        case 1:
            return move1(thisGame, thisEnemy);
    }


}