//
// Created by wiskiw on 06.12.17.
//

#include <iostream>
#include "../../../utils/Utils.h"

// регистрация типов дрока генерируемые миром
const int ENEMY_DROP_TYPES[] = {1};

// регистрация типов дрока генерируемые после смерти врагов
const int WORLD_DROP_TYPES[] = {1};


SW_Type getRandomWorldDropType() {
    int typesNumber = (sizeof(ENEMY_DROP_TYPES) / sizeof(*ENEMY_DROP_TYPES));
    int dropType = ENEMY_DROP_TYPES[random(0, typesNumber)];
    std::cout << "Spawning new enemy drop; type: " << dropType << std::endl;
    return dropType;
}

SW_Type getRandomEnemyDropType() {
    int typesNumber = (sizeof(WORLD_DROP_TYPES) / sizeof(*WORLD_DROP_TYPES));
    int dropType = WORLD_DROP_TYPES[random(0, typesNumber)];
    std::cout << "Spawning new world drop; type: " << dropType << std::endl;
    return dropType;
}

SW_Drop getDrop(GameFieldStruct *thisGame, SW_Type dropType) {
    SW_Drop newDrop;
    newDrop.type = dropType;
    newDrop.state = DROP_STATE_NORMAL;

    switch (dropType) {

        // описание свойств дропа
        case 1:
            // основные параметры
            newDrop.timeToLive = 500;


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

SW_Drop getRandomDrop(GameFieldStruct *thisGame);