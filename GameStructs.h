//
// Created by wiskiw on 01.12.17.
//

#ifndef COURSE_PAPER_GAME_STRUCTS_H
#define COURSE_PAPER_GAME_STRUCTS_H

enum GameState {
    GAME_STATE_MENU, GAME_STATE_PLAY, GAME_STATE_PAUSE
};

struct GameFieldStruct {
    GameState gameState = GAME_STATE_MENU;

} gameField;

#endif //COURSE_PAPER_GAME_STRUCTS_H
