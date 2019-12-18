//
// Created by wiskiw *n 27.12.17.
//

#include "LevelMaker.h"

/*
 X
 T
 L
 I
 S - откуда
 W - куда
 * - пусто
 Большие символы - фиксированные
 Маленькие - можно двигать
 */

// создание игрового поля по шаблону карты
GameLevelField buildLevelField(GameMapTemplate mapTemplate) {
    GameLevelField gameLevelField;
    for (int y = 0; y < S_GAME_GRID_Y; ++y) {
        for (int x = 0; x < S_GAME_GRID_X; ++x) {
            GameFieldItem gameFieldItem;
            gameFieldItem.type = mapTemplate.grid[y][x];
            if (!isupper(gameFieldItem.type)) {
                gameFieldItem.locked = true;
            }
            switch (toupper(gameFieldItem.type)) {
                case 'S':
                    gameFieldItem.openSides[1] = true;
                    break;
                case 'W':
                    gameFieldItem.openSides[3] = true;
                    break;
                case 'X':
                    gameFieldItem.locked = true;
                    gameFieldItem.openSides[0] = true;
                    gameFieldItem.openSides[1] = true;
                    gameFieldItem.openSides[2] = true;
                    gameFieldItem.openSides[3] = true;
                    break;
                case 'T':
                    gameFieldItem.openSides[3] = true;
                    gameFieldItem.openSides[1] = true;
                    gameFieldItem.openSides[0] = true;
                    break;
                case 'L':
                    gameFieldItem.openSides[0] = true;
                    gameFieldItem.openSides[1] = true;
                    break;
                case 'I':
                    gameFieldItem.openSides[3] = true;
                    gameFieldItem.openSides[1] = true;
                    break;
            }
            gameLevelField.items[y][x] = gameFieldItem;
        }
    }
    return gameLevelField;
}

// создание уровня
GameLevelField getLevelField(int n) {
    GameMapTemplate mapTemplate;

    switch (n) {
        case 1:

            mapTemplate.grid[0] = "sIITIIIIIIIIL";
            mapTemplate.grid[1] = "***I********I";
            mapTemplate.grid[2] = "***I*LIIIIL*I";
            mapTemplate.grid[3] = "***I*LIITITIL";
            mapTemplate.grid[4] = "***I***LTL***";
            mapTemplate.grid[5] = "***LIIIL*LIIw";
            mapTemplate.grid[6] = "*************";

            break;
        case 2:

            mapTemplate.grid[0] = "*************";
            mapTemplate.grid[1] = "*LIL***LIL***";
            mapTemplate.grid[2] = "*I*I***I*I***";
            mapTemplate.grid[3] = "sTTTTIITTTTL*";
            mapTemplate.grid[4] = "**I*I***I*II*";
            mapTemplate.grid[5] = "**LIL***LITTw";
            mapTemplate.grid[6] = "*************";

            break;
        case 3:
            mapTemplate.grid[0] = "sIITIIIIIIIIL";
            mapTemplate.grid[1] = "***I********I";
            mapTemplate.grid[2] = "*LIT*LIITIL*I";
            mapTemplate.grid[3] = "LL*I*LITXTTIL";
            mapTemplate.grid[4] = "I**I***LTL***";
            mapTemplate.grid[5] = "LIITIIIL*LIIw";
            mapTemplate.grid[6] = "*************";

            break;
    }

    return buildLevelField(mapTemplate);
}




