//
// Created by wiskiw on 06.12.17.
//

#include <iostream>
#include <assert.h>
#include "../../../utils/Utils.h"

// регистрация типов дрока генерируемые миром
const SW_Type ENEMY_DROP_TYPES[] = {1, 2};

// регистрация типов дрока генерируемые после смерти врагов
const SW_Type WORLD_DROP_TYPES[] = {1, 2};


SW_Drop getDrop(GameFieldStruct *thisGame, SW_Type dropType) {
    SW_Drop newDrop;
    newDrop.type = dropType;
    newDrop.state = DROP_STATE_NORMAL;

    switch (dropType) {

        // описание свойств дропа
        case 1:
            // health drop
            // основные параметры
            newDrop.timeToLive = 250;
            newDrop.chance = 3;


            // позиция спавна дропа: актуальна только при спавне дропа миров
            newDrop.pos.y = thisGame->gameBorders.rightTopY;
            newDrop.pos.x = (thisGame->gameBorders.rightTopX - thisGame->gameBorders.leftBottomX) / 2 +
                            thisGame->gameBorders.leftBottomX;
            break;
        case 2:
            // kill enemies drop
            // основные параметры
            newDrop.timeToLive = 500;
            newDrop.chance = 5;

            // позиция спавна дропа: актуальна только при спавне дропа миров
            newDrop.pos.y = thisGame->gameBorders.rightTopY;
            newDrop.pos.x = (thisGame->gameBorders.rightTopX - thisGame->gameBorders.leftBottomX) / 2 +
                            thisGame->gameBorders.leftBottomX;
            break;
        default:
            newDrop.state = DROP_STATE_UNDEFINED;
    }
    return newDrop;
}

SW_Drop getRandomDrop(GameFieldStruct *thisGame, const SW_Type *typesArr, int arrSize) {
    // chance solution: https://stackoverflow.com/questions/1761626/weighted-random-numbers

    int chanceWeightSum = 0;
    SW_Drop dropArray[arrSize];
    for (int j = 0; j < arrSize; ++j) {
        SW_Drop drop = getDrop(thisGame, typesArr[j]);
        chanceWeightSum += drop.chance;
        dropArray[j] = drop;
    }


    int rnd = random(0, chanceWeightSum);
    for (int i = 0; i < arrSize; i++) {
        SW_Drop drop = dropArray[i];
        if (rnd < drop.chance)
            return drop;
        rnd -= drop.chance;
    }


    SW_Drop nullDrop;
    nullDrop.state = DROP_STATE_UNDEFINED;
    return nullDrop;
    //assert(!"should never get here");
}

SW_Drop getRandomEnemyDrop(GameFieldStruct *thisGame) {
    int typesNumber = (sizeof(ENEMY_DROP_TYPES) / sizeof(*ENEMY_DROP_TYPES));
    return getRandomDrop(thisGame, ENEMY_DROP_TYPES, typesNumber);
}

SW_Drop getRandomWorldDrop(GameFieldStruct *thisGame) {
    int typesNumber = (sizeof(WORLD_DROP_TYPES) / sizeof(*WORLD_DROP_TYPES));
    return getRandomDrop(thisGame, WORLD_DROP_TYPES, typesNumber);
}
