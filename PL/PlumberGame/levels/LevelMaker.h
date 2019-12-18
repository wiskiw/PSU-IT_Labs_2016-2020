//
// Created by wiskiw on 27.12.17.
//

#ifndef PLUMBERGAME_LEVELMAKER_H
#define PLUMBERGAME_LEVELMAKER_H

#include <iostream>

// размеры сетки поля
const int S_GAME_GRID_X = 13;
const int S_GAME_GRID_Y = 7;

// структура шаблона карты
struct GameMapTemplate {
    std::string grid[S_GAME_GRID_Y];
};


struct GameFieldItem {
    char type = '*'; // тип
    bool isFilled = false; // заполненая / пустая
    bool locked = false; // запрет повопрота
    bool openSides[4] = {false, false, false, false}; // открытые стороны трубы

    /*
     по часовой
     0 - 0
     1 - 90
     2 - 180
     3 - 270
     */
    int orientation = 0;
};

// структура игрового поля
struct GameLevelField {
    GameFieldItem items[S_GAME_GRID_Y][S_GAME_GRID_X];
};


GameLevelField getLevelField(int n);


#endif //PLUMBERGAME_LEVELMAKER_H
