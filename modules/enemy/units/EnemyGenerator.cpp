//
// Created by wiskiw on 05.12.17.
//

#include <iostream>
#include "EnemyGenerator.h"
#include "../../../gp-elements/gun/list/gun-list.h"
#include "../../../gp-elements/bullet/list/bullet-list.h"

// регистрация типов врагов
const int ENEMY_TYPES[] = {1};

SW_Type getRandomEnemyType() {
    int typesNumber = (sizeof(ENEMY_TYPES) / sizeof(*ENEMY_TYPES));
    int enemyType = ENEMY_TYPES[random(0, typesNumber)];
    std::cout << "Spawning new enemy; type: " << enemyType << std::endl;
    return enemyType;
}



// дописывать описание врагов внутри
SW_Enemy getEnemy(GameFieldStruct *thisGame) {
    SW_Enemy newEnemy;
    newEnemy.type = getRandomEnemyType();

    switch (newEnemy.type) {

        // описание типа врага
        case 1:
            // основные параметры
            newEnemy.health = 15;
            newEnemy.speed.y = -0.4f;
            newEnemy.speed.x = 1.1f;

            // установка типа пушки и пули
            newEnemy.gun = gunsGetHimalayanGun();
            newEnemy.gun.bullet = bulletsGetDiamondbackBullet();

            // сдвиг положения пушки относительно центра
            newEnemy.gunPosValue.z = -1;
            newEnemy.gunPosValue.y = -11;

            // первоначальное положение
            newEnemy.pos.x = random(thisGame->gameBorders.leftBottomX + 50, thisGame->gameBorders.rightTopX - 50);
            newEnemy.pos.y = thisGame->gameBorders.rightTopY;
            newEnemy.pos.z = PREF_ENEMY_Z_POS;

            // размеры хитбокса (отталкиваться от метода отрисовки для типа)
            newEnemy.hitBox.leftBottomX = newEnemy.pos.x - 10;
            newEnemy.hitBox.leftBottomY = newEnemy.pos.y - 10;
            newEnemy.hitBox.rightTopX = newEnemy.pos.x + 10;
            newEnemy.hitBox.rightTopY = newEnemy.pos.y + 10;
            break;
    }

    return newEnemy;
}
