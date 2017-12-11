//
// Created by wiskiw on 05.12.17.
//

#include "EnemyConfigurator.h"
#include "../../../gp-elements/gun/list/gun-list.h"
#include "../../../gp-elements/bullet/list/bullet-list.h"

// регистрация типов врагов
const SW_Type ENEMY_TYPES[] = {1, 2};

// дописывать описание врагов внутри
SW_Enemy getEnemy(GameFieldStruct *thisGame, SW_Type enemyType) {
    SW_Enemy newEnemy;
    newEnemy.type = enemyType;
    newEnemy.state = ENEMY_STATE_STAY_FORWARD;


    switch (enemyType) {

        // описание типа врага
        case 1:
            // основные параметры
            newEnemy.score = 10;
            newEnemy.health = 15;
            newEnemy.dropChance = 4;
            newEnemy.spawnChance = 7;
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

        case 2:
            // основные параметры
            newEnemy.score = 7;
            newEnemy.health = 5;
            newEnemy.dropChance = 5;
            newEnemy.spawnChance = 1;
            newEnemy.speed.y = -0.35f;
            newEnemy.speed.x = 1.1f;

            newEnemy.state = random(1, 2) == 1 ? ENEMY_STATE_GOING_LEFT : ENEMY_STATE_GOING_RIGHT;


            // установка типа пушки и пули
            newEnemy.gun = gunsGetHimalayanGun();
            newEnemy.gun.gunSpeed = 50;
            newEnemy.gun.ammorSize = 2;
            newEnemy.gun.bullet = bulletsGetSnappingBullet();

            // сдвиг положения пушки относительно центра
            newEnemy.gunPosValue.z = -1;
            newEnemy.gunPosValue.y = -11;

            // первоначальное положение
            newEnemy.pos.x = random(thisGame->gameBorders.leftBottomX + 50, thisGame->gameBorders.rightTopX - 50);
            newEnemy.pos.y = thisGame->gameBorders.rightTopY;
            newEnemy.pos.z = PREF_ENEMY_Z_POS;

            // размеры хитбокса (отталкиваться от метода отрисовки для типа)
            newEnemy.hitBox.leftBottomX = newEnemy.pos.x - 7;
            newEnemy.hitBox.leftBottomY = newEnemy.pos.y - 7;
            newEnemy.hitBox.rightTopX = newEnemy.pos.x + 7;
            newEnemy.hitBox.rightTopY = newEnemy.pos.y + 7;
            break;
        default:
            newEnemy.state = ENEMY_STATE_UNDEFINED;
    }

    newEnemy.originHealth = newEnemy.health;
    return newEnemy;
}


SW_Enemy getRandomAvailableEnemy(GameFieldStruct *thisGame, const float maxAvailableEnemyHealth) {
    int typesNumber = (sizeof(ENEMY_TYPES) / sizeof(*ENEMY_TYPES));

    int availableEnemiesNumber = 0;
    unsigned int enemyChancesSum = 0;
    SW_Enemy availableEnemies[typesNumber];


    for (int i = 0; i < typesNumber; ++i) {
        SW_Enemy enm = getEnemy(thisGame, ENEMY_TYPES[i]);
        if (enm.health <= maxAvailableEnemyHealth) {
            availableEnemies[availableEnemiesNumber] = enm;
            availableEnemiesNumber++;
            enemyChancesSum += enm.spawnChance;
        }
    }

    if (availableEnemiesNumber != 0) {
        // chance solution by https://stackoverflow.com/questions/1761626/weighted-random-numbers
        int randomChance = random(0, enemyChancesSum);
        for (int i = 0; i < availableEnemiesNumber; i++) {
            SW_Enemy enm = availableEnemies[i];
            if (randomChance < enm.spawnChance) {
                return enm;
            }
            randomChance -= enm.spawnChance;
        }
        // assert(!"should never get here");
    }

    SW_Enemy nullEnemy;
    nullEnemy.state = ENEMY_STATE_UNDEFINED;
    return nullEnemy;
}
